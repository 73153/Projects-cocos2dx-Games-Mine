//
//  LMGameSoundManager.cpp
//  LostMonster
//
//  Created by Krithik B on 30/10/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#include "LMGameSoundManager.h"
#include "SimpleAudioEngine.h"

LMGameSoundManager::LMGameSoundManager(void) { }

LMGameSoundManager::~LMGameSoundManager(void) { }

using namespace CocosDenshion;

void LMGameSoundManager::playBackgroundSound(const char *inSoundName)
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(inSoundName, true);
}


void LMGameSoundManager::stopBackgroundSound()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void LMGameSoundManager::playSound(const char *inSoundName)
{
    SimpleAudioEngine::sharedEngine()->playEffect(inSoundName);
}

void LMGameSoundManager::playWoodCutSound()
{
     SimpleAudioEngine::sharedEngine()->playEffect("Sword (1).mp3");
}
void LMGameSoundManager::playFireSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("21 Fire Version B.mp3", 1);
    
}

void LMGameSoundManager::playRopeCutSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("39 Rope Cut Version B.mp3");
    //int randomNo = arc4random()%4;
    /*
     if(randomNo==0)
     {
     SimpleAudioEngine::sharedEngine()->playEffect("39 Rope Cut Version A.mp3");
     }
     else if (randomNo==1)
     {
     SimpleAudioEngine::sharedEngine()->playEffect("39 Rope Cut Version B.mp3");
     }
     else if (randomNo==2)
     {
     SimpleAudioEngine::sharedEngine()->playEffect("39 Rope Cut Version C.mp3");
     }
     else if (randomNo==3)
     {
     SimpleAudioEngine::sharedEngine()->playEffect("39 Rope Cut Version D.mp3");
     }
     */

}

void LMGameSoundManager::playIceCutSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("24 Slice Ice Version B.mp3");
    /*
     int randomNo = arc4random()%3;
     if(randomNo==0)
     {
     SimpleAudioEngine::sharedEngine()->playEffect("24 Slice Ice Version A.mp3");
     }
     else if (randomNo==1)
     {
     SimpleAudioEngine::sharedEngine()->playEffect("24 Slice Ice Version B.mp3");
     }
     else if (randomNo==2)
     {
     SimpleAudioEngine::sharedEngine()->playEffect("24 Slice Ice Version C.mp3");
     }
     */
}

void LMGameSoundManager::playNoMoreCutSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("25 No More Cut Sound - No Cut.mp3");
}

void LMGameSoundManager::playRolloReverseSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("43 Reverse.mp3");
}

void LMGameSoundManager::playLevelFailedSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("18 Fail.mp3");
}
void LMGameSoundManager::playIceTapSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("24 Slice Ice Version C.mp3");
}
void LMGameSoundManager::playSoftWoodTapSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("Sword (10).mp3");
}
void LMGameSoundManager::playLevelLockSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("33 Lock Jiggle Version A.mp3");
}