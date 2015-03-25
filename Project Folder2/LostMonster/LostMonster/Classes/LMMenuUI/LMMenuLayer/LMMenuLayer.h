//
//  LMMenuLayer.h
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LMGame_LMMenuLayer_h
#define LMGame_LMMenuLayer_h

#include"cocos2d.h"

#include "LMStoreLayer.h"


using namespace cocos2d;

class LMMenuLayer : public cocos2d::CCLayer {
    
public:

    LMMenuLayer();
    ~LMMenuLayer();
    
    //volume
    CCMenuItemSprite *volumeMenuItem;
    
       
    
    //Popup buy
    CCSprite *popupBg;
    
    CCMenuItemSprite *okMenuItem;

    
    //top Labels
    void updateTopLabels();

    
    //Store
    LMStoreLayer *storeLayer;
    void addStoreLayer();
    void removeStoreLayer(CCMenuItemImage *sender);

       
    //PopUp Screen
    void addPopUpScreenIfGameIsRunning( int senderTag);
    void removePopUpScreen();
    void yesButtonAction(CCMenuItemImage* sender);
    
    
    //Sound
    void soundStatus(bool inSoundStatus);
    
    void action(CCMenuItemImage* sender);

    //Update Top Labels
    void update();
    
    //Life regenaration
    float seconds;
    bool shouldCalculateLifeRegenarationTime;
};

#endif
