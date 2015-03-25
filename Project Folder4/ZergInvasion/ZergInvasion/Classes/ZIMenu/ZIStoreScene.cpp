//
//  ZIStoreScene.cpp
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 13/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "ZIStoreScene.h"

using namespace cocos2d;
//using namespace CocosDenshion;

ZIStoreScene::ZIStoreScene()
{
    CCLog("construction called in ZIStoreScene ");
   CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ZIUISpriteSheet.plist","ZIUISpriteSheet.pvr.ccz");
    this->addBackGroundWithButtons();
    //screenSize=CCDirector::sharedDirector()->getWinSize()
}

ZIStoreScene::~ZIStoreScene()
{
    CCLog("destructor called in ZIStoreScene");
}


CCScene* ZIStoreScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    CCLayer* layer = new ZIStoreScene();
    scene->addChild(layer);
    layer->release();
    return scene;
}

void ZIStoreScene::addBackGroundWithButtons()
{
    //backGround
    ZICustomSprite *backGroundSprite=backGroundSprite->spriteWithFile("Background.png");
    backGroundSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
    this->addChild(backGroundSprite);
    
    ZICustomSprite *header=header->spriteWithFrame("header.png");
    header->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-20));
    this->addChild(header,1);
    
    
    ZICustomSprite *gameModeTitle=gameModeTitle->spriteWithFrame("store_tittle.png");
    gameModeTitle->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+15, CCDirector::sharedDirector()->getWinSize().height-25));
    this->addChild(gameModeTitle,2);
    
    //backButton
    ZICustomSprite *backButtonNormalImage=backButtonNormalImage->spriteWithFrame("backButtonNormal.png");
    ZICustomSprite *backButtonSelectedImage=backButtonSelectedImage->spriteWithFrame("backButtonSelected.png");
    CCMenuItemSprite *backButton = CCMenuItemSprite::create(
                                                            backButtonNormalImage,
                                                            backButtonSelectedImage,
                                                            this,
                                                            menu_selector(ZIScoreScene::scoreMenuCallbacks));
    backButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2-120, CCDirector::sharedDirector()->getWinSize().height-25));
    backButton->setTag(1);
    
    CCMenu *backModeMenu = CCMenu::create(backButton, NULL);
    backModeMenu->setPosition(ccp(0,0));
    this->addChild(backModeMenu,2);
    
    //foreGround
    ZICustomSprite *storeForeGround=storeForeGround->spriteWithFrame("storeForground_bg.png");
    storeForeGround->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
    this->addChild(storeForeGround);
    
    ZICustomSprite *noStarsEarnedColm=noStarsEarnedColm->spriteWithFrame("starsEarnedColm.png");
    noStarsEarnedColm->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+2, CCDirector::sharedDirector()->getWinSize().height-230));
    this->addChild(noStarsEarnedColm,1);
    
    ZICustomSprite *noOfShootingStarsColm=noOfShootingStarsColm->spriteWithFrame("shootingStarsEarnedColm.png");
    noOfShootingStarsColm->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+2, CCDirector::sharedDirector()->getWinSize().height-265));
    this->addChild(noOfShootingStarsColm,1);
    
    ZICustomSprite *noOfRayGunsColm=noOfRayGunsColm->spriteWithFrame("rayGunEarnedColm.png");
    noOfRayGunsColm->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+2, CCDirector::sharedDirector()->getWinSize().height-300));
    this->addChild(noOfRayGunsColm,1);
    
    ZICustomSprite *noOfBlackHoleColm=noOfBlackHoleColm->spriteWithFrame("blackHoleEarned.png");
    noOfBlackHoleColm->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+2, CCDirector::sharedDirector()->getWinSize().height-335));
    this->addChild(noOfBlackHoleColm,1);
    
    
    ZICustomSprite *footHeader=footHeader->spriteWithFrame("header.png");
    footHeader->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-455));
    this->addChild(footHeader,1);
    
    //buttons
    ZICustomSprite *rayGun = rayGun->spriteWithFrame("ray-gunButton.png");
    rayGun->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2-110,CCDirector::sharedDirector()->getWinSize().height-455));
    this->addChild(rayGun,2);

    ZICustomSprite *shootingStar = shootingStar->spriteWithFrame("shootingStarsButton.png");
    shootingStar->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height-455));
    this->addChild(shootingStar,2);
    
       
    ZICustomSprite *blackHole = blackHole->spriteWithFrame("blackHoleButton.png");
    blackHole->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+110,CCDirector::sharedDirector()->getWinSize().height-455));
    this->addChild(blackHole,2);

   
}

void ZIStoreScene::storeMenuCallbacks(CCObject *sender)
{
    CCMenuItemImage *tempItem = (CCMenuItemImage *)sender;
    
    switch (tempItem->getTag()) {
        case 1: //Back
            
            CCDirector::sharedDirector()->replaceScene(ZIMainMenu::scene());
            break;
        default:
            break;
    }
}

