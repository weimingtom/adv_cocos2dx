#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "cocos2d.h"
#include "EasyButton.h"

USING_NS_CC;

class RadioButton : public cocos2d::CCNode
{
	std::vector<EasyButton*>* _radios;	//单选按钮组
	int _selectedNumber;	//当前选中的按钮下标
	int _tmpSelectedNumber;	//临时
	EasyButton* _selectedButton;	//当前被选中的按钮
	EasyButton* _tmpSelectedButton;	//临时储存被选中的按钮
#if 0
	EventListenerTouchOneByOne* _eventTouch;	//触碰事件
#endif
public:
	RadioButton();
	~RadioButton();
	static RadioButton* createRadioButton(EasyButton* i, ...);
	void (cocos2d::CCObject::*touchEvent)();
	cocos2d::CCObject *touchEventObj;

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	int getSelectedNumber();	//返回选择按钮下标
	void setSelectedNumber(int selectedNumber);	//设置默认被选中的按钮
};

#endif