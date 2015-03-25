//
//  LMRelicsLayer.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMRelicsLayer.h"
#include "LMStoreLayer.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "LMObjectiveCCalls.h"


#else

#endif


using namespace cocos2d;



CCScene* LMRelicsLayer::scene(){
    
    CCScene *Scene=CCScene::create();
    
    LMRelicsLayer *relicsLayer = new LMRelicsLayer();
    Scene->addChild(relicsLayer);
    relicsLayer->release();
    return Scene;
}



LMRelicsLayer::LMRelicsLayer(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LMRelicsSceneImages.plist");
  
    
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    
    // menu layer
    menuLayer = new LMMenuLayer();
    this->addChild(menuLayer,2);
    
    //Add BG
    CCSprite *bgSpr = CCSprite::create("UICommonBG.png");
    bgSpr->setPosition(CCPointMake(width/2, height/2));
    this->addChild(bgSpr);
    CCSprite *normalSprite;
    CCSprite *selectedSprite;
    
    //Adding Bottom Buttons
    //buy relics menu
    normalSprite=CCSprite::createWithSpriteFrameName("buy_relics_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("buy_relics_btn_hvr.png");
     CCMenuItemSprite *buyRelicsMenuItem=CCMenuItemSprite::create(selectedSprite, normalSprite, this, menu_selector(LMRelicsLayer::action));
    buyRelicsMenuItem->setTag(1);
    buyRelicsMenuItem->setPosition(CCPointMake(width/2-90, height/2-300));
    
    //GoTo Map menu
    normalSprite=CCSprite::createWithSpriteFrameName("go_to_map_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("go_to_map_btn_hvr.png");
      CCMenuItemSprite *goToMapMenuItem=CCMenuItemSprite::create(selectedSprite, normalSprite, this, menu_selector(LMRelicsLayer::action));
    goToMapMenuItem->setTag(2);
    goToMapMenuItem->setPosition(CCPointMake(width/2+180, height/2-300));
    
    
    //Menu
    CCMenu *bottomMenu=CCMenu::create(buyRelicsMenuItem,goToMapMenuItem,NULL);
    this->addChild(bottomMenu,1);
    bottomMenu->setPosition(CCPointMake(0, 0));
    
      

    
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
    CCSprite *relicsHeadingSpr = CCSprite::createWithSpriteFrameName("my_relics_title.png");
    relicsHeadingSpr->setPosition(CCPoint(512, 630));
    this->addChild(relicsHeadingSpr);
    
    
    //Read the monster details
    
    // Loading the plist...
    std::string strin=CCFileUtils::sharedFileUtils()->getWriteablePath();
    strin.append("LMRelicMonsterView.plist");
        
    CCDictionary *allRelicsDataBaseDict = CCDictionary::createWithContentsOfFileThreadSafe(strin.c_str());
    
      
    CCArray *relicsDataBaseDetailsArr = (CCArray *)allRelicsDataBaseDict->valueForKey("Relics");
        
    int totalCards = relicsDataBaseDetailsArr->count();
    int totalRows = totalCards/4;
    
    //Check whether we have 4 cards in each row
    int remainder = totalCards%4;
    
    if (remainder!=0) {
        totalRows++;
    }
    
    int xPos = 70;
    int yPos = (totalRows*250);
    
    int scrlHeight = 0;
    
    int index = 1;
    
    CCObject *aRelicsObj;
    CCARRAY_FOREACH(relicsDataBaseDetailsArr, aRelicsObj)
    {
        
        CCString *aRelicsStr = (CCString *)aRelicsObj;
        
        //Add Monster Card BG
        CCSprite *aRelicsCardBGSpr = CCSprite::createWithSpriteFrameName("relics_card_bg.png");
        aRelicsCardBGSpr->setPosition(CCPointMake(xPos, yPos));
        scrollLayer->addChild(aRelicsCardBGSpr);
        
        
        char aRelicsName[60];
        sprintf(aRelicsName, "%s.png",aRelicsStr->getCString());
        CCSprite *aRelic = CCSprite::create(aRelicsName);
        aRelic->setPosition(CCPointMake(xPos, yPos+15));
        scrollLayer->addChild(aRelic);
        
        char abottomRelicsName[30];
        sprintf(abottomRelicsName,"%s",aRelicsStr->getCString());
        CCLabelTTF *bottomRelicLabel=CCLabelTTF::create(abottomRelicsName,"LMVeraHumana95Bold",14);
        bottomRelicLabel->setPosition(CCPointMake(aRelic->getPositionX(), aRelic->getPositionY()-100));
        //bottomRelicLabel->setColor(ccc3(85, 10, 0));
        scrollLayer->addChild(bottomRelicLabel,10);
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        int relicsObtainedCount = LMObjectiveCCalls::noOfTimesRelicObtained(aRelicsStr->getCString());
        if(relicsObtainedCount>1)
        {
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
        xPos = xPos + 160;
        
        if(index%4==0)
        {
            xPos = 70;
            yPos = yPos-250;
            scrlHeight = scrlHeight + 250;
        }
        index++;
    }
    
    scrollView->setContentSize(CCSize(898,totalRows*250+150));
    scrollView->setContentOffset(CCPointMake(0,-totalRows*250+290), false);
    
    //scrollView->updateInset();
}


void LMRelicsLayer::action(cocos2d::CCMenuItemImage *sender){
    //if Main menu is disabled
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    int tag=sender->getTag();
    
    switch (tag) {
        case 1:
        {
            LMDataManager::sharedManager()->disableMenu = true;
            LMDataManager::sharedManager()->toGoStoreScene=2;

            storeLayer = new LMStoreLayer();
            this->addChild(storeLayer,10);
            
            CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
            CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
            CCMenuItemSprite *closeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMRelicsLayer::removeStoreLayer));
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
void LMRelicsLayer::removeStoreLayer(CCMenuItemImage *sender)
{
    this->removeChild(storeLayer, true);
    delete storeLayer;
    
    sender->removeFromParentAndCleanup(true);
    
    LMDataManager::sharedManager()->disableMenu = false;
}


LMRelicsLayer::~LMRelicsLayer(){
    CCLOG("Dealloc in ~LMRelicsLayer");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LMRelicsSceneImages.plist");
   
    this->removeChild(menuLayer, true);
    delete menuLayer;
    
}





