#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	cocos2d::CCSize visibleSize = cocos2d::CCDirector::sharedDirector()->getVisibleSize();
	cocos2d::CCPoint origin = cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
	CCLabelTTF* label2 = CCLabelTTF::create("Change the world!", "fonts/Marker Felt.ttf", 28);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
	label2->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - pLabel->getContentSize().height - 30));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
	this->addChild(label2, 2);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
	CCSprite* Junyu = CCSprite::create("IMG_4656.JPG");
	CCMenuItemImage *TestButton = CCMenuItemImage::create(
		"IMG_5226.JPG", 
		"IMG_5226.JPG", this,
		menu_selector(HelloWorld::menuTestButton));

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	Junyu->setScale(0.25);
	Junyu->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	TestButton->setPosition(ccp(200, 200));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
	this->addChild(Junyu, 1);
	//this->addChild(TestButton, 2);
    
	cocos2d::CCMenu *TestMenu = cocos2d::CCMenu::create(TestButton, NULL);
	TestMenu->setPosition(ccp(0, 0));
	this->addChild(TestMenu, 2);
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::menuTestButton(cocos2d::CCObject* pSender)
{
	cocos2d::CCSprite *Power = cocos2d::CCSprite::create("IMG_5401.JPG");
	Power->setScale(0.125);
	Power->setPosition(ccp(100, 100));
	this->addChild(Power, 3);
}
