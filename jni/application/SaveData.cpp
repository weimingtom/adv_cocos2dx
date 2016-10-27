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
	: _dataImage(nullptr)
	, _dataDate(nullptr)
	, _dataText(nullptr)
{
	/*���ذ�ť�ײ�*/
	/*
	auto stageLayer = Layer::create();
	_stageLayer->setContentSize(Size(400,110));
	_stageLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	*/
	_stageLayer = Sprite::create("/ui/saveload/noselected_bg.png");
	
	_number = i;

	updataData();

	onTouchEnded = [=](int i){};
	//this->setTouchEnabled(true);

	auto touchImage = Sprite::create("/ui/saveload/selected_bg.png");
	touchImage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	touchImage->setVisible(false);
	_stageLayer->addChild(touchImage);

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

	this->addChild(_stageLayer);
}

SaveData::~SaveData()
{
}

SaveData* SaveData::create(int i)
{
	auto tmpSavedata = new SaveData(i);
	return tmpSavedata;
}

void SaveData::updataData()
{
	auto savedata = GameSystem::getInstance()->getGameSavedata(_number);
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
			Director::getInstance()->getTextureCache()->reloadTexture(imageFile);
			_dataImage = Sprite::createWithTexture(GameSystem::getInstance()->getScreenShoot()->getSprite()->getTexture());
			_dataImage->setScale(1, -1);
		}
		else
			_dataImage = Sprite::create(imageFile);
		if (_dataImage)
		{
			
			//_dataImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
			_dataImage->setPosition(80, 55);
			_stageLayer->addChild(_dataImage);
		}

		/*��ʾ�浵��Ϣ*/
		std::string text = savedata->text;

		_dataText = Label::createWithSystemFont(text, "����", 20);
		_dataText->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_dataText->setPosition(160, 35);
		_stageLayer->addChild(_dataText);

		/*��ʾ�浵����*/
		std::string date = savedata->date;

		_dataDate = Label::createWithSystemFont(date, "����", 20);
		_dataDate->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_dataDate->setPosition(160, 65);
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
		_dataImage = Sprite::create("/ui/saveload/pic_bg.png");
		_dataImage->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		_dataImage->setPosition(15, 101);
		_stageLayer->addChild(_dataImage);

		/*��ʾ�浵����*/
		_dataDate = Label::createWithSystemFont("-/-/- --:--", "����", 20);
		_dataDate->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		_dataDate->setPosition(170, 65);
		_stageLayer->addChild(_dataDate);

		/*��ʾ�浵��ע*/
		//��ʵ��
	}
}

Sprite* SaveData::getStageLayer()
{
	//log("data Number = %d", _number);
	return _stageLayer;
}