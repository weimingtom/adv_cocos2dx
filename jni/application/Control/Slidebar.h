#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include "cocos2d.h"

USING_NS_CC;

class Slidebar : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
	cocos2d::CCSprite* _background;
	cocos2d::CCSprite* _point;
	float _maxValue;
	float _minValue;
	float* _targetValue;
	float _pointPositionX;
	float _maxWidth;
	float _change;	//滑动条改变的倍率
	float _floatValue;	//浮点参数，被改变的值
public:
	Slidebar(cocos2d::CCSprite* backgroundSprite, cocos2d::CCSprite* pointSprite);
	~Slidebar();
	static Slidebar* createSlidebar(std::string backgroundFile, std::string pointFile);
	void setLinkValue(int &value);
	void setMaxValue(float value);
	void setMinValue(float value);
	void valueChange();
	void setMaxWidth(float value);//设置滑块最大移动范围（半径）
	void setTargetValue(float *value);
	void changeTargetValue(float change);
	float getChange();	//获取滑动条改变的倍率
	void setSlidebar();	//自动设置滑块位置
	void setFloat(float value);	
	float getFloat();

	void (cocos2d::CCObject::*touchEvent) ();	//触碰事件
	CCObject *touchEventObj;
	void (cocos2d::CCObject::*moveEvent) ();	//移动事件
	CCObject *moveEventObj;

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