#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define CM CharactorManager::getInstance()

//立绘位置
enum PositionType
{
	EMPTY,	//没有位置
	LEFT,	//左边
	LEFT_CENTER,	//左中
	CENTER,	//中间
	RIGHT_CENTER,	//右中
	RIGHT
};

/*
角色信息
*/
struct Charactor
{
	std::string key;	//角色key
	std::string name;	//角色名
	cocos2d::ccColor3B color;	//对白颜色（暂时不使用）
	//待补充……
	std::map<std::string, std::string>* fgList;	//立绘列表
	int favor;	//好感度（暂时不使用）
	int hate;	//仇恨度（暂时不使用）

	cocos2d::CCSprite* faceSprite;	//当前显示中的精灵，考虑到角色入场和离场所使用的存储的变量。
	std::string currentFace;	//当前显示的立绘
	bool positionIsLeft;	//显示的位置
	PositionType currentPosition;	//当前显示的位置

	Charactor()
		:name("NoName")
		, color(cocos2d::ccBLACK)
		//待补充……
		, fgList(NULL)
		, favor(0)
		, hate(0)
		, faceSprite(NULL)
		, currentFace("")
	{}

	const char* getCharactorFace(std::string &face)	//根据face值获取角色表情
	{
		CCLOG("CM> result.first = %s", face.c_str());
		std::map<std::string, std::string>::iterator result = fgList->find(face);
		if (result != fgList->end())
		{
			CCLOG("CM> result.second = %s", result->second.c_str());
			return result->second.c_str();
		}
		else
		{
			return NULL;
		}
	}

	//FIXME:fg position
	void moveTo(PositionType pt)
	{
		int Distance;	//立绘移动的位置
		//auto actionTo = MoveTo::create(1, Point(Distance, 0));
		switch (pt)
		{
		case LEFT:
		{
			//faceSprite->setPositionX(320);
			Distance = 125/*320*/;
			faceSprite->runAction(cocos2d::CCMoveTo::create(0.3f, cocos2d::CCPoint(Distance, 0)));
			break;
		}
		case LEFT_CENTER:
		{
			//faceSprite->setPositionX(427);
			Distance = 197/*427*/;
			CCLOG("name = %s", name.c_str());
			faceSprite->runAction(cocos2d::CCMoveTo::create(0.3f, cocos2d::CCPoint(Distance, 0)));
			break;
		}
		case CENTER:
		{
			//faceSprite->setPositionX(640);
			Distance = 250/*640*/;
			faceSprite->runAction(cocos2d::CCMoveTo::create(0.3f, cocos2d::CCPoint(Distance, 0)));
			break;
		}
		case RIGHT_CENTER:
		{
			//faceSprite->setPositionX(853);
			Distance = 322/*853*/;
			faceSprite->runAction(cocos2d::CCMoveTo::create(0.3f, cocos2d::CCPoint(Distance, 0)));
			break;
		}
		case RIGHT:
		{
			//faceSprite->setPositionX(960);
			Distance = 375/*960*/;
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
角色管理类。
管理角色数据。
通过getInstance获取Managet实例
不使用时，需要调用destoryInstance进行销毁
*/
class CharactorManager
{
	static CharactorManager* _instance;

	CharactorManager();
	~CharactorManager();
	
	std::map<std::string, Charactor*> *_pool;	//配置文件列表。<角色key，角色对象>

	Charactor *defaultCharactor;	//脚本出现的角色未定义则使用默认角色
public:
	static CharactorManager* getInstance();
	static void destoryInstance();

	Charactor* getCharactor(std::string &key);	//根据Key值获取角色对象

	void addCharactor(std::string &key, Charactor* cha);	//存储角色信息
};

