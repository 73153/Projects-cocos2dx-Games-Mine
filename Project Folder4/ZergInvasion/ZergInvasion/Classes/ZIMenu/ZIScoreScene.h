//
//  ZIScoreScene.h
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 13/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ZergInvasion_ZIScoreScene_h
#define ZergInvasion_ZIScoreScene_h

#include "cocos2d.h"
#include "ZICustomSprite.h"
#include "ZIMainMenu.h"

class ZIScoreScene: public cocos2d::CCLayer
{
public:
    
    ZIScoreScene();
    virtual ~ZIScoreScene();
     
    static cocos2d::CCScene* scene();
    void addBackGroundWithButtons();
    void scoreMenuCallbacks(CCObject* sender);    
};
#endif
