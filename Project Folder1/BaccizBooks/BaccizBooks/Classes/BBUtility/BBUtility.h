//
//  BBUtility.h
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 31/01/13.
//
//

#ifndef __BaccizBooks__BBUtility__
#define __BaccizBooks__BBUtility__

#include "cocos2d.h"
#include "Box2D.h"

using namespace cocos2d;

class BBUtility: public cocos2d::CCObject  {
    
private:
    
    BBUtility(void);
    ~BBUtility(void);
    
public:
    static void addGameAnimationsToAnimationCache(const char *pszFileName);
    
};

#endif
