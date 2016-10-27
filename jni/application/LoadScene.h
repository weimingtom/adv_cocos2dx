#pragma once
#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;

class LoadScene : public cocos2d::CCLayer
{
	SaveData* dataButtons[8];
#if 0
	EventListenerTouchOneByOne* eventTouch[8];
#endif
public:
	LoadScene();
	~LoadScene();

	static cocos2d::CCScene* createScene();

	virtual bool init();

	CREATE_FUNC(LoadScene);

	void back();	//·µ»Ø

	void load(int i);	//¶Áµµ
};

