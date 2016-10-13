#include "RadioButton.h"


RadioButton::RadioButton()
	: _selectedNumber(0)
	, _tmpSelectedNumber(0)
	, _selectedButton(nullptr)
	, _tmpSelectedButton(nullptr)
{
	_radios = new std::vector<EasyButton*>;
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
		_tmpSelectedButton = nullptr;
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
	
}


RadioButton::~RadioButton()
{
	delete _radios;
}

RadioButton* RadioButton::createRadioButton(EasyButton* i, ...)
{
	auto tmpRadioButton = new RadioButton();
	/*�ɱ������ȡ*/
	va_list argPtr; //����ɱ����ָ��
	va_start(argPtr, i);
	EasyButton* p = i;
	while (p != nullptr)
	{
		p->setEventTouchEnabled(false);	//�ر�EasyButton�ļ�����
		tmpRadioButton->_radios->push_back(p);
		tmpRadioButton->addChild(p);
		p = va_arg(argPtr, EasyButton*);
	}
	va_end(argPtr);

	return tmpRadioButton;
}

void RadioButton::onTouchBegan(Touch *t, Event *e)
{

}

void RadioButton::onTouchEnded(Touch *t, Event *e, bool flag)
{
	//log("ButtonNumber: %d", _selectedNumber);
	touchEvent();
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
		log("Bad SelectedNumber!");
		return;
	}
	if (_selectedButton) _selectedButton->onTouchEnded(nullptr,nullptr,false);	//����а�ť��ѡ�еĻ����Ȼ�ԭĬ��ֵ
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
	_selectedButton->onTouchBegan(nullptr, nullptr);
	_selectedNumber = selectedNumber;
}