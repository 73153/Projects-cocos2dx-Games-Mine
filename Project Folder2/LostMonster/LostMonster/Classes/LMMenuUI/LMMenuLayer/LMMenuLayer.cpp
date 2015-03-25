//
//  LMMenuLayer.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMMenuLayer.h"

#include "LMDataManager.h"
#include "LMMainScreen.h"
#include "lmstoreLayer.h"

#include "LMWorldSelection.h"
#include "LMCollectionLayer.h"
#include "LMAchievmentsLayer.h"
#include "LMRelicsLayer.h"
#include "LMMonsterClaimedLayer.h"

#include "SimpleAudioEngine.h"
#include "LMSharedSoundManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "LMObjectiveCCalls.h"

#else

#endif

#define kStoreCoinNumberLabelTag 666
#define kLivesNumberLabel 777
#define kMonstersNumberLabel 888
#define kRelicsNumberLabel 999

#define kCloseBtnLivesLayer 123
#define kGetLivesBtnLiverLayer 124

using namespace cocos2d;
using namespace CocosDenshion;

#pragma mark - Implementation

LMMenuLayer::LMMenuLayer(){
    
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    
    //adding logo menu
    CCSprite *normalSprite;
    CCSprite *selectedSprite;
    normalSprite=CCSprite::createWithSpriteFrameName("logo_1.png");
    
    
    CCMenuItemSprite *logoMenuItem=CCMenuItemSprite::create(normalSprite, normalSprite, this, menu_selector(LMMenuLayer::action));
    logoMenuItem->setTag(0);
    CCMenu *logomenu=CCMenu::create(logoMenuItem,NULL);
    this->addChild(logomenu);
    logomenu->setPosition(CCPointMake(width-925,height-75));
    
    CCSprite *logo=CCSprite::createWithSpriteFrameName("logo_1.png");
    logo->setPosition(CCPointMake(width-925, height-75));
    this->addChild(logo);
    
    
    normalSprite=CCSprite::createWithSpriteFrameName("store_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("store_btn_hvr.png");
    
    //strore menu item
    CCMenuItemSprite *storeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    storeMenuItem->setTag(1);
    
    storeMenuItem->setPosition(CCPointMake(width-1252, height-427));
    //storeMenuItem->setScale(0.9);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    int totolCoins = LMObjectiveCCalls::getTotalMoney();
    
#else
    
#endif
    
    char  sNumber[5];
    sprintf(sNumber, "%d",totolCoins);
    
    CCLabelTTF *storeCoinNumberLabel = CCLabelTTF::create(sNumber, "LMVeraHumana95Bold", 25);
    storeCoinNumberLabel->setPosition(CCPointMake(299,713));
    storeCoinNumberLabel->setColor(ccc3(198, 170, 90));
    this->addChild(storeCoinNumberLabel,2);
    storeCoinNumberLabel->setTag(kStoreCoinNumberLabelTag);
    
    
    
    
    // world menu
    normalSprite=CCSprite::createWithSpriteFrameName("world_map_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("world_map_btn_hvr.png");
    
    CCMenuItemSprite *worldMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    worldMenuItem->setTag(3);
    worldMenuItem->setPosition(CCPointMake(width-1108, height-427));
    
    
    
    
    // collection menu
    normalSprite=CCSprite::createWithSpriteFrameName("my_collections_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("my_collections_btn_hvr.png");
    
    CCMenuItemSprite *myCollectionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    myCollectionMenuItem->setTag(4);
    myCollectionMenuItem->setPosition(CCPointMake(width-994, height-427));
    
    
    
    
    // monster claimed menu
    normalSprite=CCSprite::createWithSpriteFrameName("monsters_climd_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("monsters_climd_btn_hvr.png");
    
    CCMenuItemSprite *monsterClaimedMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    monsterClaimedMenuItem->setTag(5);
    monsterClaimedMenuItem->setPosition(CCPointMake(width-890, height-427));
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    
    int totalMonsters =LMObjectiveCCalls::numberOfMonsterObtained();
    
#else
    
#endif
    
    char  mNumber[5];
    sprintf(mNumber, "%d",totalMonsters);
    
    CCLabelTTF *monstersNumberLabel=CCLabelTTF::create(mNumber, "LMVeraHumana95Bold", 32);
    monstersNumberLabel->setPosition(CCPointMake(671,725));
    monstersNumberLabel->setColor(ccc3(225, 41, 5));
    
    this->addChild(monstersNumberLabel,2);
    
    monstersNumberLabel->setTag(kMonstersNumberLabel);
    
    
    // relics menu
    
    normalSprite=CCSprite::createWithSpriteFrameName("relics_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("relics_btn-15.png");
    CCMenuItemSprite *relicsMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    relicsMenuItem->setTag(6);
    relicsMenuItem->setPosition(CCPointMake(width-795, height-427));
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    int totalRelics=LMObjectiveCCalls::numberOfRelicsObtained();
    
#else
    
#endif
    
    char  rNumber[5];
    sprintf(rNumber, "%d",totalRelics);
    
    CCLabelTTF *relicsNumberLabel=CCLabelTTF::create(rNumber, "LMVeraHumana95Bold", 32);
    relicsNumberLabel->setPosition(CCPointMake(765,725));
    relicsNumberLabel->setColor(ccc3(227, 166, 0));
    this->addChild(relicsNumberLabel,2);
    relicsNumberLabel->setTag(kRelicsNumberLabel);
    
    
    // achievment menu
    normalSprite=CCSprite::createWithSpriteFrameName("achievmnt_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("achievmnt_btn_hvr.png");
    
    CCMenuItemSprite *achievmentsMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    achievmentsMenuItem->setTag(7);
    achievmentsMenuItem->setPosition(CCPointMake(width-705, height-427));
    
    
    
    // information menu
    
    normalSprite=CCSprite::createWithSpriteFrameName("info_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("info_btn_hvr.png");
    
    CCMenuItemSprite *infoMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    infoMenuItem->setTag(8);
    infoMenuItem->setPosition(CCPointMake(width-630, height-427));
    
    
    
    // volume menu
    normalSprite=CCSprite::createWithSpriteFrameName("volum_btn.png");
    //normalSprite->setRotation(20);
    selectedSprite=CCSprite::createWithSpriteFrameName("volum_btn_hvr.png");
    //selectedSprite->setRotation(20);
    
    
    
    CCMenuItemSprite *volumeOnSpr = CCMenuItemSprite::create(normalSprite, NULL, NULL, NULL);
    CCMenuItemSprite *volumeOffSpr = CCMenuItemSprite::create(selectedSprite, NULL, NULL, NULL);
    
    CCMenuItemToggle *soundToggleMenu = CCMenuItemToggle::createWithTarget(this,
                                                                           menu_selector(LMMenuLayer::action),
                                                                           volumeOnSpr,
                                                                           volumeOffSpr,
                                                                           NULL );
    
    soundToggleMenu->setTag(9);
    soundToggleMenu->setPosition(CCPointMake(width-570, height-432));
    
    bool isSoundOff = CCUserDefault::sharedUserDefault()->getBoolForKey("isSoundOff");
    
    if (isSoundOff) {
        soundToggleMenu->setSelectedIndex(1);
    }
    
    CCMenu *topMenu=CCMenu::create(storeMenuItem,worldMenuItem, myCollectionMenuItem,monsterClaimedMenuItem,relicsMenuItem,achievmentsMenuItem,infoMenuItem,soundToggleMenu, NULL);
    this->addChild(topMenu);
    
    
    
    
    
      
    //Create a Scheduler to Update Top Labels
    this->schedule(schedule_selector(LMMenuLayer::updateTopLabels),1);
}

#pragma mark - Button Action
void LMMenuLayer::action(cocos2d::CCMenuItemImage *sender){
           
    if (LMDataManager::sharedManager()->disableMenu) {
        
        //If sender is sound button reverse it
        if(sender->getTag()==9)
        {
            CCMenuItemToggle* item = (CCMenuItemToggle*)sender;
            if (item->getSelectedIndex()==0) {
                item->setSelectedIndex(1);
            }
            else
            {
                item->setSelectedIndex(0);
            }
        }
        
        return;
    }
    
    if (sender->getTag()!=9&&LMDataManager::sharedManager()->isGamePlayRunning == false)//Sound Button pr if game is running
    {
        //Stop any BG sound playing
        LMSharedSoundManager::sharedManager()->stopBackgroundSound();
    }
    
    int tag=sender->getTag();
    switch (tag)
    {
        case 0: //Main Screen
        {
            if(LMDataManager::sharedManager()->isGamePlayRunning)
            {
                this->addPopUpScreenIfGameIsRunning(tag);
            }
            else
            {

                //CCDirector::sharedDirector()->replaceScene(LMMainScreen::scene());
            }
        }
            break;
            
        case 1: //Store
        {
            this->addStoreLayer();
        }
            break;
            
                    
        case 3: //World Selection
        {
            if(LMDataManager::sharedManager()->isGamePlayRunning)
            {
                this->addPopUpScreenIfGameIsRunning(tag);
            }
            else
            {
                LMSharedSoundManager::sharedManager()->playSound("38 map unravelled Version A.mp3");
                // CCDirector::sharedDirector()->replaceScene(LMWorldSelection::scene());
            }
        }
            break;
        case 4: //Collection Layer
        {
            if(LMDataManager::sharedManager()->isGamePlayRunning)
            {
                this->addPopUpScreenIfGameIsRunning(tag);
            }
            else
            {
                LMSharedSoundManager::sharedManager()->playSound("34 Enter collections Page.mp3");
                CCDirector::sharedDirector()->replaceScene(LMCollectionLayer::scene());
            }
        }
            break;
            
        case 5: //Monster Obtained
        {
            if(LMDataManager::sharedManager()->isGamePlayRunning)
            {
                this->addPopUpScreenIfGameIsRunning(tag);
            }
            else
            {
                CCDirector::sharedDirector()->replaceScene(LMMonsterClaimedLayer::scene());
            }
        }
            break;
        case 6:  //Relics Obtained
        {
            if(LMDataManager::sharedManager()->isGamePlayRunning)
            {
                this->addPopUpScreenIfGameIsRunning(tag);
            }
            else{
                
                CCDirector::sharedDirector()->replaceScene( LMRelicsLayer::scene());
            }
        }
            break;
            
        case 7:  //Achievements
        {
            if(LMDataManager::sharedManager()->isGamePlayRunning)
            {
                this->addPopUpScreenIfGameIsRunning(tag);
            }
            else
            {
                CCDirector::sharedDirector()->replaceScene(LMAchievmentsLayer::scene());
            }
        }
            break;
            
        case 8: //Info Button
        {
            
        }
            break;
        case 9: // Sound
        {
            CCMenuItemToggle* item = (CCMenuItemToggle*)sender;
            int index = item->getSelectedIndex();
            this->soundStatus(index);
        }
            
            
        default:
            break;
    }
}
void LMMenuLayer:: addPopUpScreenIfGameIsRunning(int senderTag)
{
    if(LMDataManager::sharedManager()->isGamePlayRunning)
    {
        CCLog("Add  Pop over");

        cocos2d::CCDirector::sharedDirector()->pause();
        
        LMDataManager::sharedManager()->disableMenu=true;
        
        this->popupBg=CCSprite ::createWithSpriteFrameName("loading_popup.png");
        this->popupBg->setPosition(CCPointMake(512, 384));
        this->addChild(this->popupBg,50);
        
        
        //wait label
        CCLabelTTF *waitLabel=CCLabelTTF::create("Do you want to Exit the Game ?","LMVeraHumana95Bold",25);
        waitLabel->setPosition(CCPointMake(250, 212));
        waitLabel->setColor(ccc3(51, 1, 2));
        popupBg->addChild(waitLabel,51);
        
        //ok Button
        CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("yes_btn.png");
        CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("yes_btn_hvr.png");
        
        okMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::yesButtonAction));
        okMenuItem->setPosition(CCPointMake(150, 120));
        okMenuItem->setTag(senderTag);
                
        //cancel Button
        normalSprite=CCSprite::createWithSpriteFrameName("no_btn.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("no_btn_hvr.png");
        CCMenuItemSprite *cancelMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::removePopUpScreen));
        cancelMenuItem->setPosition(CCPointMake(340, 120));
        
        
        CCMenu *tempMenu = CCMenu::create(okMenuItem,cancelMenuItem,NULL);
        tempMenu->setPosition(CCPointZero);
        this->popupBg->addChild(tempMenu,10);
    }
}
void LMMenuLayer::removePopUpScreen()
{
    cocos2d::CCDirector::sharedDirector()->resume();
    LMDataManager::sharedManager()->disableMenu = false;
    this->popupBg->removeAllChildrenWithCleanup(1);
    this->popupBg->removeFromParentAndCleanup(1);
    
}

void LMMenuLayer::yesButtonAction(CCMenuItemImage* sender)
{
    LMDataManager::sharedManager()->isGamePlayRunning = false;
    cocos2d::CCDirector::sharedDirector()->resume();
     LMDataManager::sharedManager()->disableMenu=false;
    this->action(sender);
}

#pragma mark - Update Top Labels
void LMMenuLayer::updateTopLabels()
{
    if (shouldCalculateLifeRegenarationTime)
    {
        LMDataManager::sharedManager()->timeCount ++;
        
        //Add Life
        if (LMDataManager::sharedManager()->timeCount == kLifeRegenerationTime*60)
        {
            
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            
            LMObjectiveCCalls::addLivesToDatabaseWithLives(1,1);
            int noOfLivesLeft = LMObjectiveCCalls::getTotalLivesCount();
            
#else
            
#endif
            LMDataManager::sharedManager()->timeCount = 0;
            
            //Check the no of Current Lives
            if (noOfLivesLeft<5) {
                shouldCalculateLifeRegenarationTime = true;
            }
            else
            {
                shouldCalculateLifeRegenarationTime = false;
            }
        }
    }
    else
    {
        LMDataManager::sharedManager()->timeCount = 0;
    }
    
    //Top storeLabel
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    int totalCoins = LMObjectiveCCalls::getTotalMoney();
    
#else
    
#endif
    
    char  noOfTotaltotalCoins[10];
    sprintf(noOfTotaltotalCoins, "%d",totalCoins);
    
    //Get the store Coin Lbl
    CCLabelTTF *storeCoinLbl = (CCLabelTTF *)this->getChildByTag(kStoreCoinNumberLabelTag);
    if (storeCoinLbl) {
        storeCoinLbl->setString(noOfTotaltotalCoins);
    }
    
    
    
    //Top livesLabel count
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    int totalLives = LMObjectiveCCalls::getTotalLivesCount();
    
#else
    
#endif
    
    char  noOfTotalLivesNumber[10];
    sprintf(noOfTotalLivesNumber, "%d",totalLives);
    
    CCLabelTTF *totalLivesLbl = (CCLabelTTF *)this->getChildByTag(kLivesNumberLabel);
    if (totalLivesLbl) {
        totalLivesLbl->setString(noOfTotalLivesNumber);
    }
    
    
    
    //topMonstersLabel count
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    int totalMonsters = LMObjectiveCCalls::numberOfMonsterObtained();
    
#else
    
#endif
    
    char  mNumber[10];
    sprintf(mNumber, "%d",totalMonsters);
    
    CCLabelTTF *monstersNumberLabel = (CCLabelTTF *)this->getChildByTag(kMonstersNumberLabel);
    if (monstersNumberLabel) {
        monstersNumberLabel->setString(mNumber);
    }
    
    
    //topRelicsLabel count
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    int totalRelics= LMObjectiveCCalls::numberOfRelicsObtained();
    
#else
    
#endif
    
    char  rNumber[10];
    sprintf(rNumber, "%d",totalRelics);
    
    CCLabelTTF *relicsNumberLabel = (CCLabelTTF *)this->getChildByTag(kRelicsNumberLabel);
    if (relicsNumberLabel) {
        relicsNumberLabel->setString(rNumber);
    }
    
   
}


#pragma mark - Store Layer
void LMMenuLayer::addStoreLayer()
{
    cocos2d::CCDirector::sharedDirector()->pause();
    LMDataManager::sharedManager()->disableMenu = true;
    LMDataManager::sharedManager()->toGoStoreScene = 1;
    
    storeLayer = new LMStoreLayer();
    this->addChild(storeLayer,10);
    
    //Add Close Button
    //close Button
    
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
    
    CCMenuItemSprite *storeCloseMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::removeStoreLayer));
    storeCloseMenuItem->setPosition(CCPointMake(944, 719));
    
    CCMenu *tempMenu = CCMenu::createWithItem(storeCloseMenuItem);
    tempMenu->setPosition(CCPointZero);
    this->addChild(tempMenu,10);
    
}

void LMMenuLayer::removeStoreLayer(CCMenuItemImage *sender)
{
    cocos2d::CCDirector::sharedDirector()->resume();
    if (LMDataManager::sharedManager()->canMainMenuStoreBtnWork == false) {
        return;
    }
    
    this->removeChild(storeLayer, true);
    delete storeLayer;
    
    sender->removeFromParentAndCleanup(true);
    
    LMDataManager::sharedManager()->disableMenu = false;
}


#pragma mark - Sound
void LMMenuLayer::soundStatus(bool inSoundStatus)
{
    if (inSoundStatus) //OFF
    {
        CCUserDefault::sharedUserDefault()->setBoolForKey("isSoundOff", true);
        
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
    }
    else
    {
        CCUserDefault::sharedUserDefault()->setBoolForKey("isSoundOff", false);
        
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    }
}

#pragma mark - Dealloc
LMMenuLayer::~LMMenuLayer()
{
    CCLOG("Dealloc in ~LMMenuLayer");
}



