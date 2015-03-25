//
//  BBMatchGamePlay.h
//  BaccizBooks
//
//  Created by Anshul on 22/01/13.
//
//

#ifndef __BaccizBooks__BBMatchGamePlay__
#define __BaccizBooks__BBMatchGamePlay__

#include <iostream>
#include "cocos2d.h"
#include "BBGameManager.h"
#include "BBMGSprite.h"
#include "BBMenuLayer.h"

using namespace cocos2d;

class BBMatchGamePlay:public cocos2d::CCLayer {
    
public:
    
    // Default
    virtual void onEnter();
    virtual void onExit();
   
    BBMatchGamePlay();
    virtual ~BBMatchGamePlay();
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(BBMatchGamePlay);
    
    //Layer
    BBMenuLayer *menuLayer;
    
    //Game Bg
    CCSprite *gameBackground;
    CCSprite *dogAnim;
      
    // Initialize 
    void initializeGame(const char *type);
    void initializeGameUI();
    void initializeVariables();
    void addBlinkActionForRefreshButton(float dt);
    void loadLevel(int tag);
    void dogAnimation(const char *dogName);
//    void shineAnimation(BBMGSprite *Sprite);
    int randomizeInt(int GameCards[15]);
    
    //temp restart
    CCMenuItemSprite *restartMenuItem;
    
    //Cards
    CCArray *cardsArr;
    CCArray* cardsToBeShuffleArr;
    
    CCDictionary *aCardLevelDict;
    CCDictionary *aCardDict;
    
    CCLabelTTF* pLabel;
    
    BBMGSprite* firstSelectedSprite;
    BBMGSprite* secondSelectedSprite;
    
    int selectedCardCount;
    int correctMatches;
    int wrongMatches;

    void openCard(BBMGSprite *fgSpr);
    void flipCards(BBMGSprite *topCard);
    void changeImageOfTopCard(BBMGSprite *matchCard);
    void matchCardsShineAnimation(BBMGSprite *Cards);
    
    void checkCards();
    void removeCards();
    void gameOver();
    
    void cardsNotMatch(CCSprite *senderSpr);

    //Touch
    bool canTouch;
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
   
    //Button Actions
    // Level Selection
    void gotoLevel(cocos2d::CCMenuItemImage* sender);
    
    //Utility
    CCArray* shuffleArray(CCArray *cardsToShuffle);
};


#endif /* defined(__BaccizBooks__BBMatchGamePlay__) */
