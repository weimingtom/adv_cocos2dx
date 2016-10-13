#include "ScriptReader.h"
//#include "ScriptCommand.h"
#include "SCCharactorSpeak.h"
#include "SCLeave.h"
#include "SCJump.h"
#include "SCSelect.h"
#include "SCBackground.h"
#include "SCPlayBGM.h"
#include "SCStopBGM.h"
#include "SCPlaySound.h"
#include "SCStopSound.h"
#include "SCSet.h"
#include "SCIf.h"
#include "CharactorManager.h"
#include "../GameSystem.h"

USING_NS_CC;

ScriptReader* ScriptReader::_instance = NULL;

ScriptReader::ScriptReader()
	:_currentSignName("gameStart")
	, _currentCommandIndex(0)
	, nextPositionIsLeft(true)
	, charNumber(0)
	, stage(NULL)
	, isWaitingForSelection(0)
{
}


ScriptReader::~ScriptReader()
{
	clearScript();
}

void ScriptReader::initWithStage(cocos2d::CCNode* stage)
{
	this->stage = stage;
	charStage = cocos2d::CCLayer::create();
	stage->addChild(charStage);
	for (int i = 0; i < 5; i++)
	{
		chars[i] = NULL;
	}

}

ScriptReader* ScriptReader::getInstance()
{
	if (_instance == NULL)
	{
		_instance = new ScriptReader();
	}
	return _instance;
}

void ScriptReader::destoryInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = NULL;
	}
}

/*
清理数据
对于命令行，因为是用父类声明，所以不能直接delete，需要转换为子类，再delete。不然子类的字段不会被释放
*/

void ScriptReader::clearScript()
{
	typedef std::vector<ScriptCommand*>* MAP_VALUE;
	typedef std::map<std::string, MAP_VALUE> MAP;
	for (MAP::iterator itr = _scripts.begin(); itr != _scripts.end(); itr++)
	{
		MAP_VALUE list = itr->second;
		int size = list->size();
		("DeleteList size[%d]", size);
		if (size > 0)
		{
			for (int i = 0; i < size; i++)
			{
				ScriptCommand* ptr = list->at(i);
				switch (ptr->type)
				{
				case CharactorSpeak:
					delete (SCCharactorSpeak*)ptr;
					break;
				case Leave:
					delete (SCLeave*)ptr;
					break;
				case Jump:
					delete (SCJump*)ptr;
					break;
				case Select:
					delete (SCSelect*)ptr;
					break;
				case Background:
					delete (SCBackground*)ptr;
					break;
				case PlayBGM:
					delete (SCPlayBGM*)ptr;
					break;
				case StopBGM:
					delete (SCStopBGM*)ptr;
					break;
				case PlaySd:
					delete (SCPlaySound*)ptr;
					break;
				case StopSd:
					delete (SCStopSound*)ptr;
					break;
				case Set:
					delete (SCSet*)ptr;
					break;
				case If:
					delete (SCIf*)ptr;
					break;
				}
				//↑待填补

			}
		}
		list->clear();
		delete list;
	}
	_scripts.clear();
	isWaitingForSelection = false;
}

void ScriptReader::loadScriptFile(std::string path)
{
	clearScript();

	//std::string ss = FileUtils::getStringFromFile(path);
	std::string ss = CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathForFilename(path.c_str()).c_str())->getCString();

	int sPos = 0;
	int ePos = 0;

	std::string currentSign = "default";	//标签，默认default
	std::vector<ScriptCommand*> *cms = new std::vector<ScriptCommand*>();
	_scripts.insert(std::pair<std::string, std::vector<ScriptCommand*>*>(currentSign, cms));

	CCLOG("LoadScript::>");

	SCSelect* currentSelect = NULL;

	while (sPos >= 0)
	{
		//log("load succeess");
		ePos = ss.find('\n', sPos);	//从脚本中读出一行
		std::string command;	//储存解读脚本命令
		if (ePos < 0)
		{
			command = ss.substr(sPos, ss.length() - sPos);
			sPos = -1;
		}
		else
		{
			command = ss.substr(sPos, ePos - sPos - 1);
			sPos = ePos + 1;
		}

		if (command.length() > 1 && !command.empty())
		{
			if (command[0] == '/'){}	//解读为注释，忽略该行
			else
			{
				if (command[0] == '@')
				{
					//解读为记录脚本段落
					//currentSelect = nullptr;
					//log("Sign[%s] Size[%d]", currentSign.capacity(), cms->size());
					currentSign = command.substr(1, command.length() - 1);
					cms = new std::vector<ScriptCommand*>();
					_scripts.insert(std::pair < std::string, std::vector<ScriptCommand*>*>(currentSign,cms));
					CCLOG("SC> Add sign[%s]", currentSign.c_str());
				}
				else
				{
					if (command[0] == '#')	//解读脚本命令
					{
						std::string cmd = command.substr(1, command.length() - 1);
						int scriptNamePos = cmd.find_first_of(':', 0);
						std::string cmdParams = "";
						if (scriptNamePos > 0)
						{
							cmdParams = cmd.substr(scriptNamePos + 1, cmd.length() - scriptNamePos - 1);
							cmd = cmd.substr(0, scriptNamePos);
						}
						CCLOG("SC> Add command[%s] params[%s] Sign[%s]", cmd.c_str(), cmdParams.c_str(), currentSign.c_str());

						if (cmd.compare("Select") == 0)
						{
							SCSelect* selectCMD = new SCSelect(this);
							currentSelect = selectCMD;
							cms->push_back(selectCMD);
						}
						else if (cmd.compare("GameOver") == 0)
						{
							//游戏结束，待补充
						}
						else if (cmd.compare("Leave") == 0)
						{
							SCLeave* leaveCMD = new SCLeave(this, cmdParams);
							cms->push_back(leaveCMD);
						}
						else if (cmd.compare("Set") == 0)
						{
							std::string key;
							char mark;
							int value;
							int pos;
							pos = cmdParams.find_first_of("+-=", 0);
							key = cmdParams.substr(0, pos);
							mark = cmdParams[pos];
							cmdParams.substr(pos + 1, cmdParams.length() - 1);
							pos = cmdParams.find_first_of("+-", 0);
							if (pos < 0)
							{
								value = atoi(cmdParams.c_str());
							}
							else
							{
								char tmpChar = cmdParams[pos];
								std::string tmpString;
								switch (tmpChar)
								{
								case '-':
									value = 1;
									//value = GameSystem::getInstance()->getDataValue(cmdParams.substr(0, pos));// -atoi(cmdParams.substr(pos + 1, cmdParams.length() - 1).c_str());
									break;
								case '+':
									//value = GameSystem::getInstance()->getDataValue(cmdParams.substr(0, pos));// +atoi(cmdParams.substr(pos + 1, cmdParams.length() - 1).c_str());
									value = 1;
									break;
								default:
									break;
								}
							}
							SCSet* setCMD = new SCSet(this, key, mark, value);
							cms->push_back(setCMD);
						}
						else if (cmd.compare("Jump") == 0)
						{
							SCJump* jumpCMD = new SCJump(this, cmdParams);
							cms->push_back(jumpCMD);
						}
						else if (cmd.compare("Background") == 0)
						{
							SCBackground* backgroundCMD = new SCBackground(this, cmdParams);
							cms->push_back(backgroundCMD);
						}
						else if (cmd.compare("PlayBGM") == 0)
						{
							SCPlayBGM* playBGMCMD = new SCPlayBGM(this, cmdParams);
							cms->push_back(playBGMCMD);
						}
						else if (cmd.compare("StopBGM") == 0)
						{
							SCStopBGM* stopBGMCMD = new SCStopBGM(this);
							cms->push_back(stopBGMCMD);
						}
						else if (cmd.compare("PlaySound") == 0)
						{
							SCPlaySound* playSoundCMD = new SCPlaySound(this, cmdParams);
							cms->push_back(playSoundCMD);
						}
						else if (cmd.compare("StopSound") == 0)
						{
							SCStopSound* stopSoundCMD = new SCStopSound(this);
							cms->push_back(stopSoundCMD);
						}
						else if (cmd.compare("If") == 0)
						{
							std::string expression = "";	//表达式
							std::string trueTag = "";	//真跳转
							std::string falseTag = "";	//else跳转
							int pos;		

							//提取表达式
							pos = cmdParams.find_first_of(":", 0);
							expression = cmdParams.substr(0, pos);
							
							//提取真跳转
							cmdParams = cmdParams.substr(pos + 1, cmdParams.length() - 1);
							pos = cmdParams.find_first_of(":", 0);
							if (pos < 0)	//没有else跳转的情况
							{
								trueTag = cmdParams;
								//falseTag = "";

							}
							else
							{
								trueTag = cmdParams.substr(0, pos);
								cmdParams = cmdParams.substr(pos + 1, cmdParams.length() - 1);
								falseTag = cmdParams.substr(0, pos);
							}
							SCIf* ifCMD = new SCIf(this, expression, trueTag, falseTag);
							cms->push_back(ifCMD);
						}
						else
						{
							CCLOG("Unknow Script Command> [%s]:[%s]", cmd.c_str(), cmdParams.c_str());
						}
												
												
													
														
					}
					else
					{
						if (command[0] == '>')	//解读选择项
						{
							if (currentSelect != NULL)
							{
								std::string cmd = command.substr(1, command.length() - 1);
								int scriptNamePos = cmd.find_first_of(':', 0);
								std::string cmdParams = "";
								if (scriptNamePos > 0)
								{
									cmdParams = cmd.substr(scriptNamePos + 1, cmd.length() - scriptNamePos - 1);
									cmd = cmd.substr(0, scriptNamePos);
								}
								CCLOG("SC> options Sign[%s] text[%s]", cmd.c_str(), cmdParams.c_str());
								currentSelect->addOption(cmd, cmdParams);
							}
						}
						else
						{
							//对话
							std::string cmd = command;//记录人名部分
							int scriptNamePos = cmd.find_first_of(':', 0);
							std::string cmdParams = "";
							std::string face = "";
							if (scriptNamePos < 0)	//找不到":"的话cmd默认就是旁白
							{
								CCLOG("SC Csay Text[%s]", cmd.c_str());
								SCCharactorSpeak* csCMD = new SCCharactorSpeak(this, face, cmd, face);	//这里的face只是用来顶替空串而已
								cms->push_back(csCMD);
							}
							else
							{
								cmdParams = cmd.substr(scriptNamePos + 1, cmd.length() - scriptNamePos - 1);
								cmd = cmd.substr(0, scriptNamePos);
								scriptNamePos = cmd.find_first_of('#', 0);
								if (scriptNamePos > 0)
								{
									face = cmd.substr(scriptNamePos + 1, cmd.length() - scriptNamePos - 1);
									cmd = cmd.substr(0, scriptNamePos);
								}
								CCLOG("SC Csay CHA[%s] Face[%s] Text[%s]", cmd.c_str(), face.c_str(), cmdParams.c_str());
								SCCharactorSpeak* csCMD = new SCCharactorSpeak(this, cmd, cmdParams, face);
								cms->push_back(csCMD);
							}
						}
					}
				}
			}
		}
	}

}

void ScriptReader::jumpToSign(const std::string &sign)
{
	CCLOG("sign: %s", sign.c_str());
	if (sign.compare("") == 0)
	{
		CCLOG("Sign is null");
		return;
	}
	isWaitingForSelection = false;
	typedef std::map<std::string, std::vector<ScriptCommand*>*> MAP;
	MAP::iterator list = _scripts.find(sign);
	if (list == _scripts.end())
	{
		CCLOG("Sign [%s] not found", sign.c_str());
		return;
	}
	_currentSignName = sign;
	_currentCommandIndex = 0;
	nextScript();
}

void ScriptReader::nextScript()
{
	//log("loading");
	
	if (isWaitingForSelection)
	{
		CCLOG("waitting");
		return;
	}
	_currentCommandIndex++;
	//log("Size of Script = [%d]", _scripts.size);
	typedef std::map<std::string, std::vector<ScriptCommand*>*> MAP;
	MAP::iterator list = _scripts.find(_currentSignName);
	if (list == _scripts.end())
	{
		CCLOG("No Sign of currentSign [%s]", _currentSignName.c_str());
		return;
	}
	std::vector<ScriptCommand*>* cmdList = list->second;
	if (_currentCommandIndex-1 >= (int)cmdList->size())
	{
		CCLOG("End of Script..! CurrentScript");
		//do something to done
		return;
	}

	ScriptCommand* cmd = cmdList->at(_currentCommandIndex-1);

	CCLOG("sign = %s, commandIndex = %d", _currentSignName.c_str(), _currentCommandIndex);

	switch (cmd->type)
	{
	case CharactorSpeak:
		((SCCharactorSpeak*)cmd)->execute(stage);
		break;
	case Leave:
		((SCLeave*)cmd)->execute(stage);
		break;
	case Jump:
		((SCJump*)cmd)->execute(stage);
		break;
	case Select:
		((SCSelect*)cmd)->execute(stage);
		break;
	case Background:
		((SCBackground*)cmd)->execute(stage);
		break;
	case PlayBGM:
		((SCPlayBGM*)cmd)->execute(stage);
		break;
	case StopBGM:
		((SCStopBGM*)cmd)->execute(stage);
		break;
	case PlaySd:
		((SCPlaySound*)cmd)->execute(stage);
		break;
	case StopSd:
		((SCStopSound*)cmd)->execute(stage);
		break;
	case Set:
		((SCSet*)cmd)->execute(stage);
		break;
	case If:
		((SCIf*)cmd)->execute(stage);
		break;
	default:
		CCLOG("Unhandle ScriptCommandType [%d]", cmd->type);
	}
	//_currentCommandIndex++;
}

std::string ScriptReader::getCurrentSignName()
{
	return _currentSignName;
}

int ScriptReader::getCurrentCommandIndex()
{
	return _currentCommandIndex;
}

void ScriptReader::setCurrentCommandIndex(int value)
{
	_currentCommandIndex = value;
}

void ScriptReader::jumpToSign(const std::string &sign, int index)
{
	if (sign.compare("") == 0)
	{
		CCLOG("Sign is null");
		return;
	}
	isWaitingForSelection = false;
	typedef std::map<std::string, std::vector<ScriptCommand*>*> MAP;
	MAP::iterator list = _scripts.find(sign);
	if (list == _scripts.end())
	{
		CCLOG("Sign [%s] not found", sign.c_str());
		return;
	}
	_currentSignName = sign;
	_currentCommandIndex = index;
	//nextScript();
}