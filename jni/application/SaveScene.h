#pragma once
#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;

class SaveScene : public cocos2d::CCLayer
{
	SaveData* dataButtons[8];
#if 0
	EventListenerTouchOneByOne* eventTouch[8];
#endif
public:
	SaveScene();
	~SaveScene();

	static cocos2d::CCScene* createScene();

	virtual bool init();

	CREATE_FUNC(SaveScene);

	void back();	//����

	void save(int i);	//�浵
};

