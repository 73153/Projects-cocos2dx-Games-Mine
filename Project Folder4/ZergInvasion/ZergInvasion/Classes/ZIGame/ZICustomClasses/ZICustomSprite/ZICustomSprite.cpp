//
//  ZICustomSprite.cpp
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#include "ZICustomSprite.h"

ZICustomSprite::ZICustomSprite(void) {
    
}

ZICustomSprite::~ZICustomSprite(void) {
    
}

// To create separate sprite from file...
ZICustomSprite* ZICustomSprite::spriteWithFile(const char *pszFileName) {
    
    ZICustomSprite *pobSprite = new ZICustomSprite();
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
ZICustomSprite* ZICustomSprite::spriteWithFrame(const char *pszFileName) {
    
    //CCLog("name is %s",pszFileName);
    
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszFileName);
    
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszFileName);
    CCAssert(pFrame != NULL, msg);
    
    ZICustomSprite *tempSpr = ZICustomSprite::create(pFrame);
    
    return tempSpr;
}

ZICustomSprite* ZICustomSprite::create(CCSpriteFrame *pSpriteFrame) {
    
    ZICustomSprite *pobSprite = new ZICustomSprite();
    if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}