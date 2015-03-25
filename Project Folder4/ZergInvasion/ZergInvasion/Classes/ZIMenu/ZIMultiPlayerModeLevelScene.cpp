//
//  ZISelectModeLevelScene.cpp
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 13/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ZIMultiPlayerModeLevelScene.h"

using namespace cocos2d;
//using namespace CocosDenshion;

ZIMultiPlayerModeLevelScene::ZIMultiPlayerModeLevelScene()
{
    CCLog("construction called in ZIMultiPlayerModeLevelScene ");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ZIUISpriteSheet.plist","ZIUISpriteSheet.pvr.ccz");
    this->addBackGroundWithButtons();
}

ZIMultiPlayerModeLevelScene::~ZIMultiPlayerModeLevelScene()
{
    CCLog("destructor called in ZIMultiPlayerModeLevelScene ");
}

CCScene* ZIMultiPlayerModeLevelScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    CCLayer* layer = new ZIMultiPlayerModeLevelScene();
    scene->addChild(layer);
    layer->release();
    return scene;
}

void ZIMultiPlayerModeLevelScene::addBackGroundWithButtons()
{
    //backGround
    ZICustomSprite *backGroundSprite=backGroundSprite->spriteWithFile("Background.png");
    backGroundSprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
    this->addChild(backGroundSprite);
    
    ZICustomSprite *header=header->spriteWithFrame("header.png");
    header->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-20));
    this->addChild(header,1);
    
    ZICustomSprite *gameModeTitle=gameModeTitle->spriteWithFrame("selectGameModeTiittle.png");
    gameModeTitle->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2+15, CCDirector::sharedDirector()->getWinSize().height-25));
    this->addChild(gameModeTitle,2);
    
    //backButton
    ZICustomSprite *backButtonNormalImage=backButtonNormalImage->spriteWithFrame("backButtonNormal.png");
    ZICustomSprite *backButtonSelectedImage=backButtonSelectedImage->spriteWithFrame("backButtonSelected.png");
    CCMenuItemSprite *backButton = CCMenuItemSprite::create(
                                                            backButtonNormalImage,
                                                            backButtonSelectedImage,
                                                            this,
                                                            menu_selector(ZIMultiPlayerModeLevelScene::multiPlayerMenuCallbacks));
    backButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2-120, CCDirector::sharedDirector()->getWinSize().height-25));
    backButton->setTag(1);
    CCMenu *backModeMenu = CCMenu::create(backButton, NULL);
    backModeMenu->setPosition(ccp(0,0));
    this->addChild(backModeMenu,2);
    
    //multiplayerButton
    ZICustomSprite *multiPlayerButtonNormalImage=multiPlayerButtonNormalImage->spriteWithFrame("multiplayerNormalButton.png");
    ZICustomSprite *multiPlayerSelectedImage=multiPlayerSelectedImage->spriteWithFrame("multiplayerButtonSelected.png");
    CCMenuItemSprite *multiPlayerButton = CCMenuItemSprite::create(
                                                                   multiPlayerButtonNormalImage,
                                                                   multiPlayerSelectedImage,
                                                                   this,
                                                                   menu_selector(ZIMultiPlayerModeLevelScene::multiPlayerMenuCallbacks) );
    multiPlayerButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-150));
    multiPlayerButton->setTag(2);
    
    //AIButton
    ZICustomSprite *aiButtonNormalImage=aiButtonNormalImage->spriteWithFrame("aiButtonNormal.png");
    ZICustomSprite *aiSelectedImage=aiSelectedImage->spriteWithFrame("aiButtonSelected.png");
    CCMenuItemSprite *aiButton = CCMenuItemSprite::create(
                                                              aiButtonNormalImage,
                                                              aiSelectedImage,
                                                              this,
                                                              menu_selector(ZIMultiPlayerModeLevelScene::multiPlayerMenuCallbacks) );
    aiButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-240) );
    aiButton->setTag(3);
    
    //Menu
    CCMenu *gameModeMenu = CCMenu::create(aiButton,multiPlayerButton, NULL);
    gameModeMenu->setPosition(ccp(0,0));
    this->addChild(gameModeMenu);
    

}
void ZIMultiPlayerModeLevelScene::multiPlayerMenuCallbacks(CCObject* sender)
{
    CCMenuItemImage *tempItem = (CCMenuItemImage *)sender;
    
    switch (tempItem->getTag()) {
        case 1: //Back
            
            CCDirector::sharedDirector()->replaceScene(ZIGameModeScene::scene());
            break;
        case 2: //MultiPlayer
            
            CCDirector::sharedDirector()->replaceScene(ZIMainGame::scene());
            break;
        case 3: //AI
            
            CCDirector::sharedDirector()->replaceScene(ZIAIModeOptionsScene::scene());
            break;
        default:
            break;
            
    }
    
}