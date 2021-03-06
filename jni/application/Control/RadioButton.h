#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "cocos2d.h"
#include "EasyButton.h"

USING_NS_CC;

class RadioButton : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
	std::vector<EasyButton*>* _radios;	//单选按钮组
	int _selectedNumber;	//当前选中的按钮下标
	int _tmpSelectedNumber;	//临时
	EasyButton* _selectedButton;	//当前被选中的按钮
	EasyButton* _tmpSelectedButton;	//临时储存被选中的按钮
public:
	RadioButton();
	~RadioButton();
	static RadioButton* createRadioButton(EasyButton* i, ...);
	void (cocos2d::CCObject::*touchEvent)();
	cocos2d::CCObject *touchEventObj;

	virtual void onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent, bool flag);

	int getSelectedNumber();	//返回选择按钮下标
	void setSelectedNumber(int selectedNumber);	//设置默认被选中的按钮

	//触碰事件
	//http://blog.csdn.net/xuguangsoft/article/details/8777418
    virtual void onEnter();
    virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};

#endif