#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "cocos2d.h"
#include "EasyButton.h"

USING_NS_CC;

class RadioButton : public Node
{
	std::vector<EasyButton*>* _radios;	//��ѡ��ť��
	int _selectedNumber;	//��ǰѡ�еİ�ť�±�
	int _tmpSelectedNumber;	//��ʱ
	EasyButton* _selectedButton;	//��ǰ��ѡ�еİ�ť
	EasyButton* _tmpSelectedButton;	//��ʱ���汻ѡ�еİ�ť
	EventListenerTouchOneByOne* _eventTouch;	//�����¼�
public:
	RadioButton();
	~RadioButton();
	static RadioButton* createRadioButton(EasyButton* i, ...);
	std::function<void()> touchEvent;

	void onTouchBegan(Touch *t, Event *e);
	void onTouchEnded(Touch *t, Event *e, bool flag);

	int getSelectedNumber();	//����ѡ��ť�±�
	void setSelectedNumber(int selectedNumber);	//����Ĭ�ϱ�ѡ�еİ�ť
};

#endif