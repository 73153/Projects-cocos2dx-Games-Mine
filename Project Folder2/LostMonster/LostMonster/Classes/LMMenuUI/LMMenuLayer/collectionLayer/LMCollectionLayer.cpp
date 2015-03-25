//
//  LMCollectionLayer.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMCollectionLayer.h"
#include "LMLevelSelection.h"
#include "LMUtility.h"
#define LockTag 500

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "LMObjectiveCCalls.h"


#else

#endif

using namespace cocos2d;

#pragma mark -scene
CCScene* LMCollectionLayer::scene(){
    
    CCScene *scene=CCScene::create();
    
    LMCollectionLayer *collectionScene = new LMCollectionLayer();
    scene->addChild(collectionScene);
    collectionScene->release();
    return scene;
}

#pragma mark - Initialise
LMCollectionLayer::LMCollectionLayer(){
    //Releasing allocated memory
    
       //Allocating
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LMCollectionsScene.plist");
        
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    
    //Add BG
    CCSprite *collectionBGSpr = CCSprite::create("UICommonBG.png");
    collectionBGSpr->setPosition(CCPointMake(width/2,height/2));
    this->addChild(collectionBGSpr);
    
    // menu layer
    menuLayer = new LMMenuLayer();
    this->addChild(menuLayer,2);
    
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("the_lone_island_ribbn.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("the_lone_island_ribbn.png");
    
    CCMenuItemSprite *loneIslandMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMCollectionLayer::loadLoneIslandCollections));
    loneIslandMenuItem->setTag(1);
    loneIslandMenuItem->setPosition(168,538);
    loneIslandMenuItem->setAnchorPoint(CCPointZero);
    
    
    
    
    // FOREST ADVENTURE
    normalSprite=CCSprite::createWithSpriteFrameName("the_forests_adventure_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_forests_adventure_ribbn.png");
    
    CCMenuItemSprite *forestMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMCollectionLayer::loadForestAdventureCollections));
    
    forestMenuItem->setTag(2);
    forestMenuItem->setPosition(560,620);
    forestMenuItem->setAnchorPoint(CCPointZero);
    
    
    
    // HILLS OF CURIOSITY
    normalSprite=CCSprite::createWithSpriteFrameName("the_hill_curiosity_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_hill_curiosity_ribbn.png");
    CCMenuItemSprite *hillMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMCollectionLayer::loadHillsOfCuriosityCollections));
    hillMenuItem->setTag(3);
    hillMenuItem->setPosition(860,620);
    hillMenuItem->setAnchorPoint(CCPointZero);
    
    
    
    // PEAKS OF DENSITY
    normalSprite=CCSprite::createWithSpriteFrameName("the_peaks_destny_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_peaks_destny_ribbn.png");
    CCMenuItemSprite *peaksOfDivMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMCollectionLayer::loadPeaksOfDestinyCollections));
    peaksOfDivMenuItem->setTag(4);
    peaksOfDivMenuItem->setPosition(406,538);
    peaksOfDivMenuItem->setAnchorPoint(CCPointZero);
    
    
    
    // THE CHAMBERS OF BEYOND
    normalSprite=CCSprite::createWithSpriteFrameName("the_chambrs_beyond_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_chambrs_beyond_ribbn.png");
    CCMenuItemSprite *chamberOfBeyondMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMCollectionLayer::loadChambersOfBeyondCollections));
    chamberOfBeyondMenuItem->setTag(5);
    chamberOfBeyondMenuItem->setPosition(710,538);
    chamberOfBeyondMenuItem->setAnchorPoint(CCPointZero);
    
    // THE SANDS OF PERIL
    normalSprite=CCSprite::createWithSpriteFrameName("the_sands_peril_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_sands_peril_ribbn.png");
    CCMenuItemSprite *sandMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMCollectionLayer::loadSandsOfPerilCollections));
    sandMenuItem->setTag(6);
    sandMenuItem->setPosition(54,620);
    sandMenuItem->setAnchorPoint(CCPointZero);
    
    
    // THE WATERS OF UNDERSEA
    normalSprite=CCSprite::createWithSpriteFrameName("the_waters_undersea_ribbn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("the_waters_undersea_ribbn.png");
    CCMenuItemSprite *waterMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMCollectionLayer::loaWatersOfUnderseaCollections));
    waterMenuItem->setTag(7);
    waterMenuItem->setPosition(300,620);
    waterMenuItem->setAnchorPoint(CCPointZero);
    
    
    //Play Region Button
    normalSprite=CCSprite::createWithSpriteFrameName("Play_this_region_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("Play_this_region_btn_hvr.png");
    CCMenuItemSprite *playRegionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMCollectionLayer::playRegion));
    playRegionMenuItem->setPosition(512,465);
    
    
    // World menu
    CCMenu *worldMenu=CCMenu::create(loneIslandMenuItem,forestMenuItem,peaksOfDivMenuItem,chamberOfBeyondMenuItem,waterMenuItem,sandMenuItem,hillMenuItem,playRegionMenuItem, NULL);
    worldMenu->setPosition(CCPointZero);
    worldMenu->setScale(0.8);
    this->addChild(worldMenu,1);
    
    //deisign title
    CCSprite *designLeft=CCSprite::createWithSpriteFrameName("mc_title_design_1.png");
    designLeft->setPosition(CCPointMake(145, 535));
    this->addChild(designLeft,1);
    
    CCSprite *designRight=CCSprite::createWithSpriteFrameName("mc_title_design_1.png");
    designRight->setPosition(CCPointMake(885, 535));
    designRight->setFlipX(1);
    this->addChild(designRight,1);
    
    CCSprite *smallDesignLeft=CCSprite::createWithSpriteFrameName("My-collections_08.png");
    smallDesignLeft->setPosition(CCPointMake(385, 445));
    this->addChild(smallDesignLeft,1);
    
    CCSprite *smallDesignRight=CCSprite::createWithSpriteFrameName("My-collections_08.png");
    smallDesignRight->setPosition(CCPointMake(635, 445));
    smallDesignRight->setFlipX(1);
    this->addChild(smallDesignRight,1);
    
    
    
    //Create Scroll Layer
    scrollLayer = CCLayer::create();
    
    scrollView = CCScrollView::create(CCSize(1024, 350));
    scrollView->setDirection(kCCScrollViewDirectionVertical);
    scrollView->setBounceable(true);
    scrollView->setContainer(scrollLayer);
    this->addChild(scrollView,1);
    
    scrollView->setPosition(CCPointMake(-140,45));
    scrollView->updateInset();
    
    worldNameLayer=CCLayer::create();
    this->addChild(worldNameLayer,1);
    
    this->loadLoneIslandCollections();
   
    bool isWorldLocked=this->isWorldHasLock("World_1");
    if(isWorldLocked)
    {
        this->addLockImage("World_1");
    }
}


#pragma mark - lock  functions
bool LMCollectionLayer::isWorldHasLock(const char *worldname)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    bool isLocked = LMObjectiveCCalls::isWorldLocked(worldname);
    
#else
    
#endif
    return isLocked;

}

void LMCollectionLayer:: addLockImage(const char*worldName)
{
    //Remove Lock if added
    this->removeLockImage();
    
    bool isWorldLocked=this->isWorldHasLock(worldName);
    if(isWorldLocked)
    {
        CCSprite *LockSpr=CCSprite::createWithSpriteFrameName("lock.png");
        this->addChild(LockSpr,1,LockTag);
        LockSpr->setRotation(10);
        LockSpr->setScale(0.7);
        LockSpr->setPosition(CCPointMake(580,430));
    }
}

void LMCollectionLayer:: removeLockImage()
{
    this->removeChildByTag(LockTag, true);
}

void LMCollectionLayer::lockAction(int tag)
{
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    CCSprite *lockSprite=(CCSprite*)this->getChildByTag(tag);
    if (lockSprite->numberOfRunningActions()==0) {
        //level lock sound
        //this->soundManager->playLevelLockSound();
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
#pragma mark - play button functions
void LMCollectionLayer::playRegion(CCObject *sender)
{
    
    
    switch(this->worldTagNo)
    {
        case 1:
            
            LMDataManager::sharedManager()->worldName = "World_1";
            LMDataManager::sharedManager()->levelNamePrefix = "Level_1_";
            LMDataManager::sharedManager()->numberOfLevels=12;
            this->goToLevelSelectionScreen(this->worldTagNo);
            break;
        case 2:
            LMDataManager::sharedManager()->worldName = "World_2";
            LMDataManager::sharedManager()->levelNamePrefix = "Level_2_";
            LMDataManager::sharedManager()->numberOfLevels=16;
            this->goToLevelSelectionScreen(this->worldTagNo);
            break;
        case 3:
            LMDataManager::sharedManager()->worldName = "World_3";
            LMDataManager::sharedManager()->levelNamePrefix = "Level_3_";
            LMDataManager::sharedManager()->numberOfLevels=16;
            this->goToLevelSelectionScreen(this->worldTagNo);
            break;
        case 4:
            LMDataManager::sharedManager()->worldName = "World_4";
            LMDataManager::sharedManager()->levelNamePrefix = "Level_4_";
            LMDataManager::sharedManager()->numberOfLevels=16;
            this->goToLevelSelectionScreen(this->worldTagNo);
            break;
        case 5:
            LMDataManager::sharedManager()->worldName = "World_5";
            LMDataManager::sharedManager()->levelNamePrefix = "Level_5_";
            LMDataManager::sharedManager()->numberOfLevels=16;
            this->goToLevelSelectionScreen(this->worldTagNo);
            break;
        case 6:
            LMDataManager::sharedManager()->worldName = "World_6";
            LMDataManager::sharedManager()->levelNamePrefix = "Level_6_";
            LMDataManager::sharedManager()->numberOfLevels=16;
            this->goToLevelSelectionScreen(this->worldTagNo);
            break;
        case 7:
            LMDataManager::sharedManager()->worldName = "World_7";
            LMDataManager::sharedManager()->levelNamePrefix = "Level_7_";
            LMDataManager::sharedManager()->numberOfLevels=16;
            this->goToLevelSelectionScreen(this->worldTagNo);
            break;
            
        default:
            break;
    }
}

void LMCollectionLayer::goToLevelSelectionScreen(int tag)
{
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }
        
    if (LMUtility::doSpriteExistWithTag(LockTag, this))
    {
        this->lockAction(LockTag);
    }
    else{
        //CCScene *pScene = LMLevelSelection::scene();
        //CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void LMCollectionLayer::updateTag(int tagNo)
{
    this->worldTagNo=tagNo;
}


#pragma mark - Adding monsters and Relics function
void LMCollectionLayer::addRelicsAndMonsters(const char *worldName,float yPos,int bgCount)
{
    worldNameLayer->removeAllChildrenWithCleanup(1);
    scrollLayer->removeAllChildrenWithCleanup(1);
    
    
    this->relicsCount=0;
    this->monstersCount=0;
    
    
    int xPos1 = 520;
    int yPos1 = 170;
    
    int seperationFactor = 50;
    int cardContentSize ;
    for (int i=0;i<bgCount;i++)
    {
        CCSprite *aCollectionCardSpr = CCSprite::createWithSpriteFrameName("mc_cards_bg.png");
        aCollectionCardSpr->setPosition(CCPoint(xPos1, yPos1));
        scrollLayer->addChild(aCollectionCardSpr);
        
        cardContentSize = aCollectionCardSpr->getContentSize().height;
        
        yPos1 = yPos1 + cardContentSize + seperationFactor;
    }
    
    int correctContentOffset = cardContentSize + seperationFactor;
    scrollView->setContentSize(CCSize(1024,yPos1-correctContentOffset/2));
    scrollView->setContentOffset(CCPointMake(0,-yPos1+correctContentOffset+cardContentSize/2), false);
    

    char worldFullName[45];
    int tagNumber;
    if(strncmp(worldName, "World_1",7)==0){
        sprintf(worldFullName, "The Lone Island");
        tagNumber=1;
        LMCollectionLayer::updateTag(tagNumber);
        
    }
    else if(strncmp(worldName, "World_2", 7)==0){
        sprintf(worldFullName, "The Forests Of Adventure");
        tagNumber=2;
        LMCollectionLayer::updateTag(tagNumber);
        
    }
    else if(strncmp(worldName, "World_3", 7)==0){
        sprintf(worldFullName, "The Hills Of Curiosity");
        tagNumber=3;
        LMCollectionLayer::updateTag(tagNumber);
        
    }
    else if(strncmp(worldName, "World_4", 7)==0){
        sprintf(worldFullName, "The Peaks Of Destiny");
        tagNumber=4;
        LMCollectionLayer::updateTag(tagNumber);
        
    }
    else if(strncmp(worldName, "World_5", 7)==0){
        sprintf(worldFullName, "The Chambers Of Beyond");
        tagNumber=5;
        LMCollectionLayer::updateTag(tagNumber);
        
        
    }
    else if(strncmp(worldName, "World_6", 7)==0){
        sprintf(worldFullName, "The Sands Of Peril");
        tagNumber=6;
        LMCollectionLayer::updateTag(tagNumber);
        
        
    }
    else if(strncmp(worldName, "World_7", 7)==0){
        tagNumber=7;
        sprintf(worldFullName, "The Waters Of Undersea");
        LMCollectionLayer::updateTag(tagNumber);
        
        
    }
    
    levelHeadingLbl = CCLabelTTF::create(worldFullName, "LMVeraHumana95Bold", 30);
    levelHeadingLbl->setPosition(CCPointMake(512,492));
    levelHeadingLbl->setColor(ccc3(85, 10, 0));
    worldNameLayer->addChild(levelHeadingLbl,1);
    
    
    //Load  Monsters and Relics
    
    const char *pszLMCollectionViewDataPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("LMCollectionViewData.plist");
    CCDictionary *collectionViewDataDict = CCDictionary::createWithContentsOfFileThreadSafe(pszLMCollectionViewDataPath);
    
    CCArray *worldCollectionDataArr = (CCArray *)collectionViewDataDict->valueForKey(worldName);
    
    int monsterXPos=520;
    int monsterYPos=yPos;
    
    CCObject *aMonsterObjInfoObj = NULL;
    CCARRAY_FOREACH(worldCollectionDataArr, aMonsterObjInfoObj)
    {
        CCDictionary *aMonsterObjInfo = (CCDictionary*)aMonsterObjInfoObj;
        
        //Get Monster
        const char *monsterName = aMonsterObjInfo->valueForKey("Monster")->getCString();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        
        bool isMonsterObtained = LMObjectiveCCalls::isMonsterObtained(monsterName, worldName);
        
#else
        
        
#endif
        
        char aMonsterName[30];
        if(isMonsterObtained)
        {
            this->monstersCount++;
            sprintf(aMonsterName, "%s.png",monsterName);
        }
        else
        {
            sprintf(aMonsterName, "%s_mask.png",monsterName);
        }
        
        CCSprite *aMonsterSpr = CCSprite::create(aMonsterName);
        aMonsterSpr->setPosition(CCPointMake(monsterXPos, monsterYPos));
        scrollLayer->addChild(aMonsterSpr,10);
        
        
        //Get text
        CCDictionary *textDictionary=(CCDictionary*)aMonsterObjInfo->valueForKey("Text");
        CCString *message=(CCString*)textDictionary->objectForKey("Message");
        CCString *title=(CCString*)textDictionary->objectForKey("Title");
        int textLength=message->length();
        
        //text tittle
        CCLabelTTF *monsterNameLabel=CCLabelTTF::create(title->getCString(), "LMVeraHumana95Bold", 30);
        monsterNameLabel->setPosition(CCPointMake(aMonsterSpr->getPositionX()+268, aMonsterSpr->getPositionY()+130));
        monsterNameLabel->setColor(ccc3(85, 10, 0));
        scrollView->addChild(monsterNameLabel,10);
        
        //message
        
        CCLabelTTF *textLabel=CCLabelTTF::create(message->getCString(), "LMVeraHumana95Bold", 13, CCSizeMake(textLength+80, 0),kCCTextAlignmentLeft);
        textLabel->setPosition(CCPointMake(aMonsterSpr->getPositionX()+270, aMonsterSpr->getPositionY()+50));
        textLabel->setColor(ccc3(85, 10, 0));
        scrollView->addChild(textLabel,11);
        
        
        
        //Get Relics
        CCArray *relicsArr = (CCArray *)aMonsterObjInfo->valueForKey("Relics");
        
        //Adding Relics
        CCPoint relicsPosition = aMonsterSpr->getPosition();
        int relicsXpos = aMonsterSpr->getPositionX()-184;
        int relicsYpos = aMonsterSpr->getPositionY()+88;
        
        int relicsCounter = 0;
        
        int chainCounter=0;
        CCObject *aRelicObj = NULL;
        CCARRAY_FOREACH(relicsArr, aRelicObj)
        {
            CCString *aRelicStr = (CCString *)aRelicObj;
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            bool isRelicObtained = LMObjectiveCCalls::isRelicObtained(aRelicStr->getCString());
            chainCounter++;
            
#else
            
#endif
            CCSprite *aRelic;
            char aRelicsName[30];
            if (isRelicObtained)
            {
                this->relicsCount++;
                                
                sprintf(aRelicsName, "%s.png",aRelicStr->getCString());
                aRelic = CCSprite::create(aRelicsName);
                aRelic->setPosition(CCPointMake(relicsXpos, relicsYpos));
                aRelic->setScale(0.8);
                scrollLayer->addChild(aRelic,10);
                this->addChainInScrollLayer(aMonsterSpr->getPositionX(), aMonsterSpr->getPositionY(), chainCounter);
            }
            else
            {
                sprintf(aRelicsName, "%s.png",aRelicStr->getCString());
                aRelic = CCSprite::create("relic_mask.png");
                aRelic->setScale(0.55);
                aRelic->setPosition(CCPointMake(relicsXpos, relicsYpos));
                scrollLayer->addChild(aRelic,10);
            }
            
            //for adding relic count
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            int relicsObtainedCount = LMObjectiveCCalls::noOfTimesRelicObtained(aRelicStr->getCString());
            if(relicsObtainedCount>1)
            {
                
                this->relicsCount=this->relicsCount+relicsObtainedCount-1;
                CCSprite *smallRelicCountImage=CCSprite::createWithSpriteFrameName("numbrs_bg.png");
                smallRelicCountImage->setPosition(CCPointMake(130, 175));
                aRelic->addChild(smallRelicCountImage,11);
                char relicsCountNo[5];
                sprintf(relicsCountNo,"%d",relicsObtainedCount);
                CCLabelTTF *relicsCountLabel=CCLabelTTF::create(relicsCountNo, "LMVeraHumana95Bold", 22);
                relicsCountLabel->setPosition(CCPointMake(17, 19));
                smallRelicCountImage->addChild(relicsCountLabel,12);
                
            }
            
            
#else
            
            
#endif
            //Add Relic Label
            char abottomRelicName[30];
            sprintf(abottomRelicName,"%s",aRelicStr->getCString());
            CCLabelTTF *bottomRelicLabel=CCLabelTTF::create(abottomRelicName,"LMVeraHumana95Bold",10);
            bottomRelicLabel->setPosition(CCPointMake(aRelic->getPositionX(), aRelic->getPositionY()-78));
            bottomRelicLabel->setColor(ccc3(85, 10, 0));
            scrollLayer->addChild(bottomRelicLabel,10);
            relicsCounter++;
            
            if(relicsCounter==2)
            {
                relicsYpos=aMonsterSpr->getPositionY()-82;
                relicsXpos=aMonsterSpr->getPositionX()-184;
                relicsCounter=0;
            }
            else
            {
                relicsXpos=aMonsterSpr->getPositionX()+184;
            }
            
        }
        //this->addChainInScrollLayer(aMonsterSpr->getPositionX(), aMonsterSpr->getPositionY(), chainCounter);
        //Adding Bottom Buttons
        CCSprite *normalSprite;
        CCSprite *selectedSprite;
        //buy relics menu
        normalSprite=CCSprite::createWithSpriteFrameName("buy_relics_btn.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("buy_relics_btn_hvr.png");
        CCMenuItemSprite *buyRelicsMenuItem=CCMenuItemSprite::create(selectedSprite, normalSprite, this, menu_selector(LMCollectionLayer::buyRelicsButtonAction));
        buyRelicsMenuItem->setTag(1);
        buyRelicsMenuItem->setPosition(CCPointMake(aMonsterSpr->getPositionX()+370, aMonsterSpr->getPositionY()-125));
        //Menu
        CCMenu *bottomMenu=CCMenu::create(buyRelicsMenuItem,NULL);
        scrollLayer->addChild(bottomMenu,1);
        bottomMenu->setPosition(CCPointMake(0, 0));
        
        monsterYPos=monsterYPos-380;
    }
    this->addRelicsAndMonstersCountLabel(this->relicsCount, this->monstersCount);
    
    
}

#pragma mark - menu button  functions
void LMCollectionLayer::loadLoneIslandCollections()
{
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    char const *worldname="World_1";
    this->addRelicsAndMonsters(worldname,  552,2);
    this->addLockImage(worldname);
}

void LMCollectionLayer::loadForestAdventureCollections()
{
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    char const *worldname="World_2";
    this->addLockImage(worldname);
    this->addRelicsAndMonsters(worldname,  2833,8);
}

void LMCollectionLayer::loadHillsOfCuriosityCollections()
{
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    char const *worldname="World_3";
    this->addLockImage(worldname);
    this->addRelicsAndMonsters(worldname,  2833,8);
}


void LMCollectionLayer::loadPeaksOfDestinyCollections()
{
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    char const *worldname="World_4";
    this->addLockImage(worldname);
    this->addRelicsAndMonsters(worldname,  2833,8);
}

void LMCollectionLayer::loadChambersOfBeyondCollections()
{
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    char const *worldname="World_5";
    this->addLockImage(worldname);
    this->addRelicsAndMonsters(worldname,  2833,8);
}

void LMCollectionLayer::loadSandsOfPerilCollections()
{
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    char const *worldname="World_6";
    this->addLockImage(worldname);
    this->addRelicsAndMonsters(worldname,  2833,8);
}

void LMCollectionLayer::loaWatersOfUnderseaCollections()
{
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    char const *worldname="World_7";
    this->addLockImage(worldname);
    this->addRelicsAndMonsters(worldname,  2833,8);
}


#pragma mark - chain and Adding labels in scolllayer

void LMCollectionLayer:: addChainInScrollLayer(float x,float y,int noTimes)
{
    if(noTimes==1)
    {
        CCSprite *leftDesign1=CCSprite::createWithSpriteFrameName("mc_card_join_chain.png");
        leftDesign1->setPosition(CCPointMake(x-122, y+68));
        scrollLayer->addChild(leftDesign1,10);
    }
    else if(noTimes==2)
    {
       
        CCSprite *rightDesign1=CCSprite::createWithSpriteFrameName("mc_card_join_chain.png");
        rightDesign1->setPosition(CCPointMake(x+120, y+68));
        rightDesign1->setFlipX(1);
        scrollLayer->addChild(rightDesign1,10);
    }
    else if(noTimes==3)
    {
        CCSprite *leftDesign2=CCSprite::createWithSpriteFrameName("mc_card_join_chain.png");
        leftDesign2->setPosition(CCPointMake(x-122, y-85));
        leftDesign2->setFlipY(1);
        scrollLayer->addChild(leftDesign2,10);
    }
    else
    {
        CCSprite *rightDesign2=CCSprite::createWithSpriteFrameName("mc_card_join_chain.png");
        rightDesign2->setPosition(CCPointMake(x+120, y-85));
        scrollLayer->addChild(rightDesign2,10);

        
    }
       
}
void LMCollectionLayer::addRelicsAndMonstersCountLabel(int relCount,int monCount)
{
    //Relics Collected Label
    CCLabelTTF *relicsCollectedLabel=CCLabelTTF::create("You have collected          Relics\n      in this region","LMVeraHumana95Bold",21);
    relicsCollectedLabel->setPosition(CCPointMake(170, 432));
    relicsCollectedLabel->setColor(ccc3(76,54,12));
    worldNameLayer->addChild(relicsCollectedLabel,1);
    
    CCSprite *smallRelicCountImage=CCSprite::createWithSpriteFrameName("score_bg.png");
    smallRelicCountImage->setPosition(CCPointMake(195, 34));
    relicsCollectedLabel->addChild(smallRelicCountImage,1);
    
    char relicsCountNo[5];
    sprintf(relicsCountNo,"%d",relCount);
    CCLabelTTF *relicsCountLabel=CCLabelTTF::create(relicsCountNo, "LMVeraHumana95Bold", 22);
    relicsCountLabel->setPosition(CCPointMake(195, 33));
    
    relicsCollectedLabel->addChild(relicsCountLabel,3);
    
    
    //Monsters Collected Label
    CCLabelTTF *monstersCollectedLabel=CCLabelTTF::create("You have collected         Monsters\n      in this region","LMVeraHumana95Bold",21);
    monstersCollectedLabel->setPosition(CCPointMake(856, 432));
    monstersCollectedLabel->setColor(ccc3(76,54,12));
    worldNameLayer->addChild(monstersCollectedLabel,1);
    
    CCSprite *smallmonstersCountImage=CCSprite::createWithSpriteFrameName("score_bg.png");
    smallmonstersCountImage->setPosition(CCPointMake(194, 34));
    monstersCollectedLabel->addChild(smallmonstersCountImage,1);
    
    
    char monstersCountNo[5];
    sprintf(monstersCountNo,"%d",monCount);
    CCLabelTTF *monstersCountLabel=CCLabelTTF::create(monstersCountNo, "LMVeraHumana95Bold", 22);
    monstersCountLabel->setPosition(CCPointMake(194, 33));
    
    monstersCollectedLabel->addChild(monstersCountLabel,3);
    
}

#pragma mark - buy Relics Buttton functinality
void LMCollectionLayer:: buyRelicsButtonAction()
{
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    LMDataManager::sharedManager()->disableMenu = true;
    LMDataManager::sharedManager()->toGoStoreScene=2;
    
    storeLayer = new LMStoreLayer();
    this->addChild(storeLayer,10);
    //Add Close Button
    //close Button
    
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
    CCMenuItemSprite *closeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMCollectionLayer::removeStoreLayer));
    closeMenuItem->setPosition(CCPointMake(944, 719));
    
    CCMenu *tempMenu = CCMenu::createWithItem(closeMenuItem);
    tempMenu->setPosition(CCPointZero);
    this->addChild(tempMenu,10);
    
    
}
void LMCollectionLayer::removeStoreLayer(CCMenuItemImage *sender)
{
    this->removeChild(storeLayer, true);
    delete storeLayer;
    
    sender->removeFromParentAndCleanup(true);
    
    LMDataManager::sharedManager()->disableMenu = false;
}


#pragma mark - Dealloc
LMCollectionLayer::~LMCollectionLayer(){
    
   
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LMCollectionsScene.plist");
    this->removeChild(menuLayer, true);
    delete menuLayer;
    
}


