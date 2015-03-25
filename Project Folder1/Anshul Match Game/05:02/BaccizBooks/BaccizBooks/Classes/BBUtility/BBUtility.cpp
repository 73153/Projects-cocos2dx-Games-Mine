//
//  BBUtility.cpp
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 31/01/13.
//
//

#include "BBUtility.h"
USING_NS_CC;

BBUtility::BBUtility(void) { }

BBUtility::~BBUtility(void) { }


void BBUtility::addGameAnimationsToAnimationCache(const char *pszFileName) {

    CCAssert( pszFileName, "Invalid texture file name");

    const char* path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(pszFileName);

    CCDictionary *dictAnimationData = CCDictionary::createWithContentsOfFile(path);

    CCAssert( dictAnimationData, "CCAnimationCache: File could not be found");

    // Looping through the items n adding them into cache...
    
    CCDictElement* pElement = NULL;

    CCDICT_FOREACH(dictAnimationData, pElement) {

        CCDictionary *aAnimationDict = (CCDictionary *)pElement->getObject();
  
        CCArray *animFrames = CCArray::create();

        int numOfFrames = aAnimationDict->valueForKey("num_of_frames")->intValue();
        
        const char* prefixName = aAnimationDict->valueForKey("prefix")->getCString();

        for (int i = 1; i <= numOfFrames; i++) {
            
            char name[30];
            
            sprintf(name, "%s%d.png",prefixName,i);

            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
            
            animFrames->addObject(frame);
        }

        const char* key = aAnimationDict->valueForKey("Key")->getCString();

        float animationDelay = aAnimationDict->valueForKey("delay")->floatValue();
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames,animationDelay);
        animFrames->release();

        CCAnimationCache::sharedAnimationCache()->addAnimation(animation, key);
    }
}

