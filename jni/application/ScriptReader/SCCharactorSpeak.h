#pragma once
#include "ScriptReader.h"
#include "ScriptCommand.h"

enum CharactorFaceType;

class ScriptReader::SCCharactorSpeak :public ScriptCommand
{
public:
	std::string cName;
	std::string face;
	std::string text;
	
	SCCharactorSpeak(ScriptReader *reader, std::string &name, std::string &text, std::string &face);

	~SCCharactorSpeak();

	void execute(cocos2d::CCNode* stage);


};