#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define BM BackgroundManager::getInstance()

class BackgroundManager
{
	BackgroundManager();
	~BackgroundManager();
	static BackgroundManager* _instance;	//����������ʵ��

	std::map<std::string, std::string> *_pool;	//�����ļ��б�<����key�������ļ�>

	std::string defaultBackground;	//�ű����ֵĽ�ɫδ������ʹ��Ĭ�ϳ���
public:
	static BackgroundManager* getInstance();	//��ȡ����������ʵ��
	static void destoryInstance();

	std::string getBackground(std::string key);	//����Keyֵ��ȡ����

	void addBackground(std::string key, std::string background);	//�洢������Ϣ
};

