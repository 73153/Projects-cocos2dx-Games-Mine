//
//  LMSharedSoundManager.h
//  LostMonster
//
//  Created by Krithik B on 30/10/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#ifndef LostMonster_LMSharedSoundManager_h
#define LostMonster_LMSharedSoundManager_h


#include "cocos2d.h"

//THIS IS SHARED MANAGER FOR PLAYING SOUND FROM ANYWHERE
//ALSO IT HANDLES SOME EXTRA THINGS
//

class LMSharedSoundManager: public cocos2d::CCObject {
    
    
public:
    
    //Basic Vars & Methods of Shared Manager
    static LMSharedSoundManager* sharedManager(void);

    LMSharedSoundManager(void);
    ~LMSharedSoundManager(void);
    
    bool init(void);

    //Sound Manager Implementation

    static void playWorldBackgroundSound(const char *inWorldName);
    static void stopBackgroundSound();

    void playSound(const char *inSoundName);
};


#endif
