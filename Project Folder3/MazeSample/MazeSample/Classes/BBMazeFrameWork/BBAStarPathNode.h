//
//  BBAStarPathNode.h
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 12/02/13.
//
//

#ifndef __BaccizBooks__BBAStarPathNode__
#define __BaccizBooks__BBAStarPathNode__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BBAStarNode.h"


USING_NS_CC;
USING_NS_CC_EXT;


using namespace cocos2d;

class BBAStarPathNode: public cocos2d::CCObject
{
public:
    BBAStarPathNode();
    ~BBAStarPathNode();
    
    

    BBAStarNode *node;
    BBAStarPathNode *previousNode;
    float cost;
    
    
    static BBAStarPathNode* createWithAstarNode(BBAStarNode *node);
    static CCPointArray* findPathFromStartToEnd(BBAStarNode *fromNode,BBAStarNode *toNode);
    static  BBAStarPathNode* lowestCostInArray(CCArray *a);
    static  bool isPathNodeIsInList(BBAStarPathNode *a,CCArray *list);
    
    
};



#endif /* defined(__BaccizBooks__BBAStarPathNode__) */
