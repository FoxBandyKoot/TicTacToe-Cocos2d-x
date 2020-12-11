#include "UI.h"
#include "Definitions.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include <SonarFrameworks.h>

/*
constructor 
*/
UI::UI(cocos2d::Layer *layer, int &gameState)
{
    this->gameState = &gameState;

    Size const screenSize = Director::getInstance()->getVisibleSize();
    Vec2 const origin = Director::getInstance()->getVisibleOrigin();

    // Bouton pause
    pauseItem = MenuItemSprite::create(Sprite::create(PAUSE_BUTTON), Sprite::create(PAUSE_BUTTON_PRESSED), Sprite::create(PAUSE_BUTTON), CC_CALLBACK_1(UI::PauseGame, this));
    pauseItem->setPosition(Vec2(
        screenSize.width - (pauseItem->getContentSize().width / 2) + origin.x,
        screenSize.height - (pauseItem->getContentSize().height / 2) + origin.y));
    
    // Menu seulement pour le bouton pause (pas activée)
    Menu* menuButtons = Menu::create(pauseItem, NULL);
    menuButtons->setPosition(Vec2::ZERO);
    layer->addChild(menuButtons);

    // Background du menu pour le bouton pause (pas activée)
    pauseBackground = Sprite::create(GAME_OVER_BACKGROUND);
    pauseBackground->setPosition(SonarCocosHelper::UI::GetScreenCenter());
    pauseBackground->setOpacity(0);
    layer->addChild(pauseBackground);

    // Menu pause activée
    //MenuItemImage *overlayPauseWindowItem = MenuItemImage::create(GAME_OVER_BACKGROUND, GAME_OVER_BACKGROUND, GAME_OVER_BACKGROUND, NULL);

    MenuItemSprite* const resumeItem = MenuItemSprite::create(Sprite::create(RESUME_BUTTON), Sprite::create(RESUME_BUTTON_PRESSED), Sprite::create(RESUME_BUTTON), CC_CALLBACK_1(UI::PauseGame, this));
    resumeItem->setPosition(Vec2(resumeItem->getPositionX() + 125, resumeItem->getPositionY()));
   
    MenuItemSprite* const mainMenuItem = MenuItemSprite::create(Sprite::create(HOME_BUTTON), Sprite::create(HOME_BUTTON_PRESSED), Sprite::create(HOME_BUTTON), CC_CALLBACK_1(UI::GoToMainMenu, this));
    mainMenuItem->setPosition(Vec2(mainMenuItem->getPositionX() - 125, mainMenuItem->getPositionY()));

    pauseMenu = Menu::create(resumeItem, mainMenuItem, NULL);
    pauseMenu->setPosition(Vec2(SonarCocosHelper::UI::GetScreenCenter().x, SonarCocosHelper::UI::GetScreenCenter().y + screenSize.height));
    layer->addChild(pauseMenu);
}

/*
game over
*/
void UI::ShowGameOver(cocos2d::Layer* layer)
{

    // Create the background
    Sprite* const background = Sprite::create(GAME_OVER_BACKGROUND);
    background->setPosition(SonarCocosHelper::UI::GetScreenCenter());
    background->setOpacity(0);
    layer->addChild(background);
    
    // Create background apparition animation
    background->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 3.5), FadeIn::create(GAME_OVER_BACKGROUND_FADE_IN_TIME), NULL));

    // Specify items for the menu
    MenuItemImage* overlayWindowItem = MenuItemImage::create(GAME_OVER_WINDOW, GAME_OVER_WINDOW, GAME_OVER_WINDOW, NULL);

    MenuItemSprite* const retryItem = MenuItemSprite::create(Sprite::create(RETRY_BUTTON), Sprite::create(RETRY_BUTTON_PRESSED), Sprite::create(RETRY_BUTTON_PRESSED), CC_CALLBACK_1(UI::Retry, this));
    retryItem->setPosition(Vec2(retryItem->getPositionX() + 125, retryItem->getPositionY()));

    MenuItemSprite* const mainMenuItem = MenuItemSprite::create(Sprite::create(HOME_BUTTON), Sprite::create(HOME_BUTTON_PRESSED), Sprite::create(HOME_BUTTON_PRESSED), CC_CALLBACK_1(UI::GoToMainMenu, this));
    mainMenuItem->setPosition(Vec2(mainMenuItem->getPositionX() - 125, mainMenuItem->getPositionY()));

    // Create menu with these items in this particular order
    Menu *const menu = Menu::create(overlayWindowItem, retryItem, mainMenuItem, NULL);
    Size const screenSize = Director::getInstance()->getVisibleSize();
    menu->setPosition(Vec2(SonarCocosHelper::UI::GetScreenCenter().x, SonarCocosHelper::UI::GetScreenCenter().y + screenSize.height));
    layer->addChild(menu);

    // Create fall menu animation
    EaseBounceOut* menuActionEasing = EaseBounceOut::create(MoveTo::create(MENU_MOVE_BOUNCE_DURATION, SonarCocosHelper::UI::GetScreenCenter()));
    Sequence* menuShowSeq = Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 3.5), menuActionEasing, NULL);
    menu->runAction(menuShowSeq);
}

/*
retry
*/
void UI::Retry(cocos2d::Ref* pSender)
{
    Scene* scene = GameScene::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);

    Director::getInstance()->replaceScene(transition);
}

/*
back to main menu
*/
void UI::GoToMainMenu(cocos2d::Ref *pSender)
{
    Scene* scene = MainMenuScene::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);

    Director::getInstance()->replaceScene(transition);
}

/*
set pause/ take off pause
*/
void UI::PauseGame(cocos2d::Ref *pSender)
{
    Size const screenSize = Director::getInstance()->getVisibleSize();

    if (STATE_PLAYING == *gameState)
    {
        *gameState = STATE_PAUSED;

        pauseItem->setEnabled(false);
        pauseItem->setVisible(false);

        // make fall background
        pauseBackground->runAction(FadeIn::create(PAUSE_BACKGROUND_FADE_TIME));

        // make fall buttons
        EaseBounceOut* menuActionEasing = EaseBounceOut::create(
            MoveTo::create(
                MENU_MOVE_BOUNCE_DURATION, 
                SonarCocosHelper::UI::GetScreenCenter()));
                
        pauseMenu->runAction(menuActionEasing);
    } 
    else if (STATE_PAUSED == *gameState)
    {
        *gameState = STATE_PLAYING;
        
        pauseItem->setEnabled(true);
        pauseItem->setVisible(true);

        // make fly background
        pauseBackground->runAction(FadeOut::create(PAUSE_BACKGROUND_FADE_TIME));

        // make fly buttons
        EaseBounceOut* menuActionEasing = EaseBounceOut::create(
            MoveTo::create(
                MENU_MOVE_BOUNCE_DURATION, 
                Vec2(SonarCocosHelper::UI::GetScreenCenter().x, SonarCocosHelper::UI::GetScreenCenter().y + screenSize.height)));

        pauseMenu->runAction(menuActionEasing);
    }
}