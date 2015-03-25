//
//  BBMainScreen.cpp
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 21/01/13.
//
//

#include "BBGameSelection.h"
#include "BBTicToeGamePlay.h"
#include "BBMatchGamePlay.h"
#include "BBConfig.h"
#include "BBMainDataManager.h"

#define cpuSprite 555;
#define ourSprite 666;
using namespace cocos2d;


CCScene* BBGameSelection::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new BBGameSelection();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

BBGameSelection::BBGameSelection()
{
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    //add bg
    CCSprite *bg=CCSprite::create("UI/CommonBG/BGipad.png");
    bg->setPosition(CCPointMake(winsize.width/2, winsize.height/2));
    
    this->addChild(bg);
    
    
    //match label
    CCLabelTTF *matchLAbel=CCLabelTTF::create("Match", "Noteworthy-Bold", 35);
    matchLAbel->cocos2d::CCNode::setPosition(CCPointMake(winsize.width/2-200, winsize.height/2+170));
    this->addChild(matchLAbel,2);
    //ticTac label
    CCLabelTTF *ticTacToeLAbel=CCLabelTTF::create("Tic Tac Toe", "Noteworthy-Bold", 35);
    ticTacToeLAbel->cocos2d::CCNode::setPosition(CCPointMake(winsize.width/2+200, winsize.height/2+170));
    this->addChild(ticTacToeLAbel,2);
    CCSprite *normalSprite;
    
     //add match button
     normalSprite=CCSprite::create("UI/CommonBG/match.png");
    CCMenuItemSprite *matchMenuItem=CCMenuItemSprite::create(normalSprite, normalSprite, this, menu_selector(BBGameSelection::action));
    matchMenuItem->setPosition(CCPointMake(winsize.width/2-200, winsize.height/2));
    matchMenuItem->setTag(1);
    
    //add tic toe button
    normalSprite = CCSprite::create("UI/CommonBG/tictactoe.png");
    CCMenuItemSprite *ticToeMenuItem = CCMenuItemSprite::create(normalSprite, normalSprite, this, menu_selector(BBGameSelection::action));
    ticToeMenuItem->setPosition(CCPointMake(winsize.width/2+200, winsize.height/2));
    ticToeMenuItem->setTag(2);
       
    CCMenu *selectMenu=CCMenu::create(ticToeMenuItem,matchMenuItem,NULL);
    selectMenu->setPosition(CCPointZero);
    this->addChild(selectMenu);
    
}
BBGameSelection::~BBGameSelection()
{
    CCLog("destructor called in main screen");
}


void BBGameSelection::action(cocos2d::CCMenuItemImage *sender)
{
    int tag=sender->getTag();
   
    switch (tag)
    {
        case 1: //Match item
           CCDirector::sharedDirector()->replaceScene(BBMatchGamePlay::scene());
            break;
        case 2://Tic toe button
            CCDirector::sharedDirector()->replaceScene(BBTicToeGamePlay::scene());
            break;
        default:
            break;
    }

}