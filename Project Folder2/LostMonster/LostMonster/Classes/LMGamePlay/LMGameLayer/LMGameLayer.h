//
//  LMGameLayer.h
//  LostMonster
//
//  Created by Krithik B on 8/20/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "LevelHelperLoader.h"

#include "LMConfig.h"

//Managers
#include "LMLevelManager.h"
#include "LMGameUIManager.h"
#include "LMGameSoundManager.h"

//Helpers
#include "LMLine.h"
#include "TouchTrailLayer.h"
#include "MouseJointQueryCallback.h"

using namespace cocos2d;

class GLESDebugDraw;

class LMGameLayer : public cocos2d::CCLayer 
{
    
private:
    b2World* world;
    GLESDebugDraw *m_debugDraw;
    LevelHelperLoader* loader; 

public:
    ~LMGameLayer(); 
    LMGameLayer();
    
    // ******************************************************************************************
    // --------------------------------------- Variables ----------------------------------------
    
    
    //Game Vars
    int maxSliceCount;
    int sliceCount;
    int gameTimer;
    
    CCSize windowSize;
    
    bool isGameWon;
    bool isGameLost;
    
    //Managers
    LMLevelManager *levelManager;
    LMGameUIManager *gameUIManager;
    LMGameSoundManager *soundManager;
    
    //ROLLO
    LHSprite* rolloSpr;
    LHSprite *animationRolloSpr;
    LHSprite *rolloStarAnimationSpr;
    LHSprite *rolloQuestionMarkSpr;
    bool isRolloIdle;
    bool isRolloMoving;
    bool didRolloTouched;
    bool didRolloReachedExit;
    bool didGetRollosInitialPosition;
    bool runDieAnimation;
    CCPoint animationOfsetFactor;
    
    
    //Cutting
    LMLine *cuttingLineNode;
    TouchTrailLayer *trailLayer;
    CCPoint startCuttingPoint;
    CCPoint endCuttingPoint;
    CCArray *currentSplitedSpritesArr;
    bool checkWoodCollisionWithBolt;
    
    // ******************************************************************************************
    // -------------------------------------   FUNCTIONS-----------------------------------------
 
    // returns a Scene that contains the LMGameLayer as the only child
    static cocos2d::CCScene* scene();
    
    void initialiseVariables();
    void initialiseExtraViews();
    
    //Physics
    void initPhysics();
    
    //Level Helper
    void initLevelHelper();
    
    //Tutorial
    void didFinishPlayingTutorial();
    
    //Tick
    void update(float dt);
    void updateSecondTimer(float dt);
   
#ifdef kLostMonsterDebug
    virtual void draw();
#endif
    
    //Touches
    bool didTouchBegan;
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void ccTouchesMoved(CCSet* touches, CCEvent *event);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual void ccTouchesCancelled(CCSet* touches, CCEvent* event);
        
    //Split Sprites
    void splitedSprites(LHSprite *spriteA,LHSprite *spriteB);
        
    //Create Joint
    void createJointBetweenNutAndWood(LHSprite *inNut,LHSprite *inWood);
    
    //Rope
    void removeJointsForRope(LHSprite *inRope);
    
    //Wood Ice Wood Bolt Remove When touched
    void removeTouchedSpriteWithTag(int tag,CCPoint location);
  
    //Rollo is the main character
    void moveRollo();
    void getRollosInitialPosition();
    void rolloStuck();
    void rolloTouchDetected();
    void rolloReachedExit(LHContactInfo *contactInfo);
    void rolloContactWithFire(LHContactInfo *contactInfo);
    void rolloHitWithStuckWood(LHContactInfo *contactInfo);
    
    //Rollo Animations
    void runRolloIdleAnimation();
    void runRolloWhistleAnimation();
    void runRolloLookUpAnimation();
    void runRolloWalkingAnimation();
    void runRolloLookDownAnimation();
    void rolloIdleAnimationEnd();
    
    void runRolloWinAnimation();
    void rolloWinAnimOne();
    void rolloWinAnimTwo();
    
    void rolloDieAnimation();

    
    //Timer
    bool isTimerRunning;
    int timerCount;
    void startTimer();
    void updateTimer();
    void stopTimer();
    void timerEnded();
    
    
    //Wood Animation
    void runWoodAnimationAtPosition(CCPoint woodPosition);
    void removeWoodAnimation(LHSprite* senderSpr);
    
    //Game Won & Game Over
    void gameWon();
    void gameOver();
    
    //Collison with Body
    bool checkCollisionWithBox2dBody(b2Body* inBody,CCPoint touchLocationPoint);
    bool isBodyTouchingAnotherBody(b2Body* bodyOne,b2Body* bodyTwo);
        
    //Temp
    void checkForFloatingBolts();
    void removeRopesJoinedWithBolt(LHSprite * inBolt);
    
    //Level 6 Special
    void bodyGotContactWithBox2dBelt(LHContactInfo *contactInfo);
    
    //Challenge
    void checkChallengeCompleted();
    
    //sound for fire
    void initialiseSound();
    
};

#endif // __HELLO_WORLD_H__
