#include "GameScene.h"
//#include "ui/CocosGUI.h"
#include "cocos-ext.h"
//#include "SimpleAudioEngine.h"
#include "GameSystem.h"
#include "ScriptReader/BackgroundManager.h"
#include "ScriptReader/BackgroundMusicManager.h"
#include "ScriptReader/SoundManager.h"
#include "SaveScene.h"
#include "LoadScene.h"
#include "HistoryScene.h"
#ifndef History_hpp
#define History_hpp
#include "History.hpp"
#endif /* History_hpp */

USING_NS_CC;

GameScene::GameScene() 
	:_label(NULL)
	, _backgroundSprite(NULL)
	, _charNumber(0)
	, _backgroundKey("")
	, _backgroundMusicKey("")
	, _soundKey("")
	, _currentName("")
	, _currentText("")
	//, _currentOptions(NULL)
	, _optionsNumber(0)
{
	_emptyChar = new Charactor;
}


GameScene::~GameScene()
{
	delete _emptyChar;
	_emptyChar = NULL;
	for (int i = 0; i < MAX_CHARACTOR_NUMBER; i++)
	{
		if (_chars[i])
		{
			//delete _chars[i];
			_chars[i] = NULL;
		}
	}
		
	//ScriptReader::destoryInstance();
}

cocos2d::CCScene* GameScene::createScene()
{
	cocos2d::CCScene *scene = cocos2d::CCScene::create();

	GameScene *layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!this->CCLayer::init())
	{
		return false;
	}

	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    
	cocos2d::CCLayer *stageLayer = cocos2d::CCLayer::create();
	addChild(stageLayer, 13);

	//背景层
	_backgroundLayer = cocos2d::CCLayer::create();
	//_backgroundLayer->setLocalZOrder(0);
	this->addChild(_backgroundLayer, -1);

	//立绘层
	_charactorsLayer = cocos2d::CCLayer::create();
	this->addChild(_charactorsLayer, 1);
	for (int i = 0; i < 5; i++)
	{
		_chars[i] = new Charactor;
	}

	//对话框
	cocos2d::CCSprite *_dialogWindow = cocos2d::CCSprite::create("/ui/dialog/dialog_bg.png");
	_dialogWindow->setPosition(ccp(visibleSize.width / 2, 110));
	this->addChild(_dialogWindow,10);

	//文本框
	_nameLabel = CCLabelTTF::create("", "微软雅黑", 24);
	_nameLabel->setColor(ccBLACK);
	_nameLabel->setAnchorPoint(ccp(0.0f, 0.5f));
	_nameLabel->setPosition(ccp(70, _dialogWindow->getContentSize().height - 40));
	_dialogWindow->addChild(_nameLabel,11);

	_textLabel = CharLabel::create("", 24, (void (cocos2d::CCObject::*)(void)) GameScene::showClickSign, this);
	_textLabel->setPosition(ccp(_nameLabel->getPositionX(), _nameLabel->getPositionY() - 25));
	_textLabel->setColor(ccBLACK);
	_dialogWindow->addChild(_textLabel, 12);

	//对话框按钮
	cocos2d::CCMenuItemImage *buttonDict = cocos2d::CCMenuItemImage::create(
		"/ui/dialog/button_dict.png", 
		"/ui/dialog/button_dict_down.png", this,
		menu_selector(GameScene::startAutoPlay));
	buttonDict->setPosition(ccp(840, 220));

	cocos2d::CCMenuItemImage *buttonSave = cocos2d::CCMenuItemImage::create(
		"/ui/dialog/button_save.png", 
		"/ui/dialog/button_save_down.png", this, 
		menu_selector(GameScene::showSaveScene));
	buttonSave->setPosition(ccp(900, 220));

	cocos2d::CCMenuItemImage *buttonLoad = cocos2d::CCMenuItemImage::create(
		"/ui/dialog/button_load.png", 
		"/ui/dialog/button_load_down.png", this, 
		menu_selector(GameScene::showLoadScene));
	buttonLoad->setPosition(ccp(960, 220));

	cocos2d::CCMenuItemImage *buttonLog = cocos2d::CCMenuItemImage::create(
		"/ui/dialog/button_log.png", 
		"/ui/dialog/button_log_down.png", this,  
		menu_selector(GameScene::showHistoryScene));
	buttonLog->setPosition(ccp(1020, 220));

	cocos2d::CCMenuItemImage *buttonConfig = cocos2d::CCMenuItemImage::create(
		"/ui/dialog/button_config.png", 
		"/ui/dialog/button_config_down.png");
	buttonConfig->setPosition(ccp(1080, 220));

	cocos2d::CCMenuItemImage *buttonTitle = cocos2d::CCMenuItemImage::create(
		"/ui/dialog/button_title.png", 
		"/ui/dialog/button_title_down.png");
	buttonTitle->setPosition(ccp(1200, 220));

	cocos2d::ui::CheckBox *CBskip = cocos2d::ui::CheckBox::create();
	CBskip->loadTextures("/ui/dialog/charbox_skip_off.png", 
		"/ui/dialog/charbox_skip_off.png", 
		"/ui/dialog/charbox_skip_on.png", 
		"/ui/dialog/charbox_skip_off.png", 
		"/ui/dialog/charbox_skip_on.png");
	CBskip->setPosition(ccp(1000, 125));
	_dialogWindow->addChild(CBskip, 0);

	cocos2d::ui::CheckBox *CBauto = cocos2d::ui::CheckBox::create();
	CBauto->loadTextures("/ui/dialog/charbox_auto_off.png", 
		"/ui/dialog/charbox_auto_off.png", 
		"/ui/dialog/charbox_auto_on.png", 
		"/ui/dialog/charbox_auto_off.png", 
		"/ui/dialog/charbox_auto_on.png");
	CBauto->setPosition(ccp(1000, 75));
	/*
	CBauto->onTouchEnded = [=](Touch *touch, Event *unusedEvent)
	{
		//startAutoPlay();
	};
	*/
	_dialogWindow->addChild(CBauto, 1);

	cocos2d::CCMenu *menu = cocos2d::CCMenu::create(buttonDict, buttonSave, buttonLoad, buttonLog, buttonConfig, buttonTitle, NULL);
	menu->setPosition(ccp(0, 0));
	this->addChild(menu, 13);

	cocos2d::CCLayer *_selectLayer = cocos2d::CCLayer::create();
	this->addChild(_selectLayer, 13);

#if 0
	auto clickEvent = EventListenerTouchOneByOne::create();
	clickEvent->onTouchBegan = [=](Touch *t, Event *e)
	{
		this->screenClicked();
		return false;
	};
	stageLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(clickEvent, stageLayer);

	auto dialogClickEvent = EventListenerTouchOneByOne::create();
	dialogClickEvent->onTouchBegan = [=](Touch *t, Event *e)
	{
		if (_dialogWindow->getBoundingBox().containsPoint(_dialogWindow->convertTouchToNodeSpace(t)))
		{
			this->dialogClicked();
		}
		return true;
	};
	_dialogWindow->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dialogClickEvent, _dialogWindow);
#endif

	//创建ScriptReader对象
	
	ScriptReader::getInstance()->initWithStage(stageLayer);
	//绑定reader功能
	ScriptReader::getInstance()->showText = (void (CCObject::*)(std::string &text)) &GameScene::showText;
	ScriptReader::getInstance()->showTextObj = this;
	ScriptReader::getInstance()->showName = (void (CCObject::*)(std::string &name)) &GameScene::showName;
	ScriptReader::getInstance()->showNameObj = this;
	ScriptReader::getInstance()->changeBackground = (void (CCObject::*)(std::string &key)) &GameScene::changeBackground;
	ScriptReader::getInstance()->changeBackgroundObj = this;
	ScriptReader::getInstance()->playBackgroundMusic = (void (CCObject::*)(std::string &key)) &GameScene::playBackgroundMusic;
	ScriptReader::getInstance()->playBackgroundMusicObj = this;
	ScriptReader::getInstance()->stopBackgroundMusic = (void (CCObject::*)()) &GameScene::stopBackgroundMusic;
	ScriptReader::getInstance()->stopBackgroundMusicObj = this;
	ScriptReader::getInstance()->playSound = (void (CCObject::*)(std::string &file)) &GameScene::playSound;
	ScriptReader::getInstance()->playSoundObj = this;
	ScriptReader::getInstance()->stopSound = (void (CCObject::*)()) &GameScene::stopSound;
	ScriptReader::getInstance()->stopSoundObj = this;
	ScriptReader::getInstance()->showCharator = (void (CCObject::*)(std::string &cName, std::string &face)) &GameScene::displayCharator;
	ScriptReader::getInstance()->showCharatorObj = this;
	ScriptReader::getInstance()->hideCharator = (void (CCObject::*)(std::string &cName)) &GameScene::unDisplayCharator;
	ScriptReader::getInstance()->hideCharatorObj = this;
	ScriptReader::getInstance()->showSelect = (void (CCObject::*)(std::map<std::string, std::string> &options)) &GameScene::showSelect;
	ScriptReader::getInstance()->showSelectObj = this;
	
	ScriptReader::getInstance()->loadScriptFile("/scenario/TestII.txt");

	if (!GameSystem::getInstance()->getIsLoadSuccess())
	{
		ScriptReader::getInstance()->nextScript();
	}
	else
	{
		//clear();
		reloadScene();
		GameSystem::getInstance()->setIsLoadSuccess(false);
	}

	return true;
}

void GameScene::update(float dt)
{
}

void GameScene::updateLabel(std::string text)
{
	_label->setString(text.c_str());
}

void GameScene::showClickSign()
{

}

void GameScene::screenClicked()
{
	//ScriptReader::getInstance()->nextScript();
}

void GameScene::dialogClicked()
{
	ScriptReader::getInstance()->nextScript();
}

void GameScene::showName(std::string &name)
{
	_currentName = name;
	_nameLabel->setString(name.c_str());
}

void GameScene::showText(std::string &text)
{
	_currentText = text;
	_textLabel->setString(text);
}
void GameScene::changeBackground(std::string &key)
{
	std::string background = BM->getBackground(key);
	if (background.compare("") == 0) return;	//如果找不到就退出
	_backgroundKey = key;
	cocos2d::CCSprite *backgroundSprite = cocos2d::CCSprite::create(background.c_str());
	backgroundSprite->setAnchorPoint(ccp(0, 0));
	backgroundSprite->setOpacity(0);
	_backgroundLayer->addChild(backgroundSprite);
#if 0
	backgroundSprite->runAction(Sequence::createWithTwoActions(FadeIn::create(1.0f), CallFunc::create([&]()
	{
		if (_backgroundSprite)
		{
			//auto tmp = _backgroundSprite;
			_backgroundSprite = backgroundSprite;
			//tmp->removeFromParent();
		}
		else
		{
			_backgroundSprite = backgroundSprite;
		}
	}
		)
		));
#endif
}

void GameScene::playBackgroundMusic(std::string &key)
{
	stopBackgroundMusic();
	std::string bgm = BMM->getBackgroundMusic(key);
	if (bgm.compare("") == 0)
	{
		CCLOG("Unfine bgm %s", key.c_str());
		return;
	}
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(bgm.c_str(), true);
	_isPlayingMusic = true;
	_backgroundMusicKey = key;
}

void GameScene::stopBackgroundMusic()
{
	if (_isPlayingMusic)
	{
		//CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		_isPlayingMusic = false;
		_backgroundMusicKey = "";
	}
}

void GameScene::scheduleVolumeFadeIn()
{

}

void GameScene::scheduleVolumeFadeOut()
{

}

void GameScene::playSound(std::string &file)
{
	stopSound();
	//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(file.c_str());
}

void GameScene::stopSound()
{
	//CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}

void GameScene::startAutoPlay(CCObject *)
{
	//schedule(schedule_selector(GameScene::autoPlay), GameSystem::getInstance()->getAutoSpeed());
	schedule(schedule_selector(GameScene::autoPlay),1.0f);
}

void GameScene::stopAutoPlay()
{
	unschedule(schedule_selector(GameScene::autoPlay));
}

void GameScene::autoPlay(float dt)
{
	ScriptReader::getInstance()->nextScript();
}

void GameScene::createGameDate()
{
	GameData *tmpGameData = new GameData;
	tmpGameData->backgroundKey = _backgroundKey;
	tmpGameData->bgmKey = _backgroundMusicKey;
	tmpGameData->soundKey = _soundKey;
	tmpGameData->charactorCount = _charNumber;
	int n = 0;
	for (int i = 0; i < MAX_CHARACTOR_NUMBER; i++)
	{
		if (_chars[i]->faceSprite)
		{
			tmpGameData->fgCharactors[n].name = _chars[i]->key;
			tmpGameData->fgCharactors[n].face = _chars[i]->currentFace;
			tmpGameData->fgCharactors[n].number = i;
			n++;
		}
	}
	tmpGameData->currentCommandIndex = ScriptReader::getInstance()->getCurrentCommandIndex();
	tmpGameData->currentSignName = ScriptReader::getInstance()->getCurrentSignName();
	tmpGameData->currentName = _currentName;
	tmpGameData->currentText = _currentText;
	tmpGameData->optionsNumber = _optionsNumber;
	CCLOG("Test 1");
	if(_optionsNumber)
	{
		CCLOG("Select::> optionSize[%d]", _currentOptions.size());
		for (std::map<std::string, std::string>::iterator it = _currentOptions.begin(); 
			it != _currentOptions.end(); ++it)
		{
				tmpGameData->options.insert(std::pair<std::string, std::string>(it->first, it->second));
		}
		//tmpGameData->options.insert(_currentOptions.begin(), _currentOptions.end());
	}
	//tmpGameData->options = *_currentOptions;
	CCLOG("Test 2");
	GameSystem::getInstance()->setGameSceneInfo(tmpGameData);
}

void GameScene::displayCharator(std::string& cName, std::string& face)
{
	Charactor* cha = CM->getCharactor(cName);	//获取角色
	if (cha)
	{
		bool isNeedShow = false;	//判断是否需要重新显示人物立绘
		if (cha->faceSprite)
		{
			CCLOG("CurrentFace = %s, Face = %s", cha->currentFace.c_str(), face.c_str());
			if (cha->currentFace != face && face.compare("") != 0)
			{
				cha->leave();
				isNeedShow = true;
			}
		}
		else
		{
			isNeedShow = true;
		}



		if (isNeedShow)
		{
			Charactor** pChar = &_chars[2];
			PositionType tmpPT = EMPTY;

			cocos2d::CCSprite *sp = NULL;
			if (cha->getCharactorFace(face))
				sp = cocos2d::CCSprite::create(cha->getCharactorFace(face));
			cha->faceSprite = sp;
			cha->key = cName;
			cha->currentFace = face;
			if (face.compare("") != 0)
			{
				if (!_charNumber)
				{
					_charNumber++;
					pChar = &_chars[2];
					tmpPT = CENTER;
				}
				else
					if (_charNumber == 1)
					{
						if (_chars[2] == cha)
						{
							pChar = &_chars[2];
							tmpPT = CENTER;
						}
						else
						{
							_chars[2]->moveTo(LEFT_CENTER);
							_chars[1] = _chars[2];
							_chars[2] = _emptyChar;
							_charNumber++;
							pChar = &_chars[3];
							tmpPT = RIGHT_CENTER;
						}
					}
					else
					{
						if (_charNumber == 2)
						{
							if (_chars[1] == cha)
							{
								pChar = &_chars[1];
								tmpPT = LEFT_CENTER;
							}
							else
								if (_chars[3] == cha)
								{
									pChar = &_chars[3];
									tmpPT = RIGHT_CENTER;
								}
								else
								{
									_chars[1]->moveTo(LEFT);
									_chars[0] = _chars[1];
									_chars[1] = _emptyChar;
									_chars[3]->moveTo(RIGHT);
									_chars[4] = _chars[3];
									_chars[3] = _emptyChar;
									_charNumber++;
									pChar = &_chars[2];
									tmpPT = CENTER;
								}
						}
						else
						{
							if (_chars[0] == cha)
							{
								pChar = &_chars[0];
								tmpPT = LEFT;
							}
							else
								if (_chars[2] == cha)
								{
									pChar = &_chars[2];
									tmpPT = CENTER;
								}
								else
									if (_chars[4] == cha)
									{
										pChar = &_chars[4];
										tmpPT = RIGHT;
									}
									else
									{
										pChar = &_chars[2];
										tmpPT = CENTER;
									}
						}
					}


				if (((Charactor*)*pChar))
				{
					((Charactor*)*pChar)->leave();
				}



				cha->currentPosition = tmpPT;
				if (sp)
					*pChar = cha;

				switch (tmpPT)
				{
				case LEFT:
				{
					sp->setPositionX(320);
					break;
				}
				case LEFT_CENTER:
				{
					sp->setPositionX(427);
					break;
				}
				case CENTER:
				{
					sp->setPositionX(640);
					break;
				}
				case RIGHT_CENTER:
				{
					sp->setPositionX(853);
					break;
				}
				case RIGHT:
				{
					sp->setPositionX(960);
					break;
				}
				default:
				{
					break;
				}
				}

				sp->setAnchorPoint(ccp(0.5, 0));

				_charactorsLayer->addChild(sp);
			}
		}
	}
}

void GameScene::unDisplayCharator(std::string &cName)
{
	Charactor* cha = CM->getCharactor(cName);
	if (cha->faceSprite)
	{
#if 0
		cha->faceSprite->runAction(Sequence::createWithTwoActions(FadeOut::create(1.0f), CallFunc::create([=]()
		{
			if (_charNumber == 1)
			{
				_chars[2] = _emptyChar;
			}
			else
				if (_charNumber == 2)
				{
					switch (cha->currentPosition)
					{
					case LEFT_CENTER:
					{
						_chars[1] = _emptyChar;
						_chars[3]->moveTo(CENTER);
						_chars[2] = _chars[3];
						_chars[3] = _emptyChar;
						break;
					}
					case RIGHT_CENTER:
					{
						_chars[3] = _emptyChar;
						_chars[1]->moveTo(CENTER);
						_chars[2] = _chars[1];
						_chars[1] = _emptyChar;
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
					if (_charNumber == 3)
					{
						switch (cha->currentPosition)
						{
						case LEFT:
						{
							_chars[0] = _emptyChar;
							_chars[2]->moveTo(LEFT_CENTER);
							_chars[1] = _chars[2];
							_chars[2] = _emptyChar;
							_chars[4]->moveTo(RIGHT_CENTER);
							_chars[3] = _chars[4];
							_chars[4] = _emptyChar;
							break;
						}
						case CENTER:
						{
							_chars[2] = _emptyChar;
							_chars[0]->moveTo(LEFT_CENTER);
							_chars[1] = _chars[0];
							_chars[0] = _emptyChar;
							_chars[4]->moveTo(RIGHT_CENTER);
							_chars[3] = _chars[4];
							_chars[4] = _emptyChar;
							break;
						}
						case RIGHT:
						{
							_chars[4] = _emptyChar;
							_chars[0]->moveTo(LEFT_CENTER);
							_chars[1] = _chars[0];
							_chars[0] = _emptyChar;
							_chars[2]->moveTo(RIGHT_CENTER);
							_chars[3] = _chars[2];
							_chars[2] = _emptyChar;
							break;
						}
						default:
						{
							break;
						}
						}

					}
			cha->leave();
			_charNumber--;
			return;
		}
			)
			)
			);
#endif
	}
	else
		return;
}

void GameScene::showSaveScene(CCObject *)
{
	ScreenShoot();
	createGameDate();	//向GameSystem更新GameData信息
	cocos2d::CCDirector::sharedDirector()->pushScene(cocos2d::CCDirector::sharedDirector()->getRunningScene());
	cocos2d::CCDirector::sharedDirector()->replaceScene(SaveScene::createScene());
	
	//GameSystem::getInstance()->saveGameSceneInfo(1);
	//this->setScale(1.0f);
}

void GameScene::ScreenShoot()
{
	//utils::captureScreen(NULL, "savedata\\savedataImage.jpg");

	float scale = 0.1164f;	//缩小倍率
	this->setAnchorPoint(ccp(0.0f, 0.0f));
	cocos2d::CCRenderTexture *render = cocos2d::CCRenderTexture::create(getContentSize().width*scale, 
		getContentSize().height*scale);
	render->begin();
	this->setScale(scale);
	this->visit();
	render->end();
	render->retain();
	GameSystem::getInstance()->setScreenShoot(render);
	this->setScale(1.0f);
}

void GameScene::clear()
{
	
	/*清除所有立绘*/
	for (int i = 0; i < MAX_CHARACTOR_NUMBER; i++)
	{
		if (_chars[i]->faceSprite)
		{
			_chars[i]->leave();
		}
	}
	_charNumber = 0;

	/*停止播放音乐*/
	stopBackgroundMusic();

	/*清楚当前背景*/
	//std::string black = "black";
	//changeBackground(black);

	auto backgroundSprite = Sprite::create("/bgimage/Black.jpg");
	backgroundSprite->setAnchorPoint(ccp(0, 0));
	_backgroundLayer->addChild(backgroundSprite);
	_backgroundSprite = backgroundSprite;

	/*停止当前音效*/
	stopSound();

	/*清空当前文本层*/
	std::string empty = "";
	showName(empty);
	showText(empty);

	/*清空选项*/
	if (_optionsNumber)
	{
		_optionsNumber = 0;
		_currentOptions.clear();
		_selectLayer->removeAllChildren();
	}
}

void GameScene::showLoadScene(CCObject *)
{
	cocos2d::CCDirector::sharedDirector()->pushScene(cocos2d::CCDirector::sharedDirector()->getRunningScene());
	cocos2d::CCDirector::sharedDirector()->replaceScene(LoadScene::createScene());
}

void GameScene::reloadScene()
{
	if (GameSystem::getInstance()->getIsLoadSuccess())
	{ 
		/*设置背景*/
		std::string background = BM->getBackground(GameSystem::getInstance()->getGameSceneInfo()->backgroundKey);
		if (background.compare("") == 0)
			background = "black";
		cocos2d::CCSprite *backgroundSprite = cocos2d::CCSprite::create(background.c_str());
		backgroundSprite->setAnchorPoint(ccp(0, 0));
		_backgroundLayer->addChild(backgroundSprite);
		_backgroundSprite = backgroundSprite;
		/*设置当前名字*/
		showName(GameSystem::getInstance()->getGameSceneInfo()->currentName);
		/*设置当前文本*/
		showText(GameSystem::getInstance()->getGameSceneInfo()->currentText);
		/*设置当前立绘*/
		_charNumber = GameSystem::getInstance()->getGameSceneInfo()->charactorCount;
		CCLOG("load charator");
		for (int i = 0; i < _charNumber; i++)
		{
			std::string name = GameSystem::getInstance()->getGameSceneInfo()->fgCharactors[i].name;
			std::string face = GameSystem::getInstance()->getGameSceneInfo()->fgCharactors[i].face;
			int number = GameSystem::getInstance()->getGameSceneInfo()->fgCharactors[i].number;
			Charactor* cha = CM->getCharactor(name);	//获取角色
			if (cha)
			{
				Charactor** pChar = &_chars[number];
				PositionType tmpPT = EMPTY;

				cocos2d::CCSprite *sp = NULL;
				if (cha->getCharactorFace(face))
					sp = cocos2d::CCSprite::create(cha->getCharactorFace(face));
				cha->faceSprite = sp;
				cha->key = name;
				cha->currentFace = face;
				switch (number)
				{
				case 0:
					tmpPT = LEFT;
					break;
				case 1:
					tmpPT = LEFT_CENTER;
					break;
				case 2:
					tmpPT = CENTER;
					break;
				case 3:
					tmpPT = RIGHT_CENTER;
					break;
				case 4:
					tmpPT = RIGHT;
					break;
				default:
					break;
				}
				if (face.compare("") != 0)
				{

					if (((Charactor*)*pChar))
					{
						((Charactor*)*pChar)->leave();
					}



					cha->currentPosition = tmpPT;
					if (sp)
						*pChar = cha;

					switch (tmpPT)
					{
					case LEFT:
					{
						sp->setPositionX(320);
						break;
					}
					case LEFT_CENTER:
					{
						sp->setPositionX(427);
						break;
					}
					case CENTER:
					{
						sp->setPositionX(640);
						break;
					}
					case RIGHT_CENTER:
					{
						sp->setPositionX(853);
						break;
					}
					case RIGHT:
					{
						sp->setPositionX(960);
						break;
					}
					default:
					{
						break;
					}
					}

					sp->setAnchorPoint(ccp(0.5, 0));

					_charactorsLayer->addChild(sp);
				}
			}
		}
		/*设置当前播放bgm信息*/
		playBackgroundMusic(GameSystem::getInstance()->getGameSceneInfo()->bgmKey);
		/*设置当前播放音效*/
		/*设置选项信息*/
		CCLOG("load select start");
		if (GameSystem::getInstance()->getGameSceneInfo()->optionsNumber)
		{
			showSelect(GameSystem::getInstance()->getGameSceneInfo()->options);
		}
		/*设置ScriptReader*/
		std::string sign = GameSystem::getInstance()->getGameSceneInfo()->currentSignName;
		int commandIndex = GameSystem::getInstance()->getGameSceneInfo()->currentCommandIndex;
		ScriptReader::getInstance()->jumpToSign(sign, commandIndex);
	}
}

void GameScene::showSelect(std::map<std::string, std::string> &options)
{
	_currentOptions = options;

	/*cocos2d::CCMenu* */this->_menu = cocos2d::CCMenu::create();
	int startY = options.size()*(60) / 2;
	int size = options.size();
	CCLOG("Select::> optionSize[%d]", options.size());
	for (std::map<std::string, std::string>::iterator itr = options.begin(); itr != options.end(); itr++)
	{
		_optionsNumber++;	//选择数量+1
		cocos2d::CCLabelTTF *label = cocos2d::CCLabelTTF::create(itr->second.c_str(), "MSYH", 30);
		label->setColor(ccWHITE);
		label->enableShadow(CCSize(2, -2), 0, 0); //FIXME:
		CCLOG("OPTION[%s] SIGN[%s]", itr->second.c_str(), itr->first.c_str());
		//auto tmp = (std::string)itr->first.c_str();
		/*std::string*/ this->_tmp = itr->first;
		/*std::string*/ this->_tmp2 = itr->second;
		//int *test;
		cocos2d::CCMenuItemLabel *button = cocos2d::CCMenuItemLabel::create(label, this, menu_selector(GameScene::menuButton));

		this->_menu->addChild(button);
		button->setPosition(0, startY);
		startY -= 60;
	}
	_selectLayer->addChild(this->_menu, 13);
}

void GameScene::showHistoryScene(CCObject *)
{
	cocos2d::CCDirector::sharedDirector()->pushScene(cocos2d::CCDirector::sharedDirector()->getRunningScene());
	cocos2d::CCDirector::sharedDirector()->replaceScene(HistoryScene::createScene());
}

void GameScene::menuButton(CCObject *)
{
	HistoryLogger::getInstance()->addRecord("null", this->_tmp2, "");
	ScriptReader::getInstance()->jumpToSign(this->_tmp);
	this->_menu->removeFromParent();
	_currentOptions.clear();
	_optionsNumber = 0;
}