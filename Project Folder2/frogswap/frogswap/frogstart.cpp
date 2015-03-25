//
//  frogstart.cpp
//  frogswap
//
//  Created by Anshul on 29/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "frogstart.h"

using namespace cocos2d;


CCScene* frogstart::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    frogstart *layer = frogstart::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool frogstart::init()
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
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Frog World Begin", "Thonburi", 34);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("frog_game.plist");
    
    

    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("play-button2.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("play-button2.png");

    
    CCMenuItemSprite *goAheadBtn=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(frogstart::goahead));
    
    
    CCMenu *gameModeMenu = CCMenu::create(goAheadBtn, NULL);
    gameModeMenu->setPosition(ccp(240,160));
    this->addChild(gameModeMenu);
    
    return true;
}

void frogstart::goahead()
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}