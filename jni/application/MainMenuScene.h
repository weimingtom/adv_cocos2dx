#pragma once

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
	MainMenu();
	~MainMenu();

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainMenu);

	void test();

	void menuExit(Ref* pSender);

	void newgame();	//��������Ϸ
	void config();	//��Ϸ����
	void load();	//��ȡ�浵

};

