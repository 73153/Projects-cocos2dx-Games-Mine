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

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    

    // ask director the window size
    m_grossini = CCSprite::create("cat.png");
    m_tamara = CCSprite::create("car2.png");
    
    
    m_kathia = CCSprite::create("carsize.png");
    
    
    addChild(m_grossini, 1);
    addChild(m_tamara, 2);
    addChild(m_kathia, 3);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    
    m_grossini->setPosition(CCPointMake(s.width/2, 160));
    m_tamara->setPosition(CCPointMake(400, 160));
    m_kathia->setPosition(CCPointMake(80, 160));
    
    
    CCActionInterval *actionTo = CCSkewTo::create(2, 37.2f, -37.2f);
   
    CCActionInterval *actionToBack = CCSkewTo::create(2, 0, 0);
    
    CCActionInterval *actionBy = CCSkewBy::create(2, 0.0f, -90.0f);
    
    CCActionInterval *actionBy2 = CCSkewBy::create(2, 45.0f, 45.0f);
    
    CCActionInterval *actionByBack = actionBy->reverse();
    
    CCAction *p = CCRepeatForever::create((CCActionInterval*)(CCSequence::create(actionTo, actionToBack, NULL)));
    
    m_tamara->runAction(p);
    
    CCAction *a = CCRepeatForever::create((CCActionInterval*)(CCSequence::create(actionBy, actionByBack, NULL)));
    m_grossini->runAction(a);
    
    CCAction *e = CCRepeatForever::create((CCActionInterval*)(CCSequence::create(actionBy2, actionBy2->reverse(), NULL)));
    m_kathia->runAction(e);
    

    
    

    

    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
