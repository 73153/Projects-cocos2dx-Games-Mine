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

using namespace cocos2d;

class LMGameUIManager : public LMGameManager {
    
    
private:
    //instance variables
    
    
public:
    
    //member functions
    LMGameUIManager();
    ~LMGameUIManager();
    
    
    void intialiseUI();
  
    //Restart
    void restartLevel();
    void goBack();
    void blinkSliceCount();
    void updateLabel(int sliceCount);
    CCLabelTTF *maxCutsLabel;
    CCLabelTTF *noOfCutsLabel;
    CCSprite *minMaxSprite;
    
    
    //Timer
    CCSprite *countDownTimerSpr;
    CCLabelTTF *timerLabel;
    void showTimer();
    void updateTimerLabel(int timerCount);
    void removeTimer();
    void removeChallengeIntroSprite();
    void challengeIntroSpriteAction();
    CCPoint getSubLevelLabelPosition();
    
    void gameWon(bool isFirstTime);
    void gameLoss();

    
    
    
};

#endif
