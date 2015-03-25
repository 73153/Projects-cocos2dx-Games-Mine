//
//  LMLevelManager.h
//  LostMonster
//
//  Created by Krithik B on 8/20/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#ifndef LostMonster_LMLevelManager_h
#define LostMonster_LMLevelManager_h

#include "cocos2d.h"
#include "LMGameManager.h"

using namespace cocos2d;

class LMLevelManager : public LMGameManager {
  

public:
    LMLevelManager();
    ~LMLevelManager();
   
    // instance variables
    const char *levelName;
    int maxCuts;
    int challengingMoveCount;
    bool canDecreaseLife;
    
    //Rollo
    float rolloGravity;
        
    //Tutorial
    bool containsTutorial;
    CCString *tutorialVideoFileName;
    CCString *tutorialHeading;
  
   // member functions
    void initialize();
    void loadLevelDataFromPlist();
    
};

#endif
