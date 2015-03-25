//
//  LMUtility.h
//  Dominoes
//
//  Created by ICRG LABS on 25/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef LostMonster_DNUtility_h
#define LostMonster_DNUtility_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Box2D.h"

USING_NS_CC;
USING_NS_CC_EXT;



class LMUtility: public cocos2d::CCObject  {
    
private:
    
    LMUtility(void); 
    ~LMUtility(void);
    
public:
        
    static int getRandomNumberBetween(int min, int max);
    static float getAngleBetweenPoints(CCPoint startPoint,CCPoint ePoint);
    static CCRect rectForSprite(CCSprite* sprite);
    static CCPoint convertVectortoPixels(b2Vec2 vec);
    static bool bodiesAreTouching( b2Body* body1, b2Body* body2 );
    static bool doSpriteExistWithTag(int sprTag,CCLayer *inLayer);
    
    //CocosBuilder
    static void loadCocosBuilderFileWithPathAndLoader(const char *inPath,const char *loaderName, CCNodeLoader * pCCNodeLoader);
    
    //Rotation
    static void rotateNodeWithClockwiseDirection(CCNode *inNode,bool isClockWise,float duration);
};

#endif
