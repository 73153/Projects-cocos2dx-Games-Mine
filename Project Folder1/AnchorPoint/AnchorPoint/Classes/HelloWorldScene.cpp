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
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create( "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *sp1 = CCSprite::create("texture.png");
    CCSprite *sp2 = CCSprite::create("texture.png");
    CCSprite *sp3 = CCSprite::create("carr.png");
    CCSprite *sp4 = CCSprite::create("carr.png");
    
    sp1->setPosition(CCPointMake(100, s.height /2 ));
    sp2->setPosition(CCPointMake(380, s.height /2 ));
    addChild(sp1);
    addChild(sp2);
    
    sp3->setScale(0.60f);
    sp4->setScale(0.60f);
    
    sp1->addChild(sp3);
    sp2->addChild(sp4);
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("texture.plist");
    
    CCActionInterval* a1 = CCRotateBy::create(2, 360);
    CCActionInterval* a2 = CCScaleBy::create(2, 2);
    
    CCFiniteTimeAction* action1 = CCRepeatForever::create((CCActionInterval*)(CCSequence::create(a1, a2, a2->reverse(), NULL)));
    CCFiniteTimeAction* action2 = CCRepeatForever::create((CCActionInterval*)(CCSequence::create((CCActionInterval*)(a1->copy()->autorelease()),(CCActionInterval*)(a2->copy()->autorelease()), a2->reverse(), NULL) ));
    
    sp2->setAnchorPoint(CCPointMake(0,0));
    
    sp1->runAction(action1);
    sp2->runAction(action2);
 
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
