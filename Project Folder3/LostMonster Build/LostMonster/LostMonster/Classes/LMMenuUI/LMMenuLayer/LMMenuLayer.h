//
//  LMMenuLayer.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMMenuLayer_h
#define LMGame_LMMenuLayer_h
#include"cocos2d.h"

class LMMenuLayer : public cocos2d::CCLayer {
    
public:
    cocos2d::CCArray *menuItemsArray;

    LMMenuLayer();
    ~LMMenuLayer();
    
    
//    virtual bool init();
//    
//    static cocos2d::CCScene* scene();
     void action(cocos2d::CCMenuItemImage* sender);

   /// LAYER_CREATE_FUNC(LMMenuLayer);
    
};

#endif
