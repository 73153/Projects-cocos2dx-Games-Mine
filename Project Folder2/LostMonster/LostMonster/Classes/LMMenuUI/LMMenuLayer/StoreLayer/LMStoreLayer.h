//
//  LMStoreLayer.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMStoreLayer_h
#define LMGame_LMStoreLayer_h

#include "cocos2d.h"
#include "CCScrollView.h"

USING_NS_CC_EXT;

using namespace cocos2d;

class LMStoreLayer : public cocos2d::CCLayer{
    
    
public:
    
    LMStoreLayer();
    ~LMStoreLayer();
    
    bool canPressButtons;
    
    //View
    CCLayer *livesLayer;
    CCLayer *bgLayer;
    
    CCMenu *topMainMenu;
    CCMenuItemSprite *livesMenuItem;
    CCMenuItemSprite *getMenuItem;
    CCMenuItemSprite *relicsMenuItem;
    CCMenuItemSprite *mapMenuitem;
    
    //Popup buy 
    CCSprite *popupBg;
    
    CCLabelTTF *mNumberLabel;
    void updateMoneyCountInView();
    
    //Buttons
    void action(cocos2d::CCMenuItemImage* sender);
    
    //Tab Func
    void addIntialButtonsWithBG();

      
    //Relics
    void loadRelicsData();
    void purchaseRelics(CCMenuItemImage *sender);
    void showRelicsRecievedScene(int randomRelicsToGet);
    
    //Not Enough Credit
    void loadNotEnoughCredit();
    
    //Money
    void loadGetMData();
    
    //Map
    void loadWorldMapData();
    void reloadMapsData();
    void purchaseMaps(CCMenuItemImage *sender);
    void restorePurchases(CCMenuItemImage *sender);

    //IAP
    void purchaseIAP(CCMenuItemImage *sender);
    void purchaseSuccesfull(CCObject* obj);
    void purchaseFailed(CCObject* obj);
    int purchasedMoneyCount;
    bool isPurchasingMaps;
    
    bool checkIsProductPurchased(int inProductIndex);
    
    //PopUp Bg
    void addPopUpScreenBeforeBuy();
    void removePopUPBg();
    void updatePopUPBg(int state);
    
    //Data
    CCDictionary *allStoreDataDict;
    
    int moneyCount;
    
   
    
};


#endif
