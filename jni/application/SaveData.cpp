#include "SaveData.h"
#include "GameSystem.h"

#define NO_DATA_IMAGE ""

SaveData::SaveData(int number, std::string imageFile, std::string text, std::string date)
{
	/*���ش浵��ť����*/
	
	/*���ش浵���*/
	
	/*���ش浵��ͼ*/

	/*���ش浵��Ϣ*/

	/*���ر�ע��Ϣ*/
}

SaveData::SaveData(int i)
	: _dataImage(NULL)
	, _dataDate(NULL)
	, _dataText(NULL)
{
	/*���ذ�ť�ײ�*/
	/*
	auto stageLayer = Layer::create();
	_stageLayer->setContentSize(Size(400,110));
	_stageLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	*/
	_stageLayer = cocos2d::CCSprite::create("/ui/saveload/noselected_bg.png");
	
	_number = i;

	updataData();

#if 0
	onTouchEnded = [=](int i){};
#endif
	//this->setTouchEnabled(true);

	cocos2d::CCSprite *touchImage = cocos2d::CCSprite::create("/ui/saveload/selected_bg.png");
	touchImage->setAnchorPoint(ccp(0.0f, 0.0f));
	touchImage->setVisible(false);
	_stageLayer->addChild(touchImage);

#if 0
	auto eventTouch = EventListenerTouchOneByOne::create();

	eventTouch->onTouchBegan = [=](Touch *t, Event *e)
	{
		if (_stageLayer->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//�������ָ��
		{
			touchImage->setVisible(true);
			return true;
		}
		return false;
	};

	eventTouch->onTouchEnded = [=](Touch *t, Event *e)
	{
		touchImage->setVisible(false);
		if (_stageLayer->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//�������ָ��
		{
			onTouchEnded(_number);
			log("Wow!");
		}
		else
		{
			
		}
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventTouch, this);
#endif

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
		/*��ʾ�浵���*/
		/*
		auto dataNumber = Label::createWithSystemFont();
		dataNumber->setPosition();
		_stageLayer->addChild(dataNumber);
		*/

		/*��ʾ�浵��ͼ*/

		std::string imageFile = savedata->imageFile;
		if (isNeedReloadImageFile)
		{
			cocos2d::CCTextureCache::sharedTextureCache()->reloadTexture(imageFile.c_str());
			_dataImage = cocos2d::CCSprite::createWithTexture(GameSystem::getInstance()->getScreenShoot()->getSprite()->getTexture());
			_dataImage->setScaleX(1);
			_dataImage->setScaleY(-1); //FIXME:
		}
		else
			_dataImage = cocos2d::CCSprite::create(imageFile.c_str());
		if (_dataImage)
		{
			
			//_dataImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
			_dataImage->setPosition(ccp(80, 55));
			_stageLayer->addChild(_dataImage);
		}

		/*��ʾ�浵��Ϣ*/
		std::string text = savedata->text;

		_dataText = cocos2d::CCLabelTTF::create(text.c_str(), "����", 20);
		_dataText->setAnchorPoint(ccp(0.0f, 0.5f));
		_dataText->setPosition(ccp(160, 35));
		_stageLayer->addChild(_dataText);

		/*��ʾ�浵����*/
		std::string date = savedata->date;

		_dataDate = cocos2d::CCLabelTTF::create(date.c_str(), "����", 20);
		_dataDate->setAnchorPoint(ccp(0.0f, 0.5f));
		_dataDate->setPosition(ccp(160, 65));
		_stageLayer->addChild(_dataDate);

		/*��ʾ�浵��ע*/
		//��ʵ��

	}
	else
	{
		/*��ʾ�浵���*/
		/*
		auto dataNumber = Label::createWithSystemFont();
		dataNumber->setPosition();
		_stageLayer->addChild(dataNumber);
		*/

		/*��ʾ�浵��ͼ*/
		_dataImage = cocos2d::CCSprite::create("/ui/saveload/pic_bg.png");
		_dataImage->setAnchorPoint(ccp(0.0f, 1.0f));
		_dataImage->setPosition(ccp(15, 101));
		_stageLayer->addChild(_dataImage);

		/*��ʾ�浵����*/
		_dataDate = cocos2d::CCLabelTTF::create("-/-/- --:--", "����", 20);
		_dataDate->setAnchorPoint(ccp(0.0f, 0.5f));
		_dataDate->setPosition(ccp(170, 65));
		_stageLayer->addChild(_dataDate);

		/*��ʾ�浵��ע*/
		//��ʵ��
	}
}

cocos2d::CCSprite* SaveData::getStageLayer()
{
	//log("data Number = %d", _number);
	return _stageLayer;
}