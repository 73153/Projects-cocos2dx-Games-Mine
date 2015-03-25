//
//  gameOver.cpp
//  helicopterGame
//
//  Created by Vivek on 15/11/12.
//
//

#include "gameOver.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "easyGame.h"
#include "difficultGame.h"
#include "mediumGame.h"
#include "SimpleAudioEngine.h"
#include <iostream>

using namespace cocos2d;

CCScene* gameOver::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    gameOver *layer = gameOver::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool gameOver::init()
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
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemImage *backBtn = CCMenuItemImage::create("game_over.png", "game_over.png", this, menu_selector(gameOver::goahead));
    
    CCMenu *gameModeMenu = CCMenu::create(backBtn, NULL);
    gameModeMenu->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(gameModeMenu,1);
    return true;
}

void gameOver::goahead()
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}