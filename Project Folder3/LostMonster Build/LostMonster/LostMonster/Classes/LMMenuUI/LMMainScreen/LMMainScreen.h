//
//  LMMainScreen.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMMainScreen_h
#define LMGame_LMMainScreen_h
#include"cocos2d.h"

class LMMainScreen :public cocos2d::CCLayer{
    
public:
    LMMainScreen();
    ~LMMainScreen();
    static cocos2d::CCScene* scene();

    void playAction();
    void inviteFriends();

};


#endif
