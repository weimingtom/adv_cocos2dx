#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define SM SoundManager::getInstance()

class SoundManager
{
	SoundManager();
	~SoundManager();
	static SoundManager* _instance;

	std::map<std::string, std::string> *_pool;	//�����ļ��б�<����key�������ļ�>

	std::string defaultSound;	//�ű�ָ��������δ������ʹ��Ĭ������
public:
	static SoundManager* getInstance();
	static void destoryInstance();

	std::string getSound(std::string key);	//����Keyֵ��ȡ����

	void addSound(std::string key, std::string sound);	//�洢������Ϣ
};