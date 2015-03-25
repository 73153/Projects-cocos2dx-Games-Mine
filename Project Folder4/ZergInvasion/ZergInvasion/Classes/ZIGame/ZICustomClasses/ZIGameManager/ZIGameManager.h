//
//  ZIGameManager.h
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#ifndef ZergInvasion_ZIGameManager_h
#define ZergInvasion_ZIGameManager_h

#include "cocos2d.h"

class ZIMainGame;

class ZIGameManager : public cocos2d::CCObject {
    
public:
    
    ZIGameManager(void);
    virtual ~ZIGameManager(void);
    
    ZIMainGame *gameLayer;
};


#endif
