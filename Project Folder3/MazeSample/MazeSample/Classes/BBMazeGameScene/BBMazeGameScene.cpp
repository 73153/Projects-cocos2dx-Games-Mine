//
//  BBMazeGameScene.cpp
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 13/02/13.
//
//

#include "BBMazeGameScene.h"


#pragma mark - Scene
CCScene* BBMazeGameScene::scene()
{
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new BBMazeGameScene();
    scene->addChild(layer);
    layer->release();
    return scene;
}

#pragma mark-init
BBMazeGameScene::BBMazeGameScene()
{
        
    this->setTouchEnabled(true);
    this->isPathFound=false;
    //initilise variables
    
    this->gridSize=CCPointMake(64, 49);
    this->nodeSpace=16.0f;
    this->touchPointNode=CCPointMake(0, 0);
    
    this->startCoord=CCPointMake(8, 27);
    
    this->endCoord=CCPointMake(gridSize.x-8, gridSize.y-26);
    this->isTouchedNodeIsNew=false;
    
    this->foundPathArray=CCPointArray::create(1000);
    this->foundPathArray->retain();
    
    //touchArray
    this->touchArray=CCPointArray::create(100);
    this->touchArray->retain();

      
    
    //separate grid node
    this->gridNode=new CCNode();
    gridNode->setPosition(CCPointMake(0, 0));
    
    this->addChild(gridNode,3);
    
        
    this->gridArray=CCArray::createWithCapacity((int)gridSize.x);
    this->gridArray->retain();
    
    
        
    for(int x=0;x<gridSize.x;x++)
    {
        
        
        this->gridArray->addObject(this->gridArray->createWithCapacity((int)gridSize.y));
        
    }
        

  //Create AStar nodes and place them in the grid
    
    for(int x=0;x<gridSize.x;x++)
    {
        for(int y=0;y<gridSize.y;y++)
        {
            
            BBAStarNode* node = new BBAStarNode();
            CCPoint pos;
            
            if(x==8 && y==27)
            {
                pos=CCPointMake(x*nodeSpace+nodeSpace/2, y*nodeSpace+nodeSpace/2);
            }
            else{
                
            pos=CCPointMake(x*nodeSpace+nodeSpace/2, y*nodeSpace+nodeSpace/2);
            }
           
            
            node->position=pos;
                                              
            CCArray *tempArray=(CCArray*)this->gridArray->objectAtIndex(x);
            tempArray->insertObject(node, y);
                     
        }
    }
  
   
   //ADD neighbour nodes
    for(int x=0;x<gridSize.x;x++)
    {
        for(int y=0;y<gridSize.y;y++)
        {
             CCArray *tempArray=(CCArray*)this->gridArray->objectAtIndex(x);
            BBAStarNode *node=(BBAStarNode*)tempArray->objectAtIndex(y);
            node->active=false;
            
            //Add self as neighbor to neighboring nodes
            
            this->addNeighborNodeToGridNode(node, x-1, y-1);
            this->addNeighborNodeToGridNode(node, x-1, y);
            this->addNeighborNodeToGridNode(node, x-1, y+1);
            this->addNeighborNodeToGridNode(node, x, y-1);
           
            
            this->addNeighborNodeToGridNode(node, x, y+1);
            this->addNeighborNodeToGridNode(node, x+1, y-1);
            this->addNeighborNodeToGridNode(node, x+1, y);
            this->addNeighborNodeToGridNode(node, x+1, y+1);
            
            
        }
    }
    
            
    this->addGridArt();
    
    
    
    //render Texture
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    m_pTarget = CCRenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888);
    m_pTarget->retain();
    m_pTarget->setPosition(ccp(s.width / 2, s.height / 2));
    
  
    this->addChild(m_pTarget,5);
    
       // create a brush image to draw into the texture with
    m_pBrush = CCSprite::create("fire.png");
    m_pBrush->setScale(0.5);
    m_pBrush->retain();
   // m_pBrush->setColor(ccRED);
   // m_pBrush->setOpacity(20);
    
    
    
    

    
    //add black sprite
    this->spriteBlack=CCSprite::create("testBG.png");
    this->spriteBlack->setPosition(CCPointMake(512, 384));
    this->addChild(this->spriteBlack,10);
    //this->spriteBlack->setVisible(false);
    //this->spriteBlack->setOpacity(0);
    
    CCDelayTime *actionDelay = CCDelayTime::create(0.2f);
    CCSequence *actionSequence = CCSequence::createWithTwoActions(actionDelay, CCCallFuncN::create(this, callfuncN_selector(BBMazeGameScene::addWall)));
    this->runAction(actionSequence);
    
    CCMenuItemFont *item = CCMenuItemFont::create("Reset", this, menu_selector(BBMazeGameScene::replaceScene));
    item->setPosition(ccp(350,700));
    CCMenu* menu1 = CCMenu::create(item, NULL);
    menu1->setPosition(CCPointZero);
    addChild(menu1,17);
    
    //this->addBgWithObstacles();
  

     
    this->schedule(schedule_selector(BBMazeGameScene::update));
    

    
}
void BBMazeGameScene::addBgWithObstacles()
{
    //Bg
    CCSprite *backGround=CCSprite::create("BG.png");
    this->addChild(backGround,0);
    backGround->setPosition(CCPointMake(512, 384));
    
    //obstacles
    
    CCSprite *ob1=CCSprite::create("lodo.png");
    this->addChild(ob1,1);
    ob1->setPosition(CCPointMake(400, 515));
    
    CCSprite *ob2=CCSprite::create("lodo.png");
    this->addChild(ob2,1);
    ob2->setPosition(CCPointMake(400, 190));
    
    
    CCSprite *ob3=CCSprite::create("hay.png");
    this->addChild(ob3,1);
    ob3->setPosition(CCPointMake(685, 360));
    
    //startPoint
    CCSprite *s=CCSprite::create("farmer.png");
    this->addChild(s,1);
    s->setPosition(CCPointMake(85, 450));
    
    //endPoint
    CCSprite *e=CCSprite::create("vaca.png");
    this->addChild(e,1);
    e->setPosition(CCPointMake(900, 375));

     
    
}

void BBMazeGameScene::replaceScene()
{
    CCDirector::sharedDirector()->replaceScene(BBMazeGameScene::scene());
}

void BBMazeGameScene::update(CCTime dt)
{
    if(this->isPathFound)
    {
        return;
    }

    
    if(this->isTouchedNodeIsNew)
    {
        this->flipNodeWithTouchedNode();
        this->isTouchedNodeIsNew=false;
    }
    
    
    /*
    //To test any path is thr o nt
    
    for(int i=0;i<start1Array->count();i++)
    {
        BBAStarNode *node=(BBAStarNode*)start1Array->objectAtIndex(i);
         for(int m=0;m<end1Array->count();m++)
         {
            BBAStarNode *node1=(BBAStarNode*)end1Array->objectAtIndex(m);
             
              this->foundPathArray=BBAStarPathNode::findPathFromStartToEnd(node, node1);
             if(this->foundPathArray)
             {
                 this->isPathFound=true;
                // CCLog("path found");
                 CCLabelTTF *pathFoundlabel=CCLabelTTF::create("Path Found", "arial", 40);
                 pathFoundlabel->setPosition(CCPointMake(512, 700));
                 this->addChild(pathFoundlabel,15);
                 return;
                 
             }

         }
       
        
    }
    */
    
    CCArray *tempArray=(CCArray*)this->gridArray->objectAtIndex((int)startCoord.x);
    BBAStarNode *startNode=(BBAStarNode*)tempArray->objectAtIndex((int)startCoord.y);
    
    CCArray *tempArray1=(CCArray*)this->gridArray->objectAtIndex((int)endCoord.x);
    BBAStarNode *endNode=(BBAStarNode*)tempArray1->objectAtIndex((int)endCoord.y);

     
     
    this->foundPathArray=BBAStarPathNode::findPathFromStartToEnd(startNode, endNode);
    if(this->foundPathArray)
    {
        this->isPathFound=true;
       // CCLog("path found");
        CCLabelTTF *pathFoundlabel=CCLabelTTF::create("Path Found", "arial", 40);
        pathFoundlabel->setPosition(CCPointMake(512, 700));
        this->addChild(pathFoundlabel,15);
        
           
    }
    
     
 

    
}


bool BBMazeGameScene::scanForObstacles(CCPoint point)
{
      GLubyte pixelColors[4];
    glReadPixels(point.x, point.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixelColors[0]);
    if(pixelColors[0]==0&&pixelColors[1]==0&&pixelColors[0]==0)
    {
        return true;
        
    }
    
    return false;
}
void BBMazeGameScene::addNeighborNodeToGridNode(BBAStarNode *node, int x, int y)
{
    if(x>=0 && y>=0 && x<gridSize.x && y<gridSize.y)
    {
        CCArray *tempArray=(CCArray*)this->gridArray->objectAtIndex(x);
      

        BBAStarNode *nieghbor=( BBAStarNode*)tempArray->objectAtIndex(y);
        node->neighborNodesArray->addObject(nieghbor);
    }
    
}

void BBMazeGameScene::addGridArt()
{
        
    this->spritesDict=CCDictionary::create();
    this->spritesDict->retain();
    
    for(int x=0;x<gridSize.x;x++)
    {
        for(int y=0;y<gridSize.y;y++)
        {
            CCArray *tempArray=(CCArray*)this->gridArray->objectAtIndex(x);
            
            
            BBAStarNode *node=( BBAStarNode*)tempArray->objectAtIndex(y);
            CCSprite *sprite;
            if(x==8 && y==27)
            {
                sprite=CCSprite::create("Icon.png");
                sprite->setScale(1.5);
                 //sprite->setVisible(false);
            }
            else if(x==56&&y==23)
            {
                sprite=CCSprite::create("Icon.png");
                sprite->setScale(1.5);
//                sprite->setVisible(false);
            }
            else{
                 sprite=CCSprite::create("fire.png");
            }
           
            node->nodeSprite=sprite;
            sprite->setPosition(node->position);
            if(node->active)
            {
                sprite->setColor(ccc3(200, 200, 200));
            }
            else if(node->isWall && !node->active)
            {
                sprite->setColor(ccc3(100, 000, 000));
            }
            else
            {
                sprite->setColor(ccc3(100, 100, 100));
            }
            
            this->gridNode->addChild(sprite,2);
            
            CCString *ast = CCString::createWithFormat("%d,%d",x,y);
           // sprite->setVisible(false);
                        
            CCObject *tempObj = (CCObject*)sprite;
            this->spritesDict->setObject(tempObj,ast->getCString());
        }
    }
    
    CCSprite *startSprite=CCSprite::create("start_button.png");
    startSprite->setPosition(CCPointMake(startCoord.x*nodeSpace+nodeSpace/2, startCoord.y*nodeSpace+nodeSpace/2));
    this->gridNode->addChild(startSprite,2);
    
    CCSprite *endSprite=CCSprite::create("end_button.png");
    endSprite->setPosition(CCPointMake(endCoord.x*nodeSpace+nodeSpace/2, endCoord.y*nodeSpace+nodeSpace/2));
    this->gridNode->addChild(endSprite,2);
    
}

void BBMazeGameScene::flipNodeWithTouchedNode()
{
    for(int i=0;i<touchArray->count();i++)
    {
        CCPoint point1=this->touchArray->getControlPointAtIndex(i);
        int x=point1.x;
        int y=point1.y;
        
        if(x==0 && y==0)
        {
            return;
        }
        if(x==gridSize.x-1 && y==gridSize.y-1)
        {
            return;
        }
        if(x<0||y<0||x>gridSize.x-1||y>gridSize.y-1)
        {
            return;
        }
        
        
        CCArray *tempArray =(CCArray*)this->gridArray->objectAtIndex(x);
        BBAStarNode *node=(BBAStarNode*)tempArray->objectAtIndex(y);
        
        CCString *ast = CCString::createWithFormat("%d,%d",x,y);
        CCSprite *sp=(CCSprite*)this->spritesDict->objectForKey(ast->getCString());
        
        if(!node->isWall)
        {
            node->active=true;
            sp->setColor(ccc3(200,200,200));
        }
    }
    
    //Clean the Point Array
    while (touchArray->count()!=0) {
        touchArray->removeControlPointAtIndex(0);
    }
}


    
void BBMazeGameScene::addWall()
{
        
    bool isShouldAddWall;
    
    for(int p=0;p<1024;p=p+6)
    {
        for(int q=0;q<768;q=q+6)
        {
            isShouldAddWall=this->scanForObstacles(CCPointMake(p, q));
            if(isShouldAddWall)
            {
                int m=((p-gridNode->getPositionX())/nodeSpace);
                int n=((q-gridNode->getPositionY())/nodeSpace);
                CCPoint tp=CCPointMake(m, n);
                int x=tp.x;
                int y=tp.y;
                
                if(x==0 && y==0)
                {
                    continue;
                }
                if(x == gridSize.x-1 && y == gridSize.y-1){
                    continue;
                }
                
                if(x < 0 || y < 0 || x > gridSize.x-1 || y > gridSize.y-1){
                    continue;
                }
                
                CCArray *tempArray=(CCArray*)this->gridArray->objectAtIndex(x);
                BBAStarNode *node=(BBAStarNode*)tempArray->objectAtIndex(y);
                node->isWall=true;
                 CCString *ast = CCString::createWithFormat("%d,%d",x,y);
                CCSprite *sprite=(CCSprite*)this->spritesDict->objectForKey(ast->getCString());
                sprite->setColor(ccc3(100, 0, 0));
                node->active=false;
         
            }
        }
    }
    this->spriteBlack->setOpacity(100);


}


#pragma mark-Touches
void BBMazeGameScene::ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent)
{
    
    CCSetIterator it;
    CCTouch* touch;
    //this->createPointArray();
    
    
    for( it = pTouches->begin(); it != pTouches->end(); it++)
    {
        touch = (CCTouch*)(*it);
     
        if(!touch)
            break;
     
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        
//         GLubyte pixelColors[3];
     //   glReadPixels(location.x, location.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixelColors[0]);
//               
     
        //CCLog("pixel color is %f %f %d %d %d",location.x,location.y,pixelColors[0],pixelColors[1],pixelColors[2]);

        
        int x=((location.x-gridNode->getPositionX())/nodeSpace);
        int y=((location.y-gridNode->getPositionY())/nodeSpace);
        
        CCPoint tp=CCPointMake(x, y);
        this->isTouchedNodeIsNew=true;
        this->touchPointNode=tp;
        this->touchArray->addControlPoint(this->touchPointNode);
        

    }
    
}

void BBMazeGameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch1=(CCTouch*)pTouches->anyObject();
    CCPoint start=touch1->getLocation();
    CCPoint end=touch1->getPreviousLocation();
    
    m_pTarget->begin();
    float dist=ccpDistance(start, end);
    if(dist>1)
    {
        int d=(int)dist;
        for(int i=0;i<d;i++)
        {
            float difx=end.x-start.x;
            float dify=end.y-start.y;
            float delta=(float)i/dist;
            CCPoint t1= CCPointMake(start.x + (difx * delta), start.y + (dify * delta));
            
            int x=((t1.x-gridNode->getPositionX())/nodeSpace);
            int y=((t1.y-gridNode->getPositionY())/nodeSpace);
            
            CCPoint tp=CCPointMake(x, y);
            if(tp.x!=this->touchPointNode.x||tp.y!=this->touchPointNode.y)
            {
                this->isTouchedNodeIsNew=true;
                
            }
            this->touchPointNode=tp;
            this->touchArray->addControlPoint(this->touchPointNode);
            
            
            m_pBrush->setPosition(t1);
            m_pBrush->visit();
                             
        }
    
    }
     m_pTarget->end();
  
    
}
void BBMazeGameScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //this->deletePointArray();
    //CCLOG("count is %d",touchArray->count());
    
    
}

#pragma mark-Dealloc
BBMazeGameScene::~BBMazeGameScene()
{
    //CCLog("destructor called");
    m_pBrush->release();
    m_pTarget->release();
    CC_SAFE_RELEASE(this->foundPathArray);
    CC_SAFE_RELEASE(this->gridArray);
    
}
