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

    CCSprite *sprite = CCSprite::create("CloseNormal.png");
    
    sprite->setPosition(ccp(50, 100));
    
    this->addChild(sprite);
        
    
    CCActionInterval*  move = CCJumpBy::create(2,CCPointMake(300,0),50,4);
   
    CCMoveBy* move2 = (CCMoveBy*)move->copy()->autorelease();
   
    CCFiniteTimeAction*  action =CCRepeatForever::create((CCActionInterval*)(CCSequence::create(move, move2,CCDelayTime::create(1.5),NULL)));
    
    sprite->runAction(action);
    
    CCSprite *sprite1 = CCSprite::create("CloseNormal.png");
    
    sprite1->setPosition(ccp(80, 100));
    
    this->addChild(sprite1);

    CCActionInterval * p1 = CCMoveBy::create(1, ccp(300,200));
    CCFiniteTimeAction*  action1 =CCRepeatForever::create((CCActionInterval*)(CCSequence::create(p1 ,p1->reverse(),CCDelayTime::create(2.5),NULL)));
    
    sprite1->runAction(action1);
    

    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
