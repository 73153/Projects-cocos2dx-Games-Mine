//
//  PlayAgain.h
//  Test1
//
//  Created by Deepthi on 25/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Test1_PlayAgain_h
#define Test1_PlayAgain_h

#include "cocos2d.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

class PlayAgain : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    
    PlayAgain();
    ~PlayAgain();
    
    static cocos2d::CCScene* scene();
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void backToScene();
};


#endif
