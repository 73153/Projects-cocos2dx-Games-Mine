//
//  LMAchievmentsLayer.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMAchievmentsLayer.h"


using namespace cocos2d;
USING_NS_CC_EXT;

CCScene* LMAchievmentsLayer::scene(){
    
    CCScene *Scene=CCScene::create();
    
    LMAchievmentsLayer *achievementsScene = new LMAchievmentsLayer();
    Scene->addChild(achievementsScene);
    achievementsScene->release();
    return Scene;
}


LMAchievmentsLayer::LMAchievmentsLayer(){
    
    CCLOG("Init");
    this->loadAchievementsScene();

}

void LMAchievmentsLayer::loadAchievementsScene()
{
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LMAchievementImages.plist");
    
    // menu layer
    menuLayer = new LMMenuLayer();
    this->addChild(menuLayer,2);
    
    
    //Add BG
    CCSprite *achievementBGSpr = CCSprite::create("UICommonBG.png");
    achievementBGSpr->setPosition(CCPointMake(width/2,height/2));
    this->addChild(achievementBGSpr);
    
    ///Add achievement images
    
    int xOffsetAchievements = 130;
    int yOffsetAchievements = 430;
    
    
    //1st Achievement Group
    
    //Add achivement Heading
    CCSprite *aAchievementHeadingSpr = CCSprite::createWithSpriteFrameName("TheCurator.png");
    aAchievementHeadingSpr->setPosition(CCPoint(92, 520));
    aAchievementHeadingSpr->setAnchorPoint(CCPointZero);
    this->addChild(aAchievementHeadingSpr);
    
    // Loading the plist...
    
    std::string strin=CCFileUtils::sharedFileUtils()->getWriteablePath();
    strin.append("LMAchievements.plist");
    
    // Getting the dictionaries into...
    CCDictionary *allAchievementsDataBaseDataDict = CCDictionary::createWithContentsOfFileThreadSafe(strin.c_str());
    
    // Loading the plist for adding dead image name in the current world
    const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("LMAchievementsData.plist");
    CCDictionary *allAchievementsDataDict = CCDictionary::createWithContentsOfFileThreadSafe(pszPath);
    
    CCArray *aAchievementsArr = (CCArray *)allAchievementsDataDict->valueForKey("TheCurator");
    
    CCObject *aAchievementObj;
    CCARRAY_FOREACH(aAchievementsArr, aAchievementObj)
    {
        CCString *aAchievementStr = (CCString *)aAchievementObj;
        CCString *testValue1 =(CCString *)allAchievementsDataBaseDataDict->valueForKey(aAchievementStr->getCString());
        bool isCollected=testValue1->boolValue();
        if(isCollected)
        {
            char achievementMaskName[40];
            sprintf(achievementMaskName, "%s.png",aAchievementStr->getCString());
            
            CCSprite *aAchievementSpr = CCSprite::createWithSpriteFrameName(achievementMaskName);
            aAchievementSpr->setPosition(CCPoint(xOffsetAchievements,yOffsetAchievements));
            this->addChild(aAchievementSpr);
        }
        else
        {
            char achievementMaskName[40];
            sprintf(achievementMaskName, "%sOff.png",aAchievementStr->getCString());
            CCSprite *aAchievementSpr = CCSprite::createWithSpriteFrameName(achievementMaskName);
            aAchievementSpr->setPosition(CCPoint(xOffsetAchievements,yOffsetAchievements));
            this->addChild(aAchievementSpr);
            
        }
        xOffsetAchievements = xOffsetAchievements + 122;
    }
    
    //2nd Achievement Group
    xOffsetAchievements = 586;
    
    aAchievementHeadingSpr = CCSprite::createWithSpriteFrameName("MonsterWrangler.png");
    aAchievementHeadingSpr->setPosition(CCPoint(600, 520));
    aAchievementHeadingSpr->setAnchorPoint(CCPointZero);
    this->addChild(aAchievementHeadingSpr);
    
    
    aAchievementsArr = (CCArray *)allAchievementsDataDict->valueForKey("MonsterWrangler");
    
    CCARRAY_FOREACH(aAchievementsArr, aAchievementObj)
    {
        CCString *aAchievementStr = (CCString *)aAchievementObj;
        CCString *testValue1 =(CCString *)allAchievementsDataBaseDataDict->valueForKey(aAchievementStr->getCString());
        bool isCollected=testValue1->boolValue();
        if(isCollected)
        {
            char achievementMaskName[40];
            sprintf(achievementMaskName, "%s.png",aAchievementStr->getCString());
            
            CCSprite *aAchievementSpr = CCSprite::createWithSpriteFrameName(achievementMaskName);
            aAchievementSpr->setPosition(CCPoint(xOffsetAchievements,yOffsetAchievements));
            this->addChild(aAchievementSpr);
        }
        else{
            char achievementMaskName[40];
            sprintf(achievementMaskName, "%sOff.png",aAchievementStr->getCString());
            CCSprite *aAchievementSpr = CCSprite::createWithSpriteFrameName(achievementMaskName);
            aAchievementSpr->setPosition(CCPoint(xOffsetAchievements,yOffsetAchievements));
            this->addChild(aAchievementSpr);
        }
        xOffsetAchievements = xOffsetAchievements + 122;
    }
    
    //3rd Achievement Group
    
    xOffsetAchievements = 200;
    yOffsetAchievements = 110;
    
    
    aAchievementHeadingSpr = CCSprite::createWithSpriteFrameName("DoubleTrouble.png");
    aAchievementHeadingSpr->setPosition(CCPoint(92,205));
    aAchievementHeadingSpr->setAnchorPoint(CCPointZero);
    this->addChild(aAchievementHeadingSpr);
    
    
    aAchievementsArr = (CCArray *)allAchievementsDataDict->valueForKey("DoubleTrouble");
    
    CCARRAY_FOREACH(aAchievementsArr, aAchievementObj)
    {
        CCString *aAchievementStr = (CCString *)aAchievementObj;
        CCString *testValue1 =(CCString *)allAchievementsDataBaseDataDict->valueForKey(aAchievementStr->getCString());
        bool isCollected=testValue1->boolValue();
        if(isCollected)
        {
            char achievementMaskName[40];
            sprintf(achievementMaskName, "%s.png",aAchievementStr->getCString());
            
            CCSprite *aAchievementSpr = CCSprite::createWithSpriteFrameName(achievementMaskName);
            aAchievementSpr->setPosition(CCPoint(xOffsetAchievements,yOffsetAchievements));
            this->addChild(aAchievementSpr);
        }
        else
        {
            char achievementMaskName[40];
            sprintf(achievementMaskName, "%sOff.png",aAchievementStr->getCString());
            CCSprite *aAchievementSpr = CCSprite::createWithSpriteFrameName(achievementMaskName);
            aAchievementSpr->setPosition(CCPoint(xOffsetAchievements,yOffsetAchievements));
            this->addChild(aAchievementSpr);
        }
        xOffsetAchievements = xOffsetAchievements + 122;
    }
    
    
    //4th Achievement Group
    
    xOffsetAchievements = 645;
    
    aAchievementHeadingSpr = CCSprite::createWithSpriteFrameName("MultipleMayhem.png");
    aAchievementHeadingSpr->setPosition(CCPoint(600,205));
    aAchievementHeadingSpr->setAnchorPoint(CCPointZero);
    this->addChild(aAchievementHeadingSpr);
    
    
    aAchievementsArr = (CCArray *)allAchievementsDataDict->valueForKey("MultipleMayhem");
    
    CCARRAY_FOREACH(aAchievementsArr, aAchievementObj)
    {
        CCString *aAchievementStr = (CCString *)aAchievementObj;
        CCString *testValue1 =(CCString *)allAchievementsDataBaseDataDict->valueForKey(aAchievementStr->getCString());
        bool isCollected=testValue1->boolValue();
        if(isCollected)
        {
            char achievementMaskName[40];
            sprintf(achievementMaskName, "%s.png",aAchievementStr->getCString());
            
            CCSprite *aAchievementSpr = CCSprite::createWithSpriteFrameName(achievementMaskName);
            aAchievementSpr->setPosition(CCPoint(xOffsetAchievements,yOffsetAchievements));
            this->addChild(aAchievementSpr);
        }
        else{
            char achievementMaskName[40];
            sprintf(achievementMaskName, "%sOff.png",aAchievementStr->getCString());
            CCSprite *aAchievementSpr = CCSprite::createWithSpriteFrameName(achievementMaskName);
            aAchievementSpr->setPosition(CCPoint(xOffsetAchievements,yOffsetAchievements));
            this->addChild(aAchievementSpr);
        }
        xOffsetAchievements = xOffsetAchievements + 122;
    }
    allAchievementsDataDict->release();
}


void LMAchievmentsLayer::onEnter()
{
    CCLOG("OnEnter");
    CCLayer::onEnter();
    
}

void LMAchievmentsLayer::onExit()
{
    CCLOG("OnExit");
    CCLayer::onExit();
}

#pragma mark - Dealloc
LMAchievmentsLayer::~LMAchievmentsLayer()
{
    this->removeChild(menuLayer, true);
    delete menuLayer;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LMAchievementImages.plist");
    CCLOG("Dealloc in  ~LMAchievmentsLayer");
}



