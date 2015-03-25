//
//  BBAStarNode.h
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 12/02/13.
//
//

#ifndef __BaccizBooks__BBAStarNode__
#define __BaccizBooks__BBAStarNode__

#include "cocos2d.h"

using namespace cocos2d;

class BBAStarNode: public cocos2d::CCObject  {
    
public:

    BBAStarNode(void);
    ~BBAStarNode(void);
    
    CCPoint position;
    CCSprite *nodeSprite;
    CCArray *neighborNodesArray;
    bool active;
    bool isWall;
    float costMultiplier;
    
    float costToNode(BBAStarNode *node);
    static bool isNodeIsInList(BBAStarNode *a,CCArray *list);
    
       
};


#endif /* defined(__BaccizBooks__BBAStarNode__) */
