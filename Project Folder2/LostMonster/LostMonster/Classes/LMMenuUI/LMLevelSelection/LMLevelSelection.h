//
//  LMLevelSelection.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMLevelSelection_h
#define LMGame_LMLevelSelection_h

#include"cocos2d.h"
#include "cocos-ext.h"

#include "LMMenuLayer.h"
#include "LMGameSoundManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LMLevelSelection : public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
{
private:
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LMLevelSelection, create);

    LMLevelSelection();
    ~LMLevelSelection();
    
    virtual void onEnter();
    virtual void onExit();
    
    //Cocos Builder
    virtual void onNodeLoaded(CCNode * pNode,CCNodeLoader * pNodeLoader);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);

    //Initialise
    void initialiseVariables();
    void initialiseUI();
    void initialiseAnimations();

    CCLayer *cocosBuilderLayer;
    
    //LOGO
    CCSprite *logoSecondLayerSpr;
    CCSprite *logoThirdLayerSpr;

   
    LMGameSoundManager *soundManager;
    CCArray *menuItemsArray;
    bool isLevelLocked;
    bool isLevelAchieved;
    
    char *levelName;
    void lockAction( int tag);

    void gotoLevel(CCObject *sender);
    void backBtnAct(CCObject *sender);
    
    CCSprite *regionIntroSpr;
    void goToregionIntro();
    void continueFromRegionIntro();
    
    CCPoint getPosiiton(CCMenuItem *);
    
    
    //Temp
    void unlockAllLevels();
    
    //zeroLives screen
    void addNoLivesScreen();
    void goToMainScreen();
    void addLivesLayer();

};

#endif
