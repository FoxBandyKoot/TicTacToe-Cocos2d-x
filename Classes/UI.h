#pragma once

#include "cocos2d.h"

class UI
{
public:
    UI(cocos2d::Layer *layer, int &gameState);
    void ShowGameOver(cocos2d::Layer* layer);

private:
    void Retry(cocos2d::Ref* pSender);
    void GoToMainMenu(cocos2d::Ref* pSender);
    void PauseGame(cocos2d::Ref* pSender);

    int* gameState;

    cocos2d::Menu *pauseMenu;
    cocos2d::Sprite * pauseBackground;
    cocos2d::MenuItemSprite* pauseItem;
};
