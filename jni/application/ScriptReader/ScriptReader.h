#pragma once
#include "cocos2d.h"
//#include "CharactorManager.h"

/*
ScriptReader使用单例模式设计
主要作用是对脚本进行读取、解析
*/

USING_NS_CC;
struct Charactor;


enum ScriptCommandType
{
	PartSign,	//段落标签
	CharactorSpeak,	//角色发言
	Select,	//选择支
	SelectOption,	//选择支选项
	Leave,	//角色离场
	Set,	//数值修改
	GameOver,	//游戏结束
	Jump,	//段落跳跃
	Background,	//显示背景
	PlayBGM,	//播放音乐
	StopBGM,	//停止音乐
	PlaySd,		//播放音效
	StopSd,		//停止音效
	If			//判断
};

class ScriptReader
{
	/*
	脚本命令 基类
	*/
	class ScriptCommand;

	class SCCharactorSpeak;	//文字对话

	class SCLeave;	//立绘离场 

	class SCJump;	//标签跳转

	class SCSelect;	//选择分支

	class SCBackground;	//显示背景

	class SCPlayBGM;	//播放音乐

	class SCStopBGM;	//停止音乐

	class SCPlaySound;	//播放音效

	class SCStopSound;	//停止音效

	class SCSet;		//数值修改

	class SCIf;			//条件判断

	std::map<std::string, std::vector<ScriptCommand*>*> _scripts;	//储存 段落标签和对应脚本列表
	/*
	历史记录 <sign,index>存储哪个章节，执行到哪个位置。
	相应逻辑未处理。
	*/
	std::map<std::string, int> _record;

	std::string _currentSignName;	//当前章节名称
	int _currentCommandIndex;	//脚本记录

	static ScriptReader* _instance;	//实例

public:
	ScriptReader();
	~ScriptReader();

	static ScriptReader* getInstance();	//获取实例
	static void destoryInstance();	//销毁实例

	cocos2d::CCSprite* charSprites[5];//储存五个角色，0左，1左中，2中，3右中，4右
	cocos2d::CCLayer* charStage;	//存储立绘的层

	Charactor** chars[5];	//储存五个角色，0左，1左中，2中，3右中，4右
	int* charNumber; //当前显示立绘数量

	bool isWaitingForSelection;	//是否等待选择支中。出现选项菜单的时候应该由选项来触发脚本
	

	cocos2d::CCNode* stage;	//绘制场景Node

	bool nextPositionIsLeft;	//下一个角色显示位置判断。
	
	void initWithStage(cocos2d::CCNode* stage);	//初始化数据

	void (CCObject::*showText) (std::string &text);	//显示文本回调
	CCObject *showTextObj;
	void (CCObject::*showName) (std::string &text);	//显示名称回调
	CCObject *showNameObj;
	void (CCObject::*changeBackground) (std::string &background);	//切换背景图片
	CCObject *changeBackgroundObj;
	void (CCObject::*playBackgroundMusic) (std::string &file);		//播放背景音乐
	CCObject *playBackgroundMusicObj;
	void (CCObject::*stopBackgroundMusic) ();						//停止背景音乐
	CCObject *stopBackgroundMusicObj;
	void (CCObject::*playSound) (std::string &file);				//播放音效
	CCObject *playSoundObj;
	void (CCObject::*stopSound) ();								//停止音效
	CCObject *stopSoundObj;
	void (CCObject::*showCharator) (std::string &cName, std::string &face);	//显示立绘
	CCObject *showCharatorObj;
	void (CCObject::*hideCharator) (std::string &name);	//隐藏立绘
	CCObject *hideCharatorObj;
	void (CCObject::*showSelect) (std::map<std::string, std::string>&);	//显示选项
	CCObject *showSelectObj;

	void loadScriptFile(std::string path);	//载入脚本数据
	void clearScript();	//清理脚本数据
	void jumpToSign(const std::string &sign);	//章节脚本跳转
	void jumpToSign(const std::string &sign, int index);

	void nextScript();	//执行下一条脚本

	std::string getCurrentSignName();
	int getCurrentCommandIndex();
	void setCurrentCommandIndex(int value);
};

