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



GameSystem* GameSystem::_instance = nullptr;

GameSystem::GameSystem()
{
	if (!cocos2d::UserDefault::getInstance()->getBoolForKey(ISINIT))	//�ж��Ƿ��ʼ����
	{
		setDefault();
	}
	_isLoadSuccess = false;
	_savedata = new std::map<std::string, int>[100];
	_gameSceneInfo = nullptr;
	//��ʼ���浵�б�
	_savedataList = new GameSaveData[MAX_SAVEDATA_NUMBER];
	createSavedata();
	initGameSavedataList();
	_gameScene = nullptr;
}


GameSystem::~GameSystem()
{
	delete _savedata;
	if (_gameSceneInfo)
	{
		delete _gameSceneInfo;
		_gameSceneInfo = nullptr;
	}
	delete _savedataList;
	if (_screenShoot) _screenShoot->release();
	if (_gameScene)
	{
		//delete _gameScene;
		_gameScene = nullptr;
	}
}

GameSystem* GameSystem::getInstance()
{
	if (_instance == nullptr)
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
		_instance = nullptr;
	}
}
void GameSystem::setDefault()
{
	setSystemVolume(DEFAULT_SYSTEMVOLUME);
	setMusicVolume(DEFAULT_MUSICVOLUME);
	setSoundVolume(DEFAULT_SOUNDVOLUME);
	setTextSpeed(DEFAULT_TEXTSPEED);
	setAutoSpeed(DEFAULT_AUTOSPEED);
	cocos2d::UserDefault::getInstance()->setBoolForKey(ISINIT, true);
}

void GameSystem::setSystemVolume(float value)
{
	cocos2d::UserDefault::getInstance()->setFloatForKey(SYSTEMVOLUME, value);
}

void GameSystem::setMusicVolume(float value)
{
	cocos2d::UserDefault::getInstance()->setFloatForKey(MUSICVOLUME, value);
}

void GameSystem::setSoundVolume(float value)
{
	cocos2d::UserDefault::getInstance()->setFloatForKey(SOUNDVOLUME, value);
}

void GameSystem::setTextSpeed(float value)
{
	cocos2d::UserDefault::getInstance()->setFloatForKey(TEXTSPEED, value);
}

void GameSystem::setAutoSpeed(float value)
{
	cocos2d::UserDefault::getInstance()->setFloatForKey(AUTOSPEED, value);
}



float GameSystem::getSystemVolume()
{
	return cocos2d::UserDefault::getInstance()->getFloatForKey(SYSTEMVOLUME);
}

float GameSystem::getMusicVolume()
{
	return cocos2d::UserDefault::getInstance()->getFloatForKey(MUSICVOLUME);
}

float GameSystem::getSoundVolume()
{
	return cocos2d::UserDefault::getInstance()->getFloatForKey(SOUNDVOLUME);
}

float GameSystem::getTextSpeed()
{
	return cocos2d::UserDefault::getInstance()->getFloatForKey(TEXTSPEED);
}

float GameSystem::getAutoSpeed()
{
	return cocos2d::UserDefault::getInstance()->getFloatForKey(AUTOSPEED);
}

void GameSystem::setDataValue(std::string &key, int value)
{
	auto result = _savedata[0].find(key);
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
	auto result = _savedata[0].find(key);
	if (result != _savedata[0].end())
	{
		// cocos2d::log("GS> key = %s , value = %d", key.c_str(), result->second);
		return result->second;
	}
	else
	{
		return 0;
	}
}

void GameSystem::setData(std::map<std::string, int> *map)// = nullptr)
{
	if (map == nullptr)
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
	cocos2d::UserDefault::getInstance()->setBoolForKey(ch, value);
}

bool GameSystem::getSavedata(int i)
{
	char* ch = new char[4];
	itoa(i, ch, 10);
	return cocos2d::UserDefault::getInstance()->getBoolForKey(ch);
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
		_gameSceneInfo = nullptr;
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
	sprintf(file, "%s%s%s%s", FileUtils::getInstance()->getWritablePath().c_str(), path, ch, ".sav");
	char image[100];
	sprintf(image, "%s%d.jpg", path, i+1);
	cocos2d::log("Savedata file path = %s",file);
	cocos2d::log("Savedata image path = %s", image);
	FILE* savedata = fopen(file,"wb");
	if (savedata)
	{
		/*����浵��Ϣ*/
		/*--�����ͼ·��*/
		bool result = _screenShoot->saveToFile(image, false, [&](RenderTexture *r, const  std::string &s){ });
		if (result)
		{
			char tmp[100];
			sprintf(tmp, "%s%s", FileUtils::getInstance()->getWritablePath().c_str(), image);
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
			for (auto itr = _gameSceneInfo->options.begin(); itr != _gameSceneInfo->options.end(); itr++)
			{
				fwrite(itr->first.c_str(), sizeof(char), strlen(itr->first.c_str()), savedata);
				fputs("\r\n", savedata);
				fwrite(itr->second.c_str(), sizeof(char), strlen(itr->second.c_str()), savedata);
				fputs("\r\n", savedata);
			}
		}
		/*���浱ǰScriptReader��ǩ*/
		auto sign = ScriptReader::getInstance()->getCurrentSignName();
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
		cocos2d::log("savedata file error.");
	}
	savedata = NULL;
 }

void GameSystem::initGameSavedataList()
{
	//��¼cocos2d-x��CCFileUtils������û���ҵ��ļ��Ƿ񵯳���ʾ�������
	bool isNeedModifyPopupSetting = FileUtils::sharedFileUtils()->isPopupNotify();
	//�������ʾ������ʱ�رգ���Ϊ����Ķ�ȡ�����Ҳ������ļ�����Ϊ���ļ��п��ܻ�û�д���
	if (isNeedModifyPopupSetting)
	{
		FileUtils::sharedFileUtils()->setPopupNotify(false);
	}

	for (int i = 0; i < MAX_SAVEDATA_NUMBER; i++)
	{
		updateGameSavedata(i);
	}

	//�����ǰ�����Ҳ����ļ�����ʾ����Ļ�ԭ��������
	if (isNeedModifyPopupSetting)
	{
		FileUtils::sharedFileUtils()->setPopupNotify(true);
	}
}

GameSaveData* GameSystem::getGameSavedata(int i)
{
	if (_savedataList[i].date.compare("") == 0)
		return nullptr;
	else
		return &_savedataList[i];
}

void GameSystem::createSavedata()
{
	//���û�����Ŀ¼��
	std::string path = FileUtils::getInstance()->getWritablePath();
	//����savedata�ļ���
	path += "savedata";
	//log("path=%s", pathToSave.c_str());

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
	if ((GetFileAttributesA(path.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(path.c_str(), 0);
	}
#endif
	log("savadata created.");
}

void GameSystem::setScreenShoot(RenderTexture* render)
{
	_screenShoot = render;
}

RenderTexture* GameSystem::getScreenShoot()
{
	return _screenShoot;
}

void GameSystem::updateGameSavedata(int i)
{
	char path[] = "savedata/savedata";
	char ch[4];
	sprintf(ch, "%d", i+1);
	char file[100];
	sprintf(file, "%s%s%s%s", FileUtils::getInstance()->getWritablePath().c_str(), path, ch, ".sav");

	std::string data = FileUtils::getInstance()->getStringFromFile(file);
	if (data.compare("") != 0)
	{
		int sPos = 0;	//��ͷ
		int ePos = 0;	//��β
		std::string temp;	//��ʱ����һ����Ϣ
		/*��ȡ�浵��ͼ·��*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		Director::getInstance()->getTextureCache()->reloadTexture(temp);
		//cocos2d::log(temp.c_str());
		_savedataList[i].imageFile = temp;
		sPos = ePos + 1;
		/*��ȡ�浵ʱ��*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//cocos2d::log(temp.c_str());
		_savedataList[i].date = temp;
		sPos = ePos + 1;
		/*��ȡ�浵�ı�*/
		ePos = data.find('\n', sPos);
		temp = data.substr(sPos, ePos - sPos - 1);
		//cocos2d::log(temp.c_str());
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
	sprintf(file, "%s%s%s%s", FileUtils::getInstance()->getWritablePath().c_str(), path, ch, ".sav");
	std::string data = FileUtils::getInstance()->getStringFromFile(file);
	if (_gameSceneInfo)	//ɾ������Ϣ
	{
		//delete _gameSceneInfo;
		_gameSceneInfo = nullptr;
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
		for (int j = 0; j < _gameSceneInfo->charactorCount; j++)
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
		for (int j = 0; j < _gameSceneInfo->optionsNumber; j++)
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

		log("Load done.");
		return true;
	}
	else
	{
		log("%s not found", file);
		return false;
	}
}

void GameSystem::setGameScene(Scene* scene)
{
	_gameScene = scene;
}

Scene* GameSystem::getGameScene()
{
	return _gameScene;
}