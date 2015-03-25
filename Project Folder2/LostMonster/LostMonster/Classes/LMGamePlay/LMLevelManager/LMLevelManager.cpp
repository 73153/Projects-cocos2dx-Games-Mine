//
//  LMLevelManager.cpp
//  LostMonster
//
//  Created by Krithik B on 8/20/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#include <iostream>
#include "LMLevelManager.h"
#include "LMDataManager.h"

using namespace cocos2d;

LMLevelManager:: LMLevelManager()
{
    
}


LMLevelManager::~LMLevelManager()
{
    CCLog("Dealloc in ~LMLevelManager");
}


#pragma mark - Initialise

void LMLevelManager :: initialize()
{
    this->levelName = LMDataManager::sharedManager()->levelName;
    this->loadLevelDataFromPlist();
    
}


//Load Data From Plist

void LMLevelManager:: loadLevelDataFromPlist()
{
    // Loading the plist...
    const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("LMLevelData.plist");
    
    // Getting the dictionaries into...
    CCDictionary *allWorldLevelDataDict = CCDictionary::createWithContentsOfFileThreadSafe(pszPath);
    
   //Select The world
        
    const char *worldName = LMDataManager::sharedManager()->worldName;
    
    // Getting the desired World Dict ...
    CCDictionary *aWorldDict = (CCDictionary*)allWorldLevelDataDict->objectForKey(worldName);
    
    //Select The Level
    const char *levelName = LMDataManager::sharedManager()->levelName;
    
    CCDictionary *aLevelDict = (CCDictionary*)aWorldDict->objectForKey(levelName);
    
//    int maxCuts;
//    bool canDecreaseLife;
//    int woodTag;
    
    this->maxCuts = aLevelDict->valueForKey("MaxCuts")->intValue();
    this->challengingMoveCount = aLevelDict->valueForKey("ChallengingMoveCount")->intValue();
    this->canDecreaseLife = aLevelDict->valueForKey("CanDecreaseLife")->boolValue();
    
    this->rolloGravity = aLevelDict->valueForKey("rolloGravity")->floatValue();
    this->rolloWinAnimationYPos=aLevelDict->valueForKey("rolloAnimYpos")->floatValue();

    //Tutorial
    this->containsTutorial = aLevelDict->valueForKey("containsTutorial")->boolValue();
    if(this->containsTutorial)   
    {
        this->tutorialVideoFileName = CCString::create(aLevelDict->valueForKey("tutorialVideoFileName")->getCString());
        this->tutorialHeading = CCString::create(aLevelDict->valueForKey("tutorialHeading")->getCString());
    }
    
    allWorldLevelDataDict->release();

    
}
