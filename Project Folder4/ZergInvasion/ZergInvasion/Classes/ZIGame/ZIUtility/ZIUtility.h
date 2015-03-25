//
//  ZIUtility.h
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#ifndef ZergInvasion_ZIUtility_h
#define ZergInvasion_ZIUtility_h

#include "cocos2d.h"
#include "Box2D.h"

using namespace cocos2d;

class ZIUtility: public cocos2d::CCObject  {
    
private:
    
    ZIUtility(void);
    virtual ~ZIUtility(void);
    
public:
    
    static int getRandomNumberBetween(int min, int max);
    static float getAngleBetweenPoints(CCPoint startPoint,CCPoint ePoint);
    static CCRect rectForSprite(CCSprite* sprite);
};

#endif
