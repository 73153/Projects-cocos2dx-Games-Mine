//
//  DNUtility.h
//  Dominoes
//
//  Created by ICRG LABS on 25/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Dominoes_DNUtility_h
#define Dominoes_DNUtility_h

#include "cocos2d.h"

using namespace cocos2d;

class DNUtility: public cocos2d::CCObject  {
    
private:
    
    DNUtility(void); 
    ~DNUtility(void);
    
public:
        
    static int getRandomNumberBetween(int min, int max);
    static float getAngleBetweenPoints(CCPoint startPoint,CCPoint ePoint);
    static CCRect rectForSprite(CCSprite* sprite);
};

#endif
