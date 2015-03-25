//
//  LMRelicsLayer.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMRelicsLayer_h
#define LMGame_LMRelicsLayer_h


#include "cocos2d.h"
#include "LMMenuLayer.h"
#include "CCScrollView.h"
#include "LMWorldSelection.h"
#include "LMSharedSoundManager.h"
#include "LMStoreLayer.h"
#include "LMDataManager.h"


USING_NS_CC_EXT;

class LMRelicsLayer : public cocos2d::CCLayer{
private:
    LMMenuLayer *menuLayer;
    CCScrollView *scrollView;

    
public:
     LMStoreLayer *storeLayer;
    void action(cocos2d::CCMenuItemImage* sender);
    void removeStoreLayer(CCMenuItemImage *sender);
    static cocos2d::CCScene* scene();
   
    
    
    LMRelicsLayer();
    ~LMRelicsLayer();
    
   };

#endif
