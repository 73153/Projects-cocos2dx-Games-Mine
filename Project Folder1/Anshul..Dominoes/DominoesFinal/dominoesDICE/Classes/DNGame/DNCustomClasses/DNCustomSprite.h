//
//  DNCustomSprite.h
//  Dominoes
//
//  Created by ICRG LABS on 10/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Dominoes_DNCustomSprite_h
#define Dominoes_DNCustomSprite_h

#include "cocos2d.h"

class MainGameController;

using namespace cocos2d;

class DNCustomSprite : public cocos2d::CCSprite {
    
public:

    DNCustomSprite(void);
    virtual ~DNCustomSprite(void); 
    
    DNCustomSprite* spriteWithFile(const char *pszFileName);
    DNCustomSprite* spriteWithFrame(const char *pszFileName);
    DNCustomSprite* create(CCSpriteFrame *pSpriteFrame);

    MainGameController *gameLayer;
};

#endif
