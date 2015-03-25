//
//  frogover.h
//  frogswap
//
//  Created by Anshul on 29/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef frogswap_frogover_h
#define frogswap_frogover_h
#include "HelloWorldScene.h"
#include "frogover.h"

class frogover : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void backtogame();
    
    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(frogover);
};

#endif
