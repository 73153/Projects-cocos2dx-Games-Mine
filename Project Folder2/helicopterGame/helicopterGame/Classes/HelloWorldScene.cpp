
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "easyGame.h"
#include "difficultGame.h"
#include "mediumGame.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include "gameStart.h"
USING_NS_CC;

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
  
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    

    CCMenuItemImage *easyGameSpr = CCMenuItemImage::create("easy.png", "easy.png", this, menu_selector(HelloWorld::easyRelplace));
    CCMenu *gameModeMenu1 = CCMenu::create(easyGameSpr, NULL);
    gameModeMenu1->setPosition(ccp(220, 220));
    this->addChild(gameModeMenu1,1);
    
    CCMenuItemImage *mediumGameSpr = CCMenuItemImage::create("medium.png", "medium.png", this, menu_selector(HelloWorld::mediumReplace));
    CCMenu *gameModeMenu2 = CCMenu::create(mediumGameSpr, NULL);
    gameModeMenu2->setPosition(ccp(220, 160));
    this->addChild(gameModeMenu2,1);
    
    CCMenuItemImage *difficultGameSpr = CCMenuItemImage::create("hard.png", "hard.png", this, menu_selector(HelloWorld::difficultReplace));
    CCMenu *gameModeMenu3 = CCMenu::create(difficultGameSpr, NULL);
    gameModeMenu3->setPosition(ccp(220, 100));
    this->addChild(gameModeMenu3,1);
    
    CCSprite *bckImg = CCSprite::create("backgroundUwall.png");
    bckImg->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(bckImg);

    
    return true;
}


void HelloWorld::easyRelplace()
{
   CCDirector::sharedDirector()->replaceScene(easyGame::scene());
}

void HelloWorld::mediumReplace()
{
    CCDirector::sharedDirector()->replaceScene(mediumGame::scene());
}

void HelloWorld::difficultReplace()
{
    CCDirector::sharedDirector()->replaceScene(difficultGame::scene());
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
