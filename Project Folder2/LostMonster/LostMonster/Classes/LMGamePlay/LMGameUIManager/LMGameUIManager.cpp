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
#include "LMWorldSelection.h"
#include "LMCollectionLayer.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "LMObjectiveCCalls.h"

#else


#endif

using namespace cocos2d;

#pragma mark - Init

LMGameUIManager::LMGameUIManager()
{
    this->gameLayer = LMDataManager::sharedManager()->gameLayer;
}

#pragma mark - Dealloc

LMGameUIManager::~LMGameUIManager()
{
    
    this->gameLayer->removeChild(menuLayer, true);
    delete menuLayer;
}


#pragma mark - Initialise
void LMGameUIManager::intialiseUI()
{
    //Zorder of Level Top Bar
    int levelTopBarZOrder = 5;
    
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    
    // Add Top Game menu Bar
    //menuLayer = new LMMenuLayer();
    //this->gameLayer->addChild(menuLayer,10);
    
    this->movesCount=0;
    
    /*
    // Level TopBar BG
    CCSprite *gameToolBar=CCSprite::createWithSpriteFrameName("game_toolbar.png");
    this->gameLayer ->addChild(gameToolBar,levelTopBarZOrder);
    gameToolBar->cocos2d::CCNode::setPosition(winsize.width-430, winsize.height-125);//220
    
    
    //Back Button
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("back_btn.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("back_btn_hvr.png");
    CCMenuItemSprite *backMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::goBack));
    backMenuItem->setPosition(CCPointMake(winsize.width-750,  winsize.height-125));
    
    
    //Refresh Button 
    normalSprite=CCSprite::createWithSpriteFrameName("refresh_btn.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("refresh_btn_hvr.png");
    CCMenuItemSprite *refreshMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::restartLevel));
    refreshMenuItem->setPosition(CCPointMake(winsize.width-680,  winsize.height-125));
    
    
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
    levelSUbTitle->setPosition(CCPointMake(winsize.width-450, winsize.height-125));
      */
    char subLevelName[5];
    sprintf(subLevelName, "%d",LMDataManager::sharedManager()->subLevelNumber);
    
    
    CCLabelTTF *subLevelLabel=CCLabelTTF::create(subLevelName, "LMVeraHumana95Bold", 14);
    this->gameLayer->addChild(subLevelLabel,levelTopBarZOrder);
    //subLevelLabel->setPosition(CCPointMake(winsize.width-398, winsize.height-139));
    subLevelLabel->setPosition(this->getSubLevelLabelPosition());
    subLevelLabel->setAnchorPoint(CCPointMake(0, 0));
    subLevelLabel->setColor(ccc3(66, 66, 66));
    
    /*
    
    //Min Max Sprite 
    minMaxSprite=CCSprite::createWithSpriteFrameName("min_max_icon.png");
    this-> gameLayer-> addChild(minMaxSprite,levelTopBarZOrder);
    minMaxSprite->setPosition(CCPointMake(winsize.width-220, winsize.height-125));
    */
    
    // adding sprite which shows minimum no of moves 
    int maxCuts = LMDataManager::sharedManager()->gameLayer->levelManager->maxCuts;
    
    // no of cuts
    
    char minMaxMoves[10];
    sprintf(minMaxMoves,"0/%d",maxCuts);
    
    noOfCutsLabel=CCLabelTTF::create(minMaxMoves, "LMVeraHumana95Bold", 32);
    this->gameLayer->addChild(noOfCutsLabel,levelTopBarZOrder);
    noOfCutsLabel->setPosition(CCPointMake(winsize.width-170, winsize.height-125));
    noOfCutsLabel->setColor(ccc3(120, 0, 15));
    
    
    //Challenging No Move Label
    
    int challengingMoveCount =LMDataManager::sharedManager()->gameLayer->levelManager->challengingMoveCount;
    
    char challengingMoveCountChar[10];
    sprintf(challengingMoveCountChar,"%d",challengingMoveCount);
    
    CCLabelTTF *challengingNoMoveLbl=CCLabelTTF::create(challengingMoveCountChar, "LMVeraHumana95Bold", 34);
    this->gameLayer->addChild(challengingNoMoveLbl,levelTopBarZOrder);
    challengingNoMoveLbl->setPosition(CCPointMake(winsize.width-120, winsize.height-120));
    challengingNoMoveLbl->setColor(ccc3(255, 200, 76));
    
    /*
    //Adding challenge intro  label 
    
    if(strncmp(LMDataManager::sharedManager()->worldName, "World_1", 7)==0)
    {
        
        //Check for the count of challenge Count !!!
        CCSprite *challengeIntroSprite = NULL;
        if (challengingMoveCount>1) {
            challengeIntroSprite=CCSprite::createWithSpriteFrameName("level_challenge_intros.png");
        }
        else
        {
            challengeIntroSprite=CCSprite::createWithSpriteFrameName("level_challenge_intro.png");
        }
        
        
        this->gameLayer->addChild(challengeIntroSprite,levelTopBarZOrder-1,500);
        challengeIntroSprite->setPosition(CCPointMake(512, 300));
        
        
        CCLabelTTF  *challengingIntroLbl=CCLabelTTF::create(challengingMoveCountChar, "LMVeraHumana95Bold", 50);
        challengeIntroSprite->addChild(challengingIntroLbl,levelTopBarZOrder);
        challengingIntroLbl->setPosition(CCPointMake(110, 120));
        challengingIntroLbl->setColor(ccc3(255, 200, 76));
        
        
        CCDelayTime *delayAction=CCDelayTime::create(1.5);
        CCCallFunc *callBackAction=CCCallFunc::create(this, callfunc_selector(LMGameUIManager::challengeIntroSpriteAction));
        CCSequence *sequence=CCSequence::createWithTwoActions(delayAction,callBackAction);
        
        this->gameLayer->runAction(sequence);
    }
     */
}

#pragma mark - Top Bar
void LMGameUIManager::updateLabel(int sliceCount)
{
    int maxCuts = LMDataManager::sharedManager()->gameLayer->levelManager->maxCuts;
    char noOfCuts[10];
    sprintf(noOfCuts, "%d/%d",sliceCount,maxCuts);
    this->noOfCutsLabel->setString(noOfCuts);
     this->movesCount=sliceCount;
}

//blink slice count action
void LMGameUIManager::blinkSliceCount()
{    
    CCBlink *blink=CCBlink::create(0.5,3);
    minMaxSprite->runAction(blink);
    
    CCBlink *labelBlink=CCBlink::create(0.5, 3);
    noOfCutsLabel->runAction(labelBlink);
}


#pragma mark - Challenge intro
//challenge intro sprite action 
void LMGameUIManager::challengeIntroSpriteAction(){
    
    CCSprite *challengeIntroSprite=(CCSprite*)this->gameLayer->getChildByTag(500);
    CCScaleBy *scaleAction=CCScaleBy::create(0.85, 0);
    CCMoveTo *moveAction=CCMoveTo::create(1, CCPointMake(920, 630));
    CCSpawn *spawnAction= CCSpawn::createWithTwoActions(scaleAction,moveAction);
    CCCallFunc *callBackAction1=CCCallFunc::create(this, callfunc_selector(LMGameUIManager::removeChallengeIntroSprite));
    CCSequence *sequence1=CCSequence::createWithTwoActions(spawnAction,callBackAction1);
    challengeIntroSprite->runAction(sequence1);
    
}

//removing challengeIntroSprite and label 
void LMGameUIManager::removeChallengeIntroSprite(){
    this->gameLayer->removeChildByTag(500, true);
 }


#pragma mark - Timer
void LMGameUIManager::showTimer()
{
    countDownTimerSpr = CCSprite::createWithSpriteFrameName("countdoen.png");
    countDownTimerSpr->setPosition(CCPointMake(910,630));  //565
    this->gameLayer->addChild(countDownTimerSpr,4);
    
    CCMoveTo *actionMove = CCMoveTo::create(0.2, CCPointMake(910, 565));
    countDownTimerSpr->runAction(actionMove);
    
    char timerCountChar[10];
    sprintf(timerCountChar,"%d",10);
    
    timerLabel = CCLabelTTF::create(timerCountChar, "LMVeraHumana95Bold", 32);
    countDownTimerSpr->addChild(timerLabel,4);
    timerLabel->setPosition(CCPointMake(40,40));
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
//main Restart  Button
void LMGameUIManager::restartLevel()
{
   if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }
    
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

//Restart  Button in Game Loss Or Game Win Screen
void LMGameUIManager::restartGamePlay()
{
    LMDataManager::sharedManager()->disableMenu=false;
    
    CCScene *pScene = LMGameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

//Main Back Button
void LMGameUIManager::goBack()
{    
    if (LMDataManager::sharedManager()->disableMenu) {
       return;
   }
    //Stop the BG sound
    //this->gameLayer->soundManager->stopBackgroundSound();
    LMDataManager::sharedManager()->isGamePlayRunning=false;

    //CCScene *pScene = LMLevelSelection::scene();
    //CCDirector::sharedDirector()->replaceScene(pScene);
}

//Back  Button in Game Loss Or Game Win Screen
void LMGameUIManager::closeButtonAction()
{
    LMDataManager::sharedManager()->isGamePlayRunning = false;
    LMDataManager::sharedManager()->disableMenu = false;
    
    //    if (LMDataManager::sharedManager()->disableMenu) {
    //        return;
    //    }
    //Stop the BG sound
   // this->gameLayer->soundManager->stopBackgroundSound();
    
    //CCScene *pScene = LMLevelSelection::scene();
    //CCDirector::sharedDirector()->replaceScene(pScene);
    
}

//wait for new lif button
void LMGameUIManager::goToMainScreen()
{
    
    //CCDirector::sharedDirector()->replaceScene(LMMainScreen::scene());
    

}


#pragma mark - Game Win Loss

void LMGameUIManager::gameWon(bool isFirstTime, const char *relicName,bool isMaxMove)
{
    LMDataManager::sharedManager()->disableMenu=true;
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    //bg
    
    CCSprite *background=CCSprite::create("ui_popup_bg.png");
    background->setPosition(CCPointMake(winsize.width/2, winsize.height/2));
    this->gameLayer->addChild(background,20);
    
    //buttons
    CCSprite *normalSprite;
    CCSprite *selectedSprite;
    
       
    //close Button
    normalSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
    CCMenuItemSprite *closeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::closeButtonAction));
    closeMenuItem->setPosition(CCPointMake(935, 715));
    
    
    //button Menu
    CCMenu *bottomButtonsMenu=CCMenu::create(closeMenuItem,NULL);
    this->gameLayer->addChild(bottomButtonsMenu,20);
    bottomButtonsMenu->setPosition(CCPointMake(0, 0));
    
    
    //gamePlayDetailsColm
    CCSprite *detailsColm=CCSprite::createWithSpriteFrameName("game_ply_details_colm.png");
    this->gameLayer->addChild(detailsColm,20);
    detailsColm->setPosition(CCPointMake(630, 400));
    
    
    //challenge
    char challengeGoalNumber[5];
   
    sprintf(challengeGoalNumber, "%d",LMDataManager::sharedManager()->gameLayer->levelManager->challengingMoveCount);
    CCLabelTTF *challengeGoalLabel=CCLabelTTF::create(challengeGoalNumber, "LMVeraHumana95Bold", 20);
    challengeGoalLabel->setPosition(CCPointMake(265, 159));
    challengeGoalLabel->setColor(ccc3(100,10,0));
    detailsColm->addChild(challengeGoalLabel,20);
    
    //moves
    char movesNumber[5];
    sprintf(movesNumber, "%d",this->movesCount);
    CCLabelTTF *movesNumberLabel=CCLabelTTF::create(movesNumber, "LMVeraHumana95Bold", 20);
    movesNumberLabel->setPosition(CCPointMake(265, 99));
    movesNumberLabel->setColor(ccc3(100,10,0));
    detailsColm->addChild(movesNumberLabel,20);
    
    //Get the money COunt
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    int totalMoney = LMObjectiveCCalls::getTotalMoney();
    
#else
    
    
#endif
    
    //earnings
    char earningNumber[5];
    sprintf(earningNumber, "%d",totalMoney);
    
    CCLabelTTF *earningNumberLabel=CCLabelTTF::create(earningNumber, "LMVeraHumana95Bold", 20);
    earningNumberLabel->setPosition(CCPointMake(293, 38));
    earningNumberLabel->setColor(ccc3(100,10,0));
    detailsColm->addChild(earningNumberLabel,20);
    
    
    if(isFirstTime)
    {
        //challengeCompletedLabel
        CCLabelTTF *completed=CCLabelTTF::create("Challenge Completed!", "LMVeraHumana95Bold", 57);
        completed->setPosition(CCPointMake(winsize.width/2, winsize.height-160));
        completed->setColor(ccc3(85, 10, 0));
        this->gameLayer->addChild(completed,20);
        
        //dummy name
        char worldName[45];
        sprintf(worldName,"%s",LMDataManager::sharedManager()->worldName);
        
        
        char worldFullName[45];
        
        if(strncmp(worldName, "World_1",7)==0){
            sprintf(worldFullName, "The Lone Island - Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_2", 7)==0){
            sprintf(worldFullName, "The Forests Of Adventure - Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_3", 7)==0){
            sprintf(worldFullName, "The Hills Of Curiosity - Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_4", 7)==0){
            sprintf(worldFullName, "The Peaks Of Destiny- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_5", 7)==0){
            sprintf(worldFullName, "The Chambers Of Beyond- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
            
        }
        else if(strncmp(worldName, "World_6", 7)==0){
            sprintf(worldFullName, "The Sands Of Peril- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
            
        }
        else if(strncmp(worldName, "World_7", 7)==0){
            sprintf(worldFullName, "The Waters Of Undersea- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
            
        }
        
        
        CCLabelTTF *wordLabel=CCLabelTTF::create(worldFullName, "LMVeraHumana95Bold", 32);
        wordLabel->setPosition(CCPointMake(winsize.width/2-3, winsize.height-215));
        wordLabel->setColor(ccc3(150,20,0));
        this->gameLayer->addChild(wordLabel,20);
        
               
        //collectedRelicLabel
        
        CCLabelTTF *relic=CCLabelTTF::create("You have collected relic:" , "LMVeraHumana95Bold", 30);
        relic->setPosition(CCPointMake(670, 245));
        relic->setColor(ccc3(150,10,0));
        this->gameLayer->addChild(relic,20);
        
        
        
        CCLabelTTF *relicNameLabel=CCLabelTTF::create(relicName, "LMVeraHumana95Bold", 30);
        relicNameLabel->setPosition(CCPointMake(150, -20));
        relicNameLabel->setColor(ccc3(155,10,0));
        relic->addChild(relicNameLabel,20);
        char aRelicName[25];
        sprintf(aRelicName,"%s.png", relicName);
        
        
        //Relic Image
        CCSprite *aRelic=CCSprite::create(aRelicName);
        this->gameLayer->addChild(aRelic,20);
        aRelic->setPosition(CCPointMake(260, 385));
        aRelic->setScale(1.5);
        
        //myCollection Button
        normalSprite=CCSprite::createWithSpriteFrameName("my_collection_bt.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("my_collection_bt_hvr.png");
        
        CCMenuItemSprite *myCollectionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::goToCollectionScene));
        myCollectionMenuItem->setPosition(CCPointMake(380, 130));
        
        //nextChallenge Button
        normalSprite=CCSprite::createWithSpriteFrameName("next_challenge_bt.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("next_challenge_bt_hvr.png");
        CCMenuItemSprite *nextChallengeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::nextChallenge));
        nextChallengeMenuItem->setPosition(CCPointMake(660, 130));
        
               
        
        //button Menu
        CCMenu *bottomButtonsMenu=CCMenu::create(myCollectionMenuItem,nextChallengeMenuItem,NULL);
        this->gameLayer->addChild(bottomButtonsMenu,20);
        bottomButtonsMenu->setPosition(CCPointMake(0, 0));
        

        
    
           
        
    }
    else if(!isFirstTime && !isMaxMove)
    {
        //Relic alreadyLabel
        CCLabelTTF *completed=CCLabelTTF::create("Relic already obtained", "LMVeraHumana95Bold", 58);
        completed->setPosition(CCPointMake(winsize.width/2, winsize.height-160));
        completed->setColor(ccc3(85, 10, 0));
        this->gameLayer->addChild(completed,20);
        
        //dummy name
        char worldName[45];
        sprintf(worldName,"%s",LMDataManager::sharedManager()->worldName);
        
        
        char worldFullName[45];
        
        if(strncmp(worldName, "World_1",7)==0){
            sprintf(worldFullName, "The Lone Island - Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_2", 7)==0){
            sprintf(worldFullName, "The Forests Of Adventure - Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_3", 7)==0){
            sprintf(worldFullName, "The Hills Of Curiosity - Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_4", 7)==0){
            sprintf(worldFullName, "The Peaks Of Destiny- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_5", 7)==0){
            sprintf(worldFullName, "The Chambers Of Beyond- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
            
        }
        else if(strncmp(worldName, "World_6", 7)==0){
            sprintf(worldFullName, "The Sands Of Peril- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
            
        }
        else if(strncmp(worldName, "World_7", 7)==0){
            sprintf(worldFullName, "The Waters Of Undersea- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
            
        }
        
        

        CCLabelTTF *wordLabel=CCLabelTTF::create(worldFullName, "LMVeraHumana95Bold", 32);
        wordLabel->setPosition(CCPointMake(winsize.width/2-20, winsize.height-215));
        wordLabel->setColor(ccc3(150,20,0));
        this->gameLayer->addChild(wordLabel,20);
        
              
        // popuprollo
        CCSprite *rollo=CCSprite::createWithSpriteFrameName("ui_popup_rolo_frnt.png");
        this->gameLayer->addChild(rollo,20);
        rollo->setPosition(CCPointMake(260, 360));
        
        //myCollection Button
        normalSprite=CCSprite::createWithSpriteFrameName("my_collection_bt.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("my_collection_bt_hvr.png");
        
        CCMenuItemSprite *myCollectionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::goToCollectionScene));
        myCollectionMenuItem->setPosition(CCPointMake(380, 130));
        
        //nextChallenge Button
        normalSprite=CCSprite::createWithSpriteFrameName("next_challenge_bt.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("next_challenge_bt_hvr.png");
        CCMenuItemSprite *nextChallengeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::nextChallenge));
        nextChallengeMenuItem->setPosition(CCPointMake(660, 130));
        
             
        
        //button Menu
        CCMenu *bottomButtonsMenu=CCMenu::create(myCollectionMenuItem,nextChallengeMenuItem,NULL);
        this->gameLayer->addChild(bottomButtonsMenu,20);
        bottomButtonsMenu->setPosition(CCPointMake(0, 0));
        

        
      
        
        
    }
    else if(isMaxMove)
        
    
    {
        //dummy name
        char worldName[45];
        sprintf(worldName,"%s",LMDataManager::sharedManager()->worldName);
        
        
        char worldFullName[45];
        
        if(strncmp(worldName, "World_1",7)==0){
            sprintf(worldFullName, "The Lone Island - Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_2", 7)==0){
            sprintf(worldFullName, "The Forests Of Adventure - Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_3", 7)==0){
            sprintf(worldFullName, "The Hills Of Curiosity - Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_4", 7)==0){
            sprintf(worldFullName, "The Peaks Of Destiny- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
        }
        else if(strncmp(worldName, "World_5", 7)==0){
            sprintf(worldFullName, "The Chambers Of Beyond- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
            
        }
        else if(strncmp(worldName, "World_6", 7)==0){
            sprintf(worldFullName, "The Sands Of Peril- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
            
        }
        else if(strncmp(worldName, "World_7", 7)==0){
            sprintf(worldFullName, "The Waters Of Undersea- Challenge %d",LMDataManager::sharedManager()->subLevelNumber);
            
            
        }
        
        
        
        CCLabelTTF *wordLabel=CCLabelTTF::create(worldFullName, "LMVeraHumana95Bold", 32);
        wordLabel->setPosition(CCPointMake(winsize.width/2-20, winsize.height-215));
        wordLabel->setColor(ccc3(150,20,0));
        this->gameLayer->addChild(wordLabel,20);
        
      
        CCSprite *rollo=CCSprite::create("relic_mask.png");
        this->gameLayer->addChild(rollo,20);
        rollo->setPosition(CCPointMake(260, 360));
        
        //min moves number
        char minMoveNumber[50];
        sprintf(minMoveNumber,"Solve it in %d Moves \n to win a Relic",LMDataManager::sharedManager()->gameLayer->levelManager->challengingMoveCount);
        
        CCLabelTTF *livesLabel=CCLabelTTF::create(minMoveNumber,"LMVeraHumana95Bold", 25);
        livesLabel->setPosition(CCPointMake(winsize.width/2+100, winsize.height-525));
        this->gameLayer->addChild(livesLabel,20);
        livesLabel->setColor(ccc3(150,20,0));
        
        //retry
        normalSprite=CCSprite::createWithSpriteFrameName("retry_bt.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("retry_bt_hvr.png");
        CCMenuItemSprite *retryMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::restartGamePlay));
        retryMenuItem->setPosition(CCPointMake(260, 130));
        
        //myCollection Button
        normalSprite=CCSprite::createWithSpriteFrameName("my_collection_bt.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("my_collection_bt_hvr.png");
        
        CCMenuItemSprite *myCollectionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::goToCollectionScene));
        myCollectionMenuItem->setPosition(CCPointMake(510, 130));
        
        //nextChallenge Button
        normalSprite=CCSprite::createWithSpriteFrameName("next_challenge_bt.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("next_challenge_bt_hvr.png");
        CCMenuItemSprite *nextChallengeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::nextChallenge));
        nextChallengeMenuItem->setPosition(CCPointMake(760, 130));

        
        //button Menu
        CCMenu *bottomButtonsMenu=CCMenu::create(retryMenuItem,myCollectionMenuItem,nextChallengeMenuItem,NULL);
        this->gameLayer->addChild(bottomButtonsMenu,20);
        bottomButtonsMenu->setPosition(CCPointMake(0, 0));
        



    }
    
}
void LMGameUIManager::gameLoss()
{
    LMDataManager::sharedManager()->disableMenu=true;
    //Get the Current Lives count
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    int noOfLivesLeft = 5;//LMObjectiveCCalls::getTotalLivesCount();
#else
    
#endif
    
    //BG
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    CCSprite *background=CCSprite::create("ui_popup_bg.png");
    background->setPosition(CCPointMake(winsize.width/2, winsize.height/2));
    this->gameLayer->addChild(background,20);
    
    if(noOfLivesLeft>0)
    {
        //notCompletedLabel
        CCLabelTTF *notCompleted=CCLabelTTF::create("Oops! You lost a life", "LMVeraHumana95Bold", 55);
        notCompleted->setPosition(CCPointMake(winsize.width/2, winsize.height-160));
        notCompleted->setColor(ccc3(85, 10, 0));
        this->gameLayer->addChild(notCompleted,20);
        
        
        
        //Top livesLabel count
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        
        int totalLives = 5;//LMObjectiveCCalls::getTotalLivesCount();
        
#else
        
#endif

        char noOflives[50];
        sprintf(noOflives, "You now have %d lives",totalLives);

        CCLabelTTF *livesLabel=CCLabelTTF::create(noOflives, "LMVeraHumana95Bold", 33);
        livesLabel->setPosition(CCPointMake(winsize.width/2, winsize.height-213));
        this->gameLayer->addChild(livesLabel,20);
        livesLabel->setColor(ccc3(150,20,0));
        
        
        
        
        
        //Buttons
        //myCollection Button
        CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("my_collection_bt.png");
        CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("my_collection_bt_hvr.png");
        CCMenuItemSprite *myCollectionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::goToCollectionScene));
        myCollectionMenuItem->setPosition(CCPointMake(400, 120));
        
        
        //retry
        normalSprite=CCSprite::createWithSpriteFrameName("retry_bt.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("retry_bt_hvr.png");
        CCMenuItemSprite *retryMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::restartGamePlay));
        retryMenuItem->setPosition(CCPointMake(650, 120));
        
        //close Button
        normalSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
        selectedSprite=CCSprite::createWithSpriteFrameName("close_bt.png");
        CCMenuItemSprite *closeMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMGameUIManager::closeButtonAction));
        closeMenuItem->setPosition(CCPointMake(935, 715));
        
        
        //button Menu
        CCMenu *bottomButtonsMenu=CCMenu::create(myCollectionMenuItem,retryMenuItem,closeMenuItem,NULL);
        this->gameLayer->addChild(bottomButtonsMenu,20);
        bottomButtonsMenu->setPosition(CCPointMake(0, 0));
        
        //popup rollo
        CCSprite *popuprollo=CCSprite::createWithSpriteFrameName("ui_popup_rolo_wth_colm.png");
        popuprollo->setPosition(CCPointMake(470, 360));
        this->gameLayer->addChild(popuprollo,20);
        
        CCLabelTTF *popupSubLabel=CCLabelTTF::create("Dont Worry, if you run out of lives\nand want to keep playing you can\nalways get more", "LMVeraHumana95Bold", 26);
        popupSubLabel->setPosition(CCPointMake(560, 170));
        popuprollo->addChild(popupSubLabel,20);
        popupSubLabel->setColor(ccc3(85, 10, 0));
    }
    
    //zero lives
    else
    {
        //this->addNoLivesScreen();
    }
}



void LMGameUIManager::goToCollectionScene()
{
    //Enable Top Menu
     LMDataManager::sharedManager()->disableMenu=false;
    //Stop Background sound
    
    LMDataManager::sharedManager()->isGamePlayRunning=false;
    this->gameLayer->soundManager->stopBackgroundSound();
    this->gameLayer->soundManager->playSound("34 Enter collections Page.mp3");
    
    CCDirector::sharedDirector()->replaceScene(LMCollectionLayer::scene());
}

void LMGameUIManager::nextChallenge()
{
    //Enable Top Menu
    LMDataManager::sharedManager()->disableMenu=false;
    //Get the Next level Name
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    //This is highly neccessary to eliminate some memory problems regarding char release
    char *nextLevelName = new char;
   
    const char *nextLevelNameTemp = LMObjectiveCCalls::getNextLevel(LMDataManager::sharedManager()->levelName, LMDataManager::sharedManager()->worldName);
  
    int levelNo = LMObjectiveCCalls::getLevelNo(nextLevelNameTemp, LMDataManager::sharedManager()->worldName);
    sprintf(nextLevelName, "%s",nextLevelNameTemp);
    
    if(strncmp(nextLevelNameTemp, "NextWorld", 10)==0)
    {
        // CCDirector::sharedDirector()->replaceScene(LMWorldSelection::scene());
    }
    else if (strncmp(nextLevelNameTemp, "GameOver",10)==0)
    {
        
    }
    else
    {
        LMDataManager::sharedManager()->levelName = nextLevelName;
        LMDataManager::sharedManager()->subLevelNumber = levelNo;
        CCScene *pScene = LMGameLayer::scene();
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
    
#else
    
    
#endif
}

#pragma mark - Utility
//getting subLevelLabel position
CCPoint LMGameUIManager::getSubLevelLabelPosition(){
    CCPoint labelPosition;
    
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    
    char worldName[10];
    sprintf(worldName,"%s",LMDataManager::sharedManager()->worldName);
    
    
    // comparing worldName with first world name
    if(strncmp(worldName, "World_1",7)==0){
        labelPosition=CCPointMake(winsize.width-409.5, winsize.height-147.5); // label posiiton
    }
    else if(strncmp(worldName, "World_2", 7)==0){
        labelPosition=CCPointMake(winsize.width-411, winsize.height-147.5);
    }
    else if(strncmp(worldName, "World_3", 7)==0){
        labelPosition=CCPointMake(winsize.width-412, winsize.height-144.6);
    }
    else if(strncmp(worldName, "World_4", 7)==0){
        labelPosition=CCPointMake(winsize.width-412, winsize.height-145);
    }
    else if(strncmp(worldName, "World_5", 7)==0){
        labelPosition=CCPointMake(winsize.width-412, winsize.height-145);
    }
    else if(strncmp(worldName, "World_6", 7)==0){
        labelPosition=CCPointMake(winsize.width-412, winsize.height-145);
    }
    else if(strncmp(worldName, "World_7", 7)==0){
        labelPosition=CCPointMake(winsize.width-412, winsize.height-146);
    }
       return labelPosition;
}


