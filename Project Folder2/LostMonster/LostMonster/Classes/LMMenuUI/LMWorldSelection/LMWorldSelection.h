//
//  LMWorldSelection.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMWorldSelection_h
#define LMGame_LMWorldSelection_h

#include"cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LMWorldSelection : public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
 
private:
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LMWorldSelection, create);

    LMWorldSelection();
    ~LMWorldSelection();
    
    virtual void onEnter();
    virtual void onExit();
   
    //Cocos Builder
    virtual void onNodeLoaded(CCNode * pNode,CCNodeLoader * pNodeLoader);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    
    //Animations
    void initialiseAnimations();
    
    //LOGO
    CCSprite *logoSecondLayerSpr;
    CCSprite *logoThirdLayerSpr;

    //Functions
    void goToLoneIslandLevels(CCObject *obj);
    void goToPeaksOfDestinyLevels(CCObject *obj);
    void goToChamberOfBeyondLevels(CCObject *obj);
    void goToForestOfAdventureLevels(CCObject *obj);
    void goToSandOfPearlLevels(CCObject *obj);
    void goToHillsOfCuriosity( CCObject *obj);
    void goToWaterUnderSeaLevels(CCObject *obj);
    
    void goToLevelSelectionScreen(CCObject *obj);
    
    //back Button
    void backBtnAct(CCObject * pSender);
    
    //Lock Action
    void lockAction( int tag);
    
    //Temp
    void unlockAllWorlds();
};


#endif
