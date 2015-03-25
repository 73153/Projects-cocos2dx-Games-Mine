//
//  backgroundNext.h
//  helicopterGame
//
//  Created by Vivek on 14/11/12.
//
//

#ifndef __helicopterGame__backgroundNext__
#define __helicopterGame__backgroundNext__

#include <iostream>
#include "backgroundNext.h"
#include "HelloWorldScene.h"
USING_NS_CC;

class backgroundNext : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(backgroundNext);
    void replace();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    void move();
    void timer();
    void createHurdles();
    void createHurdlesUp();
    void createHurdlesDown();
    void deleteHurdles(CCObject *sender);
    void deleteHurdlesUp(CCObject *sender);
    void deleteHurdlesDown(CCObject *sender);
    void hurdlesTimer();
    void hurdlesTimerDown();
    void hurdlesTimerUp();
    void restart();
    void score();
    void reverseAction();
    void reverseAction1();
    backgroundNext();
    ~backgroundNext();
   
public:
    CCSprite *helicopterSpr;
    CCSprite *hurdleSpr0;
    CCSprite *hurdleSpr1;
    CCSprite *hurdleSpr2;
    CCSprite *hurdleSpr3;
    CCSprite *hurdlesSprDown;
    CCSprite *hurdlesSprDown1;
    CCSprite *hurdlesSprUp;
    CCSprite *hurdlesSprUp1;
    int timeKeeper = 0;
    int time = 0;
    int timeDown = 0;
    int timeUp = 0;
    int finalScore;
    CCArray *hurdlesArray;
    CCArray *hurdlesArrayDown;
    CCArray *hurdlesArrayUp;
    CCSize size;
    
};

#endif /* defined(__helicopterGame__backgroundNext__) */
