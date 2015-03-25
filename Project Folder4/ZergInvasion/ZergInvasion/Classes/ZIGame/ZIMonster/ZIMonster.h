//
//  ZIMonster.h
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#ifndef ZergInvasion_ZIMonster_h
#define ZergInvasion_ZIMonster_h

#include "ZICustomSprite.h"
#include "Box2D.h"
#include "ZIMonsterManager.h"

struct MonsterState {
    
    bool isReachedGround;
};

class ZIMonster : public ZICustomSprite {

public:
    
    ZIMonster();
    virtual ~ZIMonster();
    
    b2Body *body;
    MonsterState state;
    
    ZIMonster* spriteWithFile(const char *pszFileName);
    ZIMonster* spriteWithFrame(const char *pszFileName);
    ZIMonster* create(CCSpriteFrame *pSpriteFrame);
    
    void createMonsterContainer(float gridWidth);
    void setBox2dPropertiesForContainer();
    void changeToStatic();
    void moveMonster(bool isLeft);
    void rotateMonster(bool isLeft);
};

#endif
