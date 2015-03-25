//
//  LMLevelSelection.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMLevelSelection.h"
#include "LMMenuLayer.h"
#include "LMGameLayer.h"
#include "LMDataManager.h"
#include "LMSharedSoundManager.h"
#include "SimpleAudioEngine.h"

#include "LMWorldSelectionScreenLoader.h"

#define lockTag 500

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "LMObjectiveCCalls.h"


#else

#endif

using namespace cocos2d;

LMLevelSelection::LMLevelSelection(){
    
    this->cocosBuilderLayer = NULL;
    
    this->logoSecondLayerSpr = NULL;
    this->logoThirdLayerSpr = NULL;
}

LMLevelSelection::~LMLevelSelection(){
    CC_SAFE_RELEASE_NULL(menuItemsArray);
    
    CC_SAFE_RELEASE(this->logoSecondLayerSpr);
    CC_SAFE_RELEASE(this->logoThirdLayerSpr);

    CC_SAFE_RELEASE(this->cocosBuilderLayer);
}

void LMLevelSelection::onEnter()
{
    CCLayer::onEnter();
    
    this->initialiseVariables();
    this->initialiseUI();
    this->initialiseAnimations();

    
}

void LMLevelSelection::onExit()
{
    CCLayer::onExit();
}


#pragma mark - CocosBuilderReader

void LMLevelSelection::onNodeLoaded(CCNode * pNode,CCNodeLoader * pNodeLoader)
{
    //this->mAnimationManager = LMDataManager::sharedManager()->cocosBuilderReader->getAnimationManager();
    
}


SEL_MenuHandler LMLevelSelection::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    
    //Store
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "bactBtnAct:", LMLevelSelection::backBtnAct);
    
    return NULL;
}

SEL_CCControlHandler LMLevelSelection::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

bool LMLevelSelection::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
    //Logo
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "logoSecondLayerSpr", CCSprite *, this->logoSecondLayerSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "logoThirdLayerSpr", CCSprite *, this->logoThirdLayerSpr);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cocosBuilderLayer", CCLayer *, this->cocosBuilderLayer);

    
    return false;
}

#pragma mark - Initialise
void LMLevelSelection::initialiseVariables()
{
    //Allocate some space for holding levelName
    levelName = new char;
}

void LMLevelSelection::initialiseUI()
{
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    
    menuItemsArray=CCArray::create();
    menuItemsArray->retain();
    
    
    //Play World Background Sound
    LMSharedSoundManager::sharedManager()->playWorldBackgroundSound(LMDataManager::sharedManager()->worldName);
   
    //World backGround
    char worldBackGroundBgName[30];
    sprintf(worldBackGroundBgName,"GameUIImages/BG/%s_BG.png",LMDataManager::sharedManager()->worldName);
      
    //Here we are reusing the BG images which we are using in the game play screen
    CCSprite *selectedWorldBG = CCSprite::create(worldBackGroundBgName);
    this->addChild(selectedWorldBG);
    selectedWorldBG->setPosition(CCPointMake(winSize.width/2, winSize.height/2));
    
    this->cocosBuilderLayer->setZOrder(1);
    
    CCLOG("this->cocosBuilderLayer- is %f %f",this->cocosBuilderLayer->getPositionX(),this->cocosBuilderLayer->getPositionY());
    
    char titleName[20];
    sprintf(titleName, "%s_Heading.png",LMDataManager::sharedManager()->worldName);
    
    CCSprite *title=CCSprite::createWithSpriteFrameName(titleName);
    title->setPosition(ccp(535.0,686.0));
    this->addChild(title,1);
    
    int numberOfLevels=LMDataManager::sharedManager()->numberOfLevels;

    int x = 310.0f;
    int y = 0.0f;
    
    if (numberOfLevels==12) {
        y = 490.0f;
    }
    else
        y = 510.0f;
    
    
    //  Adding level buttons
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
        
        char tempLevelName[10];
        sprintf(tempLevelName,"%s%d",LMDataManager::sharedManager()->levelNamePrefix,i);
        
        bool isLevelLocked = false;
        bool isChallengeCompleted = true;
        
        /*
         #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
         
         bool isLevelLocked = LMObjectiveCCalls::isLevelLocked(tempLevelName, LMDataManager::sharedManager()->worldName);
         bool isChallengeCompleted = LMObjectiveCCalls::isChallengeCompleted(tempLevelName, LMDataManager::sharedManager()->worldName);
         #else
         
         #endif
         */
        // addign locks for levels
        if(isLevelLocked){
            CCSprite *lockSpr=CCSprite::createWithSpriteFrameName("lock.png");
            this->addChild(lockSpr,1,lockTag+i);
            
            CCPoint requiredPos = CCPoint(levelselectionMenuItem->getPositionX()+37, levelselectionMenuItem->getPositionY()-28);
            lockSpr->setPosition(requiredPos);
        }
        
        //adding level relics for achieves levels
        if(isChallengeCompleted){
            CCSprite *challengeCompletedSpr=CCSprite::createWithSpriteFrameName("relic_card.png");
            this->addChild(challengeCompletedSpr,3);
            
            CCPoint requiredPos = CCPoint(levelselectionMenuItem->getPositionX()+51, levelselectionMenuItem->getPositionY()+28);
            challengeCompletedSpr->setPosition(requiredPos);
        }
        
        CCSprite *levelStarSpr=CCSprite::createWithSpriteFrameName("star_3.png");
        this->addChild(levelStarSpr,3);
        
        CCPoint requiredPos = CCPoint(levelselectionMenuItem->getPositionX()-35, levelselectionMenuItem->getPositionY()+28);
        levelStarSpr->setPosition(requiredPos);
        
        
        
        //checking for the  next row of level button
        if(i%4==0){
            x = 310.0f;
            
            if (numberOfLevels==12) {
                y = y-135;
            }
            else
                y = y-114;
            
        }
        else{
            x = x+156;
        }
    }
    
    // adding levels menu
    CCMenu *menu=CCMenu::createWithArray(menuItemsArray);
    menu->setPosition(CCPointZero);
    this->addChild(menu,2);
    
    
    
 
    
    /*
     //Temp
     normalSprite=CCSprite::createWithSpriteFrameName("lock.png");
     selectedSprite=CCSprite::createWithSpriteFrameName("lock.png");
     CCMenuItemSprite *unlockAllWorldsBtn=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMLevelSelection::unlockAllLevels));
     unlockAllWorldsBtn->setPosition(1024-50,768-150);
     
     CCMenu *tempMenu = CCMenu::createWithItem(unlockAllWorldsBtn);
     tempMenu->setPosition(CCPointZero);
     this->addChild(tempMenu);
     */

}



void LMLevelSelection::backBtnAct(CCObject *sender){
    
    LMSharedSoundManager::sharedManager()->stopBackgroundSound();
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }
    
    LMUtility::loadCocosBuilderFileWithPathAndLoader("CocosBuilder/WorldSelection/WorldSelectionScreen.ccbi","LMWorldSelection",LMWorldSelectionScreenLoader::loader());
}

#pragma mark - Animations

void LMLevelSelection::initialiseAnimations()
{
    //Rotate Logo
    LMUtility::rotateNodeWithClockwiseDirection(this->logoSecondLayerSpr, false, 15.0);
    LMUtility::rotateNodeWithClockwiseDirection(this->logoThirdLayerSpr, true, 10.0);
}

void LMLevelSelection::gotoLevel(CCObject *sender)
{
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

    //Check the no Of Lives
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    int noOfLivesLeft = 5;//LMObjectiveCCalls::getTotalLivesCount();
#else
    
#endif
    
    if(noOfLivesLeft == 0)
    {
        this->addNoLivesScreen();
    }
    else
    {
        CCMenuItemSprite *senderBtn = (CCMenuItemSprite *)sender;
        int tag=senderBtn->getTag();
        
        sprintf(levelName, "%s%d",LMDataManager::sharedManager()->levelNamePrefix,senderBtn->getTag());
        
        //Check if lock exist
        if (LMUtility::doSpriteExistWithTag(lockTag+tag, this))
        {
            this->lockAction(lockTag+tag);
        }
        else
        {
            LMDataManager::sharedManager()->levelName = levelName;
            LMDataManager::sharedManager()->subLevelNumber = senderBtn->getTag();
            CCScene *pScene = LMGameLayer::scene();
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
    }
}

void LMLevelSelection::goToregionIntro(){

    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }
    
    LMDataManager::sharedManager()->disableMenu =  true;
     
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();

    char tempLevelName[25];
    sprintf(tempLevelName,"%sRegionIntro.png",LMDataManager::sharedManager()->worldName);
    CCLOG("tempLevelName is %s",tempLevelName);
    
    regionIntroSpr = CCSprite::create(tempLevelName);
    regionIntroSpr->setPosition(CCPoint(winSize.width/2, winSize.height/2));
    this->addChild(regionIntroSpr,10);
    
    //Add Continue Button
  
    CCSprite *normalSprite=CCSprite::create("continue_bt.png");
    CCSprite *selectedSprite=CCSprite::create("continue_bt.png");
    
    CCMenuItemSprite *unlockAllWorldsBtn=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMLevelSelection::continueFromRegionIntro));
    unlockAllWorldsBtn->setPosition(winSize.width-winSize.width/2+150,165);
    
    CCMenu *tempMenu = CCMenu::createWithItem(unlockAllWorldsBtn);
    tempMenu->setPosition(CCPointZero);
    regionIntroSpr->addChild(tempMenu);

}

void LMLevelSelection::continueFromRegionIntro()
{
    LMDataManager::sharedManager()->disableMenu = false;
    regionIntroSpr->removeAllChildrenWithCleanup(true);
    this->removeChild(regionIntroSpr, true);
}

void LMLevelSelection::lockAction(int tag){
    
    CCSprite *lockSprite=(CCSprite*)this->getChildByTag(tag);
    if (lockSprite->numberOfRunningActions()==0)
    {
        //level lock sound
        this->soundManager->playLevelLockSound();
        CCRotateBy *rotate=CCRotateBy::create(0.15, 30);
        CCRotateBy *rotReverse=CCRotateBy::create(0.15, -30);
        CCSequence *seq=CCSequence::createWithTwoActions(rotate,rotReverse);
        CCSequence *seq1=CCSequence::createWithTwoActions(rotate,rotReverse);
        CCSequence *seq3=CCSequence::createWithTwoActions(seq, seq1);
        CCSequence *seq4=CCSequence::createWithTwoActions(seq,seq1);
        CCSequence *seq5=CCSequence::createWithTwoActions(seq3, seq4);
        lockSprite->runAction(seq5);
    }
}

CCPoint LMLevelSelection::getPosiiton(CCMenuItem *menuItem){
    CCPoint Posiiton;
    CCPoint menuitemPosition=menuItem->getPosition();
    float x=menuitemPosition.x+546;
    float y=menuitemPosition.y+355;
    Posiiton=CCPoint(x, y);
    return Posiiton;
    
}


#pragma mark -  Temp
void LMLevelSelection::unlockAllLevels()
{
    if (LMDataManager::sharedManager()->disableMenu) {
        return;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    LMObjectiveCCalls::unlockAllLevels(LMDataManager::sharedManager()->worldName);
    //CCDirector::sharedDirector()->replaceScene(LMWorldSelection::scene());

#else
    
#endif
    
}

//NO Lives Screen
void LMLevelSelection::addNoLivesScreen()
{
   
    //bg
    CCSize winsize=CCDirector::sharedDirector()->getWinSize();
    CCSprite *background=CCSprite::create("ui_popup_bg.png");
    background->setPosition(CCPointMake(winsize.width/2, winsize.height/2));
    this->addChild(background,20);

    //notCompletedLabel
    CCLabelTTF *notCompleted=CCLabelTTF::create("Oh no! You've run out of Lives", "LMVeraHumana95Bold", 47);
    notCompleted->setPosition(CCPointMake(winsize.width/2, winsize.height-165));
    notCompleted->setColor(ccc3(85, 10, 0));
    this->addChild(notCompleted,20);
    
    CCLabelTTF *livesLabel=CCLabelTTF::create("Dont't worry it's easy to stay in the game.\n Choose from these simple options to add more Lives", "LMVeraHumana95Bold", 25);
    livesLabel->setPosition(CCPointMake(winsize.width/2, winsize.height-220));
    this->addChild(livesLabel,20);
    livesLabel->setColor(ccc3(150,20,0));
    
    //add lives Button
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("add lives.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("add lives_hvr.png");
    CCMenuItemSprite *myCollectionMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMLevelSelection::addLivesLayer));
    myCollectionMenuItem->setPosition(CCPointMake(400, 330));
    
    
    //wait for new life button
    normalSprite=CCSprite::createWithSpriteFrameName("wait life.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("wait life_hvr.png");
    CCMenuItemSprite *retryMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(LMLevelSelection::goToMainScreen));
    retryMenuItem->setPosition(CCPointMake(650, 330));
    
    
    
    //button Menu
    CCMenu *bottomButtonsMenu=CCMenu::create(myCollectionMenuItem,retryMenuItem,NULL);
    this->addChild(bottomButtonsMenu,20);
    bottomButtonsMenu->setPosition(CCPointMake(0, 0));
    
    //bottom Label
    CCLabelTTF *bottomLabel=CCLabelTTF::create("1 new life will regenerate every 10 minutes up to a maximum of 5 lives", "LMVeraHumana95Bold", 18);
    bottomLabel->setPosition(CCPointMake(winsize.width/2, winsize.height-600));
    this->addChild(bottomLabel,20);
    bottomLabel->setColor(ccc3(92,70,39));
    
}

//wait for new lif button
void LMLevelSelection::goToMainScreen()
{
    
    //CCDirector::sharedDirector()->replaceScene(LMMainScreen::scene());
    
    
}
#pragma mark - Store Layer
void LMLevelSelection::addLivesLayer()
{
    LMDataManager::sharedManager()->toAddStoreLayerInMainScreen=true;
    // CCDirector::sharedDirector()->replaceScene(LMMainScreen::scene());
    
}



