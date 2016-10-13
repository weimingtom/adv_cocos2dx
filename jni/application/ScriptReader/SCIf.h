#pragma once
#include "ScriptReader.h"
#include "ScriptCommand.h"

class ScriptReader::SCIf : public ScriptCommand
{
	std::string _expression;
	std::string _trueTag;
	std::string _falseTag;
public:
	SCIf(ScriptReader *reader, std::string expression, std::string trueTag, std::string falseTag);
	~SCIf();
	void execute(cocos2d::CCNode* stage);
	bool expressionJudge();
	void jump(std::string tag);
};