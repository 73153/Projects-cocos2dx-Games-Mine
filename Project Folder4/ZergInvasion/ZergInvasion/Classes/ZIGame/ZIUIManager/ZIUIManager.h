//
//  ZIUIManager.h
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#ifndef ZergInvasion_ZIUIManager_h
#define ZergInvasion_ZIUIManager_h

#include "ZIGameManager.h"

using namespace cocos2d;

class ZIUIManager : ZIGameManager {
    
public:
    
    ZIUIManager(void);
    virtual ~ZIUIManager(void);
    
    void setupGamePlayUI();
    void menuCallbacks(CCObject *sender); 

    // Vars
    CCSize rightPanelSize;
    CCSize topPanelSize;
};


#endif
