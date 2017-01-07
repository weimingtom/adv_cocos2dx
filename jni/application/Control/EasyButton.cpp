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
	touchEventObj = NULL;
	touchEvent = NULL;
}


EasyButton::~EasyButton()
{
}

void EasyButton::onEnter()  
{  
	//addEventListenerWithSceneGraphPriority
	//_eventTouch->setSwallowTouches(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);  
    CCNode::onEnter();  
}

void EasyButton::onExit()  
{  
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
    CCNode::onExit();  
}  

bool EasyButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//log("EasyButton Touch!");
	if (_normal->boundingBox().containsPoint(this->convertTouchToNodeSpace(pTouch)))	//如果碰到指针
	{
		onTouchBegan(pTouch, pEvent);
		return true;
	}
	return false;
}

void EasyButton::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//onTouchMoved(pTouch, pEvent);
}

void EasyButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	//log("EasyButton Touch End!");
	if (_normal->boundingBox().containsPoint(this->convertTouchToNodeSpace(pTouch)))	//如果碰到指针
	{
		onTouchEnded(pTouch, pEvent, true);
	}
	else
	{
		onTouchEnded(pTouch, pEvent, false);
	}
}

void EasyButton::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
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
}

EasyButton* EasyButton::createEasyButton(const std::string &_normalFile, const std::string &_touchFile)
{
	cocos2d::CCSprite * normalSprite = cocos2d::CCSprite::create(_normalFile.c_str());
	cocos2d::CCSprite * touchSprite = cocos2d::CCSprite::create(_touchFile.c_str());
	//Sprite* selectSprite = nullptr;
	return new EasyButton(normalSprite, touchSprite, NULL);
}

EasyButton* EasyButton::createEasyButton(const std::string &_normalFile, const std::string &_touchFile, const std::string &_selectedFile)
{
	cocos2d::CCSprite * normalSprite = cocos2d::CCSprite::create(_normalFile.c_str());
	cocos2d::CCSprite * touchSprite = cocos2d::CCSprite::create(_touchFile.c_str());
	cocos2d::CCSprite * selectSprite = cocos2d::CCSprite::create(_selectedFile.c_str());
	return new EasyButton(normalSprite, touchSprite, selectSprite);
}

void EasyButton::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (_selected)
	{
		_normal->setVisible(false);
		_selected->setVisible(true);
	}
}

void EasyButton::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent, bool flag)
{
	if (_selected)
	{
		_normal->setVisible(true);
		_selected->setVisible(false);
	}
	if (flag)
	{
		if (this->touchEventObj != 0)
		{
			(this->touchEventObj->*touchEvent)();
		}
	}
}

void EasyButton::setEventTouchEnabled(bool flag)
{
#if 0
	_eventTouch->setEnabled(flag);
#endif
}

cocos2d::CCSprite* EasyButton::getNormal()
{
	return _normal;
}


//FIXME:
void EasyButton::onTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

#endif

