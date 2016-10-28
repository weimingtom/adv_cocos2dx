#pragma once

#include "cocos2d.h"

class MainMenu : public cocos2d::CCLayer
{
public:
	MainMenu();
	~MainMenu();

	static cocos2d::CCScene* createScene();

	virtual bool init();

	CREATE_FUNC(MainMenu);

	void test();

	void menuExit(cocos2d::CCObject* pSender);

	void newgame(cocos2d::CCObject *);	//��������Ϸ
	void config(cocos2d::CCObject *);	//��Ϸ����
	void load(cocos2d::CCObject *);	//��ȡ�浵

};

