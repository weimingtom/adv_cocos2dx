#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define CM CharactorManager::getInstance()

//����λ��
enum PositionType
{
	EMPTY,	//û��λ��
	LEFT,	//���
	LEFT_CENTER,	//����
	CENTER,	//�м�
	RIGHT_CENTER,	//����
	RIGHT
};

/*
��ɫ��Ϣ
*/
struct Charactor
{
	std::string key;	//��ɫkey
	std::string name;	//��ɫ��
	cocos2d::ccColor3B color;	//�԰���ɫ����ʱ��ʹ�ã�
	//�����䡭��
	std::map<std::string, char*>* fgList;	//�����б�
	int favor;	//�øжȣ���ʱ��ʹ�ã�
	int hate;	//��޶ȣ���ʱ��ʹ�ã�

	cocos2d::CCSprite* faceSprite;	//��ǰ��ʾ�еľ��飬���ǵ���ɫ�볡���볡��ʹ�õĴ洢�ı�����
	std::string currentFace;	//��ǰ��ʾ������
	bool positionIsLeft;	//��ʾ��λ��
	PositionType currentPosition;	//��ǰ��ʾ��λ��

	Charactor()
		:name("NoName")
		, color(cocos2d::ccBLACK)
		//�����䡭��
		, fgList(NULL)
		, favor(0)
		, hate(0)
		, faceSprite(NULL)
		, currentFace("")
	{}

	char* getCharactorFace(std::string &face)	//����faceֵ��ȡ��ɫ����
	{
		CCLOG("CM> result.first = %s", face.c_str());
		std::map<std::string, char*>::iterator result = fgList->find(face);
		if (result != fgList->end())
		{
			CCLOG("CM> result.second = %s", result->second);
			return result->second;
		}
		else
		{
			return NULL;
		}
	}

	void moveTo(PositionType pt)
	{
		int Distance;	//�����ƶ���λ��
		//auto actionTo = MoveTo::create(1, Point(Distance, 0));
		switch (pt)
		{
		case LEFT:
		{
			//faceSprite->setPositionX(320);
			Distance = 320;
			faceSprite->runAction(cocos2d::CCMoveTo::create(0.3f, cocos2d::CCPoint(Distance, 0)));
			break;
		}
		case LEFT_CENTER:
		{
			//faceSprite->setPositionX(427);
			Distance = 427;
			CCLOG("name = %s", name.c_str());
			faceSprite->runAction(cocos2d::CCMoveTo::create(0.3f, cocos2d::CCPoint(Distance, 0)));
			break;
		}
		case CENTER:
		{
			//faceSprite->setPositionX(640);
			Distance = 640;
			faceSprite->runAction(cocos2d::CCMoveTo::create(0.3f, cocos2d::CCPoint(Distance, 0)));
			break;
		}
		case RIGHT_CENTER:
		{
			//faceSprite->setPositionX(853);
			Distance = 853;
			faceSprite->runAction(cocos2d::CCMoveTo::create(0.3f, cocos2d::CCPoint(Distance, 0)));
			break;
		}
		case RIGHT:
		{
			//faceSprite->setPositionX(960);
			Distance = 960;
			faceSprite->runAction(cocos2d::CCMoveTo::create(0.3f, cocos2d::CCPoint(Distance, 0)));
			break;
		}
		default:
		{
			CCLOG("[Error]CM> Unknow PositionType.");
			break;
		}
		}
		currentPosition = pt;
	}

	void leave()
	{
		if (faceSprite)
		{
			faceSprite->removeFromParent();
			faceSprite = NULL;
			currentFace = "";
			currentPosition = EMPTY;
		}
	}
};

/*
��ɫ�����ࡣ
�����ɫ���ݡ�
ͨ��getInstance��ȡManagetʵ��
��ʹ��ʱ����Ҫ����destoryInstance��������
*/
class CharactorManager
{
	static CharactorManager* _instance;

	CharactorManager();
	~CharactorManager();
	
	std::map<std::string, Charactor*> *_pool;	//�����ļ��б�<��ɫkey����ɫ����>

	Charactor *defaultCharactor;	//�ű����ֵĽ�ɫδ������ʹ��Ĭ�Ͻ�ɫ
public:
	static CharactorManager* getInstance();
	static void destoryInstance();

	Charactor* getCharactor(std::string &key);	//����Keyֵ��ȡ��ɫ����

	void addCharactor(std::string &key, Charactor* cha);	//�洢��ɫ��Ϣ
};

