#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include <SonarFrameworks.h>

USING_NS_CC;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);

    return scene;
}

bool SplashScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    SonarCocosHelper::UI::AddCentredBackground(GRID, this);
    scheduleOnce(schedule_selector(SplashScene::SwitchToMainMenu), 1.5); // Display time spash screen

    return true;
}

void SplashScene::SwitchToMainMenu(float dt)
{
        Scene* scene = MainMenuScene::createScene();
        TransitionFade* transition = TransitionFade::create(dt, scene);// create(timer, new scene)
        Director::getInstance()->replaceScene(transition);
}
