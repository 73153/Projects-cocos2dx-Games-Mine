//
//  LMMainScreen.h
//
//  Created by Krithik on 05/03/13.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "LMMainScreenLoader.h"
#include "LMMainScreen.h"
#include "LMMenuLayer.h"
#include "LMWorldSelection.h"
#include "LMDataManager.h"
#include "LMSharedSoundManager.h"

#include "LMWorldSelection.h"
#include "LMWorldSelectionScreenLoader.h"

//Animation
#include "SuperAnimNodeV2.h"
#include "SuperAnimCommon.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "LMObjectiveCCalls.h"


#else

#endif

using namespace cocos2d;


LMMainScreen::LMMainScreen()
{
    this->logoSecondLayerSpr = NULL;
    this->logoThirdLayerSpr = NULL;

    this->settingSubMenu = NULL;
    this->settingBtnBGSpr = NULL;
    this->settingBtnIconSpr = NULL;
    
    this->moreMenu = NULL;    
}

void LMMainScreen::onEnter()
{
    CCLayer::onEnter();
    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GameUIImages/MainPage/mainPageSpritesheet.plist");

    this->initialiseVariables();
    this->initialiseAnimations();
    this->schedule(schedule_selector(LMMainScreen::updateSecondTimer), 0.5);

}

void LMMainScreen::onExit()
{
    //CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GameUIImages/MainPage/mainPageSpritesheet.plist");
    CCLayer::onExit();
}

LMMainScreen::~LMMainScreen()
{
   
    CC_SAFE_RELEASE(this->logoSecondLayerSpr);
    CC_SAFE_RELEASE(this->logoThirdLayerSpr);
    
    CC_SAFE_RELEASE(this->settingSubMenu);
    CC_SAFE_RELEASE(this->settingBtnBGSpr);
    CC_SAFE_RELEASE(this->settingBtnIconSpr);

    CC_SAFE_RELEASE(this->moreMenu);
}

#pragma mark - Initialise Variables
void LMMainScreen::initialiseVariables()
{
    this->isSettingsSelected = false;
}

#pragma mark - CocosBuilderReader

void LMMainScreen::onNodeLoaded(CCNode * pNode,CCNodeLoader * pNodeLoader)
{
    //this->mAnimationManager = LMDataManager::sharedManager()->cocosBuilderReader->getAnimationManager();

}


SEL_MenuHandler LMMainScreen::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    
    //Play
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "playBtnAct:", LMMainScreen::playBtnAct);

    //More
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "collectionBtnAct:", LMMainScreen::collectionBtnAct);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "achievementsBtnAct:", LMMainScreen::achievementsBtnAct);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "monsterBtnAct:", LMMainScreen::monsterBtnAct);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "relicsBtnAct:", LMMainScreen::relicsBtnAct);

    //Settings
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "settingsBtnAct:", LMMainScreen::settingsBtnAct);

    //Store
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "storeBtnAct:", LMMainScreen::storeBtnAct);

    
    
    return NULL;
}

SEL_CCControlHandler LMMainScreen::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

bool LMMainScreen::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
    //Logo
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "logoSecondLayerSpr", CCSprite *, this->logoSecondLayerSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "logoThirdLayerSpr", CCSprite *, this->logoThirdLayerSpr);
    
    //Settings
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "settingSubMenu", CCMenu *, this->settingSubMenu);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "settingBtnBGSpr", CCSprite *, this->settingBtnBGSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "settingBtnIconSpr", CCSprite *, this->settingBtnIconSpr);


    //More
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "moreMenu", CCMenu *, this->moreMenu);
   
    return false;
}

#pragma mark - Timer
//This timer calls once every second
void LMMainScreen::updateSecondTimer(float dt)
{
    this->updateMoreMenu();
}


#pragma mark - Button Actions

void LMMainScreen::playBtnAct(CCObject * pSender)
{
    LMUtility::loadCocosBuilderFileWithPathAndLoader("CocosBuilder/WorldSelection/WorldSelectionScreen.ccbi","LMWorldSelection",LMWorldSelectionScreenLoader::loader());
}

//More
void LMMainScreen::collectionBtnAct(CCObject * pSender)
{
    
}

void LMMainScreen::achievementsBtnAct(CCObject * pSender)
{
    
}

void LMMainScreen::monsterBtnAct(CCObject * pSender)
{
    
}

void LMMainScreen::relicsBtnAct(CCObject * pSender)
{
    
}

#pragma mark - Settings
void LMMainScreen::settingsBtnAct(CCObject * pSender)
{
    float requiredAngle = 0.0f;
    float duration = 0.0f;
    bool doRequireBounce = false;
    if(this->isSettingsSelected)
    {
        this->isSettingsSelected = false;
        requiredAngle = 90.0f;
        doRequireBounce = false;
        duration = 0.4f;
    }
    else
    {
        this->isSettingsSelected = true;
        requiredAngle = 0.0f;
        doRequireBounce = true;
        duration = 0.7f;
    }
    
    CCRotateTo *rotateActionSettingsBG = CCRotateTo::create(duration,requiredAngle);
    
    CCActionInterval* move_ease_out = NULL;
   
    if(doRequireBounce)
        move_ease_out = CCEaseBounceOut::create((CCActionInterval*)(rotateActionSettingsBG->copy()->autorelease()));
    else
        move_ease_out = rotateActionSettingsBG;
    
    this->settingBtnBGSpr->runAction(move_ease_out);
    
    CCRotateTo *rotateActionMenu = CCRotateTo::create(duration,requiredAngle);
    if(doRequireBounce)
        move_ease_out = CCEaseBounceOut::create((CCActionInterval*)(rotateActionMenu->copy()->autorelease()));
    else
        move_ease_out = rotateActionMenu;

    this->settingSubMenu->runAction(move_ease_out);
}

#pragma mark - More Menu

void LMMainScreen::updateMoreMenu()
{
    int selectedMenuIndex = 0;
    
    CCArray *childrensArr = moreMenu->getChildren();
    
    CCObject *aMenuItemObj = NULL;
    CCARRAY_FOREACH(childrensArr, aMenuItemObj)
    {
        CCMenuItem *aMenuItem = (CCMenuItem *)aMenuItemObj;
        
        if(aMenuItem->isSelected())
        {
            selectedMenuIndex = aMenuItem->getTag();
            aMenuItem->unselected();
            break;
        }
    }
    
    if(selectedMenuIndex == 4)
    {
        selectedMenuIndex = 1;
    }
    else if (selectedMenuIndex == 0) {
        selectedMenuIndex = 1;
    }
    else
    {
        selectedMenuIndex = selectedMenuIndex+1;
    }
        
    CCMenuItem *aMenuItem = (CCMenuItem *)moreMenu->getChildByTag(selectedMenuIndex);
    aMenuItem->selected();
}

#pragma mark - Store
void LMMainScreen::storeBtnAct(CCObject * pSender)
{
    LMUtility::loadCocosBuilderFileWithPathAndLoader("CocosBuilder/MainMenu/MainMenu.ccbi","LMMainScreen",LMMainScreenLoader::loader());
}
 
#pragma mark - Animations

void LMMainScreen::initialiseAnimations()
{
    //Rotate Logo
    LMUtility::rotateNodeWithClockwiseDirection(this->logoSecondLayerSpr, false, 15.0);
    LMUtility::rotateNodeWithClockwiseDirection(this->logoThirdLayerSpr, true, 10.0);
    
    //Settings
    LMUtility::rotateNodeWithClockwiseDirection(this->settingBtnIconSpr, true, 5.0);

    //Rollo Animations
    std::string anAnimFileFullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("Animations/rollo idel_2.sam");
	rolloAnimationSpr = SuperAnimNode::create(anAnimFileFullPath, 0, this);
	addChild(rolloAnimationSpr);
	rolloAnimationSpr->setPosition(ccp(775, 230));
	rolloAnimationSpr->PlaySection("idle");

}

void LMMainScreen::OnAnimSectionEnd(int theId, std::string theLabelName){
    rolloAnimationSpr->PlaySection("idle");
}

#pragma mark - Touches
//This is mainly used to detect Touch of Textfields
void LMMainScreen::ccTouchesEnded(CCSet *touches, CCEvent *event)
{

    CCTouch* touch;
    CCSetIterator it;
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
       
        
    }

}
