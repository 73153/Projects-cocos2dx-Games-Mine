//
//  LMMenuScene.cpp
//  LostMonster
//
//  Created by Krithik B on 8/22/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#include <iostream>
#include "LMMenuScene.h"
#include "LMGameLayer.h"
#include "LMDataManager.h"

using namespace cocos2d;



CCScene* LMMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new LMMenuScene();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}


#pragma mark - Init


LMMenuScene::LMMenuScene()
{
    
    
    
    //Add BG
    CCSprite *bg = CCSprite::create("WorldOneBG.png");
    bg->setPosition(CCPointMake(512,384));
    this->addChild(bg);
    
    
    //Create Menu Temp Position
    CCMenuItemSprite* level_1_1 = CCMenuItemImage::create("LevelSelect1.png", "LevelSelect1.png", this, menu_selector(LMMenuScene::loadGame_1_1));
    level_1_1->setPosition(CCPointMake(100,648));
    
    CCMenuItemSprite* level_1_2 = CCMenuItemImage::create("LevelSelect2.png", "LevelSelect2.png", this, menu_selector(LMMenuScene::loadGame_1_2));
    level_1_2->setPosition(CCPointMake(200,648));
    
    CCMenuItemSprite* level_1_3 = CCMenuItemImage::create("LevelSelect3.png", "LevelSelect3.png", this, menu_selector(LMMenuScene::loadGame_1_3));
    level_1_3->setPosition(CCPointMake(300,648));
    
    CCMenuItemSprite* level_1_4 = CCMenuItemImage::create("LevelSelect4.png", "LevelSelect4.png", this, menu_selector(LMMenuScene::loadGame_1_4));
    level_1_4->setPosition(CCPointMake(400,648));

    CCMenuItemSprite* level_1_5 = CCMenuItemImage::create("LevelSelect5.png", "LevelSelect5.png", this, menu_selector(LMMenuScene::loadGame_1_5));
    level_1_5->setPosition(CCPointMake(500,648));
    
    CCMenuItemSprite* level_1_6 = CCMenuItemImage::create("LevelSelect6.png", "LevelSelect6.png", this, menu_selector(LMMenuScene::loadGame_1_6));
    level_1_6->setPosition(CCPointMake(600,648));
    
    CCMenuItemSprite* level_1_7 = CCMenuItemImage::create("LevelSelect7.png", "LevelSelect7.png", this, menu_selector(LMMenuScene::loadGame_1_7));
    level_1_7->setPosition(CCPointMake(100,448));
    
    CCMenuItemSprite* level_1_8 = CCMenuItemImage::create("LevelSelect8.png", "LevelSelect8.png", this, menu_selector(LMMenuScene::loadGame_1_8));
    level_1_8->setPosition(CCPointMake(200,448));
    
    CCMenuItemSprite* level_1_9 = CCMenuItemImage::create("LevelSelect9.png", "LevelSelect9.png", this, menu_selector(LMMenuScene::loadGame_1_9));
    level_1_9->setPosition(CCPointMake(300,448));
    
    CCMenuItemSprite* level_1_10 = CCMenuItemImage::create("LevelSelect10.png", "LevelSelect10.png", this, menu_selector(LMMenuScene::loadGame_1_10));
    level_1_10->setPosition(CCPointMake(400,448));
    
    CCMenuItemSprite* level_1_11 = CCMenuItemImage::create("LevelSelect11.png", "LevelSelect11.png", this, menu_selector(LMMenuScene::loadGame_1_11));
    level_1_11->setPosition(CCPointMake(500,448));
    
    CCMenuItemSprite* level_1_12 = CCMenuItemImage::create("LevelSelect12.png", "LevelSelect12.png", this, menu_selector(LMMenuScene::loadGame_1_12));
    level_1_12->setPosition(CCPointMake(600,448));
 
    
    CCMenu* menu = CCMenu::create(level_1_1,level_1_2,level_1_3,level_1_4,level_1_5,level_1_6,level_1_7,level_1_8,level_1_9,level_1_10,level_1_11,level_1_12, NULL);
    menu->setPosition(CCPointMake(0,0));
    this->addChild(menu,10); 
    
    
    
    //temp
     LMDataManager::sharedManager()->worldName = "World_1";
    
    
    worldName = "Level_1_";
    
    levelName = new char;
    
}

#pragma mark - Level Restart
void LMMenuScene::loadGame_1_1()
{
    sprintf(levelName, "%s%d",worldName, 1);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_2()
{
    sprintf(levelName, "%s%d",worldName, 2);

    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_3()
{
    sprintf(levelName, "%s%d",worldName, 3);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_4()
{
    sprintf(levelName, "%s%d",worldName, 4);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_5()
{
    sprintf(levelName, "%s%d",worldName, 5);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_6()
{
    sprintf(levelName, "%s%d",worldName, 6);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_7()
{
    sprintf(levelName, "%s%d",worldName, 7);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_8()
{
    sprintf(levelName, "%s%d",worldName, 8);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_9()
{
    sprintf(levelName, "%s%d",worldName, 9);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_10()
{
    sprintf(levelName, "%s%d",worldName, 10);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_11()
{
    sprintf(levelName, "%s%d",worldName, 11);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void LMMenuScene::loadGame_1_12()
{
    sprintf(levelName, "%s%d",worldName, 12);
    
    LMDataManager::sharedManager()->levelName = levelName;
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}






#pragma mark - Dealloc
LMMenuScene::~LMMenuScene()
{
    CCLog("Dealloc in LMMenuScene");    
}