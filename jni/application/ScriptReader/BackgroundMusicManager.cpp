#include "BackgroundMusicManager.h"

#define BGMLISTPATH "/bgm/bgmList.txt"

BackgroundMusicManager* BackgroundMusicManager::_instance = NULL;

BackgroundMusicManager::BackgroundMusicManager()
	:_pool(NULL)
{
	_pool = new std::map<std::string, std::string>();

	defaultBackgroundMusic = "";

	//std::string ss = FileUtils::getInstance()->getStringFromFile(BGMLISTPATH);
	std::string ss = CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(BGMLISTPATH).c_str())->getCString();

	int sPos = 0;
	int ePos = 0;
	//预先读取一行不处理，解决BOM头
	ePos = ss.find('\n', sPos);
	sPos = ePos + 1;

	while (1)
	{
		std::string key;
		std::string background;
		std::string temp;
		ePos = ss.find('\n', sPos);
		temp = ss.substr(sPos, ePos - sPos - 1);
		if (temp.compare("") == 0)
		{
			//CCLOG("BMM> Load Background ending");
			break;
		}
		sPos = ePos + 1;

		int tempPos = temp.find_first_of(',', 0);
		key = temp.substr(0, tempPos);
		background = temp.substr(tempPos + 1, temp.length() - tempPos - 1);
		background = "/bgm/" + background + ".mp3";

		//CCLOG("bgmkey = %s , backgroundmusicPath = %s", key.c_str(), background.c_str());

		addBackgroundMusic(key, background);
		//CCLOG("BMM> addBackground[%s]", key.c_str());
	}
}


BackgroundMusicManager::~BackgroundMusicManager()
{
	if (_pool)
	{
		_pool->clear();
		delete _pool;
		_pool = NULL;
	}
}


void BackgroundMusicManager::addBackgroundMusic(std::string key, std::string background)
{
	_pool->insert(std::pair<std::string, std::string>(key, background));
}

std::string BackgroundMusicManager::getBackgroundMusic(std::string key)
{
	typedef std::map<std::string, std::string> MAP;
	MAP::iterator result = _pool->find(key);
	if (result != _pool->end())
	{
		return result->second;
	}
	else
	{
		CCLOG("BMM> Unfind &s", key);
		defaultBackgroundMusic = "";
		return defaultBackgroundMusic;
	}
}

BackgroundMusicManager* BackgroundMusicManager::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new BackgroundMusicManager();
		//CCLOG("BMM> instance starting...");
	}
	return _instance;
}

void BackgroundMusicManager::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = NULL;
	}
}