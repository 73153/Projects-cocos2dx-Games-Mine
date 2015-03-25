#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <sys/time.h>
#include "PlayAgain.h"


USING_NS_CC;

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = new CCScene();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = new HelloWorld();
    
    // add layer as a child to scene
    scene->addChild(layer);
    //layer->release();
    
    // return the scene
    return scene;
}

HelloWorld::HelloWorld() {
    
    this->setTouchEnabled(true);
    
    this->bulletArray = CCArray::create();
    this->bulletArray->retain();
    
    this->monstersArray = CCArray::create();
    this->monstersArray->retain();
    
    this->gameOverCount = 3;
    
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
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    CCSprite *playerSprite = CCSprite::create("Player.png");
    playerSprite->setPosition(ccp(0,160));
    this->addChild(playerSprite, 1, 100);
    
    
    schedule(schedule_selector(HelloWorld::mainTimer));
    
    CCLabelTTF *plabel = CCLabelTTF::create("score"," Your Score", 20);
    //plabel->cocos2d::CCNode::setPosition(400, 300);
    plabel->setPosition(ccp(400, 300));
    this->addChild(plabel, 1, 101);
    
}



HelloWorld::~HelloWorld() {
    
    
}



void HelloWorld::draw(){
    
    CCLog("draw method");
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
    
    this->setTouchEnabled(true);
    
    this->bulletArray = CCArray::create();
    this->bulletArray->retain();
    
    this->monstersArray = CCArray::create();
    this->monstersArray->retain();
    
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
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    CCSprite *playerSprite = CCSprite::create("Player.png");
    playerSprite->setPosition(ccp(0,160));
    this->addChild(playerSprite, 1, 100);
    
    
    schedule(schedule_selector(HelloWorld::mainTimer));
    
    CCLabelTTF *plabel = CCLabelTTF::create("score"," Your Score", 20);
    //plabel->cocos2d::CCNode::setPosition(400, 300);
    plabel->setPosition(ccp(400, 300));
    this->addChild(plabel, 1, 101);
    
    return true;
}

void HelloWorld::createMonster()
{
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *monsterSprite = CCSprite::create("Target.png");
    monsterSprite->setPosition(ccp(winSize.width + monsterSprite->getContentSize().width/2,arc4random() % 320));
    this->addChild(monsterSprite);
    
    CCFiniteTimeAction *moveAction1 = CCMoveTo::create(1, ccp(0, monsterSprite->getPosition().y));
    
    CCFiniteTimeAction *callBack = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::deleteMonster));
    
    CCFiniteTimeAction *actioNSequence = CCSequence::create(moveAction1,callBack,NULL);
    
    monsterSprite->runAction(actioNSequence);
    
    this->monstersArray->addObject(monsterSprite);
}

void HelloWorld::deleteMonster(CCObject *sender)
{
    
    CCSprite *tempMonster = (CCSprite *)sender;
    
    if(tempMonster->getPosition().x==0 && miss <= 3)
    {
        
        miss++;
        char string[12];
        sprintf(string, "Missed %d", miss);
        
        CCLabelTTF *tempLabel = (CCLabelTTF *)this->getChildByTag(101);
        tempLabel->setString(string);
        
        if (miss == this->gameOverCount) {
            
            CCDirector::sharedDirector()->replaceScene(PlayAgain::scene());
//            sprintf(string, "Game Over %d", miss);
//            tempLabel->setString(string);
//            tempLabel->setPosition(ccp(240, 160));
        }
    }
    tempMonster->removeFromParentAndCleanup(true);
    this->monstersArray->removeObject(tempMonster);
}

void HelloWorld::createbullet(CCPoint toMovePoint) {
    
    CCSize Winsize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *bulletSprite=CCSprite::create("Projectile.png");
    bulletSprite->setPosition(ccp(0,160));
    this->addChild(bulletSprite);
    
    CCFiniteTimeAction *moveAction1 = CCMoveTo::create(1, toMovePoint);
    CCFiniteTimeAction *callBack = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::deleteBullet));
    CCFiniteTimeAction *actioNSequence = CCSequence::create(moveAction1,callBack,NULL);
    bulletSprite->runAction(actioNSequence);
    this->bulletArray->addObject(bulletSprite);
}

void HelloWorld::deleteBullet(CCObject *sender) {
    
    CCNode *tempMonster = (CCNode *)sender;
    tempMonster->removeFromParentAndCleanup(true);
    this->bulletArray->removeObject(tempMonster);
}

void HelloWorld::mainTimer()
{
      timeKeeper++;
    
    if (timeKeeper % 180 == 0) {
        
        this->createMonster();
    }
    
    // Checking collision
    CCObject *bulletObj = NULL;
    CCObject *monsterObj = NULL;
    
    CCARRAY_FOREACH(this->bulletArray, bulletObj) {
        
        CCSprite *bulletSpr = (CCSprite *)bulletObj;
        CCRect bulletRect = CCRectMake(bulletSpr->getPosition().x - bulletSpr->getContentSize().width/2,
                                       bulletSpr->getPosition().y - bulletSpr->getContentSize().height/2,
                                       bulletSpr->getContentSize().width,
                                       bulletSpr->getContentSize().height);
        
        CCARRAY_FOREACH(this->monstersArray, monsterObj) {
            
            CCSprite *monsterSpr = (CCSprite *)monsterObj;
            
            CCRect monsterRect = CCRectMake(monsterSpr->getPosition().x - monsterSpr->getContentSize().width/2,
                                            monsterSpr->getPosition().y - monsterSpr->getContentSize().height/2,
                                            monsterSpr->getContentSize().width,
                                            monsterSpr->getContentSize().height);
            
            if (CCRect::CCRectIntersectsRect(bulletRect, monsterRect) && miss <=3) {
                
                CCLog("Collided......");
                this->deleteMonster(monsterSpr);
                count++;
                
                char string[12] = {0};
                sprintf(string, "Score %d", count);
                
                CCLabelTTF *tempLabel = (CCLabelTTF *)this->getChildByTag(101);
                tempLabel->setString(string);
                CCLog("increment count....");
            }
        }
    }
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
    
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    CCPoint location = touch->locationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    CCLog("touches began %f %f",location.x,location.y);
    this->createbullet(location);
}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
    
    CCLog("touches moved");
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
    
    CCLog("touches ended");
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
