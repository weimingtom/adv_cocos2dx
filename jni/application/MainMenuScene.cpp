#include "MainMenuScene.h"
#include "GameScene.h"
#include "SettingScene.h"
//#include "SimpleAudioEngine.h"
#include "GameSystem.h"
#include "SaveScene.h"
#include "LoadScene.h"

USING_NS_CC;

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

cocos2d::CCScene* MainMenu::createScene()
{
	cocos2d::CCScene *scene = cocos2d::CCScene::create();

	cocos2d::CCLayer *layer = MainMenu::create();

	scene->addChild(layer);

	return scene;
}

bool MainMenu::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//初始化系统信息
	GameSystem::getInstance();

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    //设定背景层
	cocos2d::CCLayerColor *backgroundLayer = cocos2d::CCLayerColor::create(ccc4(0, 0, 0, 255));
	cocos2d::CCSprite *backgroundEffect1 = cocos2d::CCSprite::create("/ui/backgroundEffect/fullscreen_smoke.png");
	cocos2d::CCSprite *backgroundEffect2 = cocos2d::CCSprite::create("/ui/backgroundEffect/fullscreen_smoke_2.png");
	backgroundEffect1->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundEffect2->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//logo
	cocos2d::CCSprite *gameTitle = cocos2d::CCSprite::create("/ui/game_title.png");
	gameTitle->setPosition(ccp(433, 358));

	//菜单按钮
	cocos2d::CCMenuItemImage *buttonNew = cocos2d::CCMenuItemImage::create(
		"/ui/Title/button_new.png", 
		"/ui/Title/button_new_down.png", this, 
		menu_selector(MainMenu::newgame));
	buttonNew->setPosition(ccp(1114, visibleSize.height - 243));

	cocos2d::CCMenuItemImage *buttonLoad = cocos2d::CCMenuItemImage::create(
		"/ui/Title/button_load.png", 
		"/ui/Title/button_load_down.png", this, 
		menu_selector(MainMenu::load));
	buttonLoad->setPosition(ccp(1114, visibleSize.height - 293));

	cocos2d::CCMenuItemImage *buttonCG = cocos2d::CCMenuItemImage::create(
		"/ui/Title/button_cg.png", 
		"/ui/Title/button_cg_down.png");
	buttonCG->setPosition(ccp(1114, visibleSize.height - 343));

	cocos2d::CCMenuItemImage *buttonConfig = cocos2d::CCMenuItemImage::create(
		"/ui/Title/button_config.png", 
		"/ui/Title/button_config_down.png", this, 
		menu_selector(MainMenu::config));
	buttonConfig->setPosition(ccp(1114, visibleSize.height - 393));

	cocos2d::CCMenuItemImage *buttonExit = cocos2d::CCMenuItemImage::create(
		"/ui/Title/button_exit.png", 
		"/ui/Title/button_exit_down.png", this,
		menu_selector(MainMenu::menuExit));
	buttonExit->setPosition(ccp(1114, visibleSize.height - 443)); 

	cocos2d::CCMenu *menu = cocos2d::CCMenu::create(
		buttonNew, buttonLoad, buttonCG, buttonConfig, buttonExit, NULL);
	menu->setPosition(ccp(0, 0));



	backgroundLayer->addChild(backgroundEffect1, 0);
	backgroundLayer->addChild(backgroundEffect2, 1);
	backgroundLayer->addChild(gameTitle, 3);

	backgroundLayer->addChild(menu, 4);
	this->addChild(backgroundLayer, 0);

	return true;

}

void MainMenu::test()
{
	CCLOG("Bingo!");
}

void MainMenu::menuExit(cocos2d::CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	cocos2d::CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainMenu::newgame(cocos2d::CCObject *)
{
	GameSystem::getInstance()->setGameScene(GameScene::createScene());
	cocos2d::CCScene *scene = GameSystem::getInstance()->getGameScene();
	cocos2d::CCDirector::sharedDirector()->replaceScene(scene);
}

void MainMenu::config(cocos2d::CCObject *)
{
	cocos2d::CCDirector::sharedDirector()->pushScene(cocos2d::CCDirector::sharedDirector()->getRunningScene());
	cocos2d::CCDirector::sharedDirector()->replaceScene(SettingScene::createScene());
}

void MainMenu::load(cocos2d::CCObject *)
{
	cocos2d::CCDirector::sharedDirector()->pushScene(cocos2d::CCDirector::sharedDirector()->getRunningScene());
	cocos2d::CCDirector::sharedDirector()->replaceScene(LoadScene::createScene());
}