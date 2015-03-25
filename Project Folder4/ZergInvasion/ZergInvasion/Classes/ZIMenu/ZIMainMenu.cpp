//
//  ZIMainMenu.cpp
//  ZergInvasion
//
//  Created by Manjunatha Reddy on 12/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "ZIMainMenu.h"

using namespace cocos2d;
//using namespace CocosDenshion;

ZIMainMenu::ZIMainMenu()
{
    CCLog("construction called in ZIMainMenu");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ZIUISpriteSheet.plist","ZIUISpriteSheet.pvr.ccz");
    
    this->addBackGroundWithButtons();
    
}
ZIMainMenu::~ZIMainMenu()
{    
    CCLog("destructor called in ZIMainMenu");
}

void ZIMainMenu:: addBackGroundWithButtons()
{
    ZICustomSprite *mainBackGround=mainBackGround->spriteWithFile("homepage.png");
    mainBackGround->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
    this->addChild(mainBackGround);
    
    //playButton
    ZICustomSprite *playButtonNormalImage=playButtonNormalImage->spriteWithFrame("playButtonNormal.png");
    ZICustomSprite *playButtonSelectedImage=playButtonSelectedImage->spriteWithFrame("playButtonSelected.png");
    
    CCMenuItemSprite *playButton = CCMenuItemSprite::create(
                                                          playButtonNormalImage,
                                                          playButtonSelectedImage,
                                                          this,
                                                          menu_selector(ZIMainMenu::menuCallbacks) );
    playButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, 190) );
    playButton->setTag(1);
    
    //scoreButton
    ZICustomSprite *scoreButtonNormalImage=scoreButtonNormalImage->spriteWithFrame("scoreButtonNormal.png");
    ZICustomSprite *scoreButtonSelectedImage=scoreButtonSelectedImage->spriteWithFrame("scoreButtonSelected.png");

    CCMenuItemSprite *scoreButton = CCMenuItemSprite::create(
                                                           scoreButtonNormalImage,
                                                           scoreButtonSelectedImage,
                                                           this,
                                                           menu_selector(ZIMainMenu::menuCallbacks) );
    scoreButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, 120) );
    scoreButton->setTag(2);
    
    //storeButton
    ZICustomSprite *storeButtonNormalImage=storeButtonNormalImage->spriteWithFrame("storeButtonNormal.png");
    ZICustomSprite *storeButtonSelectedImage=storeButtonSelectedImage->spriteWithFrame("storeButtonSelected.png");
    CCMenuItemSprite *storeButton = CCMenuItemSprite::create(
                                                           storeButtonNormalImage,
                                                           storeButtonSelectedImage,
                                                           this,
                                                           menu_selector(ZIMainMenu::menuCallbacks) );
    storeButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, 50) );
    storeButton->setTag(3);
    
    //settings
    ZICustomSprite *settingsButtonNormalImage=settingsButtonNormalImage->spriteWithFrame("settingButtonNormal.png");
    ZICustomSprite *settingsButtonSelectedImage=settingsButtonSelectedImage->spriteWithFrame("settingButtonSelected.png");
    CCMenuItemSprite *settingsButton = CCMenuItemSprite::create(
                                                             settingsButtonNormalImage,
                                                              settingsButtonSelectedImage,
                                                              this,
                                                              menu_selector(ZIMainMenu::menuCallbacks) );
    settingsButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 300, 20) );
    settingsButton->setTag(4);
    
    //sound
    ZICustomSprite *soundButtonNormalImage=soundButtonNormalImage->spriteWithFrame("soundOffButton.png");
    ZICustomSprite *soundButtonSelectedImage=soundButtonSelectedImage->spriteWithFrame("soundOnButton.png");
    soundButton = CCMenuItemToggle::CCMenuItemToggle::create(    this, 
                                                             menu_selector(ZIMainMenu::menuCallbacks),
                                                             
                                                             CCMenuItemSprite::create(soundButtonNormalImage, soundButtonNormalImage),CCMenuItemSprite::create(soundButtonSelectedImage, soundButtonSelectedImage),NULL );
    soundButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    soundButton->setTag(5);
    
    //Menu
    CCMenu *mainMenu = CCMenu::create(playButton,storeButton,scoreButton,settingsButton,soundButton, NULL);
    mainMenu->setPosition(ccp(0,0));
    this->addChild(mainMenu);
    
}
void ZIMainMenu::menuCallbacks(CCObject* sender)
{
    CCMenuItemImage *tempItem = (CCMenuItemImage *)sender;
    switch (tempItem->getTag()) {
            
        case 1: //GameMode
            
            CCDirector::sharedDirector()->replaceScene(ZIGameModeScene::scene());
            break;
        case 2: //Score 
            
            CCDirector::sharedDirector()->replaceScene(ZIScoreScene::scene());
            break;
        case 3: //Store
            
            CCDirector::sharedDirector()->replaceScene(ZIStoreScene::scene());
            break;
        case 4: //Settings
            
            //CCDirector::sharedDirector()->replaceScene(ZIGameModeScene::scene());
            break;
        case 5: //Sound
            
            //CCDirector::sharedDirector()->replaceScene(ZIGameModeScene::scene());
            if (soundButton->isEnabled()) {
                
            }
            else {
                 
            }
           
            break;
        default:
            break;
            
    }
}
CCScene* ZIMainMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    CCLayer* layer = new ZIMainMenu();
    scene->addChild(layer);
    layer->release();
    return scene;
}

