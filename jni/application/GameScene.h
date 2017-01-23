#pragma once
#include "ScriptReader/ScriptReader.h"
#include "cocos2d.h"
#include "CharLabel.h"
#include "ScriptReader/CharactorManager.h"

#define MAX_CHARACTOR_NUMBER 5

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
		this->setTouchEnabled(false); //FIXME:
		this->setTouchMode(kCCTouchesOneByOne); //kCCTouchesOneByOne->ccTouchBegan,kCCTouchAllAtOnce->ccTouchesBegan
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



	//�����¼�
	//http://blog.csdn.net/xuguangsoft/article/details/8777418
#if 1
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
	{
		if (onTouchEndedObj != NULL)
		{
			(onTouchEndedObj->*onTouchEnded)();
			return true;
		}
		return false;
	}

	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
	{

	}

	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
	{

	}

	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
	{

	}


#endif

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

	//�����¼�
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
	cocos2d::CCLabelTTF* _label;//�ı�����ı���
	//ScriptReader* _reader;	//�ű�������

	cocos2d::CCLabelTTF* _nameLabel;	//������
	CharLabel* _textLabel;	//�԰׿�
	/*cocos2d::CCLayer*/StageLayer *stageLayer;
	/*cocos2d::CCSprite*/DialogSprite* _dialogWindow;	//�ı��򱳾�
	cocos2d::CCLayer* _backgroundLayer;	//������
	cocos2d::CCSprite* _backgroundSprite;	//����ͼƬ
	cocos2d::CCLayer* _charactorsLayer;	//�����
	cocos2d::CCLayer* _selectLayer;	//ѡ���

	Charactor* _chars[MAX_CHARACTOR_NUMBER];	//���浱ǰ��������
	Charactor* _emptyChar;	//�ս�ɫ
	int _charNumber;	//������������

	bool _isPlayingMusic;	//���ֲ���״̬

	std::string _backgroundKey;	//��ǰ����
	std::string _backgroundMusicKey;	//��ǰ��������
	std::string _soundKey;	//��ǰ��Ч
	std::string _currentText;	//��ǰ�ı�
	std::string _currentName;	//��ǰ����
	std::map<std::string, std::string> _currentOptions;	//��ǰѡ��
	int _optionsNumber;	//��ǰѡ������

public:
	GameScene();
	~GameScene();
	
	static cocos2d::CCScene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void update(float dt);

	void updateLabel(std::string text);

	void showName(std::string &name);	//������

	void showText(std::string &text);	//��ʾ�ı�

	void showClickSign();	//�������ͼ��

	void screenClicked();	//��Ļ����¼������˰�ť���Ի���

	void dialogClicked();	//��ʾ��һ��Ի�

	void changeBackground(std::string &key);	//�л�����

	void playBackgroundMusic(std::string &key);	//��������
	void stopBackgroundMusic();						//ֹͣ����
	void scheduleVolumeFadeIn();	//���ֵ���
	void scheduleVolumeFadeOut();	//���ֵ���

	void playSound(std::string &file);	//������Ч
	void stopSound();					//ֹͣ��Ч

	void startAutoPlay(CCObject *);	//��ʼ�Զ�ǰ��
	void stopAutoPlay();	//ֹͣ�Զ�ǰ��
	void autoPlay(float dt);	//�Զ�ǰ��

	void displayCharator(std::string &cName, std::string &face);
	void unDisplayCharator(std::string &cName);

	void createGameDate();

	void showSaveScene(CCObject *);	//����浵����
	void showLoadScene(CCObject *);	//�����������
	void showHistoryScene(CCObject *);	//������ʷ��¼����

	void ScreenShoot();	//����

	void clear();	//�����Ļ�����ж���
	void reloadScene();	//���س�����ͨ��������

	void showSelect(std::map<std::string, std::string> &options);	//��ʾѡ��


	void menuButton(CCObject *);
	cocos2d::CCMenu* _menu;
	std::string _tmp;
	std::string _tmp2;


	//Added
	void afterChangeBackground(CCNode *node, void *data);
	void afterUnDisplayCharator(CCNode *node, void *data);
};

