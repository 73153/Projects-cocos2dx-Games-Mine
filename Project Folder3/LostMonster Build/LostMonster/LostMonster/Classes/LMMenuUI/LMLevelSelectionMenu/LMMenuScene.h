//
//  LMMenuScene.h
//  LostMonster
//
//  Created by Krithik B on 8/22/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#ifndef LostMonster_LMMenuScene_h
#define LostMonster_LMMenuScene_h
#include "cocos2d.h"

using namespace cocos2d;

class LMMenuScene : public cocos2d::CCLayer {
    
public:
    ~LMMenuScene();
    LMMenuScene();
    
    void loadGame_1_1();
    void loadGame_1_2();
    void loadGame_1_3();
    void loadGame_1_4();
    void loadGame_1_5();
    void loadGame_1_6();
    void loadGame_1_7();
    void loadGame_1_8();
    void loadGame_1_9();
    void loadGame_1_10();
    void loadGame_1_11();
    void loadGame_1_12();

    char *worldName;
    char *levelName;
         
    static cocos2d::CCScene* scene();
};

#endif
