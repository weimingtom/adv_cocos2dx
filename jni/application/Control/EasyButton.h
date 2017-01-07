#ifndef EASYBUTTON_H
#define EASYBUTTON_H

#include "cocos2d.h"

USING_NS_CC;
/*
���Ǽ򻯰��Button��Ϊ����ϵ�ѡ��ť�����Ƶİ�ť��
*/
class EasyButton : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
	cocos2d::CCSprite* _normal;	//��ͨ״̬��ͼƬ
	cocos2d::CCSprite* _touch;		//����״̬��ͼƬ
	cocos2d::CCSprite* _selected;	//ѡ��״̬��ͼƬ
	//http://blog.csdn.net/xiebaochun/article/details/23281619
	//EventListenerTouchOneByOne* _eventTouch;	//�����¼�
public:
	EasyButton(cocos2d::CCSprite* _normalSprite, cocos2d::CCSprite* _touchSprite, cocos2d::CCSprite* _selectedSprite);
	~EasyButton();
	static EasyButton* createEasyButton(const std::string &_normalFile);
	static EasyButton* createEasyButton(const std::string &_normalFile, const std::string &_touchFile);
	static EasyButton* createEasyButton(const std::string &_normalFile, const std::string &_touchFile, const std::string &_selectedFile);

	//Touch *t, Event *e
	virtual void onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent, bool flag);

	void setEventTouchEnabled(bool flag);	//���ü���������
	cocos2d::CCSprite* getNormal();	//������ͨ״̬�ľ���

	//std::function<void()> touchEvent;	//�����¼�����ָ��
	void (cocos2d::CCObject::*touchEvent)(); //�����¼�����ָ��
	cocos2d::CCObject *touchEventObj;
	//std::function<void(int i)> touchEventWithInt;	//��int�����Ĵ����¼�����ָ��

	//http://blog.csdn.net/xuguangsoft/article/details/8777418
    virtual void onEnter();
    virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};

#endif