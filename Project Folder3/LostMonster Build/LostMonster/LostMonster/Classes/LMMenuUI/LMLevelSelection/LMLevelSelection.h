//
//  LMLevelSelection.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMLevelSelection_h
#define LMGame_LMLevelSelection_h

#include "cocos2d.h"
//#include "CCScrollView.h"

using namespace cocos2d;

class LMLevelSelection :public cocos2d::CCScene{

    public:
    
    LMLevelSelection();
    ~LMLevelSelection();
    
    CCArray *menuItemsArray;
    bool isLevelLocked;
    bool isLevelAchieved;
   //CCScrollView *scrollview;
    
    
    char *levelName;
    void lockAction( int tag);

    static cocos2d::CCScene* scene();
    void gotoLevel(CCObject *sender);
    void goBack();
    void goToregionIntro();
    CCPoint getPosiiton(CCMenuItem *);
    
};

#endif
