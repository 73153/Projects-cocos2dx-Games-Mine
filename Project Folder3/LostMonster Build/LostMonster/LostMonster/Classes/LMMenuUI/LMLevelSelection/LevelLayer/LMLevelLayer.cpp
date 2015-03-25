//
//  LMLevelLayer.cpp
//  LMGame
//
//  Created by Pavitra on 05/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMLevelLayer.h"
#include "LMMenuLayer.h"
#include "LMLevelSelection.h"

using namespace cocos2d;

LMLevelLayer::LMLevelLayer(){
    
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    
    // backGround
    CCSprite *backGround=CCSprite::create("UI_play-page.png");
    this->addChild(backGround);
    backGround->cocos2d::CCNode::setPosition(winsize.width/2, winsize.height/2);

    
    // menu layer
    LMMenuLayer *menuLayer=new LMMenuLayer();
    this->addChild(menuLayer);

    // game tool bar 
    CCSprite *gameToolBar=CCSprite::createWithSpriteFrameName("game_toolbar.png");
    this->addChild(gameToolBar);
    gameToolBar->cocos2d::CCNode::setPosition(winsize.width-420, winsize.height-120);
    
    
       
    
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("back_btn.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("back_btn_hvr.png");
    
    // back menu 
    CCMenuItemSprite *backMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMLevelLayer::action));
    CCMenu *backMenu=CCMenu::create(backMenuItem,NULL); 
    this->addChild(backMenu, 2);
    backMenu->setPosition(winsize.width-735,winsize.height-120);

    
    // refresh menu 
    normalSprite=CCSprite::createWithSpriteFrameName("refresh_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("refresh_btn_hvr.png");
    CCMenuItemSprite *refreshMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMLevelLayer::action));
    CCMenu *refreshMenu=CCMenu::create(refreshMenuItem,NULL); 
    this->addChild(refreshMenu, 2);
    refreshMenu->setPosition(winsize.width-660,winsize.height-120);

    
    // min max sprite 
    CCSprite *minMaxSprite=CCSprite::createWithSpriteFrameName("min_max_icon.png");
    this->addChild(minMaxSprite);
    minMaxSprite->cocos2d::CCNode::setPosition(winsize.width-200, winsize.height-120);
    
    
}

LMLevelLayer::~LMLevelLayer(){
    
}

void LMLevelLayer::action(){
    CCDirector::sharedDirector()->replaceScene(LMLevelSelection::scene());
    
    
}
