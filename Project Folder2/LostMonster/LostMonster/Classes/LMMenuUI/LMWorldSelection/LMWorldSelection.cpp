//
//  LMWorldSelection.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

#include "LMWorldSelection.h"

#include "LMDataManager.h"
#include "LMUtility.h"

#include "LMMainScreenLoader.h"
#include "LMLevelSelectionLoader.h"



USING_NS_CC;
USING_NS_CC_EXT;

#define LockTag 500

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "LMObjectiveCCalls.h"


#else

#endif

#pragma mark constructor
LMWorldSelection::LMWorldSelection()
{
    this->logoSecondLayerSpr = NULL;
    this->logoThirdLayerSpr = NULL;
}

void LMWorldSelection::onEnter()
{
    CCLayer::onEnter();
    this->initialiseAnimations();

}

void LMWorldSelection::onExit()
{
    //CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUIImages/WorldSelection/WorldSelectionSpriteSheet.plist");
    CCLayer::onExit();
}

LMWorldSelection::~LMWorldSelection(){
    
    CC_SAFE_RELEASE(this->logoSecondLayerSpr);
    CC_SAFE_RELEASE(this->logoThirdLayerSpr);

}

#pragma mark - CocosBuilderReader

void LMWorldSelection::onNodeLoaded(CCNode * pNode,CCNodeLoader * pNodeLoader)
{
    //this->mAnimationManager = LMDataManager::sharedManager()->cocosBuilderReader->getAnimationManager();
    
}


SEL_MenuHandler LMWorldSelection::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    
    //Play
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"backBtnAct:", LMWorldSelection::backBtnAct);
    
    //World Selection
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"goToLoneIslandLevels:", LMWorldSelection::goToLoneIslandLevels);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"goToForestOfAdventureLevels:", LMWorldSelection::goToForestOfAdventureLevels);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"goToHillsOfCuriosity:", LMWorldSelection::goToHillsOfCuriosity);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"goToPeaksOfDestinyLevels:", LMWorldSelection::goToPeaksOfDestinyLevels);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"goToChamberOfBeyondLevels:", LMWorldSelection::goToChamberOfBeyondLevels);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"goToSandOfPearlLevels:", LMWorldSelection::goToSandOfPearlLevels);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"goToWaterUnderSeaLevels:", LMWorldSelection::goToWaterUnderSeaLevels);

    
    return NULL;
}

SEL_CCControlHandler LMWorldSelection::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

bool LMWorldSelection::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
    //Logo
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "logoSecondLayerSpr", CCSprite *, this->logoSecondLayerSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "logoThirdLayerSpr", CCSprite *, this->logoThirdLayerSpr);
   
    return false;
}


#pragma mark - Actions

//World 1
void LMWorldSelection::goToLoneIslandLevels(CCObject *obj)
{
    LMDataManager::sharedManager()->worldName = "World_1";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_1_";
    LMDataManager::sharedManager()->numberOfLevels=12;
    
    this->goToLevelSelectionScreen(obj);
}

//World 2
void LMWorldSelection::goToForestOfAdventureLevels(CCObject *obj){
    
    LMDataManager::sharedManager()->worldName = "World_2";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_2_";
    LMDataManager::sharedManager()->numberOfLevels=16;

    this->goToLevelSelectionScreen(obj);
}


//world 3
void LMWorldSelection::goToHillsOfCuriosity( CCObject *obj)
{
    LMDataManager::sharedManager()->worldName = "World_3";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_3_";
    LMDataManager::sharedManager()->numberOfLevels=16;

    this->goToLevelSelectionScreen(obj);
}

//world 4
void LMWorldSelection::goToPeaksOfDestinyLevels(CCObject *obj)
{
    LMDataManager::sharedManager()->worldName = "World_4";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_4_";
    LMDataManager::sharedManager()->numberOfLevels=16;
    
    this->goToLevelSelectionScreen(obj);
}

// world 5
void LMWorldSelection::goToChamberOfBeyondLevels(CCObject *obj)
{
    LMDataManager::sharedManager()->worldName = "World_5";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_5_";
    LMDataManager::sharedManager()->numberOfLevels=16;
    
    this->goToLevelSelectionScreen(obj);
}




// world 6
void LMWorldSelection::goToSandOfPearlLevels( CCObject *obj){
    LMDataManager::sharedManager()->worldName = "World_6";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_6_";
    LMDataManager::sharedManager()->numberOfLevels=16;
        
    this->goToLevelSelectionScreen(obj);
}


// world 7
void LMWorldSelection::goToWaterUnderSeaLevels(CCObject *obj ){
    LMDataManager::sharedManager()->worldName = "World_7";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_7_";
    LMDataManager::sharedManager()->numberOfLevels=16;

    this->goToLevelSelectionScreen(obj);
}


void LMWorldSelection::goToLevelSelectionScreen(CCObject *obj)
{
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    CCMenuItem *menuItem=(CCMenuItem *)obj;
    int i=menuItem->getTag();
    
    if (LMUtility::doSpriteExistWithTag(LockTag+i, this))
    {
        this->lockAction(LockTag+i);
    }
    else{
        
        LMUtility::loadCocosBuilderFileWithPathAndLoader("CocosBuilder/LevelSelection/LevelSelectionScreen.ccbi","LMLevelSelection",LMLevelSelectionLoader::loader());

    }
}



void LMWorldSelection::lockAction(int tag)
{
    CCSprite *lockSprite=(CCSprite*)this->getChildByTag(tag);
    if (lockSprite->numberOfRunningActions()==0) {
       
        //level lock sound
        CCRotateBy *rotate=CCRotateBy::create(0.15, 30);
        CCRotateBy *rotReverse=CCRotateBy::create(0.15, -30);
        CCSequence *seq=CCSequence::createWithTwoActions(rotate,rotReverse);
        CCSequence *seq1=CCSequence::createWithTwoActions(rotate,rotReverse);
        CCSequence *seq3=CCSequence::createWithTwoActions(seq, seq1);
        CCSequence *seq4=CCSequence::createWithTwoActions(seq,seq1);
        CCSequence *seq5=CCSequence::createWithTwoActions(seq3, seq4);
        lockSprite->runAction(seq5);
    }
}


//back Button
void LMWorldSelection::backBtnAct(CCObject * pSender)
{
    LMUtility::loadCocosBuilderFileWithPathAndLoader("CocosBuilder/MainMenu/MainMenu.ccbi","LMMainScreen",LMMainScreenLoader::loader());
}

#pragma mark - Animations

void LMWorldSelection::initialiseAnimations()
{
    //Rotate Logo
    LMUtility::rotateNodeWithClockwiseDirection(this->logoSecondLayerSpr, false, 15.0);
    LMUtility::rotateNodeWithClockwiseDirection(this->logoThirdLayerSpr, true, 10.0);
}

#pragma mark -  Temp
void LMWorldSelection::unlockAllWorlds()
{
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    LMObjectiveCCalls::unlockAllWorlds();
    //CCDirector::sharedDirector()->replaceScene(LMWorldSelection::scene());

#else
    
#endif
    
}




