//
//  LMCollectionLayer.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMCollectionLayer_h
#define LMGame_LMCollectionLayer_h

#include "cocos2d.h"
#include "LMMenuLayer.h"
#include "CCScrollView.h"
#include "LMWorldSelection.h"
#include "LMDataManager.h"
#include "LMStoreLayer.h"


using namespace cocos2d;
USING_NS_CC_EXT;

class LMCollectionLayer : public cocos2d::CCLayer{
    
private:
    LMMenuLayer *menuLayer;
    
    CCLabelTTF *levelHeadingLbl;

    CCScrollView *scrollView;
    CCLayer *scrollLayer;
    CCLayer *worldNameLayer;
    
public:
    static cocos2d::CCScene* scene();
    LMCollectionLayer();
    ~LMCollectionLayer();
    
    LMStoreLayer *storeLayer;
    
    void playRegion(CCObject *sender);
    
    void loadLoneIslandCollections();
    void loadForestAdventureCollections();
    void loadHillsOfCuriosityCollections();
    void loadPeaksOfDestinyCollections();
    void loadChambersOfBeyondCollections();
    void loadSandsOfPerilCollections();
    void loaWatersOfUnderseaCollections();
    
    //For playing the current region
   
    void goToLevelSelectionScreen(int tag);
    void updateTag(int tagNo);
   
    //Adding relics & Monsters
    void addChainInScrollLayer(float x,float y,int noTimes);
    void addRelicsAndMonstersCountLabel(int relCount,int monCount);
    void addRelicsAndMonsters(const char *worldName,float yPos,int bgCount);
    void buyRelicsButtonAction();
    
    int worldTagNo;
    int relicsCount;
    int monstersCount;
    
    //Adding Locks
    bool isWorldHasLock(const char *worldname);
    void lockAction(int tag);
    void addLockImage(const char*worldName);
    void removeLockImage();
    
    //Store
    void removeStoreLayer(CCMenuItemImage *sender);

    
};

#endif



