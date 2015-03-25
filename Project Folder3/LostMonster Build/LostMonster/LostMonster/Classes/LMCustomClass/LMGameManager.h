//
//  LMGameManager.h
//  LostMonster
//
//  Created by Krithik B on 8/28/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#ifndef LostMonster_LMGameManager_h
#define LostMonster_LMGameManager_h


#include "cocos2d.h"

class LMGameManager : public cocos2d::CCObject {
    
public:
    
    LMGameManager(void);
    virtual ~LMGameManager(void);
    
    cocos2d::CCLayer *gameLayer;
}; 


#endif
