//
//  LMDataManager.h
//  Lost Monster
//
//  Created by ICRG LABS on 10/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

// Singleton...

#ifndef _LMDataManager_h
#define _LMDataManager_h

#include "LostMonster.h"
#include "LMGameLayer.h"

class LMDataManager: public cocos2d::CCObject  {
    
private:
    
    LMDataManager(void); 
    ~LMDataManager(void);
        
public:
    
    static LMDataManager* sharedManager(void);

    bool init(void);

    // ------- Variables

    //Level Name
    const char* worldName;
    const char* levelName;
    int numberOfLevels;
    int subLevelNumber;
    
    const char* levelNamePrefix;
    
    LMGameLayer *gameLayer;
    
    //Tutorial
    bool isTutorialPlaying;

    //Temp
    bool check;
    
};

#endif
