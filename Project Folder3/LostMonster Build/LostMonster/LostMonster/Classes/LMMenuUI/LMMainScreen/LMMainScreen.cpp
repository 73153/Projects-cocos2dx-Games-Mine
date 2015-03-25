//
//  LMMainScreen.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "LMMainScreen.h"
#include "LMMenuLayer.h"
#include "LMWorldSelection.h"

using namespace cocos2d;

CCScene* LMMainScreen::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new LMMainScreen();
    scene->addChild(layer);
    layer->release();
    return scene;
}
LMMainScreen::LMMainScreen()
{
        CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    // loading plist 
   // CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LMUIImages.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUIImages/LMSpritesheets/LMMenuImages.plist");
    
   
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUIImages/LMSpritesheets/LMMainSceenImages.plist");
    
    // adding top bar menu 
    LMMenuLayer *menuLayer=new LMMenuLayer();
    this->addChild(menuLayer,2);
    
    // backGround
    CCSprite *backGround=CCSprite::create("GameUIImages/UI_play-page.png");
    this->addChild(backGround);
    backGround->cocos2d::CCNode::setPosition(winsize.width/2, winsize.height/2);
    
    // 
    CCSprite *rollbig=CCSprite::createWithSpriteFrameName("rolloBig.png");
    this->addChild(rollbig);
    rollbig->cocos2d::CCNode::setPosition(396, 232);
    
    
    // play menu 
    CCSprite *playMenuSprite=CCSprite::createWithSpriteFrameName("play_btn.png");
    CCMenuItemSprite *playMenuItem=CCMenuItemSprite::create(playMenuSprite, playMenuSprite, this, menu_selector(LMMainScreen::playAction));
    CCMenu *menu=CCMenu::create(playMenuItem,NULL); 
    this->addChild(menu);
    menu->setPosition(86, 132);
    
    CCSprite *friendsColumnBg=CCSprite::create("GameUIImages/UI_Homepage_frnds_colm.png");
    this->addChild(friendsColumnBg);
    friendsColumnBg->setPosition(CCPointMake(312, 101));
    
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("intro_bt.png");
    //CCSprite *normalSprite=CCSprite::create("intro_bt.png");
    
    CCMenuItemSprite *introMenuItem=CCMenuItemSprite::create(normalSprite, normalSprite, this, menu_selector(LMMainScreen::inviteFriends));
    introMenuItem->setPosition(CCPointMake(420, 176));
    
    normalSprite=CCSprite::createWithSpriteFrameName("invite_friends_bt.png");
    //normalSprite=CCSprite::create("invite_friends_bt.png");
    CCMenuItemSprite *inviteFriendMenuItem=CCMenuItemSprite::create(normalSprite, normalSprite, this, menu_selector(LMMainScreen::inviteFriends));
    inviteFriendMenuItem->setPosition(CCPointMake(351, 176));

    
    normalSprite=CCSprite::createWithSpriteFrameName("give_free_lifebt.png");
    CCMenuItemSprite *giveFreelifeMenuItem=CCMenuItemSprite::create(normalSprite, normalSprite, this, menu_selector(LMMainScreen::inviteFriends));
    giveFreelifeMenuItem->setPosition(CCPointMake(270, 176));

    
    CCMenu *inviteFriendsMenu=CCMenu::create(introMenuItem,inviteFriendMenuItem,giveFreelifeMenuItem,NULL);
    this->addChild(inviteFriendsMenu);
    inviteFriendsMenu->setPosition(0,0);
    
    
    CCLabelTTF *playWithFriendsLabel=CCLabelTTF::create("Play With Friends", "Thonburi", 34);
    this->addChild(playWithFriendsLabel);
    playWithFriendsLabel->setPosition(CCPointMake(winsize.width-755, winsize.height-445));
    playWithFriendsLabel->setColor(ccc3(255, 200, 70));

    
    
}

LMMainScreen::~LMMainScreen()
{
   
}

void LMMainScreen::inviteFriends(){
    CCLog("invite friends");
}
void LMMainScreen::playAction(){
    CCDirector::sharedDirector()->replaceScene(LMWorldselection::scene());
 
}