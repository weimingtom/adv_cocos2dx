#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define BMM BackgroundMusicManager::getInstance()

class BackgroundMusicManager
{
	BackgroundMusicManager();
	~BackgroundMusicManager();
	static BackgroundMusicManager* _instance;

	std::map<std::string, std::string> *_pool;	//�����ļ��б�<����key�������ļ�>

	std::string defaultBackgroundMusic;	//�ű�ָ��������δ������ʹ��Ĭ������
public:
	static BackgroundMusicManager* getInstance();
	static void destoryInstance();

	std::string getBackgroundMusic(std::string key);	//����Keyֵ��ȡ����

	void addBackgroundMusic(std::string key, std::string bgm);	//�洢������Ϣ
};