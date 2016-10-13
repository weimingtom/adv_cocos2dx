#ifndef __EASY_BUTTON_H__
#define __EASY_BUTTON_H__
#include "EasyButton.h"


EasyButton::EasyButton(cocos2d::CCSprite* _normalSprite, cocos2d::CCSprite* _touchSprite, cocos2d::CCSprite* _selectedSprite)
{
	_normal = _normalSprite;
	this->addChild(_normal);
	_touch = _touchSprite;
	if (_touch)
	{
		this->addChild(_touch);
		_touch->setVisible(false);
	}
	_selected = _selectedSprite;
	if (_selected)
	{
		this->addChild(_selected);
		_selected->setVisible(false);
	}
#if 0
	_eventTouch = EventListenerTouchOneByOne::create();
	_eventTouch->onTouchBegan = [=](Touch *t, Event *e)
	{
		//log("EasyButton Touch!");
		if (_normal->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//如果碰到指针
		{
			onTouchBegan(t, e);
			return true;
		}
		return false;
	};
	_eventTouch->onTouchMoved = [=](Touch *t, Event *e)
	{
		//onTouchMoved(t, e);
	};
	_eventTouch->onTouchEnded = [=](Touch *t, Event *e)
	{
		//log("EasyButton Touch End!");
		if (_normal->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(t)))	//如果碰到指针
		{
			onTouchEnded(t, e, true);
		}
		else
		{
			onTouchEnded(t, e, false);
		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_eventTouch, this);
	touchEvent = [=](){};
	//touchEventWithInt = [=](){};
#endif
}


EasyButton::~EasyButton()
{
}

EasyButton* EasyButton::createEasyButton(const std::string &_normalFile)
{
   
	cocos2d::CCSprite *normalSprite = cocos2d::CCSprite::create(_normalFile.c_str());
	//Sprite* touchSprite = nullptr;
	//Sprite* selectSprite = nullptr;
	EasyButton *ret= new EasyButton(normalSprite, NULL, NULL);
    if(ret && ret->init()){
        ret->autorelease();
        return ret;
    }
    delete ret;
    ret = NULL;
    return NULL;
};

EasyButton* EasyButton::createEasyButton(const std::string &_normalFile, const std::string &_touchFile)
{
	cocos2d::CCSprite * normalSprite = cocos2d::CCSprite::create(_normalFile.c_str());
	cocos2d::CCSprite * touchSprite = cocos2d::CCSprite::create(_touchFile.c_str());
	//Sprite* selectSprite = nullptr;
	return new EasyButton(normalSprite, touchSprite, NULL);
};

EasyButton* EasyButton::createEasyButton(const std::string &_normalFile, const std::string &_touchFile, const std::string &_selectedFile)
{
	cocos2d::CCSprite * normalSprite = cocos2d::CCSprite::create(_normalFile.c_str());
	cocos2d::CCSprite * touchSprite = cocos2d::CCSprite::create(_touchFile.c_str());
	cocos2d::CCSprite * selectSprite = cocos2d::CCSprite::create(_selectedFile.c_str());
	return new EasyButton(normalSprite, touchSprite, selectSprite);
};

void EasyButton::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (_selected)
	{
		_normal->setVisible(false);
		_selected->setVisible(true);
	}
}

void EasyButton::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (_selected)
	{
		_normal->setVisible(true);
		_selected->setVisible(false);
	}
	if (flag)
	{
		touchEvent();
	}
}

void EasyButton::setEventTouchEnabled(bool flag)
{
	_eventTouch->setEnabled(flag);
}

cocos2d::CCSprite* EasyButton::getNormal()
{
	return _normal;
}

#endif