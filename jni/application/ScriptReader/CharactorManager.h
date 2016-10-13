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
	Color3B color;	//�԰���ɫ����ʱ��ʹ�ã�
	//�����䡭��
	std::map<std::string, char*>* fgList;	//�����б�
	int favor;	//�øжȣ���ʱ��ʹ�ã�
	int hate;	//��޶ȣ���ʱ��ʹ�ã�

	Sprite* faceSprite;	//��ǰ��ʾ�еľ��飬���ǵ���ɫ�볡���볡��ʹ�õĴ洢�ı�����
	std::string currentFace;	//��ǰ��ʾ������
	bool positionIsLeft;	//��ʾ��λ��
	PositionType currentPosition;	//��ǰ��ʾ��λ��

	Charactor()
		:name("NoName")
		, color(Color3B::BLACK)
		//�����䡭��
		, fgList(nullptr)
		, favor(0)
		, hate(0)
		, faceSprite(nullptr)
		, currentFace("")
	{}

	char* getCharactorFace(std::string &face)	//����faceֵ��ȡ��ɫ����
	{
		log("CM> result.first = %s", face.c_str());
		auto result = fgList->find(face);
		if (result != fgList->end())
		{
			log("CM> result.second = %s", result->second);
			return result->second;
		}
		else
		{
			return nullptr;
		}
	}

	void moveTo(PositionType pt)
	{
		int Distance;	//�����ƶ���λ��
		//auto actionTo = MoveTo::create(1, Point(Distance, 0));
		switch (pt)
		{
		case PositionType::LEFT:
		{
			//faceSprite->setPositionX(320);
			Distance = 320;
			faceSprite->runAction(MoveTo::create(0.3f, Point(Distance, 0)));
			break;
		}
		case PositionType::LEFT_CENTER:
		{
			//faceSprite->setPositionX(427);
			Distance = 427;
			log("name = %s", name.c_str());
			faceSprite->runAction(MoveTo::create(0.3f, Point(Distance, 0)));
			break;
		}
		case PositionType::CENTER:
		{
			//faceSprite->setPositionX(640);
			Distance = 640;
			faceSprite->runAction(MoveTo::create(0.3f, Point(Distance, 0)));
			break;
		}
		case PositionType::RIGHT_CENTER:
		{
			//faceSprite->setPositionX(853);
			Distance = 853;
			faceSprite->runAction(MoveTo::create(0.3f, Point(Distance, 0)));
			break;
		}
		case PositionType::RIGHT:
		{
			//faceSprite->setPositionX(960);
			Distance = 960;
			faceSprite->runAction(MoveTo::create(0.3f, Point(Distance, 0)));
			break;
		}
		default:
		{
			log("[Error]CM> Unknow PositionType.");
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
			faceSprite=nullptr;
			currentFace = "";
			currentPosition = PositionType::EMPTY;
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

