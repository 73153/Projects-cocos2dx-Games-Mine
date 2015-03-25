//
//  ZIScoreScene.cpp
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 13/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ZIScoreScene.h"

using namespace cocos2d;
//using namespace CocosDenshion;

ZIScoreScene::ZIScoreScene()
{
    CCLog("construction called in ZIScoreScene ");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ZIUISpriteSheet.plist","ZIUISpriteSheet.pvr.ccz");
    this->addBackGroundWithButtons();
    //screenSize=CCDirector::sharedDirector()->getWinSize()
}
ZIScoreScene::~ZIScoreScene()
{
    
    CCLog("destructor called in ZIScoreScene");
}


CCScene* ZIScoreScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    CCLayer* layer = new ZIScoreScene();
    scene->addChild(layer);
    layer->release();
    return scene;
}

void ZIScoreScene::addBackGroundWithButtons()
{
    ZICustomSprite *backGroundSprite=backGroundSprite->spriteWithFile("Background.png");
    backGroundSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
    this->addChild(backGroundSprite);
    
    ZICustomSprite *header=header->spriteWithFrame("header.png");
    header->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-20));
    this->addChild(header,1);
    
    
    ZICustomSprite *gameModeTitle=gameModeTitle->spriteWithFrame("store_tittle.png");
    gameModeTitle->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+15, CCDirector::sharedDirector()->getWinSize().height-25));
    this->addChild(gameModeTitle,2);
    
    //backbutton
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
    
    
}
void ZIScoreScene::scoreMenuCallbacks(CCObject *sender)
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
