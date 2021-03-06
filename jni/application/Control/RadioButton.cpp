#include "RadioButton.h"


RadioButton::RadioButton()
	: _selectedNumber(0)
	, _tmpSelectedNumber(0)
	, _selectedButton(NULL)
	, _tmpSelectedButton(NULL)
{
	_radios = new std::vector<EasyButton*>;

	this->touchEvent = NULL;
	this->touchEventObj = NULL;
}


RadioButton::~RadioButton()
{
	delete _radios;
}

RadioButton* RadioButton::createRadioButton(EasyButton* i, ...)
{
	RadioButton * tmpRadioButton = new RadioButton();
	/*可变参数读取*/
	va_list argPtr; //定义可变参数指针
	va_start(argPtr, i);
	EasyButton* p = i;
	while (p != NULL)
	{
		p->setEventTouchEnabled(false);	//关闭EasyButton的监听器
		tmpRadioButton->_radios->push_back(p);
		tmpRadioButton->addChild(p);
		p = va_arg(argPtr, EasyButton*);
	}
	va_end(argPtr);

	return tmpRadioButton;
}

void RadioButton::onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void RadioButton::onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent, bool flag)
{
	//log("ButtonNumber: %d", _selectedNumber);
	if (this->touchEventObj != NULL)
	{
		(this->touchEventObj->*touchEvent)();
	}
}

int RadioButton::getSelectedNumber()
{
	return _selectedNumber;
}

void RadioButton::setSelectedNumber(int selectedNumber)
{
	// 判断selectedNumber是否超出当前RadioButton的长度
	if (selectedNumber > _radios->size() / sizeof(EasyButton*) || selectedNumber < 0)
	{
		CCLOG("Bad SelectedNumber!");
		return;
	}
	//FIXME:
	if (_selectedButton) 
	{
		_selectedButton->onTouchEnded(NULL, NULL, false);	//如果有按钮被选中的话，先还原默认值
	}
	/*用愚蠢的方法确认selectedNumber对应的按钮是否存在，返回其位置*/
	/*--因为太愚蠢并且找到更好的方法所以屏蔽了
	int step = 0;
	EasyButton* targetButton = nullptr;
	for (auto it = _radios->begin(); it != _radios->end(); it++)
	{
		if (step++ == selectedNumber)
		{
			targetButton = (*it);
			break;
		}
	}
	if (!targetButton)	//找不到便退出
	{
		log("SelectedNumber Button unfind.");
		return;
	}
	*/
	_selectedButton = _radios->at(selectedNumber);
	_selectedButton->ccTouchesBegan(NULL, NULL);
	_selectedNumber = selectedNumber;
}


void RadioButton::onEnter()  
{  
	//addEventListenerWithSceneGraphPriority
	//_eventTouch->setSwallowTouches(true);
	//FIXME:nPriority == -10, smaller than EasyButton
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -10, true);  
    CCNode::onEnter();  
}

void RadioButton::onExit()  
{  
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
    CCNode::onExit();  
}  

bool RadioButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	_tmpSelectedNumber = 0;
	for (std::vector<EasyButton*>::iterator it = _radios->begin(); 
		it != _radios->end(); 
		it++)
	{
		if ((*it)->getNormal()->boundingBox().containsPoint((*it)->convertTouchToNodeSpace(pTouch)))	//如果碰到指针
		{
			_tmpSelectedButton = (*it);
			if (_tmpSelectedButton == _selectedButton) 
			{
				return false;	//如果当前选中按钮和之前选中按钮一样则不响应
			}
			(*it)->onTouchBegan(pTouch, pEvent);
			return true;
		}
		_tmpSelectedNumber++;
	}
	_tmpSelectedButton = NULL;
	return false;
}

void RadioButton::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void RadioButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (_tmpSelectedButton->getNormal()->boundingBox().containsPoint(_tmpSelectedButton->convertTouchToNodeSpace(pTouch)))	//判断松开时是否还在原来按钮上
	{
		if (_selectedButton)	
		{
			//确保之前被选中按钮还在，这需要有默认按钮
			_selectedButton->onTouchEnded(pTouch, pEvent, false);
		}
		_selectedButton = _tmpSelectedButton;
		_selectedNumber = _tmpSelectedNumber;
		onTouchEnded(pTouch, pEvent, true);
	}
	else
	{
		_tmpSelectedButton->onTouchEnded(pTouch, pEvent, false);
	}
}

void RadioButton::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}
