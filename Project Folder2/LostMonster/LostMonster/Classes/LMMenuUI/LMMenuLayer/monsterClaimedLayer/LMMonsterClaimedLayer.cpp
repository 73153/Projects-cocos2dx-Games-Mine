//
//  LMMonsterClaimedLayer.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMMonsterClaimedLayer.h"

using namespace cocos2d;


CCScene* LMMonsterClaimedLayer::scene(){
    
    CCScene *Scene=CCScene::create();
    
    LMMonsterClaimedLayer *monsterClaimedLayer = new LMMonsterClaimedLayer();
    Scene->addChild(monsterClaimedLayer);
    monsterClaimedLayer->release();
    return Scene;
}


LMMonsterClaimedLayer::LMMonsterClaimedLayer(){
       
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LMColleectionMonsters.plist");
    

    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    
    // menu layer
    menuLayer = new LMMenuLayer();
    this->addChild(menuLayer,2);
    
    //Add BG
    CCSprite *bgSpr = CCSprite::create("UICommonBG.png");
    bgSpr->setPosition(CCPointMake(width/2, height/2));
    this->addChild(bgSpr);
    
    CCSprite *relicsSpr = CCSprite::create("RelicsMonstersTopBG.png");
    relicsSpr->setPosition(CCPointMake(width/2, height/2-25));
    this->addChild(relicsSpr,1);

    CCLayer *scrollLayer = CCLayer::create();
    
    scrollView = CCScrollView::create(CCSize(979,463));
    scrollView->setDirection(kCCScrollViewDirectionVertical);
    scrollView->setBounceable(true);
    scrollView->setContainer(scrollLayer);
    this->addChild(scrollView,1);
    
    scrollView->setPosition(CCPointMake(200,127.5));
    
       
    //Add Heading
    CCSprite *monsterHeadingSpr = CCSprite::createWithSpriteFrameName("my_monsters_title.png");
    monsterHeadingSpr->setPosition(CCPoint(512, 630));
    this->addChild(monsterHeadingSpr);
    
    
    //Read the monster details
    
    
    // Loading the plist...
    std::string strin=CCFileUtils::sharedFileUtils()->getWriteablePath();
    strin.append("LMRelicMonsterView.plist");    // Getting the dictionaries into...
    CCDictionary *allMonstersDataDict = CCDictionary::createWithContentsOfFileThreadSafe(strin.c_str());
    

    CCArray *monsterDetailsArr = (CCArray *)allMonstersDataDict->valueForKey("Monster");
     
    
    int totalCards = monsterDetailsArr->count();
    int totalRows = totalCards/4;
    
    //Check whether we have 4 cards in each row
    int remainder = totalCards%4;
    
    if (remainder!=0) {
        totalRows++;
    }

    
    int xPos = 75;
    int yPos = totalRows*250;
    
    int scrlHeight = 0;

    int index = 1;
    
    CCObject *aMonsterObj;
    CCARRAY_FOREACH(monsterDetailsArr, aMonsterObj)
    {
        CCString *aMonsterStr = (CCString *)aMonsterObj;
        
        //Add Monster Card BG
        CCSprite *aMonsterCardBGSpr = CCSprite::createWithSpriteFrameName("monters_card_bg.png");
        aMonsterCardBGSpr->setPosition(CCPointMake(xPos, yPos));
        scrollLayer->addChild(aMonsterCardBGSpr);
        
        char aMonsterName[30];
        sprintf(aMonsterName, "%s.png",aMonsterStr->getCString());
                
        CCSprite *aRelic = CCSprite::create(aMonsterName);
        aRelic->setPosition(CCPointMake(xPos, yPos+15));
        aRelic->setScale(0.55);
        scrollLayer->addChild(aRelic);
        
        char abottomMonsterName[30];
        sprintf(abottomMonsterName,"%s",aMonsterStr->getCString());
        CCLabelTTF *bottomRelicLabel=CCLabelTTF::create(abottomMonsterName,"LMVeraHumana95Bold",20);
        bottomRelicLabel->setPosition(CCPointMake(aRelic->getPositionX(), aRelic->getPositionY()-100));
        //bottomRelicLabel->setColor(ccc3(85, 10, 0));
        scrollLayer->addChild(bottomRelicLabel,10);
        
        xPos = xPos + 160;
        

        if(index%4==0)
        {
            xPos = 75;
            yPos = yPos-250;
            scrlHeight = scrlHeight + 250;
        }
        index++;


    }
    

    scrollView->setContentSize(CCSize(898,totalRows*250+150));
    scrollView->setContentOffset(CCPointMake(0,-totalRows*250+290), false);

    scrollView->updateInset();
    
    //Adding Bottom Buttons
    CCSprite *normalSprite;
    CCSprite *selectedSprite;

    //buy relics menu
    normalSprite=CCSprite::createWithSpriteFrameName("buy_relics_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("buy_relics_btn_hvr.png");
    CCMenuItemSprite *buyRelicsMenuItem=CCMenuItemSprite::create(selectedSprite, normalSprite, this, menu_selector(LMMonsterClaimedLayer::action));
    buyRelicsMenuItem->setTag(1);
    buyRelicsMenuItem->setPosition(CCPointMake(width/2-90, height/2-300));
    
    //GoTo Map menu
    normalSprite=CCSprite::createWithSpriteFrameName("go_to_map_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("go_to_map_btn_hvr.png");
    CCMenuItemSprite *goToMapMenuItem=CCMenuItemSprite::create(selectedSprite, normalSprite, this, menu_selector(LMMonsterClaimedLayer::action));
    goToMapMenuItem->setTag(2);
    goToMapMenuItem->setPosition(CCPointMake(width/2+180, height/2-300));
    
    
    //Menu
    CCMenu *bottomMenu=CCMenu::create(buyRelicsMenuItem,goToMapMenuItem,NULL);
    this->addChild(bottomMenu,1);
    bottomMenu->setPosition(CCPointMake(0, 0));


}

void LMMonsterClaimedLayer::action(cocos2d::CCMenuItemImage *sender){
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    int tag=sender->getTag();
    
    switch (tag) {
        case 1:
        {
            LMDataManager::sharedManager()->disableMenu = true;
            LMDataManager::sharedManager()->toGoStoreScene = 2;

            storeLayer = new LMStoreLayer();
            this->addChild(storeLayer,10);
          
            //Add Close Button
            CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
            CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
            CCMenuItemSprite *closeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMonsterClaimedLayer::removeStoreLayer));
            closeMenuItem->setPosition(CCPointMake(944, 719));
            
            CCMenu *tempMenu = CCMenu::createWithItem(closeMenuItem);
            tempMenu->setPosition(CCPointZero);
            this->addChild(tempMenu,10);

        }
            break;
        case 2:
        {
            LMSharedSoundManager::sharedManager()->playSound("38 map unravelled Version A.mp3");
            //CCDirector::sharedDirector()->replaceScene(LMWorldSelection::scene());

        }
            break;
        default:
            break;
    }
}
void LMMonsterClaimedLayer::removeStoreLayer(CCMenuItemImage *sender)
{
    this->removeChild(storeLayer, true);
    delete storeLayer;
    
    sender->removeFromParentAndCleanup(true);
    
    LMDataManager::sharedManager()->disableMenu = false;
}


LMMonsterClaimedLayer::~LMMonsterClaimedLayer(){
    
    CCLOG("Dealloc in ~LMMonsterClaimedLayer");
    
    this->removeChild(menuLayer, true);
    delete menuLayer;
     CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LMColleectionMonsters.plist");
}

