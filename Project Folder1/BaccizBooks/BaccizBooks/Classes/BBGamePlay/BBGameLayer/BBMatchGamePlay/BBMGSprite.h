//
//  BBMGSprite.h
//  BaccizBooks
//
//  Created by Anshul on 23/01/13.
//
//

#ifndef BaccizBooks_BBMGSprite_h
#define BaccizBooks_BBMGSprite_h

#include "cocos2d.h"
using namespace cocos2d;
class BBMGSprite : public CCSprite
{
    
public:
    
    BBMGSprite(void);
    ~BBMGSprite(void);
    
    // Creation of a tile...
    static BBMGSprite* spriteWithFile(const char *pszFileName);
    static BBMGSprite* spriteWithFrame(const char *pszFileName);
    static BBMGSprite* create(const char *pszFileName);
    static BBMGSprite* create(CCSpriteFrame *pSpriteFrame);
    static BBMGSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    static BBMGSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
    
    // variables for matchGamePlay
    int matchID;
    int scaleCard;
    int bottomCardTag;
    int uniqueCards;
    
    const char *bottomImageName;
    const char *soundName;
    const char *matchSoundName;
    
    bool isFlipped;
};

#endif
