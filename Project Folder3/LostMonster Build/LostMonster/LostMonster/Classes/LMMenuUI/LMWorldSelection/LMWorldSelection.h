//
//  LMWorldSelection.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMWorldSelection_h
#define LMGame_LMWorldSelection_h

#include "cocos2d.h"
using namespace cocos2d;
class LMWorldselection :public cocos2d::CCLayer
{
    public:
    LMWorldselection();
    ~LMWorldselection();
    
    //Functions
    
    void goToLoneIslandLevels();
    void goToPeaksOfDestinyLevels(CCObject *obj);
    void goToChamberOfBeyondLevels(CCObject *obj);
    void goToForestOfAdventureLevels(CCObject *obj);
    void goToSandOfPearlLevels(CCObject *obj);
    void goToHillsOfCuriosity( CCObject *obj);
    void goToWaterUnderSeaLevels(CCObject *obj);
    void lockAction( int tag);
    //Touches

    static cocos2d::CCScene* scene();
    
};


#endif
