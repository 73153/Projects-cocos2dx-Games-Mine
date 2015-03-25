//
//  DNCustomSprite.cpp
//  Dominoes
//
//  Created by ICRG LABS on 10/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DNCustomSprite.h"

DNCustomSprite::DNCustomSprite(void) {
    
}

DNCustomSprite::~DNCustomSprite(void) {
    
}

// To create separate sprite from file...
DNCustomSprite* DNCustomSprite::spriteWithFile(const char *pszFileName) {
    
    DNCustomSprite *pobSprite = new DNCustomSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        //pobSprite->scheduleUpdate();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

// To create sprite from sprite sheet!
DNCustomSprite* DNCustomSprite::spriteWithFrame(const char *pszFileName) {
    
    //CCLog("name is %s",pszFileName);
    
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszFileName);
    
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszFileName);
    CCAssert(pFrame != NULL, msg);
    
    DNCustomSprite *tempSpr = DNCustomSprite::create(pFrame);
    
    return tempSpr;
}

DNCustomSprite* DNCustomSprite::create(CCSpriteFrame *pSpriteFrame) {
    
    DNCustomSprite *pobSprite = new DNCustomSprite();
    if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}