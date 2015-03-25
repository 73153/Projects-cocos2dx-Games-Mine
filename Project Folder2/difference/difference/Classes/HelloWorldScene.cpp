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

    
    m_tamara = CCSprite::create("car2.png");
    addChild(m_tamara, 1);
    m_tamara->setPosition(CCPoint(130, 160));
    
    CCActionInterval *actionTo =  CCSkewTo::create(4, 37.2f, -37.2f);
    m_tamara->runAction(actionTo);
    
    CCSprite *m_tamara2 = CCSprite::create("car2.png");
    addChild(m_tamara2, 1);
    m_tamara2->setPosition(CCPoint(350, 160));
    
    CCActionInterval *actionTo1 =  CCSkewBy::create(4, 37.2f, -37.2f);
    m_tamara2->runAction(actionTo1);
    
//    
//    CCActionInterval *actionTo = CCSkewTo::create(2, 37.2f, -37.2f);
//    CCActionInterval *actionToBack = CCSkewTo::create(2, 0, 0);
//    CCActionInterval *actionBy = CCSkewBy::create(2, 0.0f, -90.0f);
//    CCActionInterval *actionBy2 = CCSkewBy::create(2, 45.0f, 45.0f);
//    CCActionInterval *actionByBack = actionBy->reverse();
//    
//    m_tamara->runAction(CCSequence::create(actionTo, actionToBack, NULL));
//    m_grossini->runAction(CCSequence::create(actionBy, actionByBack, NULL));
//    
//    m_kathia->runAction(CCSequence::create(actionBy2, actionBy2->reverse(), NULL));
//
    

    
    
    /*
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    

   m_tamara->setPosition(CCPointMake(400, 160));

    
    
    CCActionInterval *actionTo =  CCMoveTo::create(2, CCPointMake(s.width-40, s.height-40));
    
    CCActionInterval *actionToBack =  CCMoveBy::create(2, CCPointMake(30, 160));
    
    m_tamara->runAction(CCSequence::create(actionTo, actionToBack, NULL));

    //CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_I8);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("texturedemo1.plist");
    
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("images.jpg");
    CCSprite *sprite = CCSprite::createWithSpriteFrame(frame);
    sprite->setPosition(ccp(240,160));
    this->addChild(sprite);
    
*/
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
