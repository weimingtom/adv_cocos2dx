#pragma once
#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;

class LoadScene : public cocos2d::CCLayer
{
	SaveData* dataButtons[8];
public:
	LoadScene();
	~LoadScene();
	static cocos2d::CCScene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadScene);
	void back(CCObject *);	//·µ»Ø
	void load(int i);	//¶Áµµ
};

