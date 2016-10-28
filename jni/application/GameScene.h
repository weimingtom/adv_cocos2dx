#pragma once
#include "ScriptReader/ScriptReader.h"
#include "cocos2d.h"
#include "CharLabel.h"
#include "ScriptReader/CharactorManager.h"

#define MAX_CHARACTOR_NUMBER 5

class GameScene : public cocos2d::CCLayer
{
	cocos2d::CCLabelTTF* _label;//�ı�����ı���
	//ScriptReader* _reader;	//�ű�������

	cocos2d::CCLabelTTF* _nameLabel;	//������
	CharLabel* _textLabel;	//�԰׿�
	cocos2d::CCSprite* _dialogWindow;	//�ı��򱳾�
	cocos2d::CCLayer* _backgroundLayer;	//������
	cocos2d::CCSprite* _backgroundSprite;	//����ͼƬ
	cocos2d::CCLayer* _charactorsLayer;	//�����
	cocos2d::CCLayer* _selectLayer;	//ѡ���

	Charactor* _chars[MAX_CHARACTOR_NUMBER];	//���浱ǰ��������
	Charactor* _emptyChar;	//�ս�ɫ
	int _charNumber;	//������������

	bool _isPlayingMusic;	//���ֲ���״̬

	std::string _backgroundKey;	//��ǰ����
	std::string _backgroundMusicKey;	//��ǰ��������
	std::string _soundKey;	//��ǰ��Ч
	std::string _currentText;	//��ǰ�ı�
	std::string _currentName;	//��ǰ����
	std::map<std::string, std::string> _currentOptions;	//��ǰѡ��
	int _optionsNumber;	//��ǰѡ������

public:
	GameScene();
	~GameScene();
	
	static cocos2d::CCScene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void update(float dt);

	void updateLabel(std::string text);

	void showName(std::string &name);	//������

	void showText(std::string &text);	//��ʾ�ı�

	void showClickSign();	//�������ͼ��

	void screenClicked();	//��Ļ����¼������˰�ť���Ի���

	void dialogClicked();	//��ʾ��һ��Ի�

	void changeBackground(std::string &key);	//�л�����

	void playBackgroundMusic(std::string &key);	//��������
	void stopBackgroundMusic();						//ֹͣ����
	void scheduleVolumeFadeIn();	//���ֵ���
	void scheduleVolumeFadeOut();	//���ֵ���

	void playSound(std::string &file);	//������Ч
	void stopSound();					//ֹͣ��Ч

	void startAutoPlay(CCObject *);	//��ʼ�Զ�ǰ��
	void stopAutoPlay();	//ֹͣ�Զ�ǰ��
	void autoPlay(float dt);	//�Զ�ǰ��

	void displayCharator(std::string &cName, std::string &face);
	void unDisplayCharator(std::string &cName);

	void createGameDate();

	void showSaveScene(CCObject *);	//����浵����
	void showLoadScene(CCObject *);	//�����������
	void showHistoryScene(CCObject *);	//������ʷ��¼����

	void ScreenShoot();	//����

	void clear();	//�����Ļ�����ж���
	void reloadScene();	//���س�����ͨ��������

	void showSelect(std::map<std::string, std::string> &options);	//��ʾѡ��


	void menuButton(CCObject *);
	cocos2d::CCMenu* _menu;
	std::string _tmp;
	std::string _tmp2;
};

