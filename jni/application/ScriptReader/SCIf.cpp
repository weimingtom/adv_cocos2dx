#include "SCIf.h"
#include "GameSystem.h"
#include <sstream>


ScriptReader::SCIf::SCIf(ScriptReader *reader, std::string expression, std::string trueTag, std::string falseTag)
	: _expression(expression)
	, _trueTag(trueTag)
	, _falseTag(falseTag)
{
	this->reader = reader;
	this->type = ScriptCommandType::If;
}


ScriptReader::SCIf::~SCIf()
{
}

void ScriptReader::SCIf::execute(cocos2d::Node* stage)
{
	if (_expression.compare("") == 0)
	{
		cocos2d::log("SC> If expressiong is null");
		reader->nextScript();
	}
	if (expressionJudge())
	{
		//cocos2d::log("SC> If (%s) is true, jump to %s", _expression.c_str(), _trueTag.c_str());
		jump(_trueTag);
	}
	else
	{
		//cocos2d::log("SC> If (%s) is false, jump to %s", _expression.c_str(), _falseTag.c_str());
		jump(_falseTag);
	}
	
}

//#If:key>1:gameStart -> key>1
bool ScriptReader::SCIf::expressionJudge()
{
	int pos;
	std::string exp = _expression;
	pos = exp.find_first_of("><=", 0);
	if (pos < 0)
	{
		cocos2d::log("SC> If expressiong do not have symbol");
		return true;
	}
	else
	{
		std::string sFirstValue;
		std::string sSecondValue;
		int iFirstValue;
		int iSecondValue;
		std::stringstream ssFirstValue;
		std::stringstream ssSecondValue;

		//�ӱ��ʽ����ȡ��һ��ֵ
		sFirstValue = exp.substr(0, pos);
		if ((exp[0] >= '0') && (exp[0] <= '9'))	//����һ��ֵ�ǳ���
		{
			ssFirstValue << sFirstValue;
			ssFirstValue >> iFirstValue;
		}
		else //����һ��ֵ�Ǳ���
		{
			iFirstValue = GameSystem::getInstance()->getDataValue(sFirstValue);
		}

		//�жϷ���
		if (exp[pos] == '>')	//���ڵ������
		{
			if (exp[pos + 1] == '=')	//���ڵ��ڵ������
			{
				//�ӱ��ʽ����ȡ�ڶ���ֵ
				sSecondValue = exp.substr(pos + 2, exp.length() - 1);
				if ((exp[pos + 3] >= '0') && (exp[pos + 3] <= '9'))
				{
					ssSecondValue << sSecondValue;
					ssSecondValue >> iSecondValue;
				}
				else
				{
					iSecondValue = GameSystem::getInstance()->getDataValue(sSecondValue);
				}
				
				if (iFirstValue >= iSecondValue)
					return true;
				else
					return false;
			}
			else
			{
				sSecondValue = exp.substr(pos + 1, exp.length() - 1);
				if ((exp[pos + 2] >= '0') && (exp[pos + 2] <= '9'))
				{
					ssSecondValue << sSecondValue;
					ssSecondValue >> iSecondValue;
				}
				else
				{
					iSecondValue = GameSystem::getInstance()->getDataValue(sSecondValue);
				}

				if (iFirstValue > iSecondValue)
					return true;
				else
					return false;
			}
		}
		else if (exp[pos] == '<')	//С�ڵ������
		{
			if (exp[pos + 1] == '=')	//С�ڵ��ڵ������
			{
				sSecondValue = exp.substr(pos + 2, exp.length() - 1);
				if ((exp[pos + 3] >= '0') && (exp[pos + 3] <= '9'))
				{
					ssSecondValue << sSecondValue;
					ssSecondValue >> iSecondValue;
				}
				else
				{
					iSecondValue = GameSystem::getInstance()->getDataValue(sSecondValue);
				}

				if (iFirstValue <= iSecondValue)
					return true;
				else
					return false;
			}
			else
			{
				sSecondValue = exp.substr(pos + 1, exp.length() - 1);
				if ((exp[pos + 2] >= '0') && (exp[pos + 2] <= '9'))
				{
					ssSecondValue << sSecondValue;
					ssSecondValue >> iSecondValue;
				}
				else
				{
					iSecondValue = GameSystem::getInstance()->getDataValue(sSecondValue);
				}

				if (iFirstValue < iSecondValue)
					return true;
				else
					return false;
			}

		}
		else if (exp[pos] == '=')	//��ȵ������
		{
			sSecondValue = exp.substr(pos + 2, exp.length() - 1);
			if ((exp[pos + 3] >= '0') && (exp[pos + 3] <= '9'))
			{
				ssSecondValue << sSecondValue;
				ssSecondValue >> iSecondValue;
			}
			else
			{
				iSecondValue = GameSystem::getInstance()->getDataValue(sSecondValue);
			}

			if (iFirstValue == iSecondValue)
				return true;
			else
				return false;
		}

	}
}

void ScriptReader::SCIf::jump(std::string tag)
{
	if (tag.compare("") == 0)
	{
		reader->nextScript();
		return;
	}
	else
	{
		reader->jumpToSign(tag);
	}
}