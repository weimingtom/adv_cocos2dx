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

#define ISINIT "isInitialization"	//��ʼ�����



GameSystem* GameSystem::_instance = NULL;

GameSystem::GameSystem()
{
	if (!cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey(ISINIT))	//�ж��Ƿ��ʼ����
	{
		setDefault();
	}
	_isLoadSuccess = false;
	_savedata = new std::map<std::string, int>[100];
	_gameSceneInfo = NULL;
	//��ʼ���浵�б�
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
	/*����Ϣ���浽savedata��Ӧ��file*/
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
		/*����浵��Ϣ*/
		/*--�����ͼ·��*/
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
		/*--����ʱ��*/
		time_t t;
		time(&t);
		char tmp[64];
		strftime(tmp, sizeof(tmp), "%Y-%m-%d %X", localtime((&t)));
		fwrite(tmp, sizeof(char), strlen(tmp), savedata);
		fputs("\r\n", savedata);
		/*���浱ǰ�԰�*/
		fwrite(_gameSceneInfo->currentText.c_str(), sizeof(char), strlen(_gameSceneInfo->currentText.c_str()), savedata);
		fputs("\r\n", savedata);
		/*���浱ǰ����*/
		fwrite(_gameSceneInfo->currentName.c_str(), sizeof(char), strlen(_gameSceneInfo->currentName.c_str()), savedata);
		fputs("\r\n", savedata);
		/*���浱ǰ����key*/
		fwrite(_gameSceneInfo->backgroundKey.c_str(), sizeof(char), strlen(_gameSceneInfo->backgroundKey.c_str()), savedata);
		fputs("\r\n", savedata);	//����
		/*���浱ǰ��������*/
		char cCharactorCount[2];
		sprintf(cCharactorCount, "%d", _gameSceneInfo->charactorCount);
		fwrite(cCharactorCount, sizeof(char), strlen(cCharactorCount), savedata);
		fputs("\r\n", savedata);
		/*���浱ǰ������Ϣ*/
		for (int j = 0; j < _gameSceneInfo->charactorCount; j++)
		{	
			/*�����ɫkey*/
			fwrite(_gameSceneInfo->fgCharactors[j].name.c_str(), sizeof(char), strlen(_gameSceneInfo->fgCharactors[j].name.c_str()), savedata);
			fputs("\r\n", savedata);
			/*�����ɫ����*/
			fwrite(_gameSceneInfo->fgCharactors[j].face.c_str(), sizeof(char), strlen(_gameSceneInfo->fgCharactors[j].face.c_str()), savedata);
			fputs("\r\n", savedata);
			/*�����ɫλ��*/
			char num[2];
			sprintf(num, "%d", _gameSceneInfo->fgCharactors[j].number);
			fwrite(num, sizeof(char), strlen(num), savedata);
			fputs("\r\n", savedata);
		}
		/*���浱ǰBGM��Ϣ*/
		fwrite(_gameSceneInfo->bgmKey.c_str(), sizeof(char), strlen(_gameSceneInfo->bgmKey.c_str()), savedata);
		fputs("\r\n", savedata);
		/*���浱ǰsound��Ϣ*/
		//fwrite(_gameSceneInfo->bgmKey.c_str(), sizeof(char), strlen(_gameSceneInfo->bgmKey.c_str()), savedata);
		//fputs("\r\n", savedata);
		/*���浱ǰѡ��*/
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
		/*���浱ǰScriptReader��ǩ*/
		std::string sign = ScriptReader::getInstance()->getCurrentSignName();
		fwrite(sign.c_str(), sizeof(char), strlen(sign.c_str()), savedata);
		fputs("\r\n", savedata);
		/*���浱ǰ��CommandIndex*/
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
	//��¼cocos2d-x��CCFileUtils������û���ҵ��ļ��Ƿ񵯳���ʾ�������
	bool isNeedModifyPopupSetting = cocos2d::CCFileUtils::sharedFileUtils()->isPopupNotify();
	//�������ʾ������ʱ�رգ���Ϊ����Ķ�ȡ�����Ҳ������ļ�����Ϊ���ļ��п��ܻ�û�д���
	if (isNeedModifyPopupSetting)
	{
		cocos2d::CCFileUtils::sharedFileUtils()->setPopupNotify(false);
	}

	for (int i = 0; i < MAX_SAVEDATA_NUMBER; i++)
	{
		updateGameSavedata(i);
	}

	//�����ǰ�����Ҳ����ļ�����ʾ����Ļ�ԭ��������
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
	//���û�����Ŀ¼��
	std::string path = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
	//����savedata�ļ���
	path += "savedata";
	//CCLOG("path=%s", pathToSave.c_str());

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	DIR *pDir = NULL;
	//�򿪸�·��
	pDir = opendir(path.c_str());
	if (!pDir)
	{
		//������·��
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
		int sPos = 0;	//��ͷ
		int ePos = 0;	//��β
		std::string temp;	//��ʱ����һ����Ϣ
		/*��ȡ�浵��ͼ·��*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		cocos2d::CCTextureCache::sharedTextureCache()->reloadTexture(temp.c_str());
		//CCLOG(temp.c_str());
		_savedataList[i].imageFile = temp;
		sPos = ePos + 1;
		/*��ȡ�浵ʱ��*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//CCLOG(temp.c_str());
		_savedataList[i].date = temp;
		sPos = ePos + 1;
		/*��ȡ�浵�ı�*/
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
	if (_gameSceneInfo)	//ɾ������Ϣ
	{
		//delete _gameSceneInfo;
		_gameSceneInfo = NULL;
	}
	_gameSceneInfo = new GameData;
	if (data.compare("") != 0)
	{
		int sPos = 0;	//��ͷ
		int ePos = 0;	//��β
		std::string temp;	//��ʱ����һ����Ϣ
		/*������ȡ�浵��ͼ·��*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//_savedataList[i].imageFile = temp;
		sPos = ePos + 1;
		/*������ȡ�浵ʱ��*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//_savedataList[i].date = temp;
		sPos = ePos + 1;
		/*������ȡ�浵�ı�*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		_gameSceneInfo->currentText = temp;
		sPos = ePos + 1;
		/*��ȡ��ǰ����*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->currentName = temp;
		/*��ȡ��ǰ����key*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->backgroundKey = temp;
		/*��ȡ��ǰ��������*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->charactorCount = atoi(temp.c_str());

		/*��ȡ��ǰ������Ϣ*/
		int j;
		for (/*int*/ j = 0; j < _gameSceneInfo->charactorCount; j++)
		{
			/*��ȡ��ɫkey*/
			ePos = data.find('\n', sPos);
			temp = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			_gameSceneInfo->fgCharactors[j].name = temp;
			/*��ȡ��ɫ����*/
			ePos = data.find('\n', sPos);
			temp = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
			_gameSceneInfo->fgCharactors[j].face = temp;
			/*��ȡ��ɫλ��*/
			ePos = data.find('\n', sPos);
			temp = data.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1; 
			_gameSceneInfo->fgCharactors[j].number = atoi(temp.c_str());
		}
		/*��ȡ��ǰBGM��Ϣ*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->bgmKey = temp;
		/*��ȡ��ǰsound��Ϣ*/

		/*��ȡ��ǰѡ����Ϣ*/
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
		/*��ȡ��ǰsign��Ϣ*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		sPos = ePos + 1;
		_gameSceneInfo->currentSignName = temp;
		/*��ȡ��ǰcommandIndex��Ϣ*/
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