//
//  frogover.cpp
//  frogswap
//
//  Created by Anshul on 29/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "frogover.h"

using namespace cocos2d;


CCScene* frogover::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    frogover *layer = frogover::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool frogover::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("play-button.png");
    
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("play-button.png");
    
    CCMenuItemSprite *backtogameBtn=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(frogover::backtogame));

    CCMenu *gameModeMenu = CCMenu::create(backtogameBtn, NULL);
    gameModeMenu->setPosition(ccp(240,160));
    this->addChild(gameModeMenu);
    
    return true;
}

void frogover::backtogame()
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}