//
//  DNBackgroundManager.cpp
//  Dominoes
//
//  Created by ICRG LABS on 08/08/12.
//
//

#include "DNBackgroundManager.h"
#include "DNDataManager.h"
#include "DNGameConstants.h"

using namespace cocos2d;

DNBackgroundManager::DNBackgroundManager(void) {
    
    this->gameLayer = DataManager->gameLayer;
    this->createBackground();
    
    this->isReachedLeftEdge = true;
    this->isReachedRightEdge = true;
    this->istouchedPanel = false;
}

DNBackgroundManager::~DNBackgroundManager(void) {

    imageLeft->release();
    textureLeft->release();
    
    imageLeft1->release();
    textureLeft1->release();
    
    imageRight->release();
    textureRight->release();
    
    imageRight1->release();
    textureRight1->release();
}

void DNBackgroundManager::createBackground() {

    imageLeft = new CCImage();
    imageLeft->initWithImageFile("background_2.png");
    textureLeft=new CCTexture2D();
    textureLeft->initWithImage(imageLeft);
    
    imageRight = new CCImage();
    imageRight->initWithImageFile("background_2.png");
    textureRight=new CCTexture2D();
    textureRight->initWithImage(imageRight);
    
    imageLeft1 = new CCImage();
    imageLeft1->initWithImageFile("background_2.png");
    textureLeft1=new CCTexture2D();
    textureLeft1->initWithImage(imageLeft1);
    
    imageRight1 = new CCImage();
    imageRight1->initWithImageFile("background_2.png");
    textureRight1=new CCTexture2D();
    textureRight1->initWithImage(imageRight1);
}


void DNBackgroundManager::draw(){
    
    textureLeft->drawAtPoint(ccp(DataManager->screenSize.width/2 - 640, DataManager->screenSize.height/2 - 384));
    
    textureLeft1->drawAtPoint(ccp(DataManager->screenSize.width/2 - 1920, DataManager->screenSize.height/2 - 384));
    
    textureRight->drawAtPoint(ccp(DataManager->screenSize.width/2 + 640, DataManager->screenSize.height/2 - 384 ));
    
    textureRight1->drawAtPoint(ccp(DataManager->screenSize.width/2 + 1920, DataManager->screenSize.height/2 - 384 ));
}


void DNBackgroundManager::adjustBackgroundToTilePosition(bool isToAdjustLeft,float leftEdgeTilePosition,float rightEdgeTilePosition) {
    
    if (isToAdjustLeft) { // Covering left side

        if (leftEdgeTilePosition < (UIManager->gameBar->getContentSize().width - MainGameLayer->getPosition().x)) {
            
            float leftDifference = -MainGameLayer->getPosition().x - leftEdgeTilePosition;

            CCActionInterval *moveAction = CCMoveTo::create(0.2, ccp((MainGameLayer->getPosition().x  + leftDifference) + UIManager->gameBar->getContentSize().width ,MainGameLayer->getPosition().y));
            MainGameLayer->runAction(moveAction);
            
            this->isReachedLeftEdge = true;
            this->isReachedRightEdge = false;
            
            printf("position is %f",MainGameLayer->getPosition().x);
        }
    }
    else {              // Covering right side

        if (rightEdgeTilePosition >  MainGameLayer->getContentSize().width - MainGameLayer->getPosition().x) {
            
            float rightDifference = rightEdgeTilePosition - (MainGameLayer->getContentSize().width - MainGameLayer->getPosition().x);

            CCActionInterval *moveAction = CCMoveTo::create(0.2, ccp(MainGameLayer->getPosition().x - rightDifference,MainGameLayer->getPosition().y));
            MainGameLayer->runAction(moveAction);
            
            this->isReachedLeftEdge = false;
            this->isReachedRightEdge = true;
        }
    }
}

void DNBackgroundManager::moveBackgroundToCenter() {
    
    CCActionInterval *actionMove = CCMoveTo::create(0.2, ccp(DataManager->screenSize.width/2,DataManager->screenSize.height/2));
    this->gameBackground->runAction(actionMove);
}

void DNBackgroundManager::backgroundManagerTouchesBegan(CCSet *touches) {
    
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint touchPoint = touch->getLocationInView();
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    this->xDifference = MainGameLayer->getPosition().x + MainGameLayer->getContentSize().width/2 - touchPoint.x; 

    CCRect topRect = CCRectMake(0, DataManager->screenSize.height - 100, DataManager->screenSize.width, DataManager->screenSize.height);
    
    if (topRect.containsPoint(touchPoint)) {
        
        this->isTouchedOnTop = true;
    }
}

void DNBackgroundManager::backgroundManagerTouchesMoved(CCSet *touches) {
    
    CCTouch *touch = (CCTouch*)touches->anyObject();
    
    CCPoint touchPoint = touch->getLocationInView();
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    CCPoint previousPoint = touch->getPreviousLocationInView();
    previousPoint = CCDirector::sharedDirector()->convertToGL(previousPoint);
    
    leftDifference = -MainGameLayer->getPosition().x - DominoManager->leftMostEdgeSize;

    rightDifference = DominoManager->rightMostEdgeSize - (MainGameLayer->getContentSize().width - MainGameLayer->getPosition().x);
    
    if(touchPoint.x > previousPoint.x) // background scrolling right side
    {
        if(!istouchedPanel && UIManager->onResume && MainGameLayer->getPosition().x <= 1270){
            
            MainGameLayer->setPosition(MainGameLayer->getPosition().x + 10,0);
        }
        
    }
    else {  // background scrolling left side
        
        if(!istouchedPanel && UIManager->onResume && MainGameLayer->getPosition().x >= -1600){
            
            MainGameLayer->setPosition(MainGameLayer->getPosition().x - 10,0);
            
        }
    }
    
    /*
     float toMovePosition = (touchPoint.x + this->xDifference);
     float toMovePosition = (touchPoint.x + this->xDifference) - MainGameLayer->getContentSize().width/2;
     CCLog("toMovePosition is %f",toMovePosition);
     
     float leftMostMovableXPosition = 0;
     float rightMostMovableXPosition = 1024;
     
     if (DominoManager->leftMostEdgeSize < MainGameLayer->getPosition().x) {
     
     leftMostMovableXPosition = DominoManager->leftMostEdgeSize;
     }
     
     if (DominoManager->rightMostEdgeSize > MainGameLayer->getContentSize().width) {
     
     rightMostMovableXPosition = DominoManager->rightMostEdgeSize; 
     }
     
     //int scrollSide = 3;
     
     if (previousPoint.x < touchPoint.x) { // Right Scroll
     
     //scrollSide = 1;
     this->isSwipedLeft = false;
     }
     else if(previousPoint.x > touchPoint.x) { // Left Scroll
     
     //scrollSide = 2;
     this->isSwipedLeft = true;
     }
     
     int scrollside = 0;
     
     if (scrollside == 2 && toMovePosition > leftMostMovableXPosition && isTouchedOnTop) { // Left Scroll...
     
     CCLog("toMovePosition %f leftMostMovableXPosition %f",toMovePosition,leftMostMovableXPosition);
     MainGameLayer->setPosition(ccp(toMovePosition,MainGameLayer->getPosition().y));
     }
     else if(scrollside == 1 && (toMovePosition + MainGameLayer->getContentSize().width) < rightMostMovableXPosition && isTouchedOnTop) { // Right Scroll...
     
     CCLog("toMovePosition %f rightMostMovableXPosition %f",toMovePosition + MainGameLayer->getContentSize().width,rightMostMovableXPosition);
     MainGameLayer->setPosition(ccp(toMovePosition,MainGameLayer->getPosition().y));
     }
     
     
     if (toMovePosition > leftMostMovableXPosition && toMovePosition < rightMostMovableXPosition && isTouchedOnTop) {
     CCLog("Move Position is %f leftMostMovableXPosition %f rightMostMovableXPosition %f",toMovePosition,leftMostMovableXPosition,rightMostMovableXPosition);
     MainGameLayer->setPosition(ccp(toMovePosition,MainGameLayer->getPosition().y));
     }
     
     if (isTouchedOnTop) { //50189  BC6 12C7010392
     
     MainGameLayer->setPosition(ccp(toMovePosition - MainGameLayer->getContentSize().width/2,MainGameLayer->getPosition().y));
     }
     */
}

void DNBackgroundManager::backgroundManagerTouchesEnded(CCSet *touches) {
    
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint touchPoint = touch->getLocationInView();
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    /*    
     CCPoint aTilePosition = this->gameLayer->convertToWorldSpace(this->gameBackground->getPosition());
     printf("position %f %f converted position %f %f",touchPoint.x,touchPoint.y,aTilePosition.x,aTilePosition.y);
     
     if (this->isTouchedOnTop) {
     
     if (!this->isSwipedLeft && !this->isReachedLeftEdge) {   
     
     float leftDifference = -MainGameLayer->getPosition().x - DominoManager->leftMostEdgeSize;
     
     CCActionInterval *moveAction = CCMoveTo::create(0.2, ccp(MainGameLayer->getPosition().x + leftDifference,MainGameLayer->getPosition().y));
     MainGameLayer->runAction(moveAction);
     
     this->isReachedLeftEdge = true;
     this->isReachedRightEdge = false;
     }
     else if(this->isSwipedLeft  && !this->isReachedRightEdge) {
     
     float rightDifference = DominoManager->rightMostEdgeSize - (MainGameLayer->getContentSize().width - MainGameLayer->getPosition().x);
     
     CCActionInterval *moveAction = CCMoveTo::create(0.2, ccp(MainGameLayer->getPosition().x - rightDifference,MainGameLayer->getPosition().y));
     MainGameLayer->runAction(moveAction);
     
     this->isReachedLeftEdge = false;
     this->isReachedRightEdge = true;
     }
     }
     */
    this->isTouchedOnTop = false;
}

void DNBackgroundManager::backgroundManagerTouchesCancelled(CCSet *touches) {
    
    this->isTouchedOnTop = false;
}
