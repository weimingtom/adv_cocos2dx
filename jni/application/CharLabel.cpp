#include "CharLabel.h"

USING_NS_CC;

CharLabel::CharLabel()
	: _pos(0)
	, _defaultDelayTime(0.04f)
	, _fadeTime(0.5f)
	, _lineHeight(0)
	, _charLabel(NULL)
	, _x(0)
	, _y(0)
	, _defaultFontSize(20)
	, _showFinishCallback(NULL)
	, _defaultFontColor(ccBLACK)
{
}


CharLabel::~CharLabel()
{
}

CharLabel* CharLabel::create(std::string text, int fontSize, void (CCObject::*callback)(), CCObject *callbackObj)
{
	CharLabel* ret = new CharLabel();
	if (ret && ret->init(text, fontSize))
	{
		ret->_showFinishCallback = callback;
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return NULL;
}

bool CharLabel::init(std::string &text, int fontSize)
{
	_text = text;
	_defaultFontSize = fontSize;
	showNextChar();
	return true;
}

void CharLabel::setString(std::string &text)
{
	this->CCNode::removeAllChildren();
	_charLabel = NULL;
	_text = text;
	_pos = 0;
	_x = 0;
	_y = 0;
	showNextChar();
}

void CharLabel::finishShow()
{
	removeAllChildren();
	_charLabel = CCLabelTTF::create(_text.c_str(), "Î¢ÈíÑÅºÚ", _defaultFontSize);
	_charLabel->setAnchorPoint(ccp(0.0f, 1.0f));
	_charLabel->setColor(_defaultFontColor);

	this->CCNode::addChild(_charLabel);
	if (_showFinishCallback && _showFinishCallbackObj)
	{
		(_showFinishCallbackObj->*_showFinishCallback)();
	}
}

void CharLabel::showNextChar()
{
	if (_pos >= (int)_text.length() - 1)
	{
		if (_showFinishCallback)
		{
			cocos2d::CCSprite *eventSprite = cocos2d::CCSprite::create();
			addChild(eventSprite);
#if 0
			eventSprite->runAction
				(
				cocos2d::CCSequence::create
				(
				cocos2d::CCDelayTime::create(_fadeTime),
				CallFunc::create(_showFinishCallback),
				NULL
				)
				);
#endif
		}
		return;
	}

	std::string charString = getNextChar(_text, _pos);

	if (_charLabel && _lineHeight < _charLabel->getContentSize().height)
	{
		_lineHeight = _charLabel->getContentSize().height;
	}

	while (charString.compare("\n") == 0)
	{
		_y -= _lineHeight;
		_x = 0;
		_pos += charString.length();
		charString = getNextChar(_text, _pos);
	}

	cocos2d::CCLabelTTF *tmpLabel = cocos2d::CCLabelTTF::create(charString.c_str(), "Î¢ÈíÑÅºÚ", _defaultFontSize);
	tmpLabel->setAnchorPoint(ccp(0.0f, 1.0f));
	this->CCNode::addChild(tmpLabel);
	tmpLabel->setColor(_defaultFontColor);

	_pos += charString.length();
	tmpLabel->setOpacity(0);
	tmpLabel->setPosition(ccp(_x, _y));
	_x += tmpLabel->getContentSize().width;
#if 0
	tmpLabel->runAction(cocos2d::CCSpawn::createWithTwoActions(
		FadeIn::create(_fadeTime), 
		Sequence::createWithTwoActions(
			DelayTime::create(_defaultDelayTime), 
			CallFunc::create(CC_CALLBACK_0(CharLabel::showNextChar, this)))
		));
#endif
	_charLabel = tmpLabel;
}

std::string CharLabel::getNextChar(std::string &src, int pos)
{
	if (src.length() < 1)
	{
		return std::string("");
	}

	int len = 0;
	char c = src[pos];

	if (c >= 0 && c <= 127)
	{
		len++;
	}
	else if (c < 0 && c >= -32)
	{
		len += 3;
	}
	else if (c < 0 && c >= -64)
	{
		len += 2;
	}
	else if (c < 0)
	{
		len += 1;
	}
	std::string subString = src.substr(pos, len);
	return subString;
}