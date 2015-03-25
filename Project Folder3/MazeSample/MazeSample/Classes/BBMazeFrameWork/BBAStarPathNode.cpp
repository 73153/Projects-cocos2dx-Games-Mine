//
//  BBAStarPathNode.cpp
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 12/02/13.
//
//

#include "BBAStarPathNode.h"
#include "CCValue.h"
#include "CCNumber.h"

BBAStarPathNode::BBAStarPathNode()
{
    this->cost=0.0f;
    
}
BBAStarPathNode::~BBAStarPathNode()
{
}

BBAStarPathNode* BBAStarPathNode::createWithAstarNode(BBAStarNode *node)
{
    if(!node)
    {
        return NULL;
    }
    
    BBAStarPathNode *pathNode=new BBAStarPathNode();
    pathNode->node=node;
    return pathNode;
    
}

CCPointArray* BBAStarPathNode::findPathFromStartToEnd(BBAStarNode *fromNode, BBAStarNode *toNode)
{
    CCPointArray *foundPathArray=CCPointArray::create(1000);
    foundPathArray->retain();
    
    if(fromNode->position.x==toNode->position.x && fromNode->position.y==toNode->position.y)
    {
        return NULL;
    }
    
    CCArray *openList=CCArray::create();
    openList->retain();
    
    CCArray *closedList=CCArray::create();
    closedList->retain();
    
    BBAStarPathNode *currentNode=NULL;
    BBAStarPathNode *aNode=NULL;
    
    
    BBAStarPathNode *startNode = BBAStarPathNode::createWithAstarNode(fromNode);
	BBAStarPathNode *endNode = BBAStarPathNode::createWithAstarNode(toNode);
    
    openList->addObject(startNode);
    
    while(openList->count()>0)
    {
        
        currentNode=BBAStarPathNode::lowestCostInArray(openList);
        if(currentNode->node->position.x==endNode->node->position.x && currentNode->node->position.y==endNode->node->position.y)
        {
            
            
            
            /*
             //Path Found!
             aNode = currentNode;
             while(aNode.previous != nil){
             //Mark path
             [foundPath addObject:[NSValue valueWithCGPoint: CGPointMake(aNode.node.position.x, aNode.node.position.y)]];
             aNode = aNode.previous;
             }
             [foundPath addObject:[NSValue valueWithCGPoint: CGPointMake(aNode.node.position.x, aNode.node.position.y)]];
             */
            
            //Path Found!
            aNode=currentNode;
            while(aNode->previousNode!=NULL)
            {
                foundPathArray->addControlPoint(CCPointMake(aNode->node->position.x, aNode->node->position.y));
                aNode=aNode->previousNode;
                
            }
            
            
            foundPathArray->addControlPoint(CCPointMake(aNode->node->position.x, aNode->node->position.y));
            
            
            delete startNode;
            delete endNode;
            
            CC_SAFE_RELEASE(openList);
            CC_SAFE_RELEASE(closedList);
            
            
            
            return foundPathArray;
            
        }
        else{
            //still searching
            
            closedList->addObject(currentNode);
            openList->removeObject(currentNode);
            
            for(int i=0;i<currentNode->node->neighborNodesArray->count();i++)
            {
                BBAStarNode *sampleNode=(BBAStarNode*)currentNode->node->neighborNodesArray->objectAtIndex(i);
                
                BBAStarPathNode *aNode=(BBAStarPathNode::createWithAstarNode(sampleNode));
                
                
                float a=currentNode->node->costToNode(aNode->node);
                float b=aNode->node->costToNode(endNode->node);
                
                
                aNode->cost=currentNode->cost+a+b;
                
                aNode->previousNode=currentNode;
                
                if(aNode->node->active && !(BBAStarPathNode::isPathNodeIsInList(aNode, openList))&& !(BBAStarPathNode::isPathNodeIsInList(aNode, closedList)) )
                {
                    openList->addObject(aNode);
                }
                //delete aNode;
                
            }
        }
        
        
    }
    
    CC_SAFE_RELEASE(openList);
    CC_SAFE_RELEASE(closedList);
    CC_SAFE_RELEASE(foundPathArray);


    
    //NO path Found
    
    return NULL;
    
}


BBAStarPathNode* BBAStarPathNode::lowestCostInArray(CCArray *a)
{
    BBAStarPathNode *lowest=NULL;
    for(int i=0;i<a->count();i++)
    {
    BBAStarPathNode *node=(BBAStarPathNode*)a->objectAtIndex(i);
        if(!lowest||node->cost<lowest->cost)
        {
            lowest=node;
        }
    }
    
    return lowest;
    
    
}
bool BBAStarPathNode::isPathNodeIsInList(BBAStarPathNode *a, cocos2d::CCArray *list)
{
    for(int i=0;i<list->count();i++)
    {
        BBAStarPathNode *b=(BBAStarPathNode*)list->objectAtIndex(i);
        if(a->node->position.x==b->node->position.x && a->node->position.y==b->node->position.y)
        {
            return true;
        }
            
    }
    return false;
}
