#pragma once
#include "ScriptReader.h"
class ScriptReader::ScriptCommand{
public:
	ScriptCommandType type;	//��������
	ScriptReader *reader;	//�ű�������
	void execute(cocos2d::Node* stage);	//ִ�з���
};