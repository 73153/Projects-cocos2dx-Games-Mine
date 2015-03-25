//
//  LMWorldSelection.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "LMWorldSelection.h"
#include "LMMenuLayer.h"
#include "LMLevelSelection.h"
#include "LMDataManager.h"

#define LockTag 500
using namespace cocos2d;


CCScene* LMWorldselection::scene(){
    
    CCScene *Scene=CCScene::create();
    
    LMWorldselection *worldSelectionLayer=new LMWorldselection();
    Scene->addChild(worldSelectionLayer);
    return Scene;
}

#pragma mark constructor
LMWorldselection::LMWorldselection()
{
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    
    // backGround
    CCSprite *backGround=CCSprite::create("GameUIImages/UI_worldmap_page.png");
    this->addChild(backGround);
    backGround->cocos2d::CCNode::setPosition(width/2, height/2);
    
    
    // menu layer 
    LMMenuLayer *menuLayer=new LMMenuLayer();
    this->addChild(menuLayer,2);
    
    
    
    
    //Place all the World Buttons
    
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("the_lone_island_ribbn.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("the_lone_island_ribbn.png");
    
    
    //lone island menu  item 
    CCMenuItemSprite *loneIslandMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMWorldselection::goToLoneIslandLevels));
    loneIslandMenuItem->setPosition(118,165);
    loneIslandMenuItem->setTag(1);

    
    
    
    // forest of adventure  menu  item
    
    normalSprite=CCSprite::createWithSpriteFrameName("the_forests_adventure_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_forests_adventure_ribbn.png");
    CCMenuItemSprite *forestMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMWorldselection::goToForestOfAdventureLevels));
    forestMenuItem->setPosition(272,125);
    forestMenuItem->setTag(2);
    
    
    // hill of curiosity  menu  item
    normalSprite=CCSprite::createWithSpriteFrameName("the_hill_curiosity_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_hill_curiosity_ribbn.png");
    CCMenuItemSprite *hillMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMWorldselection::goToHillsOfCuriosity));
    hillMenuItem->setTag(3);
    hillMenuItem->setPosition(164,60);


    
    
    
    // peaks of Density  menu  item 
    
    normalSprite=CCSprite::createWithSpriteFrameName("the_peaks_destny_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_peaks_destny_ribbn.png");
    CCMenuItemSprite *peaksOfDivMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMWorldselection::goToPeaksOfDestinyLevels));
    peaksOfDivMenuItem->setTag(4);
    peaksOfDivMenuItem->setPosition(288,225);
    
    
    
    // the chambers of beyond menu  item 
    
    normalSprite=CCSprite::createWithSpriteFrameName("the_chambrs_beyond_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_chambrs_beyond_ribbn.png");
    CCMenuItemSprite *chamberOfBeyondMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMWorldselection::goToChamberOfBeyondLevels));
    chamberOfBeyondMenuItem->setTag(5);
    chamberOfBeyondMenuItem->setPosition(407,170);
    
    
    // chamber of beyond lock 
    
    
    
    // waters under sea  menu item
    normalSprite=CCSprite::createWithSpriteFrameName("the_waters_undersea_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_waters_undersea_ribbn.png");
    CCMenuItemSprite *waterMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMWorldselection::goToWaterUnderSeaLevels));
    waterMenuItem->setTag(6);
    waterMenuItem->setPosition(360,95);
    
    
    
    
    // sand of pearl menu item
    normalSprite=CCSprite::createWithSpriteFrameName("the_sands_peril_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_sands_peril_ribbn.png");
    CCMenuItemSprite *sandMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMWorldselection::goToSandOfPearlLevels));
    sandMenuItem->setTag(7);
    sandMenuItem->setPosition(324,47);
        
    
    // world menu 
    CCMenu *worldMenu=CCMenu::create(loneIslandMenuItem,forestMenuItem,peaksOfDivMenuItem,chamberOfBeyondMenuItem,waterMenuItem,sandMenuItem,hillMenuItem, NULL);
    this->addChild(worldMenu,1);
    worldMenu->setPosition(ccp(0,0));
    
    
    // adding locks
    
    //Lock
    
    /*
    CCSprite * forestLockSprite=CCSprite::createWithSpriteFrameName("lock.png");
    this->addChild(forestLockSprite,1,LockTag+2);
    forestLockSprite->setRotation(20);
    forestLockSprite->setPosition(CCPointMake(340, 120));
     */
    
    // peaks of university lock
    /*
    CCSprite * peakLockSprite=CCSprite::createWithSpriteFrameName("lock.png");
    this->addChild(peakLockSprite,1,LockTag+4);
    peakLockSprite->setRotation(20);
    peakLockSprite->setPosition(CCPointMake(337, 216));
     */
    
    
    // chamber lock 
    CCSprite *chamberLockSprite=CCSprite::createWithSpriteFrameName("lock.png");
    this->addChild(chamberLockSprite,1,LockTag+5);
    chamberLockSprite->setRotation(25);
    chamberLockSprite->setPosition(CCPointMake(460, 160));
    
    
    //water of under sea lock 
    CCSprite *waterLockSprite=CCSprite::createWithSpriteFrameName("lock.png");
    this->addChild(waterLockSprite,1,LockTag+6);
    waterLockSprite->setRotation(25);
    waterLockSprite->setPosition(CCPointMake(415, 90));
    
    
    
    
    //sand of pearl lock 
    CCSprite *sandLockSprite=CCSprite::createWithSpriteFrameName("lock.png");
    this->addChild(sandLockSprite,1,LockTag+7);
    sandLockSprite->setRotation(20);
    sandLockSprite->setPosition(CCPointMake(377, 47));
    
    
    
    
    //hill of curiosity lock
    
    CCSprite *hillLockSprite=CCSprite::createWithSpriteFrameName("lock.png");
    this->addChild(hillLockSprite,1,LockTag+3);
    hillLockSprite->setRotation(10);
   hillLockSprite->setPosition(CCPointMake(214,60));
     
     
    
    
}




#pragma mark destructor 
LMWorldselection::~LMWorldselection(){
}

#pragma mark - Actions

//World 1
void LMWorldselection::goToLoneIslandLevels()
{
    LMDataManager::sharedManager()->worldName = "World_1";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_1_";
    LMDataManager::sharedManager()->numberOfLevels=12;
    LMDataManager::sharedManager()->check = false;
    CCScene *pScene = LMLevelSelection::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

//World 2
void LMWorldselection::goToForestOfAdventureLevels(CCObject *obj){
    
    LMDataManager::sharedManager()->worldName = "World_2";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_2_";
    LMDataManager::sharedManager()->check = true;
    LMDataManager::sharedManager()->numberOfLevels=16;

    CCScene *pScene = LMLevelSelection::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);

//    CCMenuItem *menuItem=(CCMenuItem *)obj;
//    int i=menuItem->getTag();
//    this->lockAction(LockTag+i);
    
}

//world 3
void LMWorldselection::goToHillsOfCuriosity( CCObject *obj)
{
    LMDataManager::sharedManager()->worldName = "World_3";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_3_";
    LMDataManager::sharedManager()->check = true;
    LMDataManager::sharedManager()->numberOfLevels=16;
    
    //CCScene *pScene = LMLevelSelection::scene();
    //CCDirector::sharedDirector()->replaceScene(pScene);
    
    CCMenuItem *menuItem=(CCMenuItem *)obj;
    int i=menuItem->getTag();
    this->lockAction(LockTag+i);
}
// world 4
void LMWorldselection::goToPeaksOfDestinyLevels(CCObject *obj)
{
    LMDataManager::sharedManager()->worldName = "World_4";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_4_";
    LMDataManager::sharedManager()->check = true;
    LMDataManager::sharedManager()->numberOfLevels=16;
    
    CCScene *pScene = LMLevelSelection::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);

    
    //CCMenuItem *menuItem=(CCMenuItem *)obj;
    //int i=menuItem->getTag();
   // this->lockAction(LockTag+i);
}

// world 5
void LMWorldselection::goToChamberOfBeyondLevels(CCObject *obj)
{
    LMDataManager::sharedManager()->worldName = "World_5";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_5_";
    LMDataManager::sharedManager()->check = true;
    CCMenuItem *menuItem=(CCMenuItem *)obj;
    int i=menuItem->getTag();
    this->lockAction(LockTag+i); 
}

// world 6
void LMWorldselection::goToWaterUnderSeaLevels(CCObject *obj ){
    LMDataManager::sharedManager()->worldName = "World_6";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_6_";
    LMDataManager::sharedManager()->check = true;
    CCMenuItem *menuItem=(CCMenuItem *)obj;
    int i=menuItem->getTag();
    this->lockAction(LockTag+i);
}


// worild 7
void LMWorldselection::goToSandOfPearlLevels( CCObject *Obj){
    LMDataManager::sharedManager()->worldName = "World_7";
    LMDataManager::sharedManager()->levelNamePrefix = "Level_7_";
    LMDataManager::sharedManager()->check = true;
    CCMenuItem *menuItem=(CCMenuItem *)Obj;
    int i=menuItem->getTag();
    this->lockAction(LockTag+i);
}


void LMWorldselection::lockAction(int tag){
    
    CCSprite *lockSprite=(CCSprite*)this->getChildByTag(tag);
    if (lockSprite->numberOfRunningActions()==0) {
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








