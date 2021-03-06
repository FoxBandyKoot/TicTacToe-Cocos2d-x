#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace ui;

class MainMenuScene : public cocos2d::Layer{

public:

	// FUNC
	static cocos2d::Scene* createScene();

	virtual bool init();

	void SwitchToGameScene(float dt);

	CREATE_FUNC(MainMenuScene)

private:
	void clickEvent(Ref* sender, Widget::TouchEventType touchEventType);
};