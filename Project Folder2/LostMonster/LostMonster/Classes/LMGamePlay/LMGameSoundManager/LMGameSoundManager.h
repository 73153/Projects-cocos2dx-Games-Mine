//
//  LMGameSoundManager.h
//  LostMonster
//
//  Created by Krithik B on 30/10/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#ifndef LostMonster_LMGameSoundManager_h
#define LostMonster_LMGameSoundManager_h

#include "LMGameManager.h"

//...
//THIS CLASS USES SIMPLE SOUND ENGINE TO PLAY THE SOUND
//ALSO IT WILL HELP TO PLAY RANDOM SOUNDS ETC
// ...


class LMGameSoundManager : public LMGameManager {

private:
    
    
    
public:
    LMGameSoundManager(void);
    ~LMGameSoundManager(void);
    
    //Initialise
    
    
    //Basic Methods to play sound
    void playBackgroundSound(const char *inSoundName);
    void stopBackgroundSound();
    
    void playSound(const char *inSoundName);
    
    void playWoodCutSound();
    void playRopeCutSound();
    void playIceCutSound();
    
    void playNoMoreCutSound();
    void playRolloReverseSound();
    void playLevelFailedSound();
    void playLevelLockSound();
    void playIceTapSound();
    void playSoftWoodTapSound();
    void playFireSound();
    
};

#endif
