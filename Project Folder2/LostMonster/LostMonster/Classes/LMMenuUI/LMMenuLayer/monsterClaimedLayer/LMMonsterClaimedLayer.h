//
//  LMMonsterClaimedLayer.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMMonsterClaimedLayer_h
#define LMGame_LMMonsterClaimedLayer_h

#include "cocos2d.h"
#include "LMMenuLayer.h"
#include "CCScrollView.h"
#include "LMWorldSelection.h"
#include "LMSharedSoundManager.h"
#include "LMStoreLayer.h"
#include "LMDataManager.h"

USING_NS_CC_EXT;

class LMMonsterClaimedLayer : public cocos2d::CCLayer{
    
private:
    LMMenuLayer *menuLayer;
    CCScrollView *scrollView;
     
    
public:
    LMStoreLayer *storeLayer;

    
     static cocos2d::CCScene* scene();
    void action(cocos2d::CCMenuItemImage* sender);
    void removeStoreLayer(CCMenuItemImage *sender);
   
    LMMonsterClaimedLayer();
    ~LMMonsterClaimedLayer();
    
   
};

#endif
