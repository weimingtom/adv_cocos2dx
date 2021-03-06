#include "SaveScene.h"
#include "GameSystem.h"

SaveScene::SaveScene()
{
}


SaveScene::~SaveScene()
{
}

cocos2d::CCScene* SaveScene::createScene()
{
	cocos2d::CCScene *scene = cocos2d::CCScene::create();

	SaveScene *layer = SaveScene::create();

	scene->addChild(layer);

	return scene;
}

bool SaveScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    
	cocos2d::CCLayer *stageLayer = cocos2d::CCLayer::create();

	/*���ر���*/
	cocos2d::CCLayerColor *backgroundLayer = cocos2d::CCLayerColor::create(
		ccc4(0, 0, 0, 255));
	stageLayer->addChild(backgroundLayer);

	cocos2d::CCSprite *backgroundImage = cocos2d::CCSprite::create("/ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	cocos2d::CCSprite *backgroundWindow = cocos2d::CCSprite::create("/ui/saveload/window_bg.png");
	backgroundWindow->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundWindow);

	/*���ذ�ť*/

	//dataButtons[8];
	int i;
	for (/*int*/ i = 0; i < 4; i++)
	{
		dataButtons[i] = SaveData::create(i);
		dataButtons[i]->setPosition(140/*425*/, 235/*520*/ - 50/*115*/ * i);
		dataButtons[i]->onTouchEndedObj = this;
		dataButtons[i]->onTouchEnded = (void (CCObject::*)(int)) &SaveScene::save;
		stageLayer->addChild(dataButtons[i]);
	}
	for (/*int*/ i = 4; i < 8; i++)
	{
		dataButtons[i] = SaveData::create(i);
		dataButtons[i]->setPosition(335/*850*/, 235/*520*/ - 50/*115*/ * (i - 4));
		dataButtons[i]->onTouchEndedObj = this;
		dataButtons[i]->onTouchEnded = (void (CCObject::*)(int)) &SaveScene::save;
		stageLayer->addChild(dataButtons[i]);
	}

	//���ذ�ť
	cocos2d::CCMenuItemImage *buttonBack = cocos2d::CCMenuItemImage::create(
		"/ui/button_return.png", 
		"/ui/button_return_down.png", this,  
		menu_selector(SaveScene::back));
	buttonBack->setPosition(ccp(60/*175*/, 50/*90*/));
	cocos2d::CCMenu *menu = cocos2d::CCMenu::create(buttonBack, NULL);
	menu->setPosition(ccp(0, 0));
	stageLayer->addChild(menu);


	this->addChild(stageLayer);
	return true;
}

void SaveScene::back(cocos2d::CCObject *)
{
	GameSystem::getInstance()->initGameSavedataList();
	cocos2d::CCDirector::sharedDirector()->popScene();
}

void SaveScene::save(int i)
{
	GameSystem::getInstance()->saveGameSceneInfo(i);
	GameSystem::getInstance()->updateGameSavedata(i);
	dataButtons[i]->updataData();
}
