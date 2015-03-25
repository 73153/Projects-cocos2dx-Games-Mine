//
//  LMGameUIManager.h
//  LostMonster
//
//  Created by Krithik B on 8/28/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#ifndef LostMonster_LMGameUIManager_h
#define LostMonster_LMGameUIManager_h

#include "cocos2d.h"
#include "LMGameManager.h"
#include "LMMenuLayer.h"
#include "LMStoreLayer.h"
#include "LMMainScreen.h"

using namespace cocos2d;

class LMGameUIManager : public LMGameManager {
    
    
private:
    //instance variables
    
    
public:
    
    //member functions
    LMGameUIManager();
    ~LMGameUIManager();
    
    void intialiseUI();
    
    //lives
    LMStoreLayer *livesLayer;
    
    //
    LMMenuLayer *menuLayer;
    
    //Top Game Bar
    CCLabelTTF *maxCutsLabel;
    CCLabelTTF *noOfCutsLabel;
    CCSprite *minMaxSprite;
    
    int movesCount;

    void blinkSliceCount();
    void updateLabel(int sliceCount);
     
          
    //Timer
    CCSprite *countDownTimerSpr;
    CCLabelTTF *timerLabel;
    void showTimer();
    void updateTimerLabel(int timerCount);
    void removeTimer();
    
    
    //Challenge Intro Sprite
    void challengeIntroSpriteAction();
    void removeChallengeIntroSprite();
    
    
    //Level Subtitile
    CCPoint getSubLevelLabelPosition();
    
    
    //Game Win Game Loss
    void gameWon(bool isFirstTime, const char *relicName, bool isMaxMove);
    void gameLoss();

    //Restart
    void restartLevel();
    void restartGamePlay();
    void goBack();
    void closeButtonAction();
    
    void nextChallenge();
    void goToCollectionScene();
    
    
  
       
    //gotMainscreen
    void goToMainScreen();
    
};

#endif
