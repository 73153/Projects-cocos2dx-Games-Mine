//
//  BBTicToeGamePlay.h
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 24/01/13.
//
//

#ifndef __BaccizBooks__BBTicToeGamePlay__
#define __BaccizBooks__BBTicToeGamePlay__

#include "cocos2d.h"
#include "BBMenuLayer.h"
#include "BBGameManager.h"
#include "BBGameUIManager.h"


class BBTicToeGamePlay : public cocos2d::CCLayer
{
    
public:
    
    static cocos2d::CCScene* scene();
      
   
    virtual void onEnter();
    virtual void onExit();
    
    BBTicToeGamePlay();
    ~BBTicToeGamePlay();
    
    void initialiseVariables();
    
    BBMenuLayer *menuLayer;
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(BBTicToeGamePlay);
    
    CCSize winsize;
    //ccpoint array
    
    CCPointArray *ticToePointArray;
    CCArray *freeSlotsArray;
    
 
    
    //for checking filled or not
    int index[10];
    int noOfBoxsFilled;
    
    //line
    int indexPoint;
    float rotatingAngle;
    float scalingFactor;
     
    
    //twoPlayer Game variables
    bool isFirstPlayeTurn;
       
    //temp
    bool isDifficultModePlay;
    
    
    //singlePlayer Game variables
    bool isCpuTurn;
    bool isSpriteAddedInitiallyInIpadVsPlayerMode;
    
    //GameModes
    bool isPlayerVsIad;
    bool isIpadVsPlayer;
    bool isTwoPlayer;
    
    bool isGameOver;
    bool isLabelAdded;
    
    //select gameModeBg
    CCSprite *selectPlayerBg;
    CCSprite *dogAnim;
    
    CCLabelTTF *header;
    CCMenuItemSprite *xMenuItem;
    CCMenuItemSprite *oMenuItem;
    CCMenuItemSprite *restartMenuItem;
    CCMenu *buttonMenu;
    
    bool isPlayerSelectedXsprite;
    
    //Add UI
    void addTicToeBackGround();
    
    // Two Player Function
    void addSpriteOnTouchedPoint(int currentIndex);
    
    //singlePlayer Functions
    void addDelayActionAfterPlayerTurn();
    void addComputerPlayedSprite();
    int getFreeIndex();
    int getEasyModeIndex();
    int getDangerIndex(int type);
    
    //blink functions
    void applyBlinkAction(float dt);
    void addBlinkActionForRefreshButton(float dt);
    
    //touches
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    //common Functions
    bool checkGameResult(int type);
    void addLine();
    void addLabel(const char *labelname);
    void addSpriteOfType(bool isXType,int currentIndex,int filledIndexType);
    void checkForGameMode(CCPoint location);
    //Buttons
    void action(cocos2d::CCMenuItemImage* sender);
     
};


#endif /* defined(__BaccizBooks__BBTicToeGamePlay__) */
