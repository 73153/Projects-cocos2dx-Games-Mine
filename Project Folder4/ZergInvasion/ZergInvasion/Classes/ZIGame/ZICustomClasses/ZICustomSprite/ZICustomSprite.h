//
//  ZICustomSprite.h
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#ifndef ZergInvasion_ZICustomSprite_h
#define ZergInvasion_ZICustomSprite_h

#include "cocos2d.h"

class ZIMainGame;

using namespace cocos2d;

class ZICustomSprite : public cocos2d::CCSprite {
    
public:
    
    ZICustomSprite(void);
    virtual ~ZICustomSprite(void);
    
    ZICustomSprite* spriteWithFile(const char *pszFileName);
    ZICustomSprite* spriteWithFrame(const char *pszFileName);
    ZICustomSprite* create(CCSpriteFrame *pSpriteFrame);
    
    ZIMainGame *gameLayer;
};

#endif
