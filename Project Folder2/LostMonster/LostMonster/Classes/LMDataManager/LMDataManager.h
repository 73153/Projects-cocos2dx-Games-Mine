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

#include "CCBReader.h"
#include "cocos-ext.h"

#include "LostMonster.h"
#include "LMGameLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LMDataManager: public cocos2d::CCObject  {
    
private:
    
    LMDataManager(void); 
    ~LMDataManager(void);
        
public:
    
    static LMDataManager* sharedManager(void);

    bool init(void);

    // ------- Variables
    
    //Cocos Builder
    cocos2d::extension::CCBReader *cocosBuilderReader;

    //Level Name
    const char* worldName;
    const char* levelName;
    int numberOfLevels;
    int subLevelNumber;
    
    const char* levelNamePrefix;
    
    //Weak Reff to gameLayer
    LMGameLayer *gameLayer;
    
    //Tutorial & Others
    bool disableMenu;
    
    //STORE
    //This Variable holds the value to go to specific Tab in Store Page
    int toGoStoreScene;
    bool canMainMenuStoreBtnWork;
    bool toAddStoreLayerInMainScreen;
    bool canStoreButtonsWork;
    
    //Live Regenaration
    float timeCount;
    
    //Check GamePlay is Running
    bool isGamePlayRunning;
    
    //show LoadingVideo
    bool showIntroVideo;
    
    //ServerSync
    const char* userName;
    const char* passWord;

};

#endif
