//
//  ZISelectModeLevelScene.h
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 13/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ZergInvasion_ZISelectModeLevelScene_h
#define ZergInvasion_ZISelectModeLevelScene_h

#include  "cocos2d.h"
#include "ZICustomSprite.h"
#include "ZIGameModeScene.h"
#include "ZIAIModeOptionsScene.h"
#include "ZIMainGame.h"

class ZIMultiPlayerModeLevelScene: public cocos2d::CCLayer
{
public:
    
    ZIMultiPlayerModeLevelScene();
    virtual ~ZIMultiPlayerModeLevelScene();
    
    static cocos2d::CCScene* scene();
    void addBackGroundWithButtons();
    void multiPlayerMenuCallbacks(CCObject* sender);
     
};
#endif
