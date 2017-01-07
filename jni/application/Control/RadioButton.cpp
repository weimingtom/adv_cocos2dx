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
	/*�ɱ������ȡ*/
	va_list argPtr; //����ɱ����ָ��
	va_start(argPtr, i);
	EasyButton* p = i;
	while (p != NULL)
	{
		p->setEventTouchEnabled(false);	//�ر�EasyButton�ļ�����
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
	// �ж�selectedNumber�Ƿ񳬳���ǰRadioButton�ĳ���
	if (selectedNumber > _radios->size() / sizeof(EasyButton*) || selectedNumber < 0)
	{
		CCLOG("Bad SelectedNumber!");
		return;
	}
	//FIXME:
	if (_selectedButton) 
	{
		_selectedButton->onTouchEnded(NULL, NULL, false);	//����а�ť��ѡ�еĻ����Ȼ�ԭĬ��ֵ
	}
	/*���޴��ķ���ȷ��selectedNumber��Ӧ�İ�ť�Ƿ���ڣ�������λ��*/
	/*--��Ϊ̫�޴������ҵ����õķ�������������
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
	if (!targetButton)	//�Ҳ������˳�
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
		if ((*it)->getNormal()->boundingBox().containsPoint((*it)->convertTouchToNodeSpace(pTouch)))	//�������ָ��
		{
			_tmpSelectedButton = (*it);
			if (_tmpSelectedButton == _selectedButton) 
			{
				return false;	//�����ǰѡ�а�ť��֮ǰѡ�а�ťһ������Ӧ
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
	if (_tmpSelectedButton->getNormal()->boundingBox().containsPoint(_tmpSelectedButton->convertTouchToNodeSpace(pTouch)))	//�ж��ɿ�ʱ�Ƿ���ԭ����ť��
	{
		if (_selectedButton)	
		{
			//ȷ��֮ǰ��ѡ�а�ť���ڣ�����Ҫ��Ĭ�ϰ�ť
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
