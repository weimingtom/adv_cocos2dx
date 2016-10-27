#pragma once

#include "cocos2d.h"

USING_NS_CC;

class CharLabel:public cocos2d::CCNode
{
	cocos2d::CCLabelTTF* _charLabel;	//�����ɵ�����
	int _pos;	//��ǰ��ʾ������λ��
	float _defaultDelayTime;	//Ĭ����ʾ����ʱ��
	float _fadeTime;	//����fadein��ʱ��
	int _defaultFontSize;	//Ĭ�����ִ�С
	std::string _text;	//Ҫ��ʾ���ַ���

	cocos2d::ccColor3B _defaultFontColor;

	//�´���ʾ���ֵ�λ��
	float _lineHeight;	//�����и�
	float _x;	//��ʾλ������X
	float _y;	//��ʾλ������Y

	void showNextChar();	//��ʾ��һ������

	void (CCObject::*_showFinishCallback)() ;	//��ʾ��ɺ�Ļص�
	CCObject *_showFinishCallbackObj;
public:
	CharLabel();
	~CharLabel();

	static CharLabel* create(std::string text, int fontSize = 24, void (CCObject::*callback)() = NULL, CCObject *callbackObj = NULL);	//��������
	bool init(std::string &text, int fontSize);	//��ʼ����text ��ʾ���ı���fontSize �ı���С

	/*
	����Ҫ��ʾ���ַ���
	��ֱ���滻��ǰ�ַ�����Ҳ�����޸�Ϊ������ʧ
	*/
	void setString(std::string &text);

	/*
	˲����ʾ�ַ���
	*/
	void finishShow();

	/*
	��ȡ�ַ�����һ�����֣����UTF8
	*/
	static std::string getNextChar(std::string &src, int pos);

	/*
	��ʾȫ�����ʱ�����õķ���
	*/
	void setShowFinishCallback(void (CCObject::*callback)())
	{
		_showFinishCallback = callback;
	}

	/*
	����������ɫ
	*/
	void setColor(cocos2d::ccColor3B color)
	{
		_defaultFontColor = color;
	}

};

