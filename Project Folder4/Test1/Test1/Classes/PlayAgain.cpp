//
//  PlayAgain.cpp
//  Test1
//
//  Created by Deepthi on 25/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "PlayAgain.h"

CCScene *PlayAgain::scene() {
    
    CCScene *scene = CCScene::create();
    
    PlayAgain *layer = new PlayAgain();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}



PlayAgain::~PlayAgain() {
    
}



PlayAgain::PlayAgain() {
    
    this->setTouchEnabled(true);
    //CCSprite *pp = CCSprite::create("Target.png");
    //pp->setPosition(ccp(200,160));
    CCLabelTTF *label = CCLabelTTF::create("PlayAgain","thobunkari",50);
    label->setPosition(ccp(300, 220));
    this->addChild(label, 2, 101);
       
    CCMenuItemImage *backBtn = CCMenuItemImage::create("Target.png", "Target.png", this, menu_selector(PlayAgain::backToScene));
    
    CCMenu *gameModeMenu = CCMenu::create(backBtn, NULL);
    gameModeMenu->setPosition(ccp(240,160));
    this->addChild(gameModeMenu);
    
}

void PlayAgain::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
    
    //CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    //CCPoint location = touch->locationInView();
    //location = CCDirector::sharedDirector()->convertToGL(location);
   //CCLog("touches began %f %f",location.x,location.y);
    
}

void PlayAgain::backToScene()
{
    //CCLOG("back");
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

