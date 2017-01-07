#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "cocos2d.h"
#include "EasyButton.h"

USING_NS_CC;

class RadioButton : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
	std::vector<EasyButton*>* _radios;	//��ѡ��ť��
	int _selectedNumber;	//��ǰѡ�еİ�ť�±�
	int _tmpSelectedNumber;	//��ʱ
	EasyButton* _selectedButton;	//��ǰ��ѡ�еİ�ť
	EasyButton* _tmpSelectedButton;	//��ʱ���汻ѡ�еİ�ť
#if 0
	EventListenerTouchOneByOne* _eventTouch;	//�����¼�
#endif
public:
	RadioButton();
	~RadioButton();
	static RadioButton* createRadioButton(EasyButton* i, ...);
	void (cocos2d::CCObject::*touchEvent)();
	cocos2d::CCObject *touchEventObj;

	virtual void onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent, bool flag);

	int getSelectedNumber();	//����ѡ��ť�±�
	void setSelectedNumber(int selectedNumber);	//����Ĭ�ϱ�ѡ�еİ�ť

	//http://blog.csdn.net/xuguangsoft/article/details/8777418
    virtual void onEnter();
    virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};

#endif