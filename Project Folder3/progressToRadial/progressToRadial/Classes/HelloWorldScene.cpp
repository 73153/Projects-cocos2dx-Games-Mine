#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCProgressTo *to1 = CCProgressTo::create(4, 100);
    CCProgressTo *to2 = CCProgressTo::create(4, 100);
    
    CCProgressTimer *left = CCProgressTimer::create(CCSprite::create("Tulips.png"));
    left->setType( kCCProgressTimerTypeRadial );
    addChild(left);
    left->setPosition(CCPointMake(100, s.height/2));
    left->runAction( CCRepeatForever::create(to1));
    
    CCProgressTimer *right = CCProgressTimer::create(CCSprite::create("car2.png"));
    right->setType(kCCProgressTimerTypeRadial);
    // Makes the ridial CCW
    right->setReverseProgress(true);
    addChild(right);
    right->setPosition(CCPointMake(s.width-100, s.height/2));
    right->runAction( CCRepeatForever::create(to2));
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
