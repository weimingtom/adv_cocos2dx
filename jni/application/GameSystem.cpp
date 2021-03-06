#include "GameSystem.h"
//#include "cocos2d\cocos\base\CCUserDefault.h"
#include "cocos2d.h"
#include <stdlib.h>
#include "ScriptReader\ScriptReader.h"

#define DEFAULT_SYSTEMVOLUME 1.0f
#define DEFAULT_MUSICVOLUME 1.0f
#define DEFAULT_SOUNDVOLUME 1.0f
#define DEFAULT_TEXTSPEED 1.0f
#define DEFAULT_AUTOSPEED 1.0f
#define MAX_SAVEDATA_NUMBER 100

#define ISINIT "isInitialization"	//初始化标记



GameSystem* GameSystem::_instance = NULL;

GameSystem::GameSystem()
{
	if (!cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey(ISINIT))	//判断是否初始化过
	{
		setDefault();
	}
	_isLoadSuccess = false;
	_savedata = new std::map<std::string, int>[100];
	_gameSceneInfo = NULL;
	//初始化存档列表
	_savedataList = new GameSaveData[MAX_SAVEDATA_NUMBER];
	createSavedata();
	initGameSavedataList();
	_gameScene = NULL;
}


GameSystem::~GameSystem()
{
	delete _savedata;
	if (_gameSceneInfo)
	{
		delete _gameSceneInfo;
		_gameSceneInfo = NULL;
	}
	delete _savedataList;
	if (_screenShoot) _screenShoot->release();
	if (_gameScene)
	{
		//delete _gameScene;
		_gameScene = NULL;
	}
}

GameSystem* GameSystem::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new GameSystem();
	}
	return _instance;
}

void GameSystem::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = NULL;
	}
}
void GameSystem::setDefault()
{
	setSystemVolume(DEFAULT_SYSTEMVOLUME);
	setMusicVolume(DEFAULT_MUSICVOLUME);
	setSoundVolume(DEFAULT_SOUNDVOLUME);
	setTextSpeed(DEFAULT_TEXTSPEED);
	setAutoSpeed(DEFAULT_AUTOSPEED);
	cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey(ISINIT, true);
}

void GameSystem::setSystemVolume(float value)
{
	cocos2d::CCUserDefault::sharedUserDefault()->setFloatForKey(SYSTEMVOLUME, value);
}

void GameSystem::setMusicVolume(float value)
{
	cocos2d::CCUserDefault::sharedUserDefault()->setFloatForKey(MUSICVOLUME, value);
}

void GameSystem::setSoundVolume(float value)
{
	cocos2d::CCUserDefault::sharedUserDefault()->setFloatForKey(SOUNDVOLUME, value);
}

void GameSystem::setTextSpeed(float value)
{
	cocos2d::CCUserDefault::sharedUserDefault()->setFloatForKey(TEXTSPEED, value);
}

void GameSystem::setAutoSpeed(float value)
{
	cocos2d::CCUserDefault::sharedUserDefault()->setFloatForKey(AUTOSPEED, value);
}



float GameSystem::getSystemVolume()
{
	return cocos2d::CCUserDefault::sharedUserDefault()->getFloatForKey(SYSTEMVOLUME);
}

float GameSystem::getMusicVolume()
{
	return cocos2d::CCUserDefault::sharedUserDefault()->getFloatForKey(MUSICVOLUME);
}

float GameSystem::getSoundVolume()
{
	return cocos2d::CCUserDefault::sharedUserDefault()->getFloatForKey(SOUNDVOLUME);
}

float GameSystem::getTextSpeed()
{
	return cocos2d::CCUserDefault::sharedUserDefault()->getFloatForKey(TEXTSPEED);
}

float GameSystem::getAutoSpeed()
{
	return cocos2d::CCUserDefault::sharedUserDefault()->getFloatForKey(AUTOSPEED);
}

void GameSystem::setDataValue(std::string &key, int value)
{
	std::map<std::string, int>::iterator result = _savedata[0].find(key);
	if (result != _savedata[0].end())
	{
		result->second = value;
	}
	else
	{
		_savedata[0].insert(std::pair<std::string, int>(key, value));
	}
}

int GameSystem::getDataValue(std::string &key)
{
	std::map<std::string, int>::iterator result = _savedata[0].find(key);
	if (result != _savedata[0].end())
	{
		// CCLOG("GS> key = %s , value = %d", key.c_str(), result->second);
		return result->second;
	}
	else
	{
		return 0;
	}
}

void GameSystem::setData(std::map<std::string, int> *map)// = NULL)
{
	if (map == NULL)
	{
		if (!(_savedata[0].empty())) _savedata[0].clear();
	}
	else
	{
		_savedata[0] = *map;
	}
}

void GameSystem::setSavedata(int i, bool value)
{
	char* ch = new char[4];
	itoa(i, ch, 10);
	cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey(ch, value);
}

bool GameSystem::getSavedata(int i)
{
	char* ch = new char[4];
	itoa(i, ch, 10);
	return cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey(ch);
}

GameData* GameSystem::getGameSceneInfo()
{
	return _gameSceneInfo;
}

void GameSystem::setGameSceneInfo(GameData* gameData)
{
	if (_gameSceneInfo)
	{
		delete _gameSceneInfo;
		_gameSceneInfo = NULL;
	}
	_gameSceneInfo = gameData;
}

void GameSystem::setIsLoadSuccess(bool value)
{
	_isLoadSuccess = value;
}

bool GameSystem::getIsLoadSuccess()
{
	return _isLoadSuccess;
}

void GameSystem::saveGameSceneInfo(int i)
{
	setSavedata(i, true);
	/*将信息保存到savedata对应的file*/
	char path[] = "savedata/savedata";
	char ch[3];
	sprintf(ch, "%d", i+1);
	char file[100];
	sprintf(file, "%s%s%s%s", cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), path, ch, ".sav");
	char image[100];
	sprintf(image, "%s%d.jpg", path, i+1);
	CCLOG("Savedata file path = %s",file);
	CCLOG("Savedata image path = %s", image);
	FILE* savedata = fopen(file,"wb");
	if (savedata)
	{
		/*保存存档信息*/
		/*--储存截图路径*/
#if 0
		bool result = _screenShoot->saveToFile(image, false, [&](RenderTexture *r, const  std::string &s){ });
#else
		bool result = _screenShoot->saveToFile(image);
#endif
		if (result)
		{
			char tmp[100];
			sprintf(tmp, "%s%s", cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), image);
			fwrite(tmp, sizeof(char), strlen(tmp), savedata);
		}
		fputs("\r\n", savedata);
		/*--储存时间*/
		time_t t;
		time(&t);
		char tmp[64];
		strftime(tmp, sizeof(tmp), "%Y-%m-%d %X", localtime((&t)));
		fwrite(tmp, sizeof(char), strlen(tmp), savedata);
		fputs("\r\n", savedata);
		/*保存当前对白*/
		fwrite(_gameSceneInfo->currentText.c_str(), sizeof(char), strlen(_gameSceneInfo->currentText.c_str()), savedata);
		fputs("\r\n", savedata);
		/*保存当前名字*/
		fwrite(_gameSceneInfo->currentName.c_str(), sizeof(char), strlen(_gameSceneInfo->currentName.c_str()), savedata);
		fputs("\r\n", savedata);
		/*保存当前背景key*/
		fwrite(_gameSceneInfo->backgroundKey.c_str(), sizeof(char), strlen(_gameSceneInfo->backgroundKey.c_str()), savedata);
		fputs("\r\n", savedata);	//换行
		/*保存当前立绘数量*/
		char cCharactorCount[2];
		sprintf(cCharactorCount, "%d", _gameSceneInfo->charactorCount);
		fwrite(cCharactorCount, sizeof(char), strlen(cCharactorCount), savedata);
		fputs("\r\n", savedata);
		/*保存当前立绘信息*/
		for (int j = 0; j < _gameSceneInfo->charactorCount; j++)
		{	
			/*保存角色key*/
			fwrite(_gameSceneInfo->fgCharactors[j].name.c_str(), sizeof(char), strlen(_gameSceneInfo->fgCharactors[j].name.c_str()), savedata);
			fputs("\r\n", savedata);
			/*保存角色表情*/
			fwrite(_gameSceneInfo->fgCharactors[j].face.c_str(), sizeof(char), strlen(_gameSceneInfo->fgCharactors[j].face.c_str()), savedata);
			fputs("\r\n", savedata);
			/*保存角色位置*/
			char num[2];
			sprintf(num, "%d", _gameSceneInfo->fgCharactors[j].number);
			fwrite(num, sizeof(char), strlen(num), savedata);
			fputs("\r\n", savedata);
		}
		/*保存当前BGM信息*/
		fwrite(_gameSceneInfo->bgmKey.c_str(), sizeof(char), strlen(_gameSceneInfo->bgmKey.c_str()), savedata);
		fputs("\r\n", savedata);
		/*保存当前sound信息*/
		//fwrite(_gameSceneInfo->bgmKey.c_str(), sizeof(char), strlen(_gameSceneInfo->bgmKey.c_str()), savedata);
		//fputs("\r\n", savedata);
		/*保存当前选项*/
		char num[2];
		sprintf(num, "%d", _gameSceneInfo->optionsNumber);
		fwrite(num, sizeof(char), strlen(num), savedata);
		fputs("\r\n", savedata);
		if (_gameSceneInfo->optionsNumber)
		{
			for (std::map<std::string, std::string>::iterator itr = _gameSceneInfo->options.begin(); itr != _gameSceneInfo->options.end(); itr++)
			{
				fwrite(itr->first.c_str(), sizeof(char), strlen(itr->first.c_str()), savedata);
				fputs("\r\n", savedata);
				fwrite(itr->second.c_str(), sizeof(char), strlen(itr->second.c_str()), savedata);
				fputs("\r\n", savedata);
			}
		}
		/*保存当前ScriptReader标签*/
		std::string sign = ScriptReader::getInstance()->getCurrentSignName();
		fwrite(sign.c_str(), sizeof(char), strlen(sign.c_str()), savedata);
		fputs("\r\n", savedata);
		/*保存当前的CommandIndex*/
		auto commandIndex = ScriptReader::getInstance()->getCurrentCommandIndex();
		char sCommandIndex[4];
		sprintf(sCommandIndex, "%d", commandIndex);
		fwrite(sCommandIndex, sizeof(char), strlen(sCommandIndex), savedata);
		fputs("\r\n", savedata);
		fclose(savedata);

		
		
	}
	else
	{
		CCLOG("savedata file error.");
	}
	savedata = NULL;
 }

void GameSystem::initGameSavedataList()
{
	//记录cocos2d-x中CCFileUtils，对于没有找到文件是否弹出提示框的设置
	bool isNeedModifyPopupSetting = cocos2d::CCFileUtils::sharedFileUtils()->isPopupNotify();
	//如果有提示，就暂时关闭，因为这里的读取可能找不到该文件，因为该文件有可能还没有创建
	if (isNeedModifyPopupSetting)
	{
		cocos2d::CCFileUtils::sharedFileUtils()->setPopupNotify(false);
	}

	for (int i = 0; i < MAX_SAVEDATA_NUMBER; i++)
	{
		updateGameSavedata(i);
	}

	//如果以前设置找不到文件有提示，则改回原来的设置
	if (isNeedModifyPopupSetting)
	{
		cocos2d::CCFileUtils::sharedFileUtils()->setPopupNotify(true);
	}
}

GameSaveData* GameSystem::getGameSavedata(int i)
{
	if (_savedataList[i].date.compare("") == 0)
		return NULL;
	else
		return &_savedataList[i];
}

void GameSystem::createSavedata()
{
	//绑定用户储存目录下
	std::string path = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	//创建savedata文件夹
	path += "savedata";
	//CCLOG("path=%s", pathToSave.c_str());

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	DIR *pDir = NULL;
	//打开该路径
	pDir = opendir(path.c_str());
	if (!pDir)
	{
		//创建该路径
		mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	}
#else

#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif	// INVALID_FILE_ATTRIBUTES

	if ((GetFileAttributesA(path.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(path.c_str(), 0);
	}
#endif
	CCLOG("savadata created.");
}

void GameSystem::setScreenShoot(cocos2d::CCRenderTexture* render)
{
	_screenShoot = render;
}

cocos2d::CCRenderTexture* GameSystem::getScreenShoot()
{
	return _screenShoot;
}

void GameSystem::updateGameSavedata(int i)
{
	char path[] = "savedata/savedata";
	char ch[4];
	sprintf(ch, "%d", i+1);
	char file[100];
	sprintf(file, "%s%s%s%s", cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), path, ch, ".sav");

	//std::string data = cocos2d::CCFileUtils::sharedFileUtils()->getStringFromFile(file);
	std::string strFullPathString = CCFileUtils::sharedFileUtils()->fullPathForFilename(file);
	const char *strFullPath = strFullPathString.c_str();
	FILE *fp = fopen(strFullPath, "wb");
	std::string data = "";
	if (fp != NULL)
	{
		fclose(fp);
		CCString *contents = CCString::createWithContentsOfFile(strFullPath);
		if (!contents)
		{
			data = contents->getCString();
		}
	}
	if (data.compare("") != 0)
	{
		int sPos = 0;	//行头
		int ePos = 0;	//行尾
		std::string temp;	//临时储存一行信息
		/*读取存档截图路径*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		cocos2d::CCTextureCache::sharedTextureCache()->reloadTexture(temp.c_str());
		//CCLOG(temp.c_str());
		_savedataList[i].imageFile = temp;
		sPos = ePos + 1;
		/*读取存档时间*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//CCLOG(temp.c_str());
		_savedataList[i].date = temp;
		sPos = ePos + 1;
		/*读取存档文本*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//CCLOG(temp.c_str());
		_savedataList[i].text = temp;
		sPos = ePos + 1;
	}
}

bool GameSystem::loadGameSceneInfo(int i)
{
	char path[] = "savedata/savedata";
	char ch[4];
	sprintf(ch, "%d", i + 1);
	char file[100];
	sprintf(file, "%s%s%s%s", cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath().c_str(), path, ch, ".sav");
	//std::string data = cocos2d::CCFileUtils::sharedFileUtils()->getStringFromFile(file);
	std::string data = CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(file).c_str())->getCString();
	if (_gameSceneInfo)	//删掉旧信息
	{
		//delete _gameSceneInfo;
		_gameSceneInfo = NULL;
	}
	_gameSceneInfo = new GameData;
	if (data.compare("") != 0)
	{
		int sPos = 0;	//行头
		int ePos = 0;	//行尾
		std::string temp;	//临时储存一行信息
		/*丢弃读取存档截图路径*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//_savedataList[i].imageFile = temp;
		sPos = ePos + 1;
		/*丢弃读取存档时间*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//_savedataList[i].date = temp;
		sPos = ePos + 1;
		/*丢弃读取存档文本*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		_gameSceneInfo->currentText = temp;
		sPos = ePos + 1;
		/*读取当前名字*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->currentName = temp;
		/*读取当前背景key*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->backgroundKey = temp;
		/*读取当前立绘数量*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->charactorCount = atoi(temp.c_str());

		/*读取当前立绘信息*/
		int j;
		for (/*int*/ j = 0; j < _gameSceneInfo->charactorCount; j++)
		{
			/*读取角色key*/
			ePos = data.find('\n', sPos);
			temp = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			_gameSceneInfo->fgCharactors[j].name = temp;
			/*读取角色表情*/
			ePos = data.find('\n', sPos);
			temp = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			_gameSceneInfo->fgCharactors[j].face = temp;
			/*读取角色位置*/
			ePos = data.find('\n', sPos);
			temp = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1; 
			_gameSceneInfo->fgCharactors[j].number = atoi(temp.c_str());
		}
		/*读取当前BGM信息*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->bgmKey = temp;
		/*读取当前sound信息*/

		/*读取当前选项信息*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->optionsNumber = atoi(temp.c_str());
		for (/*int*/ j = 0; j < _gameSceneInfo->optionsNumber; j++)
		{
			std::string sign;
			std::string text;
			ePos = data.find('\n', sPos);
			sign = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			ePos = data.find('\n', sPos);
			text = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			_gameSceneInfo->options.insert(std::pair<std::string, std::string>(sign, text));
		}
		/*读取当前sign信息*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->currentSignName = temp;
		/*读取当前commandIndex信息*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->currentCommandIndex = atoi(temp.c_str());

		CCLOG("Load done.");
		return true;
	}
	else
	{
		CCLOG("%s not found", file);
		return false;
	}
}

void GameSystem::setGameScene(cocos2d::CCScene* scene)
{
	_gameScene = scene;
}

cocos2d::CCScene* GameSystem::getGameScene()
{
	return _gameScene;
}