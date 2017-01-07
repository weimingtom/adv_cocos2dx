#include "LoadScene.h"
#include "GameSystem.h"
#include "GameScene.h"

LoadScene::LoadScene()
{
}


LoadScene::~LoadScene()
{
}

cocos2d::CCScene* LoadScene::createScene()
{
	cocos2d::CCScene *scene = cocos2d::CCScene::create();

	LoadScene *layer = LoadScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoadScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    
	cocos2d::CCLayer *stageLayer = cocos2d::CCLayer::create();

	/*加载背景*/
	cocos2d::CCLayerColor *backgroundLayer = cocos2d::CCLayerColor::create(ccc4(0, 0, 0, 255));
	stageLayer->addChild(backgroundLayer);

	cocos2d::CCSprite *backgroundImage = cocos2d::CCSprite::create("/ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	cocos2d::CCSprite *backgroundWindow = cocos2d::CCSprite::create("/ui/saveload/window_bg.png");
	backgroundWindow->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundWindow);

	/*加载按钮*/

	dataButtons[8];
#if 0
	eventTouch[8];
#endif
	int i;
	for (/*int*/ i = 0; i < 4; i++)
	{
		dataButtons[i] = SaveData::create(i);
		dataButtons[i]->setPosition(425, 520 - 115 * i);
#if 0
		eventTouch[i] = EventListenerTouchOneByOne::create();
		eventTouch[i]->onTouchBegan = [=](Touch *t, Event *e)
		{
			if (dataButtons[i]->getStageLayer()->getBoundingBox().containsPoint(dataButtons[i]->convertTouchToNodeSpace(t)))	//如果碰到指针
			{
				return true;
			}
			return false;
		};
		eventTouch[i]->onTouchEnded = [=](Touch *t, Event *e)
		{
			if (dataButtons[i]->getStageLayer()->getBoundingBox().containsPoint(dataButtons[i]->convertTouchToNodeSpace(t)))	//如果碰到指针
			{
				load(i);
			}
			else
			{
				
			}
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventTouch[i], this);
#endif
		stageLayer->addChild(dataButtons[i]);
	}
	for (/*int*/ i = 4; i < 8; i++)
	{
		dataButtons[i] = SaveData::create(i);
		dataButtons[i]->setPosition(850, 520 - 115 * (i - 4));

#if 0
		eventTouch[i] = EventListenerTouchOneByOne::create();
		eventTouch[i]->onTouchBegan = [=](Touch *t, Event *e)
		{
			if (dataButtons[i]->getStageLayer()->getBoundingBox().containsPoint(dataButtons[i]->convertTouchToNodeSpace(t)))	//如果碰到指针
			{
				return true;
			}
			return false;
		};
		eventTouch[i]->onTouchEnded = [=](Touch *t, Event *e)
		{
			if (dataButtons[i]->getStageLayer()->getBoundingBox().containsPoint(dataButtons[i]->convertTouchToNodeSpace(t)))	//如果碰到指针
			{
				load(i);
			}
			else
			{
			}
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventTouch[i], this);
#endif
		stageLayer->addChild(dataButtons[i]);
	}



	//返回按钮
	cocos2d::CCMenuItemImage *buttonBack = cocos2d::CCMenuItemImage::create(
		"/ui/button_return.png", 
		"/ui/button_return_down.png", this,
		menu_selector(LoadScene::back));
	buttonBack->setPosition(ccp(60/*175*/, 50/*90*/));
	cocos2d::CCMenu *menu = cocos2d::CCMenu::create(buttonBack, NULL);
	menu->setPosition(ccp(0, 0));
	stageLayer->addChild(menu);


	this->addChild(stageLayer);
	return true;
}

void LoadScene::back(CCObject *)
{
	//GameSystem::getInstance()->initGameSavedataList();
	cocos2d::CCDirector::sharedDirector()->popScene();
}

void LoadScene::load(int i)
{
	CCLOG("loadsave = %d", i + 1);
	GameSystem::getInstance()->setIsLoadSuccess(GameSystem::getInstance()->loadGameSceneInfo(i));
	if (GameSystem::getInstance()->getGameScene())
	{
		cocos2d::CCDirector::sharedDirector()->popScene();
	}
	GameSystem::getInstance()->setGameScene(GameScene::createScene());
	cocos2d::CCScene *scene = GameSystem::getInstance()->getGameScene();
	cocos2d::CCDirector::sharedDirector()->replaceScene(scene);
}
