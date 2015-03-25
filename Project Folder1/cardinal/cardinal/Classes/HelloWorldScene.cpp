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
    
    
    all = CCSprite::create("carsize.png");
    
    this->addChild(all,3);
    
    all->setPosition(CCPointMake(20, 160));
    
    
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCPointArray *m_pArray1 = CCPointArray::create(20);
    m_pArray1->addControlPoint(ccp(0, 0));
    m_pArray1->addControlPoint(ccp(50, 40));
    m_pArray1->addControlPoint(ccp(200, 60));
    m_pArray1->addControlPoint(ccp(100,80));

    
    CCCardinalSplineBy *action = CCCardinalSplineBy::create(2, m_pArray1, 0);
    
    CCActionInterval *reverse = action->reverse();
	
    CCFiniteTimeAction *seq = CCSequence::create(action, reverse, NULL);
    
    all->runAction(seq);
    
    return true;
}

void HelloWorld::draw()
{
	// move to 50,50 since the "by" path will start at 50,50
	kmGLPushMatrix();
	kmGLTranslatef(200, 127, 75);
	ccDrawCatmullRom(m_pArray1, 50);
	kmGLPopMatrix();
    //ccDrawCatmullRom(m_pArray2,50);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
