//
//  gameStart.cpp
//  helicopterGame
//
//  Created by Vivek on 20/11/12.
//
//

#include "gameStart.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "easyGame.h"
#include "difficultGame.h"
#include "mediumGame.h"
#include "SimpleAudioEngine.h"
#include <iostream>
USING_NS_CC;

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* gameStart::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    gameStart *layer = gameStart::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool gameStart::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    
    CCMenuItemImage *easyGameSpr = CCMenuItemImage::create("frontSprite1.png", "frontSprite1.png", this, menu_selector(gameStart::replace));
    CCMenu *gameModeMenu1 = CCMenu::create(easyGameSpr, NULL);
    gameModeMenu1->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(gameModeMenu1,1);
       
    
    return true;
}


void gameStart::replace()
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

