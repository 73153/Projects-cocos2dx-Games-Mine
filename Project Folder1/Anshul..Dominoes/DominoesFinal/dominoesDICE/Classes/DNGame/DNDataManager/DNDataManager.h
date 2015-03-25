//
//  DNDataManager.h
//  Dominoes
//
//  Created by ICRG LABS on 10/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

// Singleton...

#ifndef Dominoes_DNDataManager_h
#define Dominoes_DNDataManager_h

#include "cocos2d.h"
#include "MainGameController.h"

using namespace cocos2d;

class DNDataManager: public cocos2d::CCObject  {
    
private:
    
     DNDataManager(void); 
    ~DNDataManager(void);
    
    bool m_isRunning;
    
public:
    
    bool init(void);
    static DNDataManager* sharedManager(void);
    
    // var
    MainGameController *gameLayer;
    cocos2d::CCSize screenSize;
    cocos2d::CCRect boardCenterRect;
    
    cocos2d::CCLayer *UILayer;
    
    int count;
    int score;
    int opponentCount;
    int opponenttilecount;
    int click;
    bool isGameOver;
    bool isGameFinished;
    int playerTileCount;
    int opponentOneTileCount;
    int opponentTwoTileCount;
    int sec;
    int min;
};

#endif
