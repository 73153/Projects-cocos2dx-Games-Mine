//
//  ZIStoreScene.h
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 13/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ZergInvasion_ZIStoreScene_h
#define ZergInvasion_ZIStoreScene_h
#include  "cocos2d.h"
#include "ZICustomSprite.h"
#include "ZIMainMenu.h"
class ZIStoreScene: public cocos2d::CCLayer
{
public:
    
    ZIStoreScene();
    virtual ~ZIStoreScene();
   
    static cocos2d::CCScene* scene();
    void addBackGroundWithButtons();
    void storeMenuCallbacks(CCObject* sender);
    
    
};
#endif
