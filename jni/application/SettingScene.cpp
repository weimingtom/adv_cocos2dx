#include "SettingScene.h"
#include "GameSystem.h"
//#include "SimpleAudioEngine.h"


SettingScene::SettingScene()
{
}


SettingScene::~SettingScene()
{
}

cocos2d::CCScene* SettingScene::createScene()
{
	cocos2d::CCScene *scene = cocos2d::CCScene::create();

	SettingScene *layer = SettingScene::create();

	scene->addChild(layer);

	return scene;
}

bool SettingScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    
	cocos2d::CCLayer *stageLayer = cocos2d::CCLayer::create();
	
	
	/*¼ÓÔØ±³¾°*/
	cocos2d::CCLayerColor *backgroundLayer = cocos2d::CCLayerColor::create(
		ccc4(0, 0, 0, 255));
	stageLayer->addChild(backgroundLayer);

	cocos2d::CCSprite *backgroundImage = cocos2d::CCSprite::create(
		"/ui/backgroundEffect/fullscreen_smoke.png");
	backgroundImage->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundImage);

	cocos2d::CCSprite *backgroundBox = cocos2d::CCSprite::create(
		"/ui/config/window_bg.png");
	backgroundBox->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	stageLayer->addChild(backgroundBox);
	
	/*¼ÓÔØ°´Å¥*/

	//SliderBar
	_musicVolumeSlidebar = Slidebar::createSlidebar("/ui/scroll_bar.png", "/ui/scroll_point.png");
	_musicVolumeSlidebar->setPosition(ccp(280/*750*/, 177/*400*/));
	_musicVolumeSlidebar->setFloat(GameSystem::getInstance()->getMusicVolume());
	_musicVolumeSlidebar->moveEvent = (void (CCObject::*)()) &SettingScene::changeMusicVolume; 
	_musicVolumeSlidebar->moveEventObj = this;
	_musicVolumeSlidebar->touchEvent = (void (CCObject::*)()) &SettingScene::changeMusicVolume;
	_musicVolumeSlidebar->touchEventObj = this;
	stageLayer->addChild(_musicVolumeSlidebar);
	
	//

	//²âÊÔ°´Å¥
	EasyButton *testButton = EasyButton::createEasyButton(
		"/ui/charbox_off.png", "/ui/charbox_off.png", "/ui/charbox_on.png");
	testButton->setPosition(ccp(280/*710*/, 120/*275*/));
	EasyButton *testButton2 = EasyButton::createEasyButton(
		"/ui/charbox_off.png", "/ui/charbox_off.png", "/ui/charbox_on.png");
	testButton2->setPosition(ccp(370/*920*/, 120/*275*/));

	_testRadio = RadioButton::createRadioButton(testButton, testButton2, NULL);
	_testRadio->setSelectedNumber(1);
	stageLayer->addChild(_testRadio);
	_testRadio->touchEvent = (void (CCObject::*)()) &SettingScene::test;
	_testRadio->touchEventObj = this;



	//·µ»Ø°´Å¥
	cocos2d::CCMenuItemImage *buttonBack = cocos2d::CCMenuItemImage::create(
		"/ui/button_return.png", 
		"/ui/button_return_down.png", this, 
		menu_selector(SettingScene::back));
	buttonBack->setPosition(ccp(60/*175*/, 50/*90*/));
	cocos2d::CCMenu *menu = cocos2d::CCMenu::create(buttonBack, NULL);
	menu->setPosition(ccp(0, 0));
	stageLayer->addChild(menu);
	
	this->addChild(stageLayer);
	
	return true;
}

void SettingScene::back(CCObject *)
{
	cocos2d::CCDirector::sharedDirector()->popScene();
}

void SettingScene::test()
{
	CCLOG("RadioButton Number: %d", _testRadio->getSelectedNumber());
}

void SettingScene::changeMusicVolume()
{
	CCLOG("Music Value : %f", _musicVolumeSlidebar->getFloat());
	GameSystem::getInstance()->setMusicVolume(_musicVolumeSlidebar->getFloat());
	//CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(GameSystem::getInstance()->getMusicVolume());
}