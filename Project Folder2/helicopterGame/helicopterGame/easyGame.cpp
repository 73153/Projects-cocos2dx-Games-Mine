//
//  takeItEasy.cpp
//  helicopterGame
//
//  Created by Vivek on 20/11/12.
//
//


#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "easyGame.h"
#include "difficultGame.h"
#include "mediumGame.h"
#include "SimpleAudioEngine.h"
#include <iostream>
USING_NS_CC;

using namespace cocos2d;
using namespace CocosDenshion;



USING_NS_CC;

CCScene* easyGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    easyGame *layer = easyGame::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

easyGame::easyGame()
{
    this->hurdlesArray = CCArray::create();
    this->hurdlesArray->retain();
    
    this->hurdlesArrayDown = CCArray::create();
    this->hurdlesArrayDown->retain();
    
    this->hurdlesArrayUp = CCArray::create();
    this->hurdlesArrayUp->retain();
}

easyGame::~easyGame()
{
    this->hurdlesArray->release();
    
    this->hurdlesArrayDown->release();
    
    this->hurdlesArrayUp->release();
}

bool easyGame::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return true;
    }
    
    this->setTouchEnabled(true);
    
    CCLabelTTF *plabel1 = CCLabelTTF::create("Distance"," arial", 20);
    plabel1->setPosition(ccp(120,60));
    this->addChild(plabel1, 2, 102);
    
    CCLabelTTF *plabel2 = CCLabelTTF::create("Score"," arial", 20);
    plabel2->setPosition(ccp(380,60));
    this->addChild(plabel2, 2, 103);
    
    this->schedule(schedule_selector(easyGame::timer));
    
    this->schedule(schedule_selector(easyGame::hurdlesTimer));
    
    this->schedule(schedule_selector(easyGame::hurdlesTimerDown));
    
    this->schedule(schedule_selector(easyGame::hurdlesTimerUp));
    
    CCLabelTTF *labelp = CCLabelTTF::create("RESTART"," ARIAL", 20);
    CCMenuItemLabel *lab = CCMenuItemLabel::create(labelp, this, menu_selector(easyGame::restart));
    
    CCMenu *m = CCMenu::create(lab,NULL);
    m->setPosition(ccp(200,300));
    this->addChild(m,1);
    
    size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *bckSpr = CCSprite::create("blackBcg.png");
    bckSpr->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(bckSpr,1);
    
    helicopterSpr = CCSprite::create("helicopter.png");
    helicopterSpr->setPosition(ccp(50,160));
    this->addChild(helicopterSpr,1);
    return true;
}

void easyGame::createHurdles()
{
    hurdleSpr0 = CCSprite::create("hurdles1.png");
    hurdleSpr0->setPosition(ccp(size.width+hurdleSpr0->getContentSize().width,arc4random() % 320));
    this->addChild(hurdleSpr0,2);
    
    CCFiniteTimeAction *moveAction1 = CCMoveTo::create(1, ccp(1, hurdleSpr0->getPosition().y));
    
    CCFiniteTimeAction *callBack = CCCallFuncN::create(this,callfuncN_selector(easyGame::deleteHurdles));
    
    CCSequence *actioNSequence = (CCSequence*)CCSequence::create(moveAction1,callBack,NULL);
    hurdleSpr0->runAction(actioNSequence);
    this->hurdlesArray->addObject(hurdleSpr0);
}

void easyGame::createHurdlesDown()
{
    hurdlesSprDown = CCSprite::create("hurdlesSprDown.png");
    hurdlesSprDown->setPosition(ccp(size.width/2,size.height-300));
    this->addChild(hurdlesSprDown,1);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    hurdlesSprDown1 = CCSprite::create("hurdlesDownImp.png");
    hurdlesSprDown1->setPosition(ccp(800,size.height-300));
    this->addChild(hurdlesSprDown1,1);
    
    CCLOG(" pos %d and %d ",hurdlesSprDown->getPositionX(),hurdlesSprDown->getPositionY());
    
    CCFiniteTimeAction *moveAction = CCMoveTo::create(3, ccp(-800, hurdlesSprDown->getPosition().y));
    
    CCFiniteTimeAction *callBack1 = CCCallFuncN::create(this,callfuncN_selector(easyGame::deleteHurdlesDown));
    
//    CCFiniteTimeAction *callBack2 = CCCallFuncN::create(this,callfuncN_selector(easyGame::reverseAction1));
    CCSequence*actioNSequence = (CCSequence*)CCSequence::create(moveAction,callBack1,NULL);
    hurdlesSprDown->runAction(actioNSequence);
    this->hurdlesArrayDown->addObject(hurdlesSprDown);
 
    CCFiniteTimeAction *moveAction1 = CCMoveTo::create(3, ccp(-1460, hurdlesSprDown->getPosition().y));
    CCFiniteTimeAction *callBack2 = CCCallFuncN::create(this,callfuncN_selector(easyGame::deleteHurdlesDown));
    CCSequence*actioNSequence1 = (CCSequence*)CCSequence::create(moveAction1,callBack2,NULL);
    hurdlesSprDown1->runAction(actioNSequence1);
    this->hurdlesArrayDown->addObject(hurdlesSprDown1);

}

void easyGame::reverseAction1()
{
//        hurdlesSprDown1 = CCSprite::create("hurdlesDownImp.png");
//        hurdlesSprDown1->setPosition(ccp(480,size.height-300));
//        this->addChild(hurdlesSprDown1,1);
//    
//        CCFiniteTimeAction *moveAction1 = CCMoveTo::create(2, ccp(-880, hurdlesSprDown1->getPosition().y));
//        CCFiniteTimeAction *callBack = CCCallFuncN::create(this,callfuncN_selector(easyGame::createHurdlesDown));
//         CCFiniteTimeAction *callBack1 = CCCallFuncN::create(this,callfuncN_selector(easyGame::deleteHurdlesDown));
//    
//        CCFiniteTimeAction *actioNSequence = CCSequence::create(moveAction1,callBack,callBack1,NULL);
//        hurdlesSprDown1->runAction(actioNSequence);
//        this->hurdlesArrayDown->addObject(hurdlesSprDown1);
}

void easyGame::createHurdlesUp()
{
    hurdlesSprUp = CCSprite::create("hurdlesSprUp.png");
    hurdlesSprUp->setPosition(ccp(size.width/2,size.height-10));
    this->addChild(hurdlesSprUp,1);
    
    hurdlesSprUp1 = CCSprite::create("hurdlesUPImp.png");
    hurdlesSprUp1->setPosition(ccp(800,size.height-10));
    this->addChild(hurdlesSprUp1,1);
    
    CCLOG("%d and %d",hurdlesSprUp->getPositionX(),hurdlesSprUp->getPositionY());
    CCFiniteTimeAction *moveAction = CCMoveTo::create(3, ccp(-900, hurdlesSprUp->getPosition().y));
    CCFiniteTimeAction *callBack = CCCallFuncN::create(this,callfuncN_selector(easyGame::deleteHurdlesUp));
    CCFiniteTimeAction *actioNSequence = CCSequence::create(moveAction,callBack,NULL);
    hurdlesSprUp->runAction(actioNSequence);
    this->hurdlesArrayUp->addObject(hurdlesSprUp);
    

    
    CCFiniteTimeAction *moveAction1 = CCMoveTo::create(5, ccp(-1460, hurdlesSprUp1->getPosition().y));
    CCFiniteTimeAction *callBack1 = CCCallFuncN::create(this,callfuncN_selector(easyGame::deleteHurdlesUp));
    CCFiniteTimeAction *actioNSequence1 = CCSequence::create(moveAction1,callBack1,NULL);
    hurdlesSprUp1->runAction(actioNSequence1);
    this->hurdlesArrayUp->addObject(hurdlesSprUp1);
    
}

void easyGame::reverseAction()
{
    //    hurdlesSprUp1 = CCSprite::create("hurdlesSprUp1.png");
    //    hurdlesSprUp1->setPosition(ccp(300,size.height-30));
    //    this->addChild(hurdlesSprUp1,1);
    //    CCFiniteTimeAction  *moveAction1 = CCMoveTo::create(2, ccp(-300, hurdlesSprUp1->getPosition().y));
    //    CCFiniteTimeAction  *callBack1 = CCCallFuncN::create(this,callfuncN_selector(Easy::deleteHurdlesUp));
    //    CCFiniteTimeAction  *callBack2 = CCCallFuncN::create(this,callfuncN_selector(Easy::createHurdlesUp));
    //    CCFiniteTimeAction *actioNSequence1 = CCSequence::create(moveAction1,callBack2,callBack1,NULL);
    //    hurdlesSprUp1->runAction(actioNSequence1);
    //    this->hurdlesArrayUp->addObject(hurdlesSprUp1);
}


void easyGame::hurdlesTimer()
{
    time++;
    if(time % 60 ==0)
    {
        this->createHurdles();
    }
    CCRect helicopterSprRect = CCRectMake(helicopterSpr->getPosition().x - helicopterSpr->getContentSize().width/2,helicopterSpr->getPosition().y - helicopterSpr->getContentSize().height/2,helicopterSpr->getContentSize().width, helicopterSpr->getContentSize().height);
    
    CCObject *hurdlesObj = NULL;
    
    CCARRAY_FOREACH(this->hurdlesArray, hurdlesObj) {
        
        CCSprite *hurdleSpr = (CCSprite *)hurdlesObj;
        CCRect hurdlesRect = CCRectMake(hurdleSpr->getPosition().x - hurdleSpr->getContentSize().width/2,
                                        hurdleSpr->getPosition().y - hurdleSpr->getContentSize().height/2,
                                        hurdleSpr->getContentSize().width,
                                        hurdleSpr->getContentSize().height);
        
        if(CCRect::CCRectIntersectsRect(helicopterSprRect, hurdlesRect))
        {
            this->replace();
        }
    }
}

void easyGame::hurdlesTimerDown()
{
    timeDown++;
    if(timeDown % 80 ==0)
    {
        this->createHurdlesDown();
    }
    CCRect helicopterSprRect = CCRectMake(helicopterSpr->getPosition().x - helicopterSpr->getContentSize().width/2,helicopterSpr->getPosition().y - helicopterSpr->getContentSize().height/2,helicopterSpr->getContentSize().width, helicopterSpr->getContentSize().height);
    
    CCObject *hurdlesObj = NULL;
    
    CCARRAY_FOREACH(this->hurdlesArrayDown, hurdlesObj) {
        
        CCSprite *hurdlesSprDown = (CCSprite *)hurdlesObj;
        
        CCRect hurdlesSprDownRect = CCRectMake(hurdlesSprDown->getPosition().x - hurdlesSprDown->getContentSize().width/2,hurdlesSprDown->getPosition().y - hurdlesSprDown->getContentSize().height/2,hurdlesSprDown->getContentSize().width, hurdlesSprDown->getContentSize().height);
        
        if(CCRect::CCRectIntersectsRect(hurdlesSprDownRect, helicopterSprRect))
        {
            this->replace();
        }
    }
}

void easyGame::hurdlesTimerUp()
{
    timeUp++;
    if(timeUp % 80 ==0)
    {
        this->createHurdlesUp();
    }
    CCRect helicopterSprRect = CCRectMake(helicopterSpr->getPosition().x - helicopterSpr->getContentSize().width/2,helicopterSpr->getPosition().y - helicopterSpr->getContentSize().height/2,helicopterSpr->getContentSize().width, helicopterSpr->getContentSize().height);
    
    CCObject *hurdlesObj = NULL;
    CCARRAY_FOREACH(this->hurdlesArrayUp, hurdlesObj) {
        
        CCSprite *hurdlesSprup = (CCSprite *)hurdlesObj;
        CCRect hurdlesSprUpRect = CCRectMake(hurdlesSprUp->getPosition().x - hurdlesSprUp->getContentSize().width/2,hurdlesSprUp->getPosition().y - hurdlesSprUp->getContentSize().height/2,hurdlesSprUp->getContentSize().width, hurdlesSprUp->getContentSize().height);
        
        if(CCRect::CCRectIntersectsRect(hurdlesSprUpRect, helicopterSprRect))
        {
            this->replace();
        }
    }
}

void easyGame::deleteHurdles(CCObject *sender)
{
    CCSprite *tempHurdles = (CCSprite *)sender;
    tempHurdles->removeFromParentAndCleanup(true);
    this->hurdlesArray->removeObject(tempHurdles);
}

void easyGame::deleteHurdlesDown(CCObject *sender)
{
    CCSprite *tempHurdlesDown = (CCSprite *)sender;
    tempHurdlesDown->removeFromParentAndCleanup(true);
    this->hurdlesArrayDown->removeObject(tempHurdlesDown);
}

void easyGame::deleteHurdlesUp(CCObject *sender)
{
    CCSprite *tempHurdlesUp = (CCSprite *)sender;
    tempHurdlesUp->removeFromParentAndCleanup(true);
    this->hurdlesArrayDown->removeObject(tempHurdlesUp);
}

void easyGame::restart()
{
    CCDirector::sharedDirector()->replaceScene(gameStart::scene());
}

void easyGame::replace()
{
    CCDirector::sharedDirector()->replaceScene(gameOver::scene());
}

void easyGame::timer()
{
    timeKeeper++;
    if(timeKeeper % 1 == 0)
    {
        char string1[100]={0};
        sprintf(string1, "Distance %1.0d", timeKeeper);
        CCLabelTTF *tempLabel = (CCLabelTTF *)this->getChildByTag(102);
        tempLabel->setString(string1);
        finalScore = timeKeeper;
        this->score();
    }
}

void easyGame::score()
{
    char string[100];
    sprintf(string, "Score %d", finalScore);
    CCLabelTTF *tempLabel3 = (CCLabelTTF *)this->getChildByTag(103);
    tempLabel3->setString(string);
    sprintf(string, "score %d", finalScore);
    CCLOG(" score = %d",finalScore);
    
    if(timeKeeper > finalScore)
    {
        finalScore=timeKeeper;
        CCLabelTTF *tempLabel = (CCLabelTTF *)this->getChildByTag(103);
        tempLabel->setString(string);
        sprintf(string, "score %d", finalScore);
        CCLOG(" score = %d",finalScore);
    }
    else if(timeKeeper < finalScore)
    {
        finalScore=timeKeeper;
        CCLabelTTF *tempLabel1 = (CCLabelTTF *)this->getChildByTag(103);
        tempLabel1->setString(string);
        sprintf(string, "score %d", finalScore);
        CCLOG(" score = %d",finalScore);
    }
}

void easyGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( pTouches->anyObject());
    CCPoint location = touch->getLocation();
    CCActionInterval*  actionTo = CCMoveTo::create(1.5, CCPointMake(50,size.height-helicopterSpr->getContentSize().width/2));
    helicopterSpr->runAction( actionTo);
}

void easyGame::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    CCPoint location = touch->getLocationInView();
}

void easyGame::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocationInView();
    CCActionInterval*  actionTo = CCMoveTo::create(1.5, CCPointMake(50,size.height/helicopterSpr->getContentSize().width/2));
    helicopterSpr->runAction( actionTo);
}
