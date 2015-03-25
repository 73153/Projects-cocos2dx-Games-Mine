//
//  LMMainScreen.h
//
//  Created by Krithik on 05/03/13.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMMainScreen_h
#define LMGame_LMMainScreen_h

#include"cocos2d.h"
#include "cocos-ext.h"

//Animation
#include "SuperAnimNodeV2.h"
using namespace SuperAnim;

USING_NS_CC;
USING_NS_CC_EXT;

class LMMainScreen : public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener
,public SuperAnimNodeListener
{    
private:
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LMMainScreen, create);
    
    LMMainScreen();
    virtual ~LMMainScreen();
    
    virtual void onEnter();
    virtual void onExit();
    
    //Initialise Variables
    void initialiseVariables();
    
    //Cocos Builder
    virtual void onNodeLoaded(CCNode * pNode,CCNodeLoader * pNodeLoader);
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);

    
    //--- START
    
    //Timer
    void updateSecondTimer(float dt);
    
    //LOGO
    CCSprite *logoSecondLayerSpr;
    CCSprite *logoThirdLayerSpr;
    
    //Animations
    SuperAnimNode* rolloAnimationSpr;
    void initialiseAnimations();
    void OnAnimSectionEnd(int theId, std::string theLabelName);

    //Settings
    bool isSettingsSelected;
    CCSprite *settingBtnBGSpr;
    CCSprite *settingBtnIconSpr;
    CCMenu *settingSubMenu;
    void settingsBtnAct(CCObject * pSender);

    //More Menu
    CCMenu *moreMenu;
    void updateMoreMenu();
    
    //Store
    void storeBtnAct(CCObject * pSender);
        
    //MENU
    
    //Buttons
    
    //Menu Functions
    void playBtnAct(CCObject * pSender);

    //More
    void collectionBtnAct(CCObject * pSender);
    void achievementsBtnAct(CCObject * pSender);
    void monsterBtnAct(CCObject * pSender);
    void relicsBtnAct(CCObject * pSender);

    //Settings
    void introBtnAct(CCObject * pSender);
    void syncBtnAct(CCObject * pSender);
    void soundBtnAct(CCObject * pSender);

  
    //Touches
    virtual void ccTouchesEnded(CCSet *pTouch, CCEvent *pEvent);
    
};

#endif
 
