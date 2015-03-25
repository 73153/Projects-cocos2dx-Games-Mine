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
    
    m_grossini = CCSprite::create("blood.png");
  
    
    m_tamara = CCSprite::create("carr.png");
   
    
    m_kathia = CCSprite::create("carr.png");
    
    
    addChild(m_grossini, 1);
    addChild(m_tamara, 2);
    addChild(m_kathia, 3);

    m_grossini->setPosition(CCPointMake(100, 160));
    m_tamara->setPosition(CCPointMake(40, 2*s.height/3));
    m_kathia->setPosition(CCPointMake(s.width/2, s.height/2));
    


    m_grossini->setPosition( CCPointMake(250, 160));
    m_tamara->setPosition( CCPointMake(100, s.height/2));
    m_kathia->setPosition( CCPointMake(400, s.height/2));
    
    CCFiniteTimeAction*  action = CCSequence::create( CCDelayTime::create(3), CCCallFuncN::create( this, callfuncN_selector(HelloWorld::repeat) ), NULL);
    
    m_grossini->runAction(action);
    
    return true;
}
void HelloWorld::repeat(CCNode* pSender){


CCRepeatForever *repeat = CCRepeatForever::create( CCRotateBy::create(4, 180) );

pSender->runAction(repeat);

}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
