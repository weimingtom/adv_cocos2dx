#include "HistoryScene.h"

HistoryMessage::HistoryMessage(std::string text, std::string name, cocos2d::ccColor4B color)
{
	_nameLabel = cocos2d::CCLabelTTF::create(name.c_str(), "黑体", 20);
	_nameLabel->setColor(ccWHITE);
	_nameLabel->setAnchorPoint(ccp(0.0f, 0.5f));
	_nameLabel->setPosition(ccp(-265, 12));
	this->addChild(_nameLabel);

	_textLabel = cocos2d::CCLabelTTF::create(text.c_str(), "黑体", 20);
	_textLabel->setAnchorPoint(ccp(0.0f, 0.5f));
	_textLabel->setPosition(ccp(-265, -12));
	this->addChild(_textLabel);
}


HistoryMessage::~HistoryMessage()
{
}

HistoryMessage* HistoryMessage::create(record* record)
{
	std::string text = record->text;
	std::string name = record->name;
	cocos2d::ccColor4B color = record->color;
	HistoryMessage *tmpHM = new HistoryMessage(text, name, color);
	return tmpHM;
}

HistoryScene::HistoryScene()
{
}


HistoryScene::~HistoryScene()
{
}

cocos2d::CCScene* HistoryScene::createScene()
{
	cocos2d::CCScene* scene = cocos2d::CCScene::create();

	HistoryScene *layer = HistoryScene::create();

	scene->addChild(layer);

	return scene;
}

bool HistoryScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    
	cocos2d::CCLayer *stageLayer = cocos2d::CCLayer::create();

	/*加载背景*/
	cocos2d::CCLayerColor *backgroundLayer = cocos2d::CCLayerColor::create(ccc4(0, 0, 0, 255));//FIXME:
	stageLayer->addChild(backgroundLayer);

	cocos2d::CCSprite* backgroundImage = cocos2d::CCSprite::create("/ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	/*加载历史记录*/
	cocos2d::CCSprite *historyList = cocos2d::CCSprite::create();
	int startY = 0;
	for (int i = 0; i < HistoryLogger::getInstance()->getLength(); i++)
	{
		//log("i = %d", i);
		record* record = HistoryLogger::getInstance()->getRecord(i);
		CCLOG("Record[%d] = [%s , %s]", i, record->name.c_str(), record->text.c_str());
		HistoryMessage *hm = HistoryMessage::create(record);
		hm->setAnchorPoint(ccp(0.5f, 1.0f));
		hm->setPosition(visibleSize.width / 2, startY);
		historyList->addChild(hm);
		startY -= hm->getContentSize().height + 50;

	}
	historyList->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(historyList);

	/*给历史记录添加触碰事件*/
	/*
	auto et = EventListenerTouchOneByOne::create();
	pointPositionY = historyList->getPosition().y;
	et->onTouchBegan = [=](Touch *t, Event *e)
	{
		if (stageLayer->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//如果碰到指针
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	et->onTouchMoved = [=](Touch *t, Event *e)
	{
		float yOff = t->getLocation().x - t->getStartLocation().x;


		historyList->setPositionY(pointPositionY + yOff);

	};

	et->onTouchEnded = [&](Touch *t, Event *e)
	{
		//保存指针位置
		pointPositionY = historyList->getPositionY();
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(et, this);

	*/

	//返回按钮
	cocos2d::CCMenuItemImage *buttonBack = cocos2d::CCMenuItemImage::create(
		"/ui/button_return.png", 
		"/ui/button_return_down.png", this,
		menu_selector(HistoryScene::back));
	buttonBack->setPosition(ccp(175, 90)); 
	cocos2d::CCMenu *menu = cocos2d::CCMenu::create(buttonBack, NULL);
	menu->setPosition(ccp(0, 0));
	stageLayer->addChild(menu);

	

	addChild(stageLayer);

	return true;
}

void HistoryScene::back(CCObject *)
{
	cocos2d::CCDirector::sharedDirector()->popScene();
}