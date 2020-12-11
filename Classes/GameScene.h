#pragma once

#include "cocos2d.h"
#include "AI.h"
#include "UI.h"


class GameScene : public cocos2d::Layer
{

public:
	
	// ATTR
	static cocos2d::Scene* createScene();

	// FUNC
	virtual bool init();

	CREATE_FUNC(GameScene)

private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void InitGridRects();
	void InitGridPieces();

	void CheckAndPlacePiece(cocos2d::Touch *touch);
	void CheckWin(int x, int y);
	void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);
	void SetWinningPieces(int a, int x, int y);

	cocos2d::Sprite* winningPieces[3];
	cocos2d::Sprite *gridSprite;
	cocos2d::Rect gridSpaces[3][3];
	cocos2d::Sprite* gridPieces[3][3];
	cocos2d::__String winningPieceStr;

	int gridArray[3][3];
	int turn;
	int gameState;

	AI* ai;
	UI* ui;

};