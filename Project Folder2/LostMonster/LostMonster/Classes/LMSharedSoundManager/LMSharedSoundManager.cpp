//
//  LMSharedSoundManager.cpp
//  LostMonster
//
//  Created by Krithik B on 30/10/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#include "LMSharedSoundManager.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


static LMSharedSoundManager *gSharedManager = NULL;

#pragma mark - Basic Methods of Shared Manager

LMSharedSoundManager::LMSharedSoundManager(void)
{
    
}

LMSharedSoundManager::~LMSharedSoundManager(void)
{
    
}


LMSharedSoundManager* LMSharedSoundManager::sharedManager(void) {
    
	LMSharedSoundManager *pRet = gSharedManager;
    
	if (! gSharedManager)
	{
		pRet = gSharedManager = new LMSharedSoundManager();
        
		if (! gSharedManager->init())
		{
			delete gSharedManager;
			gSharedManager = NULL;
			pRet = NULL;
		}
	}
	return pRet;
}

bool LMSharedSoundManager::init(void) {
	return true;
}


#pragma mark - Sound Manager Implementation

void LMSharedSoundManager::playWorldBackgroundSound(const char *inWorldName)
{
    
    if(strncmp(inWorldName, "World_1",7)==0)
    {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Lone Island.mp3", true);
    }
    else if (strncmp(inWorldName, "World_2",7)==0)
    {
        int randomNo = arc4random()%2;
        if(randomNo==0)
        {
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Forests of Adventure Version A.mp3", true);
        }
        else
        {
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Forests of Adventure Version B.mp3", true);
        }
    }
    else if (strncmp(inWorldName, "World_3",7)==0)
    {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Hills of curiosity.mp3", true);
    }
    else if (strncmp(inWorldName, "World_4",7)==0)
    {
        int randomNo = arc4random()%2;
        if(randomNo==0)
        {
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Peaks of destiny Version A.mp3", true);
        }
        else
        {
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Peaks of destiny Version B.mp3", true);
        }
    }
    else if (strncmp(inWorldName, "World_5",7)==0)
    {
         
        int randomNo = arc4random()%2;
        if(randomNo==0)
        {
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Chambers of Beyond Version A.mp3", true);
            //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("21 Fire Version B.mp3", true);
        }
        else
        {
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Chambers of Beyond Version B.mp3", true);
            //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("21 Fire Version B.mp3", true);
        }
    }
    else if (strncmp(inWorldName, "World_6",7)==0)
    {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sands of Peril.mp3", true);
    }
    else if (strncmp(inWorldName, "World_7",7)==0)
    {
        int randomNo = arc4random()%2;
        if(randomNo==0)
        {
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("The Waters of Undersea Version A.mp3", true);
        }
        else
        {
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic("The Waters of Undersea Version B.mp3", true);
        }
    }
}

void LMSharedSoundManager::stopBackgroundSound()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}


void LMSharedSoundManager::playSound(const char *inSoundName)
{
    SimpleAudioEngine::sharedEngine()->playEffect(inSoundName);
}
