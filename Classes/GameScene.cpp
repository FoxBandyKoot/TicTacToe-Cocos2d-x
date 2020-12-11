#include "GameScene.h"
#include "Definitions.h"
#include <iostream>
#include "UI.h"
#include <SonarFrameworks.h>

USING_NS_CC;

Scene* GameScene::createScene() {

	auto scene = Scene::create();
	auto layer = GameScene::create();

	scene->addChild(layer);
	return scene;
}

bool GameScene::init() {
	if (!Layer::init()) {
		return false;
	}

	SonarCocosHelper::UI::AddCentredBackground(GRID, this);
	gridSprite = Sprite::create(GRID);
	gridSprite->setPosition(SonarCocosHelper::UI::GetScreenCenter());
	this->addChild(gridSprite);

	InitGridRects();
	InitGridPieces();
	
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			gridArray[x][y] = PIECE_EMPTY;
		}
	}

	turn = PIECE_PLAYER;

	ai = new AI(turn);

	ui = new UI(this, gameState);

	gameState = STATE_PLAYING;

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

/*
interactions
*/
bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return true; } // true if the function wants to swallow the touch}

void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){}

void GameScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event){}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (STATE_PLAYING == gameState) {
		CheckAndPlacePiece(touch);
	}
}

/*
create the grid : set the differents clickables cases
*/
void GameScene::InitGridRects() {
	/**************************************************************************/
									/*first row*/
	/**************************************************************************/

	gridSpaces[0][0] = Rect(
		gridSprite->getBoundingBox().getMinX(),
		gridSprite->getBoundingBox().getMinY(),
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3);

	gridSpaces[1][0] = Rect(
		gridSprite->getBoundingBox().getMinX() + gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().getMinY(),
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3);

	gridSpaces[2][0] = Rect(
		gridSprite->getBoundingBox().getMinX() + (gridSprite->getBoundingBox().size.width / 3) * 2,
		gridSprite->getBoundingBox().getMinY(),
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3);
	
	/**************************************************************************/
									/*second row*/
	/**************************************************************************/
	gridSpaces[0][1] = Rect(
		gridSprite->getBoundingBox().getMinX(),
		gridSprite->getBoundingBox().getMinY() + gridSprite->getBoundingBox().size.height / 3,
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3);

	gridSpaces[1][1] = Rect(
		gridSprite->getBoundingBox().getMinX() + gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().getMinY() + gridSprite->getBoundingBox().size.height / 3,
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3);

	gridSpaces[2][1] = Rect(
		gridSprite->getBoundingBox().getMinX() + (gridSprite->getBoundingBox().size.width / 3) * 2,
		gridSprite->getBoundingBox().getMinY() + gridSprite->getBoundingBox().size.height / 3,
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3);

	/**************************************************************************/
								/*third row*/
	/**************************************************************************/
	gridSpaces[0][2] = Rect(
		gridSprite->getBoundingBox().getMinX(),
		gridSprite->getBoundingBox().getMinY() + (gridSprite->getBoundingBox().size.height / 3) * 2,
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3);

	gridSpaces[1][2] = Rect(
		gridSprite->getBoundingBox().getMinX() + gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().getMinY() + (gridSprite->getBoundingBox().size.height / 3) * 2,
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3);

	gridSpaces[2][2] = Rect(
		gridSprite->getBoundingBox().getMinX() + (gridSprite->getBoundingBox().size.width / 3) * 2,
		gridSprite->getBoundingBox().getMinY() + (gridSprite->getBoundingBox().size.height / 3) * 2,
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3);
}


void GameScene::InitGridPieces() {

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			gridPieces[x][y] = Sprite::create(PIECE_X);
			
			gridPieces[x][y]->setPosition(Vec2(
				gridSprite->getPositionX() + gridPieces[x][y]->getContentSize().width  * (x - 1),
				gridSprite->getPositionY() + gridPieces[x][y]->getContentSize().height * (y - 1)
			));

			gridPieces[x][y]->setVisible(false);
			gridPieces[x][y]->setOpacity(0);
			this->addChild(gridPieces[x][y]);
		}
	}
}

/*
when click on case, place a piece
*/
void GameScene::CheckAndPlacePiece(cocos2d::Touch* touch) {
	Rect const rect1 = gridSprite->getBoundingBox();
	Point const touchPoint = touch->getLocation();

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			
			if (gridSpaces[x][y].containsPoint(touchPoint)) {
				if (PIECE_EMPTY == gridArray[x][y]) {

					gameState = STATE_PLACING_PIECE;
					gridArray[x][y] = turn;
					if (PIECE_X_ID == turn) {
						gridPieces[x][y]->setTexture(PIECE_X);
					}
					else {
						gridPieces[x][y]->setTexture(PIECE_O);
					}

					gridPieces[x][y]->setVisible(true);
					gridPieces[x][y]->runAction(Sequence::create(
						FadeIn::create(PIECE_FADE_IN_TIME), 
						CallFunc::create(std::bind(&GameScene::CheckWin, this, x, y)), NULL));
				}
			}
		}
	}
}

/*
test the 8 combinations to win
change turn player
check if game is a draw
*/
void GameScene::CheckWin(int x, int y) {
	
	Check3PiecesForMatch(0, 0, 1, 0, 2, 0, PIECE_PLAYER);
	Check3PiecesForMatch(0, 1, 1, 1, 2, 1, PIECE_PLAYER);
	Check3PiecesForMatch(0, 2, 1, 2, 2, 2, PIECE_PLAYER);
	Check3PiecesForMatch(0, 0, 0, 1, 0, 2, PIECE_PLAYER);
	Check3PiecesForMatch(1, 0, 1, 1, 1, 2, PIECE_PLAYER);
	Check3PiecesForMatch(2, 0, 2, 1, 2, 2, PIECE_PLAYER);
	Check3PiecesForMatch(0, 0, 1, 1, 2, 2, PIECE_PLAYER);
	Check3PiecesForMatch(0, 2, 1, 1, 2, 0, PIECE_PLAYER);

	// for 2 players on the same screen
	//if (PIECE_X_ID == turn) {
	//	turn = PIECE_O_ID;
	//}
	//else {
	//	turn = PIECE_X_ID;
	//}

	if (STATE_WON != gameState)
	{
		gameState = STATE_AI_PLAYING;
		ai->PlacePiece(&gridArray, gridPieces, &gameState);

		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, PIECE_AI);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, PIECE_AI);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, PIECE_AI);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, PIECE_AI);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, PIECE_AI);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, PIECE_AI);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, PIECE_AI);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, PIECE_AI);
	}

	int emptyNum = 9;

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (PIECE_EMPTY != gridArray[x][y])
			{
				emptyNum--;
			}
		}
	}

	// check if the game is a draw
	if (0 == emptyNum)
	{
		gameState = STATE_DRAW;
	}

	if (gameState == STATE_WON || gameState == STATE_LOSE || gameState == STATE_DRAW) {
		ui->ShowGameOver(this);
	}

	std::cout << gameState << std::endl;
}

/*
check if win
x : x-axis
y : y-axis
*/
void GameScene::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {
	
	/**************************************************************************/
							/*IF TRUE => WIN */
	/**************************************************************************/
	
	if (pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3]) {
		if (PIECE_O_ID == pieceToCheck) {
			winningPieceStr = PIECE_O_WIN;
		}
		else {
			winningPieceStr = PIECE_X_WIN;
		}

		SetWinningPieces(0, x1, y1);
		SetWinningPieces(1, x2, y2);
		SetWinningPieces(2, x3, y3);

		winningPieces[0]->runAction(FadeIn::create(PIECE_FADE_IN_TIME));
		winningPieces[1]->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 0.5), FadeIn::create(PIECE_FADE_IN_TIME), NULL));
		winningPieces[2]->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 1.5), FadeIn::create(PIECE_FADE_IN_TIME), NULL));

		if (PIECE_PLAYER == pieceToCheck)
		{
			gameState = STATE_WON;
		}
		else
		{
			gameState = STATE_LOSE;
		}
	}
}

/*
replace pieces by winning pieces
*/
void GameScene::SetWinningPieces(int a, int x, int y) {
	winningPieces[a] = Sprite::create(winningPieceStr.getCString());
	winningPieces[a]->setPosition(gridPieces[x][y]->getPosition());
	winningPieces[a]->setOpacity(0);
	this->addChild(winningPieces[a]);
}