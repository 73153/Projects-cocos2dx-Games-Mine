//
//  frogstart.h
//  frogswap
//
//  Created by Anshul on 29/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef frogswap_frogstart_h
#define frogswap_frogstart_h
#include "HelloWorldScene.h"
#include "frogstart.h"

class frogstart : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void goahead();
 
    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(frogstart);
};

#endif
