#include "CharactorManager.h"
#define charactorPath "/charactor/charactorList.txt"

CharactorManager* CharactorManager::_instance = NULL;

CharactorManager::CharactorManager()
	:_pool(NULL)
	, defaultCharactor(NULL)
{
	_pool = new std::map<std::string, Charactor*>();

	defaultCharactor = new Charactor();

	//Load datas

	//std::string ss = FileUtils::getInstance()->getStringFromFile(charactorPath);
	std::string ss = CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(charactorPath).c_str())->getCString();

	int sPos = 0;
	int ePos = 0;
	//预先读取一行不处理，解决BOM头
	ePos = ss.find('\n', sPos);
	sPos = ePos + 1;
	
	while (1)
	{
		Charactor *tempCharactor = new Charactor();
		std::string key;
		std::string name;
		ePos = ss.find('\n', sPos);
		key = ss.substr(sPos, ePos - sPos - 1);
		if (key.compare("") == 0)
		{
			break;
		}
		sPos = ePos + 1;
		ePos = ss.find('\n', sPos);
		name = ss.substr(sPos, ePos - sPos - 1);
		tempCharactor->name = name;
		sPos = ePos + 1;
		tempCharactor->fgList = new std::map<std::string, std::string>();
		while (1)
		{
			std::string temp;
			ePos = ss.find('\n', sPos);
			temp = ss.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			if (temp.compare("") == 0) break;
			std::string face;
			std::string facePath;
			int tempPos = temp.find_first_of(',', 0);
			face = temp.substr(0, tempPos);
			facePath = temp.substr(tempPos + 1, temp.length() - tempPos - 1);
			facePath = "/charactor/" + facePath + ".png";
			//char* tmpfacePath = new char;
			//facePath.copy(tmpfacePath,facePath.length(),0);
			//*(tmpfacePath + facePath.length()) = '\0';
			tempCharactor->fgList->insert(std::pair<std::string, std::string>(face, facePath/*tmpfacePath*/));
			CCLOG(">>>>>>insert %s, %s", face.c_str(), facePath.c_str());
		}

		/*
		//check list
		for (auto i = tempCharactor->fgList->begin(); i != tempCharactor->fgList->end(); i++)
		{
			log("%s , %s", i->first.c_str(), i->second);
		}
		*/

		addCharactor(key, tempCharactor);
		CCLOG("CM> addCharactor[%s]", tempCharactor->name.c_str());
	}
}


CharactorManager::~CharactorManager()
{
	if (_pool)
	{
		typedef std::map<std::string, Charactor*> MAP;
		for (MAP::iterator i = _pool->begin(); i != _pool->end(); i++)
		{
			delete i->second;
		}
		_pool->clear();
		delete _pool;
		_pool = NULL;
	}

	if (defaultCharactor)
	{
		delete defaultCharactor;
		defaultCharactor = NULL;
	}
}

CharactorManager* CharactorManager::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new CharactorManager();
	}
	return _instance;
}

void CharactorManager::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = NULL;
	}
}

Charactor* CharactorManager::getCharactor(std::string &key)
{
	typedef std::map<std::string, Charactor*> MAP;
	MAP::iterator result = _pool->find(key);
	if (result != _pool->end())
	{
		return result->second;
	}
	else
	{
		defaultCharactor->name = "Undefind Charactor[" + key + "]";
		return defaultCharactor;
	}
}

void CharactorManager::addCharactor(std::string &key, Charactor* cha)
{
	_pool->insert(std::pair<std::string, Charactor*>(key, cha));
}


