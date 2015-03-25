#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "BBMGSprite.h"


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
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fliptest.plist");
    
    topCard = CCSprite::createWithSpriteFrameName("2x2_1.png");
    topCard->setPosition(ccp(240,160));
    this->addChild(topCard);
    
    isFlipped = false;
    this->flipCards(topCard);  
    return true;
}



void HelloWorld::flipCards(CCSprite *topCard) {
    
    if (isFlipped) {
        
        isFlipped = false;
    }
    else {
        
        isFlipped = true;
    }
    
    float d = 0.25f;
    
    CCOrbitCamera *firstHalfFlip = CCOrbitCamera::create(d/2, 1, 0, 0, 90, 0, 0);
    CCOrbitCamera *secondHalfFlip = CCOrbitCamera::create(d/2, 1, 0, 270, 90, 0, 0);
    
    CCCallFuncN* changeMatchCardImageFunc = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::changeImageOfTopCard));
    
    CCFiniteTimeAction *flipSequence = CCSequence::create(firstHalfFlip, changeMatchCardImageFunc,secondHalfFlip, NULL);
    topCard->runAction(flipSequence);
}


void HelloWorld::changeImageOfTopCard(CCSprite *matchCard) {
    
    if(isFlipped)
    {
        //Change the image of Top Card to bottom Card
        CCSpriteFrame *newImage = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("2x2_1.png");
        matchCard->setDisplayFrame(newImage);
        
    }
    else
    {
        //Change the image of bottom Card to Top Card
        CCSpriteFrame *newImage = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("card_2x2.png");
        topCard->setDisplayFrame(newImage);
    }
}

#pragma mark - Touch
void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event) {
    
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
    }
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
