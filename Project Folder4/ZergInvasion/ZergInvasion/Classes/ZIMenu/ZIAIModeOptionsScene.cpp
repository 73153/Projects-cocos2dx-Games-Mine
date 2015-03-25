//
//  ZIAIModeOptionsScene.cpp
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 13/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ZIAIModeOptionsScene.h"

using namespace cocos2d;
//using namespace CocosDenshion;

ZIAIModeOptionsScene::ZIAIModeOptionsScene()
{
    CCLog("construction called in ZIAIModeOptionsScene ");
   CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ZIUISpriteSheet.plist","ZIUISpriteSheet.pvr.ccz");
    this->addBackGroundWithButtons();
    
}
ZIAIModeOptionsScene::~ZIAIModeOptionsScene()
{
   CCLog("destructor called in ZIAIModeOptionsScene");
}


CCScene* ZIAIModeOptionsScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    CCLayer* layer = new ZIAIModeOptionsScene();
    scene->addChild(layer);
    layer->release();
    return scene;
}

void ZIAIModeOptionsScene::addBackGroundWithButtons()
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
                                                            menu_selector(ZIAIModeOptionsScene::aiModeMenuCallbacks));

    backButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2-120, CCDirector::sharedDirector()->getWinSize().height-25));
    backButton->setTag(1);
    
    CCMenu *backModeMenu = CCMenu::create(backButton, NULL);
    backModeMenu->setPosition(ccp(0,0));
    this->addChild(backModeMenu,2);
    
    //easyButton
    ZICustomSprite *easyButtonNormalImage=easyButtonNormalImage->spriteWithFrame("easyButtonNormal.png");
    ZICustomSprite *easyButtonSelectedImage=easyButtonSelectedImage->spriteWithFrame("easyButtonSelected.png");

    CCMenuItemSprite *easyButton = CCMenuItemSprite::create(
                                                                 easyButtonNormalImage,
                                                                 easyButtonSelectedImage,
                                                                 this,
                                                                 menu_selector(ZIAIModeOptionsScene::aiModeMenuCallbacks) );
    easyButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-150));
    easyButton->setTag(2);
    
    //mediumButton
    ZICustomSprite *mediumButtonNormalImage=mediumButtonNormalImage->spriteWithFrame("mediumButtonNormal.png");
    ZICustomSprite *mediumButtonSelectedImage=mediumButtonSelectedImage->spriteWithFrame("mediumButtonSelected.png");
    CCMenuItemSprite *mediumButton = CCMenuItemSprite::create(
                                                        mediumButtonNormalImage,
                                                        mediumButtonSelectedImage,
                                                        this,
                                                        menu_selector(ZIAIModeOptionsScene::aiModeMenuCallbacks));
    mediumButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-240) );
    mediumButton->setTag(3);
    
    //difficultButton
    ZICustomSprite *difficultButtonNormalImage=difficultButtonNormalImage->spriteWithFrame("difficultButtonNormal.png");
    ZICustomSprite *difficultButtonSelectedImage=difficultButtonSelectedImage->spriteWithFrame("difficultButtonSelected.png");
    CCMenuItemSprite *difficultButton = CCMenuItemSprite::create(
                                                            difficultButtonNormalImage,
                                                            difficultButtonSelectedImage,
                                                            this,
                                                            menu_selector(ZIAIModeOptionsScene::aiModeMenuCallbacks) );
    difficultButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-330));
    difficultButton->setTag(4);
    
    //Menu
    CCMenu *gameModeMenu = CCMenu::create(easyButton,mediumButton,difficultButton,NULL);
    gameModeMenu->setPosition(ccp(0,0));
    this->addChild(gameModeMenu);
    
    
}
void ZIAIModeOptionsScene::aiModeMenuCallbacks(CCObject* sender)
{
    CCMenuItemImage *tempItem = (CCMenuItemImage *)sender;
    switch (tempItem->getTag()) {
        case 1: //Back
            
            CCDirector::sharedDirector()->replaceScene(ZIMultiPlayerModeLevelScene::scene());
            break;
        case 2: //Easy
            
            CCDirector::sharedDirector()->replaceScene(ZIMainGame::scene());
            break;
        case 3: //Medium
            
            CCDirector::sharedDirector()->replaceScene(ZIMainGame::scene());
            break;
        case 4: //Difficult
            
            CCDirector::sharedDirector()->replaceScene(ZIMainGame::scene());
            break;
        default:
            break;
            
            
    }
    
}
