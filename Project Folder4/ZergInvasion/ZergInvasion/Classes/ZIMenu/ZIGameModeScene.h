//
//  ZIGameScene.h
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 13/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ZergInvasion_ZIGameScene_h
#define ZergInvasion_ZIGameScene_h

#include "cocos2d.h"
#include "ZICustomSprite.h"
#include "ZIMainMenu.h"
#include "ZIMultiPlayerModeLevelScene.h"
#include "ZIMainGame.h"

class ZIGameModeScene: public cocos2d::CCLayer
{
public:
    ZIGameModeScene();
    virtual ~ZIGameModeScene();
    
    static cocos2d::CCScene* scene();
    void addGameModesWithBackground();
    void gameModeMenuCallbacks(CCObject* sender);

};
#endif
