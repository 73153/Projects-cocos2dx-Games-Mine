//
//  BBMenuLayer.cpp
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 21/01/13.
//
//

#include "BBMenuLayer.h"
#include "BBGameSelection.h"
using namespace cocos2d;

#pragma mark - Implementation

BBMenuLayer::BBMenuLayer()
{
    //add bg
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    //add bg
    CCSprite *bg=CCSprite::create("UI/CommonBG/BGipad.png");
    bg->setPosition(CCPointMake(winsize.width/2, winsize.height/2));
    this->addChild(bg);
    
    
     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/UISpriteSheets/BBMenuLayerImages.plist");
    //add back button
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("btn_games.png");
    
    CCMenuItemSprite *backMenuItem=CCMenuItemSprite::create(normalSprite, normalSprite, this, menu_selector(BBMenuLayer::action));
    backMenuItem->setPosition(CCPointMake(winsize.width/2-400, winsize.height/2+290));
    backMenuItem->setTag(1);
    
        
//    
//    //add play again/restart button
//    normalSprite = CCSprite::createWithSpriteFrameName("PlayAgain_restart.png");
//    CCMenuItemSprite *playMenuItem = CCMenuItemSprite::create(normalSprite, normalSprite, this, menu_selector(BBMenuLayer::action));
//    playMenuItem->setPosition(CCPointMake(winsize.width/2-400, winsize.height/2-200));
//    playMenuItem->setTag(2);
//    
    
    
    CCMenu *selectMenu=CCMenu::create(backMenuItem,NULL);
    selectMenu->setPosition(CCPointZero);
    this->addChild(selectMenu,2);
    
    
}

BBMenuLayer::~BBMenuLayer()
{
    CCLog("destructor called in BBMenuLayer");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("UI/UISpriteSheets/BBMenuLayerImages.plist");
}
void BBMenuLayer::action(cocos2d::CCMenuItemImage *sender)
{
    int tag=sender->getTag();
    switch (tag)
    {
        case 1: //backMenu item
            CCDirector::sharedDirector()->replaceScene(BBGameSelection::scene());
            break;
        case 2://play button
            break;
        default:
            break;
    }
    
    
}