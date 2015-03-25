//
//  ZIMainMenu.h
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 12/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ZergInvasion_ZIMainMenu_h
#define ZergInvasion_ZIMainMenu_h


#include "cocos2d.h"
#include "ZICustomSprite.h"
#include "ZIGameModeScene.h"
#include "ZIStoreScene.h"
#include "ZIScoreScene.h"

class ZIMainMenu: public cocos2d::CCLayer
{
public:
    
    ZIMainMenu();
    virtual ~ZIMainMenu();
    CCMenuItemToggle *soundButton;
    static cocos2d::CCScene* scene();
    void addBackGroundWithButtons();
    void menuCallbacks(CCObject* sender);    
};
#endif
