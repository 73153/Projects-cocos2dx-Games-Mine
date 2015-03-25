//
//  BBAStarNode.cpp
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 12/02/13.
//
//

#include "BBAStarNode.h"

BBAStarNode::BBAStarNode()
{
    this->active=true;
    this->isWall=false;
    this->neighborNodesArray=CCArray::create();
    this->neighborNodesArray->retain();
    this->costMultiplier=1.0f;
    
}
BBAStarNode::~BBAStarNode()
{
    CC_SAFE_RELEASE_NULL(this->neighborNodesArray);
}

float BBAStarNode::costToNode(BBAStarNode *node)
{
    CCPoint src=CCPointMake(this->position.x, this->position.y);
    CCPoint dst=CCPointMake(node->position.x, node->position.y);
    //sqrt( pow( (p1.x-p2.x) ,2) + pow( (p1.y-p2.y) ,2) );
    
    
    float cost=ccpDistance(src, dst)*node->costMultiplier;
    return cost;
}
bool BBAStarNode::isNodeIsInList(BBAStarNode *a, cocos2d::CCArray *list)
{
    for(int i=0;i<list->count();i++)
    {
        BBAStarNode *b=(BBAStarNode*)list->objectAtIndex(i);
        if(a->position.x==b->position.x && a->position.y==b->position.y)
        {
            return true;
        }
        
    }
    return false;
}