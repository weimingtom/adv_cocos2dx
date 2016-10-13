#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include "cocos2d.h"

USING_NS_CC;

class Slidebar : public cocos2d::CCNode 
{
	cocos2d::CCSprite* _background;
	cocos2d::CCSprite* _point;
	float _maxValue;
	float _minValue;
	float* _targetValue;
#if 0
	EventListenerTouchOneByOne* _controlEvent;
#endif
	float _pointPositionX;
	float _maxWidth;
	float _change;	//�������ı�ı���
	float _floatValue;	//������������ı��ֵ
public:
	Slidebar(cocos2d::CCSprite* backgroundSprite, cocos2d::CCSprite* pointSprite);
	~Slidebar();
	static Slidebar* createSlidebar(std::string backgroundFile, std::string pointFile);
	void setLinkValue(int &value);
	void setMaxValue(float value);
	void setMinValue(float value);
	void valueChange();
#if 0
	EventListenerTouchOneByOne* createControlEvent();	//���������¼�
#endif
	void setMaxWidth(float value);//���û�������ƶ���Χ���뾶��
	void setTargetValue(float *value);
	void changeTargetValue(float change);
	float getChange();	//��ȡ�������ı�ı���
	void setSlidebar();	//�Զ����û���λ��
	void setFloat(float value);	
	float getFloat();

	void (*touchEvent) ();	//�����¼�
	void (*moveEvent) ();	//�ƶ��¼�
};

#endif