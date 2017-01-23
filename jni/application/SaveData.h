#pragma once
#include "cocos2d.h"
#include "GameSystem.h"

USING_NS_CC;

class SaveData : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
	/*基本信息*/
	std::string _imageFile;	//存档截图路径
	int _number;	//存档序号
	std::string _text;	//存档信息
	std::string _other;	//备注信息
	std::string _date;	//存档时间

	cocos2d::CCSprite* _dataImage;	//截图
	cocos2d::CCLabelTTF* _dataText;	//文本层
	cocos2d::CCLabelTTF* _dataDate;	//时间

	cocos2d::CCSprite* _stageLayer;	//储存底层
public:
	SaveData(int number, std::string imageFile, std::string text, std::string date);
	SaveData(int number);
	~SaveData();
	void setOther();	//设置备注信息
	static SaveData* create(int i);	//创建一个SaveData按钮
	
	//void (*onTouchEnded)(int);
	void (cocos2d::CCObject::*onTouchEnded)(int);
	cocos2d::CCObject *onTouchEndedObj;

	void updataData();	//刷新按钮数据
	cocos2d::CCSprite* getStageLayer();

	//触碰事件
	//http://blog.csdn.net/xuguangsoft/article/details/8777418
    virtual void onEnter();
    virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	cocos2d::CCSprite *touchImage;
};

