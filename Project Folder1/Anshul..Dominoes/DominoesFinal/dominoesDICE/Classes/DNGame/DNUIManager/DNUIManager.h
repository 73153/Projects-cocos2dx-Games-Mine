//
//  DNUIManager.h
//  Dominoes
//
//  Created by ICRG LABS on 28/08/12.
//
//

#ifndef Dominoes_DNUIManager_h
#define Dominoes_DNUIManager_h

#include "DNGameManager.h"
#include "DNPlayerPanel.h"
#include "DNBackground.h"
#include "DNBackgroundManager.h"
#include "DNDomino.h"

#include "cocos2d.h"

class DNBackground;
using namespace cocos2d;

class DNUIManager : DNGameManager {
    
public:
    
    DNUIManager(void);
    virtual ~DNUIManager(void);
//    static bool init();
    void setupOpponents();
    void setupPlayer();
    void setupGameBarMenuBtns();
    void scaleDownPanels();
    void menuCallbacks(CCObject* sender);
    void menuCallback();
    int getCurrentPlayerPanelTag(int playerNumber);
    void startTimerAnimation();
    void callback();
    void pause();
    void opponentsTilesOpen();
    void restart();
    
    
    // Touch Methods
    void UIManagerTouchesBegan(CCSet *touches);
    void UIManagerTouchesMoved(CCSet *touches);
    void UIManagerTouchesEnded(CCSet *touches);
    void UIManagerTouchesCancelled(CCSet *touches);
    static cocos2d::CCScene* scene();
    CCMenu *mainMenu;
    CCMenu *playersMenu;
    CCMenu *actionMenu;
    
    CCSprite *yellow;
    CCSprite *orange;
    CCSprite *red;
    
    // Vars
    DNCustomSprite *gameBar;
    DNPlayerPanel *playerPanel1;
    DNPlayerPanel *playerPanel2;
    DNPlayerPanel *playerPanel3;
    DNDomino *domi;
    
    DNBackground *gameBackground;
    
    float xDifference;
    
    CCArray *panelsArray;
    
    CCMenuItemSprite *twoPlayersItem;
    CCMenuItemSprite *threePlayersItem;
    CCMenuItemSprite *restartItem;
    CCMenuItemToggle *item2;
    CCLabelTTF *score;
    
    int numberOfTilesPerHead;
    int click;
    int timekeeper;
    
    bool onResume;
    bool onPause;
//    LAYER_CREATE_FUNC(DNUIManager);
    
};

#endif
