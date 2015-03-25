//
//  BBMazeGameScene.h
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 13/02/13.
//
//

#ifndef __BaccizBooks__BBMazeGameScene__
#define __BaccizBooks__BBMazeGameScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "BBAStarNode.h"
#include "BBAStarPathNode.h"

USING_NS_CC;
USING_NS_CC_EXT;



class BBMazeGameScene:public CCLayer
{
private:
    BBMazeGameScene();
    ~BBMazeGameScene();
    
public:
     static cocos2d::CCScene* scene();
    
        
    CCArray *gridArray;
    
    CCPointArray *touchArray;
    
    CCPoint gridSize;
    float nodeSpace;  //The space between each node
    CCNode *gridNode; //Where we draw everything
    
    CCDictionary *spritesDict;
    CCPoint touchPointNode; //Where we touched
    bool isTouchedNodeIsNew;
    bool isPathFound;
    
    CCPointArray *foundPathArray;
    //start Point
    CCPoint startCoord;
    //end Point
    CCPoint endCoord;
  
    
    
    CCSprite *spriteBlack;
    
    CCRenderTexture *m_pTarget;
    CCSprite *m_pBrush;

    CCArray *start1Array;
    CCArray *end1Array;
    
    //ui
    void addBgWithObstacles();
   
    void addWall();
    void addGridArt();
    void addNeighborNodeToGridNode(BBAStarNode *node,int x,int y);
    void flipNodeWithTouchedNode();
    
    void findPath();
    bool scanForObstacles(CCPoint point);
    void replaceScene();
    
       
    //update;
    void update(CCTime dt);
    
       
    
    //touches
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
 
    
    
    
};

#endif /* defined(__BaccizBooks__BBMazeGameScene__) */
