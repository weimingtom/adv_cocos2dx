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

	Sprite* charSprites[5];//���������ɫ��0��1���У�2�У�3���У�4��
	Layer* charStage;	//�洢����Ĳ�

	Charactor** chars[5];	//���������ɫ��0��1���У�2�У�3���У�4��
	int* charNumber; //��ǰ��ʾ��������

	bool isWaitingForSelection;	//�Ƿ�ȴ�ѡ��֧�С�����ѡ��˵���ʱ��Ӧ����ѡ���������ű�
	

	Node* stage;	//���Ƴ���Node

	bool nextPositionIsLeft;	//��һ����ɫ��ʾλ���жϡ�
	
	void initWithStage(Node* stage);	//��ʼ������

	std::function<void(std::string &text)> showText;	//��ʾ�ı��ص�
	std::function<void(std::string &text)> showName;	//��ʾ���ƻص�
	std::function<void(std::string &background)> changeBackground;	//�л�����ͼƬ
	std::function<void(std::string &file)> playBackgroundMusic;		//���ű�������
	std::function<void()> stopBackgroundMusic;						//ֹͣ��������
	std::function<void(std::string &file)> playSound;				//������Ч
	std::function<void()> stopSound;								//ֹͣ��Ч
	std::function<void(std::string &cName, std::string &face)> showCharator;	//��ʾ����
	std::function<void(std::string &name)> hideCharator;	//��������
	std::function<void(std::map<std::string, std::string>)> showSelect;	//��ʾѡ��

	void loadScriptFile(std::string path);	//����ű�����
	void clearScript();	//����ű�����
	void jumpToSign(const std::string &sign);	//�½ڽű���ת
	void jumpToSign(const std::string &sign, int index);

	void nextScript();	//ִ����һ���ű�

	std::string getCurrentSignName();
	int getCurrentCommandIndex();
	void setCurrentCommandIndex(int value);
};

