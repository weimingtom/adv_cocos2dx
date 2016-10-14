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

#define DEFAULT_TEXT_FONT "微软雅黑"
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
    //背景图片，使用九宫格精灵储存
	cocos2d::extension::CCScale9Sprite* _backgroundSprite;
    //背景层，可以用于阻挡Event传递
    cocos2d::CCLayerColor* _backgroundLayer;
    //当前按钮数量
    int _buttonCounter;
    //储存按钮的容器
    std::vector<PopupButton*> *_buttonList;
    //按钮所在的Y值
    int _buttonPositionY;
    //按钮菜单
	cocos2d::CCMenu* _buttonMenu;
    //对话框文字
    cocos2d::CCLabelTTF* _popupText;
    int _popupTextSize;
    float _popupTextPositionX;
    float _popupTextPositionY;
    std::string _popupTextFont;
    //排列按钮
    void arrange();
    
    PopupLayer(const std::string &backgroundImage);
public:
    ~PopupLayer();
    
    //创建PopupLayer的静态方法
    static PopupLayer* create(const std::string &backgroundImage);
    //无触碰图片和触发图片的按钮添加方式
    void addButton(const std::string &normalImage, void (&callback) (cocos2d::CCObject*));
    //无触碰图片的按钮添加方式
    void addButton(const std::string &normalImage, const std::string &selectedImage, void (&callback) (cocos2d::CCObject*));
    //完整的按钮添加方式
    void addButton(const std::string &normalImage, const std::string &touchImage, const std::string &selectedImage, void (&callback) (cocos2d::CCObject*) );
    //Label按钮的添加方式
	//http://blog.csdn.net/xiebaochun/article/details/23281555
	//SEL_MenuHandler 
#if 0
    void addLabelButton(const std::string &buttonText, const ccMenuCallback& callback);
#endif
    //设置文本框内容
    void setString(const std::string &text);
};

#endif /* PopuLayer_hpp */
