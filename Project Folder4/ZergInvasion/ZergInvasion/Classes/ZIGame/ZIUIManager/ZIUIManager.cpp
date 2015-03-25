//
//  ZIUIManager.cpp
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#include "ZIUIManager.h"
#include "ZIDataManager.h"
#include "ZICustomSprite.h"
#include "ZIMainMenu.h"

ZIUIManager::ZIUIManager(void) {
    
    // Assigning the layer
    this->gameLayer = DataManager->gameLayer;
    
    // Setup the UI
    this->setupGamePlayUI();
    
    // Initializing values
    this->rightPanelSize = CCSizeMake(90, 480);
    this->topPanelSize = CCSizeMake(320, 50);
}

ZIUIManager::~ZIUIManager(void) {
    
    CCLog("UI manager dealloc");
}

void ZIUIManager::setupGamePlayUI() {
 
    // Setting up background
    ZICustomSprite *background = background->spriteWithFile("Background.png");
    background->setPosition(ccp(DataManager->screenSize.width/2, DataManager->screenSize.height/2));
    MainGameLayer->addChild(background, -4);
    
    // Setting up the panel
    ZICustomSprite *panel = panel->spriteWithFile("saidbar_Bg.png");
    panel->setPosition(ccp(DataManager->screenSize.width/2, DataManager->screenSize.height/2));
    DataManager->UILayer->addChild(panel);
    
    
    ZICustomSprite *backButtonNormalImage=backButtonNormalImage->spriteWithFrame("backButtonNormal.png");
    ZICustomSprite *backButtonSelectedImage=backButtonSelectedImage->spriteWithFrame("backButtonSelected.png");
   
   
    CCMenuItemSprite* backItem = CCMenuItemSprite::create(backButtonNormalImage, backButtonSelectedImage, this, menu_selector(ZIUIManager::menuCallbacks));
    backItem->setTag(1);
    backItem->setPosition(ccp(43, 457));
    
    ZICustomSprite *pauseButtonNormalImage=pauseButtonNormalImage->spriteWithFrame("pauseButtonNormal.png");
    ZICustomSprite *pauseButtonSelectedImage=pauseButtonSelectedImage->spriteWithFrame("pauseButtonSelected.png");
    

    CCMenuItemSprite *pauseItem = CCMenuItemSprite::create(pauseButtonNormalImage, pauseButtonSelectedImage, this, menu_selector(ZIUIManager::menuCallbacks));
    pauseItem->setTag(2);
    pauseItem->setPosition(ccp(109, 457));
    
    ZICustomSprite *buyButtonNormalImage=buyButtonNormalImage->spriteWithFrame("buyButtonNormal.png");
    ZICustomSprite *buyButtonSelectedImage=buyButtonSelectedImage->spriteWithFrame("buyButtonSelected.png");

    CCMenuItemSprite* buyItem = CCMenuItemSprite::create(buyButtonNormalImage, buyButtonSelectedImage, this, menu_selector(ZIUIManager::menuCallbacks));
    buyItem->setTag(3);
    buyItem->setPosition(ccp(200, 457));
    
    CCMenu *mainMenu = CCMenu::create(backItem,pauseItem,buyItem,NULL);
    //mainMenu->alignItemsHorizontallyWithPadding(10);
    mainMenu->setPosition(CCPointZero);
    DataManager->UILayer->addChild(mainMenu);
    
    ZICustomSprite *starCounter = starCounter->spriteWithFrame("star_bg.png");
    starCounter->setPosition(ccp(279,457));
    DataManager->UILayer->addChild(starCounter);
    
    ZICustomSprite *shootingStar = shootingStar->spriteWithFrame("shootingStarsButton.png");
    shootingStar->setPosition(ccp(279,376));
    DataManager->UILayer->addChild(shootingStar);
    
    ZICustomSprite *rayGun = rayGun->spriteWithFrame("ray-gunButton.png");
    rayGun->setPosition(ccp(279,303));
    DataManager->UILayer->addChild(rayGun);
    
    ZICustomSprite *blackHole = blackHole->spriteWithFrame("blackHoleButton.png");
    blackHole->setPosition(ccp(279,233));
    DataManager->UILayer->addChild(blackHole);
}

void ZIUIManager::menuCallbacks(CCObject *sender) {
    
    CCMenuItemImage *tempItem = (CCMenuItemImage *)sender;
    
    switch (tempItem->getTag()) {
        case 1: // back
            
            CCDirector::sharedDirector()->replaceScene(ZIMainMenu::scene());
            break;
        case 2: // pause
            
            break;
        case 3: // Store
            
            break;
    }
}