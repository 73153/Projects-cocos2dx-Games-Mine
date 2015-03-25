//
//  mediumGame.h
//  helicopterGame
//
//  Created by Vivek on 20/11/12.
//
//

#ifndef __helicopterGame__mediumGame__
#define __helicopterGame__mediumGame__

#include <iostream>

//
//  takeItEasy.h
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
#include "gameOver.h"
#include <iostream>
USING_NS_CC;

class mediumGame: public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(mediumGame);
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
    mediumGame();
    ~mediumGame();
    
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

#endif /* defined(__helicopterGame__mediumGame__) */
