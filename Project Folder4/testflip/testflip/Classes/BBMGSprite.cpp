//
//  BBMGSprite.cpp
//  BaccizBooks
//
//  Created by Anshul on 23/01/13.
//
//

#include "BBMGSprite.h"

BBMGSprite::BBMGSprite(void)
{
    
}

BBMGSprite::~BBMGSprite(void)
{
    
}


// To create separate sprite from file...
BBMGSprite* BBMGSprite::spriteWithFile(const char *pszFileName)
{
    BBMGSprite *pobSprite = new BBMGSprite();
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
BBMGSprite* BBMGSprite::spriteWithFrame(const char *pszFileName) {
    
    //CCLog("name is %s",pszFileName);
    
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszFileName);
    
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszFileName);
    CCAssert(pFrame != NULL, msg);
    
    BBMGSprite *tempSpr = BBMGSprite::create(pFrame);
    
    return tempSpr;
}



BBMGSprite* BBMGSprite::create(const char *pszFileName)
{
    BBMGSprite *pobSprite = new BBMGSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

BBMGSprite* BBMGSprite::create(CCSpriteFrame *pSpriteFrame)
{
    BBMGSprite *pobSprite = new BBMGSprite();
    if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

BBMGSprite* BBMGSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

BBMGSprite* BBMGSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    BBMGSprite *pobSprite = new BBMGSprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
