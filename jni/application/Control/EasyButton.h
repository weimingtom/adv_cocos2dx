#ifndef EASYBUTTON_H
#define EASYBUTTON_H

#include "cocos2d.h"

USING_NS_CC;
/*
这是简化版的Button，为了配合单选按钮组而设计的按钮。
*/
class EasyButton : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
	cocos2d::CCSprite* _normal;	//普通状态的图片
	cocos2d::CCSprite* _touch;		//触碰状态的图片
	cocos2d::CCSprite* _selected;	//选择状态的图片
	//http://blog.csdn.net/xiebaochun/article/details/23281619
	//EventListenerTouchOneByOne* _eventTouch;	//触碰事件
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

	void setEventTouchEnabled(bool flag);	//设置监听器开关
	cocos2d::CCSprite* getNormal();	//返回普通状态的精灵

	//std::function<void()> touchEvent;	//触碰事件方法指针
	void (cocos2d::CCObject::*touchEvent)(); //触碰事件方法指针
	cocos2d::CCObject *touchEventObj;
	//std::function<void(int i)> touchEventWithInt;	//带int参数的触碰事件方法指针

	//http://blog.csdn.net/xuguangsoft/article/details/8777418
    virtual void onEnter();
    virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};

#endif