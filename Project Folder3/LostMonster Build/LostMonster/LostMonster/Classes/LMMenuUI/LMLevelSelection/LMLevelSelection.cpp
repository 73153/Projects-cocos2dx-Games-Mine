//
//  LMLevelSelection.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMLevelSelection.h"
#include "LMMenuLayer.h"
#include "LMWorldSelection.h"
#include "LMGameLayer.h"
#include "LMDataManager.h"
#define lockTag 500


using namespace cocos2d;

CCScene* LMLevelSelection::scene(){
    CCScene *scene=CCScene::create();
    LMLevelSelection *layer=new LMLevelSelection();
    scene->addChild(layer);
    
    return scene;
}

LMLevelSelection::LMLevelSelection(){
    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    menuItemsArray=CCArray::create();
    
    menuItemsArray->retain();
    LMMenuLayer *menuLayer=new LMMenuLayer();
    this->addChild(menuLayer,2);
    
      
    char worldBackGroundBgName[30];
    sprintf(worldBackGroundBgName,"%s_BGSpritesheet.png",LMDataManager::sharedManager()->worldName);
    
    CCLOG("worldBackGroundBgName is %s",worldBackGroundBgName);
    
    //Here we are reusing the BG images which we are using in the game play screen
    CCSprite *selectedWorldBG = CCSprite::create(worldBackGroundBgName,CCRectMake(0, 0, winSize.width, winSize.height));
    this->addChild(selectedWorldBG);
    selectedWorldBG->setPosition(CCPointMake(winSize.width/2, winSize.height/2));
  
    
    char titleName[20];
    sprintf(titleName, "%s_Heading.png",LMDataManager::sharedManager()->worldName);
    
    CCSprite *title=CCSprite::createWithSpriteFrameName(titleName);
    this->addChild(title);
    title->cocos2d::CCNode::setPosition(winSize.width-240, winSize.height-75);
    int numberOfLevels=LMDataManager::sharedManager()->numberOfLevels;
    int x=winSize.width-656;
    int y;
    if(numberOfLevels<=12)
    {
        y=winSize.height-310;
    }
    else
    {
        y=winSize.height-290;
    }
    
    //
    
    //  adding level buttons 
    
    int j=0;
    for(int i=1;i<=numberOfLevels;i++)
    {
        
        char levelSelectionBtnName[30]; // level button name 
        char levelSelectionBtnNameHvr[30];  // selected level button name 
        
        sprintf(levelSelectionBtnName,"level_selection_%d.png",i);
        CCSprite *normalSprite = CCSprite::createWithSpriteFrameName(levelSelectionBtnName);
        
        sprintf(levelSelectionBtnNameHvr,"level_selection_%d_hvr.png",i);
        CCSprite *selectedSprite = CCSprite::createWithSpriteFrameName(levelSelectionBtnNameHvr);
        
        // adding level button
        CCMenuItemSprite *levelselectionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMLevelSelection::gotoLevel));
        levelselectionMenuItem->setTag(i);
        levelselectionMenuItem->setPosition(x, y);
        menuItemsArray->addObject(levelselectionMenuItem);
        
        if(i%6==0){
            j++;
            if(j==2)
            {
                 x=winSize.width-585;
            }
            else
            {
            x=winSize.width-656;
            }
            y=y-57;
            
        }
        else{
            x=x+70;
        }
        
        
    }
    
    // adding levels menu 
    CCMenu *menu=CCMenu::createWithArray(menuItemsArray);
    this->addChild(menu);
    
    
    // adding  Region intro menu
    
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("region_intro_bt.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("region_intro_bt.png");
    CCMenuItemSprite *regionIntroMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this,menu_selector(LMLevelSelection::goToregionIntro));
    regionIntroMenuItem->setPosition(CCPointMake(winSize.width-605, winSize.height-450));

    
   // adding  back menu item 
    normalSprite=CCSprite::createWithSpriteFrameName("level_back_bt.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("level_back_bt.png");
    CCMenuItemSprite *backMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this,menu_selector(LMLevelSelection::goBack));
    backMenuItem->setPosition(CCPointMake(winSize.width-685, winSize.height-450));

    
    // 
    CCMenu *regionMenu=CCMenu::create(regionIntroMenuItem,backMenuItem, NULL);
    this->addChild(regionMenu);
        
    
    //Allocate some space for holding levelName
    levelName = new char;
}

LMLevelSelection::~LMLevelSelection(){
    CC_SAFE_RELEASE_NULL(menuItemsArray);
}


void LMLevelSelection::goBack(){
    CCDirector::sharedDirector()->replaceScene(LMWorldselection::scene());
}

void LMLevelSelection::gotoLevel(CCObject *sender)
{
    CCMenuItemSprite *senderBtn = (CCMenuItemSprite *)sender;
    
    sprintf(levelName, "%s%d",LMDataManager::sharedManager()->levelNamePrefix,senderBtn->getTag());
    
    LMDataManager::sharedManager()->levelName = levelName;
    LMDataManager::sharedManager()->subLevelNumber=senderBtn->getTag();
    
    if(senderBtn->getTag()>18)
        
    {
        //if(LMDataManager::sharedManager()->check)
        
        
        //{
        int tag=senderBtn->getTag();
        this->lockAction(lockTag+tag);
        
        //}
        //return;
    }
    
    else
    {
        if(LMDataManager::sharedManager()->check)
        {
            if(senderBtn->getTag()>16)
            {
                return;
            }
        }
        CCScene *pScene = LMGameLayer::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void LMLevelSelection::goToregionIntro(){}

void LMLevelSelection::lockAction(int tag){
    
    CCSprite *lockSprite=(CCSprite*)this->getChildByTag(tag);
    CCRotateBy *rotate=CCRotateBy::create(0.15, 30);
    CCRotateBy *rotReverse=CCRotateBy::create(0.15, -30);
    CCSequence *seq=CCSequence::createWithTwoActions(rotate,rotReverse);
    CCSequence *seq1=CCSequence::createWithTwoActions(rotate,rotReverse);
    CCSequence *seq3=CCSequence::createWithTwoActions(seq, seq1);
    CCSequence *seq4=CCSequence::createWithTwoActions(seq,seq1);
    CCSequence *seq5=CCSequence::createWithTwoActions(seq3, seq4);
    lockSprite->runAction(seq5);
}

CCPoint LMLevelSelection::getPosiiton(CCMenuItem *menuItem){
    CCPoint Posiiton;
    CCPoint menuitemPosition=menuItem->getPosition();
    float x=menuitemPosition.x+546;
    float y=menuitemPosition.y+355;
    Posiiton=CCPoint(x, y);
    return Posiiton;
    
}