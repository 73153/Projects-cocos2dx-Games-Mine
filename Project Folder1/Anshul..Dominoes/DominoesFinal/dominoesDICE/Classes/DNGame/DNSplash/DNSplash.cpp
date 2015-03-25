//
//  DNSplash.cpp
//  Dominoes
//
//  Created by Dinesh on 16/11/12.
//
//

#include "DNSplash.h"
#include "MainGameController.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

CCScene* DNSplash::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    DNSplash *layer = DNSplash::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

DNSplash::DNSplash() {

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *splashScreen = CCSprite::create("Default.png");
    splashScreen->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(splashScreen);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("btn_animal_timer.plist");
    
    CCSprite *ok_normal = CCSprite::createWithSpriteFrameName("ok_btn1.png");
    CCSprite *ok_selected = CCSprite::createWithSpriteFrameName("ok_pressed.png");
    
    CCMenuItemSprite *okbtn = CCMenuItemSprite::create(ok_normal,ok_selected,this,menu_selector(DNSplash::gotoGame));
    okbtn->setPosition(ccp(120,80));
    
    CCMenu *passMenu = CCMenu::create(okbtn,NULL);
    passMenu->setPosition(CCPointZero);
    passMenu->setVisible(true);
    splashScreen->addChild(passMenu,10);
}

DNSplash::~DNSplash() {
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("btn_animal_timer.plist");
    
}

void DNSplash::gotoGame() {
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle_Click.mp3");
    
    CCDirector::sharedDirector()->replaceScene(MainGameController::scene());
}