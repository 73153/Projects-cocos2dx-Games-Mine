//
//  ZIMonsterManager.h
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#ifndef __ZergInvasion__ZIMonsterManager__
#define __ZergInvasion__ZIMonsterManager__

#include "cocos2d.h"
#include "ZIGameManager.h"

using namespace cocos2d;

class ZIMonsterManager : ZIGameManager {
    
public:
    
    ZIMonsterManager();
    virtual ~ZIMonsterManager();
    
    // Vars
    CCArray *monstersArray;

    CCSize gridSize;
    CCPoint touchStartPoint;
    
    bool isTouchStarted;
    
    // Functions!
    void createMonster();
    void monsterManagerContactListener();
    void computeGridSize();
    
    // Touches!
    void monsterManagerTouchBegan(CCSet *touches);
    void monsterManagerTouchMoved(CCSet *touches);
    void monsterManagerTouchEnded(CCSet *touches);
    void monsterManagerTouchCanceled(CCSet *touches);
};

#endif /* defined(__ZergInvasion__ZIMonsterManager__) */
