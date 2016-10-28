#include "RadioButton.h"


RadioButton::RadioButton()
	: _selectedNumber(0)
	, _tmpSelectedNumber(0)
	, _selectedButton(NULL)
	, _tmpSelectedButton(NULL)
{
	_radios = new std::vector<EasyButton*>;
#if 0
	touchEvent = [=](){};
	_eventTouch = EventListenerTouchOneByOne::create();
	_eventTouch->setSwallowTouches(true);	//��Touch����EasyButton����
	_eventTouch->onTouchBegan = [=](Touch *t, Event *e)
	{
		_tmpSelectedNumber = 0;
		for (auto it = _radios->begin(); it != _radios->end(); it++)
		{
			if ((*it)->getNormal()->getBoundingBox().containsPoint((*it)->convertTouchToNodeSpace(t)))	//�������ָ��
			{
				_tmpSelectedButton = (*it);
				if (_tmpSelectedButton == _selectedButton) return false;	//�����ǰѡ�а�ť��֮ǰѡ�а�ťһ������Ӧ
				(*it)->onTouchBegan(t, e);
				return true;
			}
			_tmpSelectedNumber++;
		}
		_tmpSelectedButton = NULL;
		return false;
	};

	_eventTouch->onTouchEnded = [=](Touch *t, Event *e)
	{
		
		if (_tmpSelectedButton->getNormal()->getBoundingBox().containsPoint(_tmpSelectedButton->convertTouchToNodeSpace(t)))	//�ж��ɿ�ʱ�Ƿ���ԭ����ť��
		{
			if (_selectedButton)	//ȷ��֮ǰ��ѡ�а�ť���ڣ�����Ҫ��Ĭ�ϰ�ť
				_selectedButton->onTouchEnded(t, e, false);
			_selectedButton = _tmpSelectedButton;
			_selectedNumber = _tmpSelectedNumber;
			onTouchEnded(t, e,true);
		}
		else
		{
			_tmpSelectedButton->onTouchEnded(t, e, false);
		}
		
	};
	
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_eventTouch, this);
#endif
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

void RadioButton::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

}

void RadioButton::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	//log("ButtonNumber: %d", _selectedNumber);
	(this->touchEventObj->*touchEvent)();
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
#if 0
	if (_selectedButton) _selectedButton->onTouchEnded(NULL, NULL, false);	//����а�ť��ѡ�еĻ����Ȼ�ԭĬ��ֵ
#else
	if (_selectedButton) _selectedButton->ccTouchesEnded(NULL, NULL);	//����а�ť��ѡ�еĻ����Ȼ�ԭĬ��ֵ
#endif
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