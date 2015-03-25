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

   
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    

	
    this->createDefault();
  
   	
    CCPointArray *array = CCPointArray::create(20);
    
    array->addControlPoint(ccp(0, 0));
    array->addControlPoint(ccp(80, 80));
    array->addControlPoint(ccp(s.width - 80, 80));
    array->addControlPoint(ccp(s.width - 80, s.height - 80));
    array->addControlPoint(ccp(80, s.height - 80));
    array->addControlPoint(ccp(80, 80));
    array->addControlPoint(ccp(s.width / 2, s.height / 2));
    
    CCCatmullRomBy *action = CCCatmullRomBy::create(3, array);
    CCFiniteTimeAction *reverse = action->reverse();
	
    CCFiniteTimeAction *seq = CCSequence::create(action, reverse, NULL);
	
    m_tamara->runAction(seq);
   

	

    return true;
}


void HelloWorld::createDefault()
{
    m_tamara = CCSprite::create("carsize.png");
    m_tamara->retain();
    m_tamara->setPosition(ccp(50, 50));
    this->addChild(m_tamara);

}
//void HelloWorld::tempo(){
//
//	kmGLPushMatrix();
//	kmGLTranslatef(10, 10, 0);
//	ccDrawCatmullRom(m_pArray1, 10);
//	kmGLPopMatrix();
//	ccDrawCatmullRom(m_pArray2,10);
//}




void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
