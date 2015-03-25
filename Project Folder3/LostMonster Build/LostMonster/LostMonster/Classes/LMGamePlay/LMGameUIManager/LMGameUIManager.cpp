//
//  LMGameUIManager.cpp
//  LostMonster
//
//  Created by Krithik B on 8/28/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#include <iostream>

#include "LMGameUIManager.h"
#include "LMDataManager.h"
#include "LMLevelSelection.h"
#include "LMMenuLayer.h"

using namespace cocos2d;

#pragma mark - Init

LMGameUIManager::LMGameUIManager()
{
    this->gameLayer = LMDataManager::sharedManager()->gameLayer;
}

#pragma mark - Dealloc

LMGameUIManager::~LMGameUIManager()
{
    
}


#pragma mark - Initialise
void LMGameUIManager::intialiseUI()
{
    //Zorder of Level Top Bar
    int levelTopBarZOrder = 5;
    
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    
    // Add Top Game menu Bar
    LMMenuLayer *menuLayer=new LMMenuLayer;
    this->gameLayer->addChild(menuLayer,10);
    
    
    // Level TopBar BG
    CCSprite *gameToolBar=CCSprite::createWithSpriteFrameName("game_toolbar.png");
    this->gameLayer ->addChild(gameToolBar,levelTopBarZOrder);
    gameToolBar->cocos2d::CCNode::setPosition(winsize.width-210, winsize.height-60);//220
    
    
    //Back Button
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("back_btn.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("back_btn_hvr.png");
    CCMenuItemSprite *backMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::goBack));
    backMenuItem->setPosition(CCPointMake(winsize.width-355,  winsize.height-60));
    
    
    //Refresh Button 
    normalSprite=CCSprite::createWithSpriteFrameName("refresh_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("refresh_btn_hvr.png");
    CCMenuItemSprite *refreshMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::restartLevel));
    refreshMenuItem->setPosition(CCPointMake(winsize.width-320,  winsize.height-60));
    
    
    //Top bar menu 
    CCMenu *topBarMenu=CCMenu::create(backMenuItem,refreshMenuItem, NULL);
    this->gameLayer->addChild(topBarMenu,levelTopBarZOrder);
    topBarMenu->setPosition(CCPointMake(0, 0));
    
    // adding level titile
    
    char levelSUbTitleName[30];
    sprintf(levelSUbTitleName, "%sSubTitle.png",LMDataManager::sharedManager()->worldName);
    CCLog("%s",levelSUbTitleName);
    
    CCSprite *levelSUbTitle=CCSprite::createWithSpriteFrameName(levelSUbTitleName);
    this->gameLayer->addChild(levelSUbTitle,levelTopBarZOrder);
    levelSUbTitle->setPosition(CCPointMake(winsize.width-220, winsize.height-60));
    
    char subLevelName[5];
    sprintf(subLevelName, "%d",LMDataManager::sharedManager()->subLevelNumber);
    
    
    CCLabelTTF *subLevelLabel=CCLabelTTF::create(subLevelName, "Arial", 8);
    this->gameLayer->addChild(subLevelLabel,levelTopBarZOrder);
    //subLevelLabel->setPosition(CCPointMake(winsize.width-398, winsize.height-139));
    subLevelLabel->setPosition(this->getSubLevelLabelPosition());
    subLevelLabel->setAnchorPoint(CCPointMake(0, 0));
    subLevelLabel->setColor(ccc3(66, 66, 66));
    
    
    
    //Min Max Sprite 
    minMaxSprite=CCSprite::createWithSpriteFrameName("min_max_icon.png");
    this-> gameLayer-> addChild(minMaxSprite,levelTopBarZOrder);
    minMaxSprite->setPosition(CCPointMake(winsize.width-117, winsize.height-58));
    
    
    // adding sprite which shows minimum no of moves 
    int maxCuts = LMDataManager::sharedManager()->gameLayer->levelManager->maxCuts;
    
    // no of cuts
    
    char minMaxMoves[10];
    sprintf(minMaxMoves,"0/%d",maxCuts);
    
    noOfCutsLabel=CCLabelTTF::create(minMaxMoves, "Thonburi", 14);
    this->gameLayer->addChild(noOfCutsLabel,levelTopBarZOrder);
    noOfCutsLabel->setPosition(CCPointMake(winsize.width-96, winsize.height-60));
    noOfCutsLabel->setColor(ccc3(120, 0, 15));
    
    
    //Challenging No Move Label
    
    int challengingMoveCount =LMDataManager::sharedManager()->gameLayer->levelManager->challengingMoveCount;
    
    char challengingMoveCountChar[10];
    sprintf(challengingMoveCountChar,"%d",challengingMoveCount);
    
    CCLabelTTF *challengingNoMoveLbl=CCLabelTTF::create(challengingMoveCountChar, "Thonburi", 16);
    this->gameLayer->addChild(challengingNoMoveLbl,levelTopBarZOrder);
    challengingNoMoveLbl->setPosition(CCPointMake(winsize.width-71, winsize.height-58));
    challengingNoMoveLbl->setColor(ccc3(255, 200, 76));
    
    
    
    //adding challenge intro  label 
    CCSprite *challengeIntroSprite;
    if(strncmp(LMDataManager::sharedManager()->worldName, "World_1", 7)==0){
        
        if(challengingMoveCount<=1)
        {
            challengeIntroSprite=CCSprite::createWithSpriteFrameName("level_challenge_intro.png");
        }
        else
        {
            challengeIntroSprite=CCSprite::createWithSpriteFrameName("level_challenge_intro1.png");
        }
        this->gameLayer->addChild(challengeIntroSprite,levelTopBarZOrder-1,500);
        challengeIntroSprite->setPosition(CCPointMake(240, 145));
        
        
        
        CCLabelTTF  *challengingIntroLbl=CCLabelTTF::create(challengingMoveCountChar, "Arial", 20);
        challengeIntroSprite->addChild(challengingIntroLbl,levelTopBarZOrder);
        challengingIntroLbl->setPosition(CCPointMake(53, 56));
        challengingIntroLbl->setColor(ccc3(255, 200, 76));
        
        
        CCDelayTime *delayAction=CCDelayTime::create(1.5);
        CCCallFunc *callBackAction=CCCallFunc::create(this, callfunc_selector(LMGameUIManager::challengeIntroSpriteAction));
        CCSequence *sequence=CCSequence::createWithTwoActions(delayAction,callBackAction);
        
        this->gameLayer->runAction(sequence);
        
    }
}

#pragma mark-functions
void LMGameUIManager::updateLabel(int sliceCount)
{
    int maxCuts = LMDataManager::sharedManager()->gameLayer->levelManager->maxCuts;
    char noOfCuts[10];
    sprintf(noOfCuts, "%d/%d",sliceCount,maxCuts);
    this->noOfCutsLabel->setString(noOfCuts);
}

//blibk slice count action 
void LMGameUIManager::blinkSliceCount()
{    
    CCBlink *blink=CCBlink::create(0.5,3);
    minMaxSprite->runAction(blink);
    
    CCBlink *labelBlink=CCBlink::create(0.5, 3);
    noOfCutsLabel->runAction(labelBlink);
}

//challebge intro sprite action 
void LMGameUIManager::challengeIntroSpriteAction(){
    
    CCSprite *challengeIntroSprite=(CCSprite*)this->gameLayer->getChildByTag(500);
    CCScaleBy *scaleAction=CCScaleBy::create(0.85, 0);
    CCMoveTo *moveAction=CCMoveTo::create(1, CCPointMake(460, 300));
    CCSpawn *spawnAction= CCSpawn::createWithTwoActions(scaleAction,moveAction);
    CCCallFunc *callBackAction1=CCCallFunc::create(this, callfunc_selector(LMGameUIManager::removeChallengeIntroSprite));
    CCSequence *sequence1=CCSequence::createWithTwoActions(spawnAction,callBackAction1);
    challengeIntroSprite->runAction(sequence1);
    
}

//removing challengeIntroSprite and label 
void LMGameUIManager::removeChallengeIntroSprite(){
    this->gameLayer->removeChildByTag(500, true);
 }

//getting sunLevelLabel position 
CCPoint LMGameUIManager::getSubLevelLabelPosition(){
    CCPoint labelPosition;
    
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    
    char worldName[10];
    sprintf(worldName,"%s",LMDataManager::sharedManager()->worldName);  

    
    // comparing worldName with first world name
    if(strncmp(worldName, "World_1",7)==0){
        labelPosition=CCPointMake(winsize.width-190, winsize.height-72); // label posiiton 
    }
    //    //comparing worldName with second world name
    else if(strncmp(worldName, "World_2", 7)==0){
        labelPosition=CCPointMake(winsize.width-202, winsize.height-72);
    }
    else if(strncmp(worldName, "World_3", 7)==0){
        labelPosition=CCPointMake(winsize.width-202, winsize.height-70);
    }
   
    else {
            labelPosition=CCPointMake(winsize.width-202, winsize.height-71);
        }
    
    return labelPosition;
}

#pragma mark - Timer
void LMGameUIManager::showTimer()
{
    countDownTimerSpr = CCSprite::createWithSpriteFrameName("countdoen.png");
    countDownTimerSpr->setPosition(CCPointMake(410,250));  //565
    this->gameLayer->addChild(countDownTimerSpr,4);
    
    CCMoveTo *actionMove = CCMoveTo::create(0.2, CCPointMake(410, 230));
    countDownTimerSpr->runAction(actionMove);
    
    char timerCountChar[10];
    sprintf(timerCountChar,"%d",10);
    
    timerLabel = CCLabelTTF::create(timerCountChar, "Thonburi", 13);
    countDownTimerSpr->addChild(timerLabel,4);
    timerLabel->setPosition(CCPointMake(18,18));
}


void LMGameUIManager::updateTimerLabel(int timerCount)
{
    char timeCountChar[10];
    sprintf(timeCountChar, "%d",timerCount);
    
    if(this->timerLabel)
        this->timerLabel->setString(timeCountChar);
}




void LMGameUIManager::removeTimer()
{
    this->countDownTimerSpr->removeFromParentAndCleanup(true);
}



#pragma mark - Button Actions
void LMGameUIManager::restartLevel()
{
    //LMGameUIManager::gameLoss();
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}


void LMGameUIManager::goBack()
{
    //LMGameUIManager::gameWon(1);
    CCScene *pScene = LMLevelSelection::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
void LMGameUIManager::gameWon(bool isFirstTime)
{
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    //bg
    
    CCSprite *background=CCSprite::create("GameUIImages/ui_popup_bg.png");
    background->setPosition(CCPointMake(winsize.width/2, winsize.height/2));
    this->gameLayer->addChild(background,20);
    
    //buttons
    //brag
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("brag_bt.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("brag_bt_hvr.png");
    CCMenuItemSprite *bragMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::goBack));
    bragMenuItem->setPosition(CCPointMake(126, 45));
    
    
    //myCollection Button
    normalSprite=CCSprite::createWithSpriteFrameName("my_collection_bt.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("my_collection_bt_hvr.png");
    CCMenuItemSprite *myCollectionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::restartLevel));
    myCollectionMenuItem->setPosition(CCPointMake(235, 45));
    
    //nextChallenge Button
    normalSprite=CCSprite::createWithSpriteFrameName("next_challenge_bt.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("next_challenge_bt_hvr.png");
    CCMenuItemSprite *nextChallengeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::restartLevel));
    nextChallengeMenuItem->setPosition(CCPointMake(350, 45));
    
    //close Button
    normalSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
    CCMenuItemSprite *closeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::restartLevel));
    closeMenuItem->setPosition(CCPointMake(430, 300));
    
    
    //button Menu
    CCMenu *bottomButtonsMenu=CCMenu::create(bragMenuItem,myCollectionMenuItem,nextChallengeMenuItem,closeMenuItem,NULL);
    this->gameLayer->addChild(bottomButtonsMenu,20);
    bottomButtonsMenu->setPosition(CCPointMake(0, 0));
    
    
    //gamePlayDetailsColm
    CCSprite *detailsColm=CCSprite::createWithSpriteFrameName("game_ply_details_colm.png");
    this->gameLayer->addChild(detailsColm,20);
    detailsColm->setPosition(CCPointMake(300, 160));
    
    
    //challenge
    char challengeGoalNumber[5];
    sprintf(challengeGoalNumber, "%d",LMDataManager::sharedManager()->subLevelNumber);
    CCLabelTTF *challengeGoalLabel=CCLabelTTF::create(challengeGoalNumber, "Arial", 10);
    challengeGoalLabel->setPosition(CCPointMake(126, 75));
    challengeGoalLabel->setColor(ccc3(100,10,0));
    detailsColm->addChild(challengeGoalLabel,20);
    
    //moves
    char movesNumber[5];
    sprintf(movesNumber, "%d",LMDataManager::sharedManager()->subLevelNumber);
    CCLabelTTF *movesNumberLabel=CCLabelTTF::create(challengeGoalNumber, "Arial", 10);
    movesNumberLabel->setPosition(CCPointMake(126, 48));
    movesNumberLabel->setColor(ccc3(100,10,0));
    detailsColm->addChild(movesNumberLabel,20);
    
    //earnings
    char earningNumber[5];
    sprintf(earningNumber, "%d",LMDataManager::sharedManager()->subLevelNumber);
    CCLabelTTF *earningNumberLabel=CCLabelTTF::create(challengeGoalNumber, "Arial", 10);
    earningNumberLabel->setPosition(CCPointMake(135, 20));
    earningNumberLabel->setColor(ccc3(100,10,0));
    detailsColm->addChild(earningNumberLabel,19);
    
    
    if(isFirstTime)
    {
        
        //challengeCompletedLabel
        CCLabelTTF *completed=CCLabelTTF::create("Challenge Completed!", "Arial", 25);
        completed->setPosition(CCPointMake(winsize.width/2, winsize.height-60));
        completed->setColor(ccc3(85, 10, 0));
        this->gameLayer->addChild(completed,20);
        
        
        //dummy name
        char name[45]="The Hills Of Curiosity - Challenge";
        CCLabelTTF *wordLabel=CCLabelTTF::create(name, "Arial", 14);
        wordLabel->setPosition(CCPointMake(winsize.width/2, winsize.height-85));
        wordLabel->setColor(ccc3(150,20,0));
        this->gameLayer->addChild(wordLabel,20);
        
        char challengeCount[3];;
        sprintf(challengeCount, "%d",LMDataManager::sharedManager()->subLevelNumber);
        CCLabelTTF *challengeCountLabel=CCLabelTTF::create(challengeCount, "Arial", 13);
        challengeCountLabel->setColor(ccc3(150,20,0));
        challengeCountLabel->setPosition(CCPointMake(215, 8));
        wordLabel->addChild(challengeCountLabel,20);
        
        //collectedRelicLabel
        
        CCLabelTTF *relic=CCLabelTTF::create("You have collected relic:" , "Arial", 13);
        relic->setPosition(CCPointMake(300, 95));
        relic->setColor(ccc3(150,10,0));
        this->gameLayer->addChild(relic,20);
        
        
        char relicName[45]="Steel Bracer";
        //sprintf(relicName, "%d",LMDataManager::sharedManager()->subLevelNumber);
        CCLabelTTF *relicNameLabel=CCLabelTTF::create(relicName, "Arial", 13);
        relicNameLabel->setPosition(CCPointMake(80, -10));
        relicNameLabel->setColor(ccc3(155,10,0));
        relic->addChild(relicNameLabel,20);
        
        
    }
    else
    {
        //Relic alreadyLabel
        CCLabelTTF *completed=CCLabelTTF::create("Relic already obtained", "Arial", 25);
        completed->setPosition(CCPointMake(winsize.width/2, winsize.height-60));
        completed->setColor(ccc3(85, 10, 0));
        this->gameLayer->addChild(completed,20);
        
        //dummy name
        char name[45]="The Forests of Adventure - Challenge";
        CCLabelTTF *wordLabel=CCLabelTTF::create(name, "Arial", 14);
        wordLabel->setPosition(CCPointMake(winsize.width/2-5, winsize.height-85));
        wordLabel->setColor(ccc3(150,20,0));
        this->gameLayer->addChild(wordLabel,20);
        
        char challengeCount[3];;
        sprintf(challengeCount, "%d",LMDataManager::sharedManager()->subLevelNumber);
        CCLabelTTF *challengeCountLabel=CCLabelTTF::create(challengeCount, "Arial", 13);
        challengeCountLabel->setColor(ccc3(150,20,0));
        challengeCountLabel->setPosition(CCPointMake(242, 7));
        wordLabel->addChild(challengeCountLabel,20);
        
        // popuprollo
        CCSprite *rollo=CCSprite::createWithSpriteFrameName("ui_popup_rolo_frnt.png");
        this->gameLayer->addChild(rollo,20);
        rollo->setPosition(CCPointMake(140, 140));
        
        
    }
    
}
void LMGameUIManager::gameLoss()
{
    //bg
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    CCSprite *background=CCSprite::create("GameUIImages/ui_popup_bg.png");
    background->setPosition(CCPointMake(winsize.width/2, winsize.height/2));
    this->gameLayer->addChild(background,20);
    
    //notCompletedLabel
    CCLabelTTF *notCompleted=CCLabelTTF::create("Oops! You lost a life", "Helvetica", 25);
    notCompleted->setPosition(CCPointMake(winsize.width/2, winsize.height-60));
    notCompleted->setColor(ccc3(85, 10, 0));
    this->gameLayer->addChild(notCompleted,20);
    
    CCLabelTTF *livesLabel=CCLabelTTF::create("You now have     lives", "Helvetica", 14);
    livesLabel->setPosition(CCPointMake(winsize.width/2, winsize.height-85));
    this->gameLayer->addChild(livesLabel,20);
    livesLabel->setColor(ccc3(150,20,0));
    
    char noOflives[20];
    sprintf(noOflives, "%d",LMDataManager::sharedManager()->subLevelNumber);
    CCLabelTTF *wordLabel=CCLabelTTF::create(noOflives, "Arial", 14);
    wordLabel->setPosition(CCPointMake(winsize.width/2+30, winsize.height-85));
    wordLabel->setColor(ccc3(150,20,0));
    this->gameLayer->addChild(wordLabel,20);
    
    
    //buttons
    //myCollection Button
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("my_collection_bt.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("my_collection_bt_hvr.png");
    CCMenuItemSprite *myCollectionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::restartLevel));
    myCollectionMenuItem->setPosition(CCPointMake(170, 40));
    
    
    //retry
    normalSprite=CCSprite::createWithSpriteFrameName("retry_bt.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("retry_bt_hvr.png");
    CCMenuItemSprite *retryMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::goBack));
    retryMenuItem->setPosition(CCPointMake(280, 40));
    
    //close Button
    normalSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
    CCMenuItemSprite *closeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::restartLevel));
    closeMenuItem->setPosition(CCPointMake(430, 300));
    
    
    //button Menu
    CCMenu *bottomButtonsMenu=CCMenu::create(myCollectionMenuItem,retryMenuItem,closeMenuItem,NULL);
    this->gameLayer->addChild(bottomButtonsMenu,20);
    bottomButtonsMenu->setPosition(CCPointMake(0, 0));
    
    //popup rollo
    CCSprite *popuprollo=CCSprite::createWithSpriteFrameName("ui_popup_rolo_wth_colm.png");
    popuprollo->setPosition(CCPointMake(200, 150));
    this->gameLayer->addChild(popuprollo,20);
    
    CCLabelTTF *popupSubLabel=CCLabelTTF::create("Dont Worry, if you run out of lives\nand want to keep playing you can\nalways get more", "Arial", 14);
    popupSubLabel->setPosition(CCPointMake(280, 90));
    popuprollo->addChild(popupSubLabel,20);
    popupSubLabel->setColor(ccc3(150,20,0));
    
}

