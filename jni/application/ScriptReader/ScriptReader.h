#pragma once
#include "cocos2d.h"
//#include "CharactorManager.h"

/*
ScriptReaderʹ�õ���ģʽ���
��Ҫ�����ǶԽű����ж�ȡ������
*/

USING_NS_CC;
struct Charactor;


enum ScriptCommandType
{
	PartSign,	//�����ǩ
	CharactorSpeak,	//��ɫ����
	Select,	//ѡ��֧
	SelectOption,	//ѡ��֧ѡ��
	Leave,	//��ɫ�볡
	Set,	//��ֵ�޸�
	GameOver,	//��Ϸ����
	Jump,	//������Ծ
	Background,	//��ʾ����
	PlayBGM,	//��������
	StopBGM,	//ֹͣ����
	PlaySd,		//������Ч
	StopSd,		//ֹͣ��Ч
	If			//�ж�
};

class ScriptReader
{
	/*
	�ű����� ����
	*/
	class ScriptCommand;

	class SCCharactorSpeak;	//���ֶԻ�

	class SCLeave;	//�����볡 

	class SCJump;	//��ǩ��ת

	class SCSelect;	//ѡ���֧

	class SCBackground;	//��ʾ����

	class SCPlayBGM;	//��������

	class SCStopBGM;	//ֹͣ����

	class SCPlaySound;	//������Ч

	class SCStopSound;	//ֹͣ��Ч

	class SCSet;		//��ֵ�޸�

	class SCIf;			//�����ж�

	std::map<std::string, std::vector<ScriptCommand*>*> _scripts;	//���� �����ǩ�Ͷ�Ӧ�ű��б�
	/*
	��ʷ��¼ <sign,index>�洢�ĸ��½ڣ�ִ�е��ĸ�λ�á�
	��Ӧ�߼�δ����
	*/
	std::map<std::string, int> _record;

	std::string _currentSignName;	//��ǰ�½�����
	int _currentCommandIndex;	//�ű���¼

	static ScriptReader* _instance;	//ʵ��

public:
	ScriptReader();
	~ScriptReader();

	static ScriptReader* getInstance();	//��ȡʵ��
	static void destoryInstance();	//����ʵ��

	cocos2d::CCSprite* charSprites[5];//���������ɫ��0��1���У�2�У�3���У�4��
	cocos2d::CCLayer* charStage;	//�洢����Ĳ�

	Charactor** chars[5];	//���������ɫ��0��1���У�2�У�3���У�4��
	int* charNumber; //��ǰ��ʾ��������

	bool isWaitingForSelection;	//�Ƿ�ȴ�ѡ��֧�С�����ѡ��˵���ʱ��Ӧ����ѡ���������ű�
	

	cocos2d::CCNode* stage;	//���Ƴ���Node

	bool nextPositionIsLeft;	//��һ����ɫ��ʾλ���жϡ�
	
	void initWithStage(cocos2d::CCNode* stage);	//��ʼ������

	void (CCObject::*showText) (std::string &text);	//��ʾ�ı��ص�
	CCObject *showTextObj;
	void (CCObject::*showName) (std::string &text);	//��ʾ���ƻص�
	CCObject *showNameObj;
	void (CCObject::*changeBackground) (std::string &background);	//�л�����ͼƬ
	CCObject *changeBackgroundObj;
	void (CCObject::*playBackgroundMusic) (std::string &file);		//���ű�������
	CCObject *playBackgroundMusicObj;
	void (CCObject::*stopBackgroundMusic) ();						//ֹͣ��������
	CCObject *stopBackgroundMusicObj;
	void (CCObject::*playSound) (std::string &file);				//������Ч
	CCObject *playSoundObj;
	void (CCObject::*stopSound) ();								//ֹͣ��Ч
	CCObject *stopSoundObj;
	void (CCObject::*showCharator) (std::string &cName, std::string &face);	//��ʾ����
	CCObject *showCharatorObj;
	void (CCObject::*hideCharator) (std::string &name);	//��������
	CCObject *hideCharatorObj;
	void (CCObject::*showSelect) (std::map<std::string, std::string>&);	//��ʾѡ��
	CCObject *showSelectObj;

	void loadScriptFile(std::string path);	//����ű�����
	void clearScript();	//����ű�����
	void jumpToSign(const std::string &sign);	//�½ڽű���ת
	void jumpToSign(const std::string &sign, int index);

	void nextScript();	//ִ����һ���ű�

	std::string getCurrentSignName();
	int getCurrentCommandIndex();
	void setCurrentCommandIndex(int value);
};

