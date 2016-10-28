#pragma once
#include "cocos2d.h"
#include "Control/RadioButton.h"
#include "Control/Slidebar.h"

USING_NS_CC;


class SettingScene : public cocos2d::CCLayer
{
	//��ѡ��ť��
	RadioButton* _testRadio;
	RadioButton* _isWindowRadio;	//����orȫ��
	RadioButton* _isSkipReaded;		//�Ƿ���������
	//������
	Slidebar* _musicVolumeSlidebar;	//�����������ڻ�����
	Slidebar* _soundVolumeSlidebar;	//��Ч�������ڻ�����
	Slidebar* _autoSpeedSlidebar;	//�Զ�ǰ���ٶȻ�����
	Slidebar* _skipSpeedSlidebar;	//����ǰ���ٶȻ�����
public:
	SettingScene();
	~SettingScene();

	static cocos2d::CCScene* createScene();

	virtual bool init();

	CREATE_FUNC(SettingScene);

	void back(CCObject *);	//����
	void test();	//���Է���
	void changeMusicVolume();
};

