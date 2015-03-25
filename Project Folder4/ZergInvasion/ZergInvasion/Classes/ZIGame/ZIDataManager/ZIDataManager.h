//
//  DNDataManager.h
//  Dominoes
//
//  Created by ICRG LABS on 10/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

// Singleton...

#ifndef ZergInvasion_ZIDataManager_h
#define ZergInvasion_ZIDataManager_h

#include "cocos2d.h"
#include "Box2D.h"
#include "ZIMainGame.h"
#include "ZIGameConstants.h"

using namespace cocos2d;

class ZIDataManager: public cocos2d::CCObject  {
    
private:
    
    ZIDataManager(void); 
    virtual ~ZIDataManager(void);
    
public:
    
    bool init(void);
    static ZIDataManager* sharedManager(void);
    
    // var
    ZIMainGame *gameLayer;
    b2World* gameWorld;
    
    cocos2d::CCSize screenSize;
    
    cocos2d::CCLayer *UILayer;
};

#endif
