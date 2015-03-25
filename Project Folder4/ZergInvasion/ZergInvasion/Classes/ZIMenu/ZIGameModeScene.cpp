//
//  ZIGameScene.cpp
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 13/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "ZIGameModeScene.h"
using namespace cocos2d;

ZIGameModeScene::ZIGameModeScene()
{
    CCLog("construction called inZIGameModeScene ");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ZIUISpriteSheet.plist","ZIUISpriteSheet.pvr.ccz");
    this->addGameModesWithBackground();
}
ZIGameModeScene::~ZIGameModeScene()
{
    
    CCLog("destructor called");
}

CCScene* ZIGameModeScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    CCLayer* layer = new ZIGameModeScene();
    scene->addChild(layer);
    layer->release();
    return scene;
}


void ZIGameModeScene::addGameModesWithBackground()
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
                                                            menu_selector(ZIScoreScene::scoreMenuCallbacks));

    backButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2-120, CCDirector::sharedDirector()->getWinSize().height-25));
    backButton->setTag(1);
    
    CCMenu *backModeMenu = CCMenu::create(backButton, NULL);
    backModeMenu->setPosition(ccp(0,0));
    this->addChild(backModeMenu,2);
    
    //survivalButton
    ZICustomSprite *survivalButtonNormalImage=survivalButtonNormalImage->spriteWithFrame("survivalButtonNormal.png");
    ZICustomSprite *survivalButtonSelectedImage=survivalButtonSelectedImage->spriteWithFrame("survivalButtonSelected.png");
   
    CCMenuItemSprite *survivalButton = CCMenuItemSprite::create(
                                                              survivalButtonNormalImage,
                                                              survivalButtonSelectedImage,
                                                              this,
                                                              menu_selector(ZIGameModeScene::gameModeMenuCallbacks) );
    
    survivalButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-180) );
    survivalButton->setTag(2);
    
    //meteorButton
    ZICustomSprite *meteorButtonNormalImage=meteorButtonNormalImage->spriteWithFrame("meteorNormalButton.png");
    ZICustomSprite *meteorButtonSelectedImage=meteorButtonSelectedImage->spriteWithFrame("meteorButtonSelected.png");
   
    CCMenuItemSprite *meteorButton = CCMenuItemSprite::create(
                                                            meteorButtonNormalImage,
                                                            meteorButtonSelectedImage,
                                                            this,
                                                            menu_selector(ZIGameModeScene::gameModeMenuCallbacks) );
    meteorButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-260) );
    meteorButton->setTag(3);
    
    //multiplayerButton
    ZICustomSprite *multiPlayerButtonNormalImage=multiPlayerButtonNormalImage->spriteWithFrame("multiplayerNormalButton.png");
    ZICustomSprite *multiPlayerSelectedImage=multiPlayerSelectedImage->spriteWithFrame("multiplayerButtonSelected.png");
   
    CCMenuItemSprite *multiPlayerButton = CCMenuItemSprite::create(
                                                                 multiPlayerButtonNormalImage,
                                                                 multiPlayerSelectedImage,
                                                                 this,
                                                                 menu_selector(ZIGameModeScene::gameModeMenuCallbacks) );
    multiPlayerButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-340));
    multiPlayerButton->setTag(4);
    
    //Menu
    CCMenu *gameModeMenu = CCMenu::create(survivalButton,meteorButton,multiPlayerButton, NULL);
    gameModeMenu->setPosition(ccp(0,0));
    this->addChild(gameModeMenu);
}

void ZIGameModeScene::gameModeMenuCallbacks(CCObject* sender)
{
    CCMenuItemImage *tempItem = (CCMenuItemImage *)sender;
    
    switch (tempItem->getTag()) {

        case 1: // Back
            CCDirector::sharedDirector()->replaceScene(ZIMainMenu::scene());
            break;
        case 2: // Survival
            
            CCDirector::sharedDirector()->replaceScene(ZIMainGame::scene());
            break;
        case 3: // Meteor
           
            CCDirector::sharedDirector()->replaceScene(ZIMainGame::scene());
            break;

        case 4: // Multiplayer
            
            CCDirector::sharedDirector()->replaceScene(ZIMultiPlayerModeLevelScene::scene());
            break;
        default:
            break;
    }
}