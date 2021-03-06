#pragma once
#include "ScriptReader/ScriptReader.h"
#include "cocos2d.h"
#include "CharLabel.h"
#include "ScriptReader/CharactorManager.h"

#define MAX_CHARACTOR_NUMBER 5

#define USE_STAGELAYER_TOUCH_ENABLE 0

class StageLayer : public cocos2d::CCLayer
{
public:
	StageLayer() {}
	virtual ~StageLayer(){}

	virtual bool init()
	{
		if (!this->CCLayer::init())
		{
			return false;
		}
		//FIXME:crash here
#if USE_STAGELAYER_TOUCH_ENABLE
		this->setTouchPriority(-128); //FIXME:???must setTouchPriority, or crash !!!
		this->setTouchEnabled(true); //FIXME:
		this->setTouchMode(kCCTouchesOneByOne); //kCCTouchesOneByOne->ccTouchBegan,kCCTouchAllAtOnce->ccTouchesBegan
#endif
		return true;
	}

	//CREATE_FUNC(StageLayer);
	static StageLayer* create()
	{
		StageLayer *pRet = new StageLayer();
		if (pRet && pRet->init())
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(pRet);
		}
    
		return pRet;
	}

	//触碰事件
	//http://blog.csdn.net/xuguangsoft/article/details/8777418
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
	{
		if (onTouchEndedObj != NULL)
		{
			CCLOG("StageLayer ccTouchBegan");
			(onTouchEndedObj->*onTouchEnded)();
			return true;
		}
		return false;
	}
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){}
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){}
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){}
public:
	void (cocos2d::CCObject::*onTouchEnded)();
	cocos2d::CCObject *onTouchEndedObj;
};

class DialogSprite : public cocos2d::CCSprite, public cocos2d::CCTargetedTouchDelegate
{
public:
	DialogSprite() {}
	virtual ~DialogSprite(){}

	static DialogSprite* create(const char *pszFileName)
	{
		DialogSprite *pobSprite = new DialogSprite();
		if (pobSprite && pobSprite->initWithFile(pszFileName))
		{
			pobSprite->autorelease();
			return pobSprite;
		}
		CC_SAFE_DELETE(pobSprite);
		return NULL;
	}

	virtual void onEnter()  
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);  
		CCSprite::onEnter();  
	}

	virtual void onExit()  
	{  
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
		CCSprite::onExit();  
	}  

	//触碰事件
	//http://blog.csdn.net/xuguangsoft/article/details/8777418
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
	{
		if (this->boundingBox().containsPoint(this->convertTouchToNodeSpace(pTouch)))
		{
			if (onTouchEndedObj != NULL)
			{
				(onTouchEndedObj->*onTouchEnded)();
				return true;
			}
		}
		return false;
	}

public:
	void (cocos2d::CCObject::*onTouchEnded)();
	cocos2d::CCObject *onTouchEndedObj;
};


class GameScene : public cocos2d::CCLayer
{
	cocos2d::CCLabelTTF* _label;//文本框的文本层
	//ScriptReader* _reader;	//脚本解析器

	cocos2d::CCLabelTTF* _nameLabel;	//姓名框
	CharLabel* _textLabel;	//对白框
	/*cocos2d::CCLayer*/StageLayer *stageLayer;
	/*cocos2d::CCSprite*/DialogSprite* _dialogWindow;	//文本框背景
	cocos2d::CCLayer* _backgroundLayer;	//背景层
	cocos2d::CCSprite* _backgroundSprite;	//背景图片
	cocos2d::CCLayer* _charactorsLayer;	//立绘层
	cocos2d::CCLayer* _selectLayer;	//选项层

	Charactor* _chars[MAX_CHARACTOR_NUMBER];	//储存当前立绘资料
	Charactor* _emptyChar;	//空角色
	int _charNumber;	//储存立绘数量

	bool _isPlayingMusic;	//音乐播放状态

	std::string _backgroundKey;	//当前背景
	std::string _backgroundMusicKey;	//当前背景音乐
	std::string _soundKey;	//当前音效
	std::string _currentText;	//当前文本
	std::string _currentName;	//当前姓名
	std::map<std::string, std::string> _currentOptions;	//当前选项
	int _optionsNumber;	//当前选项数量

public:
	GameScene();
	~GameScene();
	
	static cocos2d::CCScene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void update(float dt);

	void updateLabel(std::string text);

	void showName(std::string &name);	//姓名框

	void showText(std::string &text);	//显示文本

	void showClickSign();	//点击继续图标

	void screenClicked();	//屏幕点击事件，除了按钮、对话框

	void dialogClicked();	//显示下一句对话

	void changeBackground(std::string &key);	//切换场景

	void playBackgroundMusic(std::string &key);	//播放音乐
	void stopBackgroundMusic();						//停止音乐
	void scheduleVolumeFadeIn();	//音乐淡入
	void scheduleVolumeFadeOut();	//音乐淡出

	void playSound(std::string &file);	//播放音效
	void stopSound();					//停止音效

	void startAutoPlay(CCObject *);	//开始自动前进
	void stopAutoPlay();	//停止自动前进
	void autoPlay(float dt);	//自动前进

	void displayCharator(std::string &cName, std::string &face);
	void unDisplayCharator(std::string &cName);

	void createGameDate();

	void showSaveScene(CCObject *);	//进入存档界面
	void showLoadScene(CCObject *);	//进入读档界面
	void showHistoryScene(CCObject *);	//进入历史记录界面

	void ScreenShoot();	//截屏

	void clear();	//清楚屏幕的所有东西
	void reloadScene();	//重载场景，通常读档用

	void showSelect(std::map<std::string, std::string> &options);	//显示选项


	void menuButton(CCObject *);
	cocos2d::CCMenu* _menu;
	std::string _tmp;
	std::string _tmp2;


	//Added
	void afterChangeBackground(CCNode *node, void *data);
	void afterUnDisplayCharator(CCNode *node, void *data);
};

