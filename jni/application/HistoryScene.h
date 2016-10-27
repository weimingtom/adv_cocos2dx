#pragma once
#include "cocos2d.h"
#include "History.hpp"
USING_NS_CC;

class HistoryMessage : public cocos2d::CCNode
{
	cocos2d::CCLabelTTF* _nameLabel;	//名字
	cocos2d::CCLabelTTF* _textLabel;	//文字
	cocos2d::CCSprite* _voice;	//语音（暂留）
public:
	HistoryMessage(std::string text, std::string name, cocos2d::ccColor4B color);
	~HistoryMessage();
	static HistoryMessage* create(record* record);	//创建一条历史信息
};

class HistoryScene : public cocos2d::CCLayer
{
	int pointPositionY;
public:
	HistoryScene();
	~HistoryScene();

	static cocos2d::CCScene* createScene();

	virtual bool init();

	CREATE_FUNC(HistoryScene);

	void back();
};

