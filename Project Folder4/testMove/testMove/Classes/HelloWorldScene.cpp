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

    
    //Add 2  button
    
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint buttonPos = ccp(30,30);
    
    CCMenuItemImage* item1 = CCMenuItemImage::create("1copy.png", "1copy.png", this, menu_selector(HelloWorld::carmove));
    item1->setPosition(buttonPos);
    
    CCLog("buttonPos is X%f Y%f ",buttonPos.x,buttonPos.y);
    
    
    
    
    CCMenuItem* item2 = CCMenuItemImage::create("2copy.png", "2copy.png", this, menu_selector(HelloWorld::carreverse) );
    item2->setPosition(ccp(450,30));
    

    CCMenu* menu = CCMenu::create(item1,item2, NULL);
    menu->setPosition(CCPointZero);
    addChild(menu,0);
    

    //Add a car
    carSprite = CCSprite::create("vivek.png");
    
    // position the sprite on the center of the screen
    carSprite->setPosition( ccp(winsize.width/2, winsize.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(carSprite, 0);
 
   
    return true;
}

void HelloWorld::carmove(){
    
    
    CCLOG("calling");
    
    
   CCSize winsize = CCDirector::sharedDirector()->getWinSize();
       
    CCActionInterval*  actiono = CCMoveTo::create(1, CCPointMake(20,160 ));
   CCActionInterval*  rotate = CCRotateTo::create( 1, 180);
     CCActionInterval*  rotate1 = CCRotateTo::create( 1, 360);
   
//     CCActionInterval*  rotate2 = CCRotateBy::create(1, 360);
    
     CCFiniteTimeAction*  action = CCSequence::create(actiono,rotate,rotate1
                                                    ,NULL);
    carSprite->runAction(action);
  
}
void HelloWorld::carreverse(){
    
    CCFiniteTimeAction* reversed = CCMoveTo::create(2, CCPointMake(450,160));
    CCActionInterval*  rotate = CCRotateTo::create( 1, 180);
    CCActionInterval*  rotate1 = CCRotateTo::create( 1, 360);
    
    CCFiniteTimeAction*  action = CCSequence::create(reversed,rotate,rotate1, NULL);
    carSprite->runAction(action);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
