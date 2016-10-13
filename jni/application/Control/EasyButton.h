#ifndef EASYBUTTON_H
#define EASYBUTTON_H

#include "cocos2d.h"

USING_NS_CC;
/*
���Ǽ򻯰��Button��Ϊ����ϵ�ѡ��ť�����Ƶİ�ť��
*/
class EasyButton : public cocos2d::CCNode
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
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void setEventTouchEnabled(bool flag);	//���ü���������
	cocos2d::CCSprite* getNormal();	//������ͨ״̬�ľ���

	//std::function<void()> touchEvent;	//�����¼�����ָ��
	void (*touchEvent)();	//�����¼�����ָ��
	//std::function<void(int i)> touchEventWithInt;	//��int�����Ĵ����¼�����ָ��
};

#endif