//
//  ZIAIModeOptionsScene.h
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 13/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ZergInvasion_ZIAIModeOptionsScene_h
#define ZergInvasion_ZIAIModeOptionsScene_h

#include "cocos2d.h"
#include "ZICustomSprite.h"
#include "ZIMultiPlayerModeLevelScene.h"
#include "ZIMainGame.h"

class ZIAIModeOptionsScene: public cocos2d::CCLayer
{
public:
    
    ZIAIModeOptionsScene();
    virtual ~ZIAIModeOptionsScene();
    
    static cocos2d::CCScene* scene();
    void addBackGroundWithButtons();
    void aiModeMenuCallbacks(CCObject* sender);
    
};
#endif
