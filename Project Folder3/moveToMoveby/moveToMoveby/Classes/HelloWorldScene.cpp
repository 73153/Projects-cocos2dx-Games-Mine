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
    this->addChild(pMenu);
 
    m_grossini = CCSprite::create("carsize.png");
    m_grossini->retain();
    
    m_tamara = CCSprite::create("dog.png");
    m_tamara->retain();
    
    m_kathia = CCSprite::create("cat.png");
    m_kathia->retain();
    
    addChild(m_grossini, 1);
    addChild(m_tamara, 1);
    addChild(m_kathia, 1);
    this->move();
    
       return true;
}


void HelloWorld::move(){
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    m_grossini->setPosition(CCPointMake(s.width/2, s.height/3));
    m_tamara->setPosition(CCPointMake(s.width/2, 2*s.height/3));
    m_kathia->setPosition(CCPointMake(s.width/2, s.height/2));
    
    
    CCActionInterval*  actionTo = CCMoveTo::create(2, CCPointMake(s.width-40, s.height-40));
    CCActionInterval*  actionBy = CCMoveBy::create(2, CCPointMake(80,80));
    CCActionInterval*  actionByBack = actionBy->reverse();
    
    m_tamara->runAction( actionTo);
    m_grossini->runAction( CCSequence::create(actionBy, actionByBack, NULL));
    m_kathia->runAction(CCMoveTo::create(3, CCPointMake(40,40)));

    }

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
