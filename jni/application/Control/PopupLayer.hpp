//
//  PopuLayer.hpp
//  Karma
//
//  Created by SunnyRx on 16/7/31.
//
//

#ifndef PopupLayer_hpp
#define PopupLayer_hpp

#include "cocos2d.h"
#if 0
#include "extensions/cocos-ext.h"
#else
#include "cocos-ext.h"
#endif

USING_NS_CC;

#define DEFAULT_TEXT_FONT "΢���ź�"
#define DEFAULT_TEXT_SIZE 20

struct PopupButton
{
	cocos2d::CCMenuItem* button;
    enum ButtonType
    {
        FONT,
        IMAGE
    } buttonType;
};

class PopupLayer : public cocos2d::CCNode
{
    //����ͼƬ��ʹ�þŹ����鴢��
	cocos2d::extension::CCScale9Sprite* _backgroundSprite;
    //�����㣬���������赲Event����
    cocos2d::CCLayerColor* _backgroundLayer;
    //��ǰ��ť����
    int _buttonCounter;
    //���水ť������
    std::vector<PopupButton*> *_buttonList;
    //��ť���ڵ�Yֵ
    int _buttonPositionY;
    //��ť�˵�
	cocos2d::CCMenu* _buttonMenu;
    //�Ի�������
    cocos2d::CCLabelTTF* _popupText;
    int _popupTextSize;
    float _popupTextPositionX;
    float _popupTextPositionY;
    std::string _popupTextFont;
    //���а�ť
    void arrange();
    
    PopupLayer(const std::string &backgroundImage);
public:
    ~PopupLayer();
    
    //����PopupLayer�ľ�̬����
    static PopupLayer* create(const std::string &backgroundImage);
    //�޴���ͼƬ�ʹ���ͼƬ�İ�ť��ӷ�ʽ
    void addButton(const std::string &normalImage, void (&callback) (cocos2d::CCObject*));
    //�޴���ͼƬ�İ�ť��ӷ�ʽ
    void addButton(const std::string &normalImage, const std::string &selectedImage, void (&callback) (cocos2d::CCObject*));
    //�����İ�ť��ӷ�ʽ
    void addButton(const std::string &normalImage, const std::string &touchImage, const std::string &selectedImage, void (&callback) (cocos2d::CCObject*) );
    //Label��ť����ӷ�ʽ
	//http://blog.csdn.net/xiebaochun/article/details/23281555
	//SEL_MenuHandler 
#if 0
    void addLabelButton(const std::string &buttonText, const ccMenuCallback& callback);
#endif
    //�����ı�������
    void setString(const std::string &text);
};

#endif /* PopuLayer_hpp */
