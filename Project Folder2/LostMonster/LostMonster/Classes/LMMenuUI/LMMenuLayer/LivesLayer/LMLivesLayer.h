//
//  LMLivesLayer.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMLivesLayer_h
#define LMGame_LMLivesLayer_h

#include"cocos2d.h"
#include "LMStoreLayer.h"

class LMLivesLayer : public cocos2d::CCLayer {
    
public:
    LMLivesLayer();
    ~LMLivesLayer();
    
    static cocos2d::CCScene* scene();
    
    LMStoreLayer *storeLayer;
};

#endif


