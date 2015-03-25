//
//  LMMenuLayer.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMMenuLayer.h"
#include "LMMainScreen.h"
#include "lmstoreLayer.h"
#include "LMLivesLayer.h"
#include "LMWorldSelection.h"
#include "LMCollectionLayer.h"
#include "LMCollectionLayer.h"
#include "LMAchievmentsLayer.h"
#include "LMRelicsLayer.h"
#include "LMMonsterClaimedLayer.h"

using namespace cocos2d;

LMMenuLayer::LMMenuLayer(){
    
    menuItemsArray=CCArray::create();
    //float width=CCDirector::sharedDirector()->getWinSize().width;
    //float height=CCDirector::sharedDirector()->getWinSize().height;

    
    //adding logo menu
    CCSprite *normalSprite;
    CCSprite *selectedSprite;
    
    normalSprite=CCSprite::createWithSpriteFrameName("logo_1.png");

    
    CCMenuItemSprite *logoMenuItem=CCMenuItemSprite::create(normalSprite, normalSprite, this, menu_selector(LMMenuLayer::action));
    logoMenuItem->setTag(0);
    CCMenu *logomenu=CCMenu::create(logoMenuItem,NULL);
    this->addChild(logomenu);
    logomenu->setPosition(CCPointMake(41,282));
    
    CCSprite *logo=CCSprite::createWithSpriteFrameName("logo_1.png");
    logo->setPosition(CCPointMake(41, 282));
    this->addChild(logo);
    
    
    normalSprite=CCSprite::createWithSpriteFrameName("store_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("store_btn_hvr.png");
    //strore meni item 
        CCMenuItemSprite *storeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    storeMenuItem->setTag(1);
    
    storeMenuItem->setPosition(CCPointMake(111, 297));
    //storeMenuItem->setScale(0.9);
    
    
    
    // lives menu  item
    
    normalSprite=CCSprite::createWithSpriteFrameName("life_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("life_btn_hvr.png");
        CCMenuItemSprite *livesMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    livesMenuItem->setTag(2);
    livesMenuItem->setPosition(CCPointMake(175, 297));




    // world menu 
    normalSprite=CCSprite::createWithSpriteFrameName("world_map_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("world_map_btn_hvr.png");
        CCMenuItemSprite *worldMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    worldMenuItem->setTag(3);
    worldMenuItem->setPosition(CCPointMake(226, 297));




    // collection menu 
    normalSprite=CCSprite::createWithSpriteFrameName("my_collections_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("my_collections_btn_hvr.png");
        CCMenuItemSprite *myCollectionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    myCollectionMenuItem->setTag(4);
    myCollectionMenuItem->setPosition(CCPointMake(272, 297));




    // monster claimed menu 
    normalSprite=CCSprite::createWithSpriteFrameName("monsters_climd_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("monsters_climd_btn_hvr.png");
        CCMenuItemSprite *monsterClaimedMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    monsterClaimedMenuItem->setTag(5);
    monsterClaimedMenuItem->setPosition(CCPointMake(315, 297));


    
    
    // relics menu 
    
    normalSprite=CCSprite::createWithSpriteFrameName("relics_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("relics_btn-15.png");
        CCMenuItemSprite *relicsMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    relicsMenuItem->setTag(6);
    relicsMenuItem->setPosition(CCPointMake(357, 297));


    
    
    // achievment menu 
    normalSprite=CCSprite::createWithSpriteFrameName("achievmnt_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("achievmnt_btn_hvr.png");
        CCMenuItemSprite *achievmentsMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    achievmentsMenuItem->setTag(7);
    achievmentsMenuItem->setPosition(CCPointMake(428, 297));

   
    
    // information menu 
    
    normalSprite=CCSprite::createWithSpriteFrameName("info_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("info_btn_hvr.png");
        CCMenuItemSprite *infoMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    infoMenuItem->setTag(8);
    infoMenuItem->setPosition(CCPointMake(394, 297));


    
    // volume menu 
    normalSprite=CCSprite::createWithSpriteFrameName("volum_btn.png");
    normalSprite->setRotation(20);
    selectedSprite=CCSprite::createWithSpriteFrameName("volum_btn-15.png");
    selectedSprite->setRotation(20);

        CCMenuItemSprite *volumeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMMenuLayer::action));
    volumeMenuItem->setTag(9);
    volumeMenuItem->setPosition(CCPointMake(458, 298));


    
    
       
    CCMenu *topMenu=CCMenu::create(storeMenuItem,livesMenuItem,worldMenuItem, myCollectionMenuItem,monsterClaimedMenuItem,relicsMenuItem,achievmentsMenuItem,infoMenuItem,volumeMenuItem, NULL);
    this->addChild(topMenu);
    topMenu->setPosition(ccp(0,0));

   // topMenu->setPosition(ccp(260,300));
    //topMenu->alignItemsHorizontally();
    

    
}

void LMMenuLayer::action(cocos2d::CCMenuItemImage *sender){
    
    int tag=sender->getTag();
    switch (tag) {
        case 0: {
            CCDirector::sharedDirector()->replaceScene(LMMainScreen::scene());
            
        }
        case 1:
        {
            LMStoreLayer *storeLayer=new LMStoreLayer();
            this->addChild(storeLayer);
            
        }
            break;
            
        case 2:
        {
            LMLivesLayer *livesLayer=new LMLivesLayer();
            this->addChild(livesLayer);
            
        }
            break;  
            
            
        case 3:
        {
            CCDirector::sharedDirector()->replaceScene(LMWorldselection::scene());
            
        }
            break;  
        case 4:
        {
            
        }
            break;  
            
        case 5:
        {
            
        }
            break;
        case 6:
        {
            
        }
            break;
        case 7:
        {
            
        }
            break;
        case 8:
        {
            
        }
            break;
            
        default:
            break;
    }
    
}
LMMenuLayer::~LMMenuLayer(){
    
}



