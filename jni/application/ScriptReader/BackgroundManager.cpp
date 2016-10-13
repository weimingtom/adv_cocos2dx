#include "BackgroundManager.h"

//�ű��ļ�·��
#define BGLISTPATH "/bgimage/bgList.txt"

BackgroundManager* BackgroundManager::_instance = nullptr;

BackgroundManager::BackgroundManager()
	:_pool(nullptr)
{
	_pool = new std::map<std::string, std::string>();	//��������

	defaultBackground = "";	//�趨Ĭ�ϵı���Ϊ�յ�ַ

	std::string ss = FileUtils::getInstance()->getStringFromFile(BGLISTPATH);	//��ȡ�ļ�

	int sPos = 0;	//��ͷ
	int ePos = 0;	//��β
	//Ԥ�ȶ�ȡһ�в��������BOMͷ
	ePos = ss.find('\n', sPos);
	sPos = ePos + 1;

	/*��ʼ����*/
	while (1)
	{
		std::string key;	//��ʱ���泡����
		std::string background;	//���汳��
		std::string temp;	//��ʱ����һ����Ϣ

		/*��ȡһ����Ϣ*/
		ePos = ss.find('\n', sPos);
		temp = ss.substr(sPos, ePos - sPos - 1);
		if (temp.compare("") == 0)	//����ǿյľ����ļ�β��
		{
			break;
		}
		sPos = ePos + 1;

		/*��ȡ�������ļ������Զ���ȫ·��*/
		int tempPos = temp.find_first_of(',', 0);
		key = temp.substr(0, tempPos);
		background = temp.substr(tempPos + 1, temp.length() - tempPos - 1);
		background = "/bgimage/" + background;

		//log("bgkey = %s , backgroundPath = %s", key.c_str(), background.c_str());

		/*��ӽ���������*/
		addBackground(key, background);
		log("SCB> addBackground[%s]", key.c_str());
	}
}


BackgroundManager::~BackgroundManager()
{
	if (_pool)
	{
		_pool->clear();
		delete _pool;
		_pool = nullptr;
	}
}


void BackgroundManager::addBackground(std::string key, std::string background)
{
	_pool->insert(std::pair<std::string, std::string>(key,background));
}

std::string BackgroundManager::getBackground(std::string key)
{
	auto result = _pool->find(key);
	if (result != _pool->end())
	{
		return result->second;
	}
	else
	{
		log("BM> Unfind &s", key);
		defaultBackground = "/bgimage/Black.jpg";
		return defaultBackground;
	}
}

BackgroundManager* BackgroundManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new BackgroundManager();
	}
	return _instance;
}

void BackgroundManager::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}