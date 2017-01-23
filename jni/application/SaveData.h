#pragma once
#include "cocos2d.h"
#include "GameSystem.h"

USING_NS_CC;

class SaveData : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
	/*������Ϣ*/
	std::string _imageFile;	//�浵��ͼ·��
	int _number;	//�浵���
	std::string _text;	//�浵��Ϣ
	std::string _other;	//��ע��Ϣ
	std::string _date;	//�浵ʱ��

	cocos2d::CCSprite* _dataImage;	//��ͼ
	cocos2d::CCLabelTTF* _dataText;	//�ı���
	cocos2d::CCLabelTTF* _dataDate;	//ʱ��

	cocos2d::CCSprite* _stageLayer;	//����ײ�
public:
	SaveData(int number, std::string imageFile, std::string text, std::string date);
	SaveData(int number);
	~SaveData();
	void setOther();	//���ñ�ע��Ϣ
	static SaveData* create(int i);	//����һ��SaveData��ť
	
	//void (*onTouchEnded)(int);
	void (cocos2d::CCObject::*onTouchEnded)(int);
	cocos2d::CCObject *onTouchEndedObj;

	void updataData();	//ˢ�°�ť����
	cocos2d::CCSprite* getStageLayer();

	//�����¼�
	//http://blog.csdn.net/xuguangsoft/article/details/8777418
    virtual void onEnter();
    virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	cocos2d::CCSprite *touchImage;
};

