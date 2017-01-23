#include "SaveData.h"
#include "GameSystem.h"

#define NO_DATA_IMAGE ""

SaveData::SaveData(int number, std::string imageFile, std::string text, std::string date)
{
	/*¼ÓÔØ´æµµ°´Å¥±³¾°*/
	
	/*¼ÓÔØ´æµµ±àºÅ*/
	
	/*¼ÓÔØ´æµµ½ØÍ¼*/

	/*¼ÓÔØ´æµµÐÅÏ¢*/

	/*¼ÓÔØ±¸×¢ÐÅÏ¢*/
}

SaveData::SaveData(int i)
	: _dataImage(NULL)
	, _dataDate(NULL)
	, _dataText(NULL)
{
	/*¼ÓÔØ°´Å¥µ×²ã*/
	/*
	auto stageLayer = Layer::create();
	_stageLayer->setContentSize(Size(400,110));
	_stageLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	*/
	_stageLayer = cocos2d::CCSprite::create("/ui/saveload/noselected_bg.png");
	
	_number = i;

	updataData();

	onTouchEndedObj = NULL;
	onTouchEnded = NULL;

	//this->setTouchEnabled(true);

	touchImage = cocos2d::CCSprite::create("/ui/saveload/selected_bg.png");
	touchImage->setAnchorPoint(ccp(0.0f, 0.0f));
	touchImage->setVisible(false);
	_stageLayer->addChild(touchImage);

	this->addChild(_stageLayer);
}

SaveData::~SaveData()
{
}

SaveData* SaveData::create(int i)
{
	SaveData *tmpSavedata = new SaveData(i);
	return tmpSavedata;
}

void SaveData::updataData()
{
	GameSaveData *savedata = GameSystem::getInstance()->getGameSavedata(_number);
	bool isNeedReloadImageFile = false;
	if (_dataImage)
	{
		_dataImage->removeFromParent();
		isNeedReloadImageFile = true;
	}
	if (_dataDate) _dataDate->removeFromParent();
	if (_dataText) _dataText->removeFromParent();
	if (savedata)
	{
		/*ÏÔÊ¾´æµµÐòºÅ*/
		/*
		auto dataNumber = Label::createWithSystemFont();
		dataNumber->setPosition();
		_stageLayer->addChild(dataNumber);
		*/

		/*ÏÔÊ¾´æµµ½ØÍ¼*/

		std::string imageFile = savedata->imageFile;
		if (isNeedReloadImageFile)
		{
			cocos2d::CCTextureCache::sharedTextureCache()->reloadTexture(imageFile.c_str());
			_dataImage = cocos2d::CCSprite::createWithTexture(GameSystem::getInstance()->getScreenShoot()->getSprite()->getTexture());
			_dataImage->setScaleX(1);
			_dataImage->setScaleY(-1); //FIXME:
		}
		else
		{
			_dataImage = cocos2d::CCSprite::create(imageFile.c_str());
		}
		if (_dataImage)
		{
			
			//_dataImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
			_dataImage->setPosition(ccp(40/*80*/, 25/*55*/));
			_stageLayer->addChild(_dataImage);
		}

		/*ÏÔÊ¾´æµµÐÅÏ¢*/
		std::string text = savedata->text;

		_dataText = cocos2d::CCLabelTTF::create(text.c_str(), "ºÚÌå", 10/*20*/);
		_dataText->setAnchorPoint(ccp(0.0f, 0.5f));
		_dataText->setPosition(ccp(85/*160*/, 5/*35*/));
		_stageLayer->addChild(_dataText);

		/*ÏÔÊ¾´æµµÈÕÆÚ*/
		std::string date = savedata->date;

		_dataDate = cocos2d::CCLabelTTF::create(date.c_str(), "ºÚÌå", 10/*20*/);
		_dataDate->setAnchorPoint(ccp(0.0f, 0.5f));
		_dataDate->setPosition(ccp(85/*160*/, 35/*65*/));
		_stageLayer->addChild(_dataDate);

		/*ÏÔÊ¾´æµµ±¸×¢*/
		//´ýÊµÏÖ

	}
	else
	{
		/*ÏÔÊ¾´æµµÐòºÅ*/
		/*
		auto dataNumber = Label::createWithSystemFont();
		dataNumber->setPosition();
		_stageLayer->addChild(dataNumber);
		*/

		/*ÏÔÊ¾´æµµ½ØÍ¼*/
		_dataImage = cocos2d::CCSprite::create("/ui/saveload/pic_bg.png");
		_dataImage->setAnchorPoint(ccp(0.0f, 1.0f));
		_dataImage->setPosition(ccp(6/*15*/, 48/*101*/));
		_stageLayer->addChild(_dataImage);

		/*ÏÔÊ¾´æµµÈÕÆÚ*/
		_dataDate = cocos2d::CCLabelTTF::create("-/-/- --:--", "ºÚÌå", 10/*20*/);
		_dataDate->setAnchorPoint(ccp(0.0f, 0.5f));
		_dataDate->setPosition(ccp(85/*170*/, 35/*65*/));
		_stageLayer->addChild(_dataDate);

		/*ÏÔÊ¾´æµµ±¸×¢*/
		//´ýÊµÏÖ
	}
}

cocos2d::CCSprite* SaveData::getStageLayer()
{
	//log("data Number = %d", _number);
	return _stageLayer;
}



void SaveData::onEnter()  
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);  
    CCNode::onEnter();  
}

void SaveData::onExit()  
{  
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
    CCNode::onExit();  
}  

bool SaveData::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (_stageLayer->boundingBox().containsPoint(this->convertTouchToNodeSpace(pTouch)))	//Èç¹ûÅöµ½Ö¸Õë
	{
		touchImage->setVisible(true);
		return true;
	}
	return false;
}

void SaveData::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void SaveData::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	touchImage->setVisible(false);
	if (_stageLayer->boundingBox().containsPoint(this->convertTouchToNodeSpace(pTouch)))	//Èç¹ûÅöµ½Ö¸Õë
	{
		if (onTouchEndedObj != NULL)
		{
			(onTouchEndedObj->*onTouchEnded)(_number);
		}
		CCLOG("Wow!");
	}
	else
	{
		
	}
}

void SaveData::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

