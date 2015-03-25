//
//  DNDominoManager.cpp
//  Dominoes
//
//  Created by ICRG LABS on 23/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DNDominoManager.h"
#include "DNUIManager.h"
#include "DNDataManager.h"
#include "DNScheduleManager.h"
#include "DNGameConstants.h"
#include "DNUtility.h"
#include "DNDomino.h"
#include "SimpleAudioEngine.h"

DNDominoManager::DNDominoManager(void) {
    
    score = CCLabelTTF::create("", "Arial",50);
    
    DataManager->UILayer->addChild(this->score);
    score->setPosition(ccp(500,500));
    // Assigning Main Layer...
    this->gameLayer = DataManager->gameLayer;
    
    // Initiating Arrays...
    this->dominoesArray = CCArray::create();
    this->dominoesArray->retain();
    
    this->touchesArray = CCArray::create();
    this->touchesArray->retain();
    
    this->lineOfPlayArray = CCArray::create();
    this->lineOfPlayArray->retain();
    
    this->backTileArray = CCArray::create();
    this->backTileArray->retain();
    
    this->playerArray = CCArray::create();
    this->playerArray->retain();
    
    this->opponentOneArray = CCArray::create();
    this->opponentOneArray->retain();
    
    this->opponentTwoArray = CCArray::create();
    this->opponentTwoArray->retain();
    
    // Initialize Values
    this->selectedTile = NULL;
    
    this->isFirstThrow = true;
    
    this->selectedtilecount = 1;
    
    this->passcount = 0;
    
    this->remainingtilecount = 0;
    
    //    this->gameLayer->schedule(schedule_selector(DNDomino::tick));
    
    // Loading the plist...
    const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("DominoProperties.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("btn_animal_timer.plist");
    
    // Getting the dictionaries into...
    this->dominoDetailsDict = CCDictionary::createWithContentsOfFileThreadSafe(pszPath);
    
    // Shuffle Tiles
    this->suffleTiles();
    
    // Dynamically allocating the array!
    this->slots = new int [(DataManager->opponentCount + 1) * UIManager->numberOfTilesPerHead];
    
    // Serving tiles according to number of players
    if (DataManager->opponentCount == 1) {
        
        this->serveTilesForPlayer(0);
        this->serveTilesForPlayer(1);
        UIManager->scaleDownPanels();
        this->assignDownScaleWorldCoordinates();
    }
    else {
        
        this->serveTilesForPlayer(0);
        this->serveTilesForPlayer(1);
        this->serveTilesForPlayer(2);
        UIManager->scaleDownPanels();
        this->assignDownScaleWorldCoordinates();
    }
    
    // Text field...
    CCLabelTTF *dragLabel = CCLabelTTF::create("Drag Tile Here", "Helvetica", 20);
    dragLabel->setPosition(ccp(DataManager->screenSize.width/2+100,DataManager->screenSize.height/2));
    dragLabel->setTag(4444);
    this->gameLayer->addChild(dragLabel);
    
}

DNDominoManager::~DNDominoManager(void) {
    
    CC_SAFE_RELEASE_NULL(this->dominoesArray);
    CC_SAFE_RELEASE_NULL(this->touchesArray);
    CC_SAFE_RELEASE_NULL(this->lineOfPlayArray);
    CC_SAFE_RELEASE_NULL(this->backTileArray);
    CC_SAFE_RELEASE_NULL(this->playerArray);
    CC_SAFE_RELEASE_NULL(this->opponentOneArray);
    CC_SAFE_RELEASE_NULL(this->opponentTwoArray);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("btn_animal_timer.plist");
}

//void DNDominoManager::dominoManagerTick(void) {
//
//}

void DNDominoManager::suffleTiles() {
    
    int i, n, tmp;
    
    // Assigning values
    for (i = 0; i < kTotalNumberOfTiles; ++i) {
        
        //printf("\n i value is %d",i);
        this->suffledValues[i] = i + 1;
    }
    
    // Shuffling the array
    for (i = 0; i < kTotalNumberOfTiles; ++i) {
        
        n = arc4random() % kTotalNumberOfTiles;
        tmp = this->suffledValues[n];
        this->suffledValues[n] = this->suffledValues[i];
        this->suffledValues[i] = tmp;
    }
    
    // Just for Printing
    //    for (i = 0; i < kTotalNumberOfTiles; ++i) {
    //
    //        printf("\n%d ---> %d",i,suffledValues[i]);
    //    }
}


void DNDominoManager::serveTilesForPlayer(int playerNumber) {
    
    for (int i = playerNumber * UIManager->numberOfTilesPerHead; i < (playerNumber + 1) * UIManager->numberOfTilesPerHead; i++) {
        
        char name[20];
        int number = this->suffledValues[i];
        sprintf(name, "Domino%d.png",number);
        
        // Parsing Values from the returned dict! :)
        CCDictionary *tileDict = this->getDetailsOfTile(number);
        const char *tileName = (const char *)tileDict->valueForKey("SpriteName")->getCString();
        int topValue = tileDict->valueForKey("TopValue")->intValue();
        int bottomValue = tileDict->valueForKey("BottomValue")->intValue();
        int id = tileDict->valueForKey("Id")->intValue();
        
        // Creating a tile...
        DNDomino *aDomino = aDomino->spriteWithFrame(tileName);
        aDomino->createSpriteAtPosition(CCPointMake(0,0), id, 1, topValue, bottomValue, i, playerNumber,kPlayerPanelStartingTag+playerNumber + 1,UIManager->numberOfTilesPerHead);
        
        this->dominoesArray->addObject(aDomino);
        
        if(DataManager->opponentCount == 2)
        {
            if(playerNumber == 0 )
            {
                this->playerArray->addObject(aDomino);
                
                DataManager->playerTileCount++;
                CCLOG("player tile count = %d",DataManager->playerTileCount);
                
                if(DataManager->playerTileCount == 5){
                    
                    CCObject *pobj;
                    this->playerScore = 0;
                    
                    CCARRAY_FOREACH( this->playerArray,pobj){
                        
                        DNDomino *aDomino = (DNDomino *)pobj;
                        this->playerScore =  this->playerScore + aDomino->totalValue;
                    }
                    CCLog("playerscore = %d",this->playerScore);
                }
            }
            
            else if(playerNumber == 1)
            {
                this->opponentOneArray->addObject(aDomino);
                
                DataManager->opponentOneTileCount++;
                CCLOG("player tile count = %d",DataManager->opponentOneTileCount);
                
                if(DataManager->opponentOneTileCount == 5)
                {
                    CCObject *pobj;
                    opponentOneScore = 0;
                    
                    CCARRAY_FOREACH(this->opponentOneArray,pobj){
                        
                        DNDomino *aDomino = (DNDomino *)pobj;
                        this-> opponentOneScore = this->opponentOneScore + aDomino->totalValue;
                        
                    }
                    CCLog("opponentOneScore = %d",this->opponentOneScore);
                    
                }
                
            }
            else if(playerNumber == 2)
            {
                this->opponentTwoArray->addObject(aDomino);
                DataManager->opponentTwoTileCount++;
                
                if(DataManager->opponentTwoTileCount == 5)
                {
                    CCObject *pobj;
                    opponentTwoScore = 0;
                    
                    CCARRAY_FOREACH(this->opponentTwoArray,pobj){
                        
                        DNDomino *aDomino = (DNDomino *)pobj;
                        this->opponentTwoScore = this->opponentTwoScore + aDomino->totalValue;
                        
                    }
                    CCLog("opponentTwoScore = %d",this->opponentTwoScore);
                }
            }
            
        }
        if(DataManager->opponentCount == 1)
        {
            if(playerNumber == 0)
            {
                this->playerArray->addObject(aDomino);
                
                DataManager->playerTileCount++;
                CCLOG("player tile count = %d",DataManager->playerTileCount);
                
                if(DataManager->playerTileCount == 7)
                {
                    CCObject *pobj;
                    this->playerScore = 0;
                    
                    CCARRAY_FOREACH( this->playerArray,pobj){
                        
                        DNDomino *aDomino =(DNDomino *)pobj;
                        this->playerScore =  this->playerScore + aDomino->totalValue;
                    }
                    CCLog("playerscore = %d",this->playerScore);
                }
                
            }
            
            else if(playerNumber == 1)
            {
                this->opponentOneArray->addObject(aDomino);
                
                DataManager->opponentOneTileCount++;
                CCLOG("opponentOneTileCount = %d",DataManager->opponentOneTileCount);
                
                if(DataManager->opponentOneTileCount == 7)
                {
                    CCObject *pobj;
                    opponentOneScore = 0;
                    
                    CCARRAY_FOREACH( this->opponentOneArray,pobj){
                        
                        DNDomino *aDomino = (DNDomino *)pobj;
                        this-> opponentOneScore =  this->opponentOneScore + aDomino->totalValue;
                    }
                    CCLog("opponentOneScore = %d",this->opponentOneScore);
                }
            }
        }
        
        this->slots[i] = 1; // Allocating slots values
        
        if (playerNumber != 0) {  // placing the back tile on top of the opponent tiles
            
            DNDomino *ab = aDomino->spriteWithFrame("backTile.png");
            ab->createSpriteAtPosition(CCPointMake(0, 0), id + 50, 2, 10, 10, i, playerNumber,kPlayerPanelStartingTag+playerNumber + 1, UIManager->numberOfTilesPerHead);
            ab->setVisible(true);
            this->backTileArray->addObject(ab);
            
        }
        if(playerNumber == 1){
            
            aDomino->setVisible(false);
        }
        else if(playerNumber == 2){
            
            aDomino->setVisible(false);
        }
    }
}


CCDictionary* DNDominoManager::getDetailsOfTile(int tileNumber) {
    
    // Convert integer into char...
    char dictName[5];
    sprintf(dictName, "%d",tileNumber);
    
    // Getting the desired tile dict...
    CCDictionary *tileDict = (CCDictionary*)this->dominoDetailsDict->objectForKey(dictName);
    
    return tileDict;
}

// Get Next Tile
// Move into Previous Position
// Check for the next tile of the same player
// If present move into previous position

void DNDominoManager::arrangeTilesOfPlayer(int playerNumber, int tileLocation) {
    
    for (int i = tileLocation; i < (playerNumber + 1) * UIManager->numberOfTilesPerHead; i++) {
        
        DNDomino *currentTile = (DNDomino *)this->dominoesArray->objectAtIndex(i);
        
        if (this->isLastTileForPlayer(playerNumber, currentTile->location)) {
            
            break;
        }
        else {
            
            DNDomino *nextTile = (DNDomino *)this->dominoesArray->objectAtIndex(i+1);
            
            if (playerNumber == nextTile->playerID) {
                
                nextTile->setPosition(currentTile->position);
                nextTile->location = currentTile->location;
                
                this->slots[i] = 1;
                this->slots[i+1] = 0;
            }
        }
    }
    
    for (int i = playerNumber * UIManager->numberOfTilesPerHead; i < (playerNumber + 1) * UIManager->numberOfTilesPerHead; i++) {
        
        printf("\n slot[%d] is %d \n",i,slots[i]);
    }
}

bool DNDominoManager::isLastTileForPlayer(int playerNumber, int tileLocation) {
    
    bool isLastTile = true;
    
    for (int i = tileLocation + 1; i < (playerNumber + 1) * UIManager->numberOfTilesPerHead; i++) {
        
        if (this->slots[i] == 1) {
            
            isLastTile = false;
        }
    }
    return isLastTile;
}

int DNDominoManager::numberOfTilesWithPlayer(int playerNumber) {
    
    int numberOfTiles = 0;
    
    for (int i = playerNumber * UIManager->numberOfTilesPerHead; i < (playerNumber + 1) * UIManager->numberOfTilesPerHead; i++) {
        
        if (slots[i] == 1) {
            
            numberOfTiles++;
        }
    }
    return numberOfTiles;
}

/*
 void DNDominoManager::arrangeTilesOfPlayer(int playerNumber) {
 
 printf("(playerNumber + 1) * this->numberOfTilesPerHead is %d",(playerNumber + 1) * this->numberOfTilesPerHead);
 
 CCPoint previousTilePosition;
 for (int i = playerNumber * this->numberOfTilesPerHead; i < (playerNumber + 1) * this->numberOfTilesPerHead; i++) {
 
 DNDomino *aDomino = (DNDomino *)this->dominoesArray->objectAtIndex(i);
 
 if (this->slots[i] == 0) {
 
 int nextNumber = i + 1;
 
 if (nextNumber > (playerNumber + 1) * this->numberOfTilesPerHead) {
 
 nextNumber = i;
 }
 
 DNDomino *aTile = (DNDomino *)this->dominoesArray->objectAtIndex(nextNumber);
 aTile->setPosition(previousTilePosition);
 previousTilePosition = aTile->position;
 aTile->position = aDomino->position;
 this->slots[nextNumber] = 0;
 this->slots[i] = 1;
 }
 }
 
 int internalCounter = 0;
 CCPoint previousTilePosition = CCPointMake(0, 0);
 
 for (int i = playerNumber * this->numberOfTilesPerHead; i < (playerNumber + 1) * this->numberOfTilesPerHead; i++) {
 
 if (slots[i] == 1) {
 
 internalCounter++;
 }
 }
 
 for (int i = playerNumber * this->numberOfTilesPerHead; i < internalCounter; i++) {
 
 if (this->slots[i] == 0) {
 
 int nextTileIndex = i + 1;
 printf("nextTileIndex is %d \n",nextTileIndex);
 
 if (nextTileIndex > internalCounter) {
 
 nextTileIndex = i;
 break;
 }
 
 DNDomino *aTile = (DNDomino *)this->dominoesArray->objectAtIndex(i);
 //previousTilePosition = aTile->position;
 
 DNDomino *nextTile = (DNDomino *)this->dominoesArray->objectAtIndex(nextTileIndex);
 
 if (CCPoint::CCPointEqualToPoint(previousTilePosition, CCPointMake(0, 0)) && nextTile->state != kTileInBoard) {
 
 nextTile->setPosition(aTile->position);
 }
 else if(nextTile->state != kTileInBoard) {
 
 nextTile->setPosition(previousTilePosition);
 }
 
 previousTilePosition = nextTile->position;
 nextTile->position = aTile->position;
 nextTile->location = nextTile->location - 1;
 this->slots[nextTileIndex] = 0;
 this->slots[i] = 1;
 }
 }
 
 for (int i = playerNumber * this->numberOfTilesPerHead; i < (playerNumber + 1) * this->numberOfTilesPerHead; i++) {
 
 printf("\n slot[%d] is %d \n",i,slots[i]);
 }
 }
 */

void DNDominoManager::dominoesManagerTouchesBegan(CCSet *touches) {
    
    //this->suffleTiles();
    //this->serveTiles();
    
    // Getting the touched location...
    CCTouch *touch = (CCTouch *)touches->anyObject();
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
    
    if(!this->gameLayer->uiManager->onPause){
        
        this->getSelectedTile(touch);
    }
    
    // Adding touches to the array...
    this->addTouchToArray(touches);
    
    // Get double tapped angle and release the selected tile...
    this->getDoubleTappedAngleAndNullifySelectedTile();
}

void DNDominoManager::dominoesManagerTouchesMoved(CCSet *touches) {
    
    CCTouch *touch = (CCTouch*)touches->anyObject() ;
    CCPoint touchPoint = touch->getLocationInView() ;
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint) ;
    
    // Multitouch rotation and single touch movement...
    this->rotateAndMoveTile(touchPoint);
}

void DNDominoManager::dominoesManagerTouchesEnded(CCSet *touches) {
    // Removing touches from the array...
    this->removeTouchFromArray(touches);
    
    // Get double tapped angle and release the selected tile...
    this->getDoubleTappedAngleAndNullifySelectedTile();
    
}

void DNDominoManager::dominoesManagerTouchesCancelled(CCSet *touches) {
    
    // Removing touches from the array...
    this->removeTouchFromArray(touches);
}

// Touch Helper functions!
void DNDominoManager::addTouchToArray(CCSet *touches) {
    
    CCSetIterator it;
    
    for( it = touches->begin(); it != touches->end(); it++) {
        
        this->touchesArray->addObject((CCTouch *)*it);
    }
}

void DNDominoManager::removeTouchFromArray(CCSet *touches) {
    
    CCSetIterator it;
    
    for( it = touches->begin(); it != touches->end(); it++) {
        
        this->touchesArray->removeObject((CCTouch *)*it);
    }
}

void DNDominoManager::getSelectedTile(CCTouch *touch) {
    
    UIManager->playerPanel1->getChildByTag(10);
    
    // Convert into point!
    CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
    
    // If no other tiles are selected then select one...
    if (!this->selectedTile) {
        
        // Fast enumuration through the array... For detecting the touched tile...
        CCObject* pObj = NULL;
        
        CCARRAY_FOREACH(this->dominoesArray, pObj) {
            
            DNDomino *aDomino = (DNDomino *)pObj;
            CCRect aTileRect;
            bool canSelectTile = false;
            
            if (aDomino->playerID == 0) {
                
                CCPoint aTilePosition = UIManager->playerPanel1->convertToWorldSpace(aDomino->getPosition());
                
                aTileRect = CCRectMake(aTilePosition.x - aDomino->getContentSize().width/2, aTilePosition.y - aDomino->getContentSize().height/2, aDomino->getContentSize().width, aDomino->getContentSize().height);
                
                if (UIManager->playerPanel1->state == kPanelOpened) {
                    
                    canSelectTile = true;
                }
            }
            else if(aDomino->playerID == 1) {
                
                CCPoint aTilePosition = UIManager->playerPanel2->convertToWorldSpace(aDomino->getPosition());
                
                aTileRect = CCRectMake(aTilePosition.x - aDomino->getContentSize().width/2, aTilePosition.y - aDomino->getContentSize().height/2, aDomino->getContentSize().width, aDomino->getContentSize().height);
                
                if (UIManager->playerPanel2->state == kPanelOpened) {
                    
                    canSelectTile = true;
                }
            }
            else if(aDomino->playerID == 2) {
                
                CCPoint aTilePosition = UIManager->playerPanel3->convertToWorldSpace(aDomino->getPosition());
                
                aTileRect = CCRectMake(aTilePosition.x - aDomino->getContentSize().width/2, aTilePosition.y - aDomino->getContentSize().height/2, aDomino->getContentSize().width, aDomino->getContentSize().height);
                
                if (UIManager->playerPanel3->state == kPanelOpened) {
                    
                    canSelectTile = true;
                }
            }
            
            if (aTileRect.containsPoint(location) && aDomino->state == kTileWithPlayer && canSelectTile && this->selectedtilecount == 1) {
                
                this->selectedTile = aDomino;
                this->selectedTile->touchId = touch->getID();
                
                // Remove from Panel and add it into UILayer
                this->selectedTile->removeFromParentAndCleanup(false);
                DataManager->UILayer->addChild(this->selectedTile);
                this->selectedTile->setPosition(location);
                this->selectedtilecount = 0;
                break;
            }
        }
    }
    
    if (this->selectedTile) {
        
        // Get the starting angle... (Important)
        this->startingAngle = this->selectedTile->getRotation();
    }
}

void DNDominoManager::rotateAndMoveTile(CCPoint touchPoint) {
    
    // Only run the following code if there is more than one touch && a tile must be selected...
    if (this->touchesArray->count() > 1 && this->touchesArray->count() < 3 && this->selectedTile) // Rotate tile on multi touch...
    {
        // Create "UITouch" objects representing each touch
        CCTouch *fingerOne = (CCTouch *)this->touchesArray->objectAtIndex(0);
        CCTouch *fingerTwo = (CCTouch *)this->touchesArray->objectAtIndex(1);
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        CCPoint pointOne = fingerOne->getLocationInView();
        CCPoint pointTwo = fingerTwo->getLocationInView();
        
        pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
        pointTwo = CCDirector::sharedDirector()->convertToGL(pointTwo);
        
        float currentTouchAngle_ = DNUtility::getAngleBetweenPoints(pointOne,pointTwo);
        
        // Main formula to rotate on multitouch...
        this->selectedTile->setRotation(this->startingAngle + (currentTouchAngle_ - this->doubleTappedAngle));
    }
    else if(this->touchesArray->count() == 1 && this->selectedTile) { // Move tile on single touch...
        
        CCTouch *fingerOne = (CCTouch *)this->touchesArray->objectAtIndex(0);
        
        if (fingerOne->getID() == this->selectedTile->touchId) { // Check on the finger Id... First touch can only move the tile...
            
            this->selectedTile->setPosition(touchPoint);
        }
    }
}

void DNDominoManager::getDoubleTappedAngleAndNullifySelectedTile(void) {
    
    if (this->touchesArray->count() == 2) {
        
        CCTouch *fingerOne = (CCTouch *)this->touchesArray->objectAtIndex(0);
        CCTouch *fingerTwo = (CCTouch *)this->touchesArray->objectAtIndex(1);
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        CCPoint pointOne = fingerOne->getLocationInView();
        CCPoint pointTwo = fingerTwo->getLocationInView();
        
        // The touch points are always in "portrait" coordinates - you will need to convert them if in landscape (which we are)
        pointOne = CCDirector::sharedDirector()->convertToGL(pointOne);
        pointTwo = CCDirector::sharedDirector()->convertToGL(pointTwo);
        
        this->doubleTappedAngle = DNUtility::getAngleBetweenPoints(pointOne,pointTwo);
    }
    else if(this->touchesArray->count() == 0 && this->selectedTile) {
        
        // Setting to correct angle...
        
        this->selectedTile->rotateToAppropriateAngle(this->selectedTile->getCurrentAngle());
        
        if(this->selectedTile->checkForCorrectRotation()) {
            
            this->selectedTile->checkCollision();
        }
        else {
            
            // Turn on indicators
            this->selectedTile->tilePlacementIndicator(false);
            //this->selectedTile->moveBackToPlayer();
        }
        // Important...
        this->selectedTile = NULL;
    }
}

// Used to assign the world coordinate for each tile after the panels are scaled down...
void DNDominoManager::assignDownScaleWorldCoordinates() {
    
    // Fast enumuration through the array... For detecting the touched tile...
    CCObject* pObj = NULL;
    
    CCARRAY_FOREACH(this->dominoesArray, pObj) {
        
        DNDomino *aDomino = (DNDomino *)pObj;
        aDomino->scaleDownWorldCoordinate = aDomino->tilesOwnerPanel->convertToWorldSpace(aDomino->getPosition());
    }
}

#pragma mark - AI
// Function for handling AI Move!
/*
 void DNDominoManager::playOpponentMove() {
 
 CCArray *possibleTilesForCurrentPlayer = this->getPossibleTilesForOpponents(ScheduleManager->currentPlayerNumber);
 
 if(DataManager->isGameOver == false){
 
 if (this->possibleTileCount > 0) {
 
 if(DataManager->opponentCount == 2){
 
 if(ScheduleManager->currentPlayerNumber == 1){  //set red colour for opponent1 panel
 
 playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
 playerPanel2->setColor(ccc3(255,0,0));
 
 playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
 playerPanel1->setColor(ccc3(255,255,255));
 
 playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
 playerPanel3->setColor(ccc3(255,255,255));
 }
 else if(ScheduleManager->currentPlayerNumber == 2){  //set red colour for opponent2 panel
 
 playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
 playerPanel3->setColor(ccc3(255,0,0));
 
 playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
 playerPanel2->setColor(ccc3(255,255,255));
 
 playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
 playerPanel1->setColor(ccc3(255,255,255));
 }
 else if(ScheduleManager->currentPlayerNumber == 0){  //set red colour for player panel
 
 playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
 playerPanel1->setColor(ccc3(255,0,0));
 
 playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
 playerPanel3->setColor(ccc3(255,255,255));
 
 playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
 playerPanel2->setColor(ccc3(255,255,255));
 }
 }
 else if(DataManager->opponentCount == 1){
 
 if(ScheduleManager->currentPlayerNumber == 1){
 
 playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
 playerPanel2->setColor(ccc3(255,0,0));
 
 playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
 playerPanel1->setColor(ccc3(255,255,255));
 }
 else if(ScheduleManager->currentPlayerNumber == 0){
 
 playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
 playerPanel1->setColor(ccc3(255,0,0));
 
 playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
 playerPanel2->setColor(ccc3(255,255,255));
 }
 }
 
 if (ScheduleManager->currentPlayerNumber != 0) {
 
 CCObject* pObj = NULL;
 
 CCARRAY_FOREACH(possibleTilesForCurrentPlayer, pObj) {
 
 DNDomino *aDomino = (DNDomino *)pObj;
 
 printf("\n Tile top value = %d , bottom value = %d",aDomino->bottomValue,aDomino->bottomValue);
 }
 
 DNDomino *aDomino = (DNDomino *)possibleTilesForCurrentPlayer->objectAtIndex(0);
 
 // Getting the top dummy tile and remove it
 DNPlayerPanel *holder = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(aDomino->playerID+1+kPlayerPanelStartingTag);
 
 DNDomino *tempDomino = (DNDomino *)holder->getChildByTag(aDomino->getTag() + 50);
 DNDomino *tempDominoToRemoveFromPanel = (DNDomino *)holder->getChildByTag(aDomino->getTag() );
 tempDomino->setVisible(false);
 
 CCLOG("TAG IS = %d",aDomino->getTag());
 
 if(ScheduleManager->currentPlayerNumber == 1){
 
 this->opponentOneArray->removeObject(tempDominoToRemoveFromPanel);
 CCLOG("remainingTiles COUNT = %d",this->opponentOneArray->count());
 }
 else if(ScheduleManager->currentPlayerNumber == 2){
 
 opponentTwoArray->removeObject(tempDominoToRemoveFromPanel);
 CCLOG("leftTiles COUNT = %d",this->opponentTwoArray->count());
 }
 
 tempDomino->removeFromParentAndCleanup(true);
 
 aDomino->setVisible(true);
 
 if(DataManager->opponentCount == 2) {
 
 if(this->gameLayer->scheduleManager->currentPlayerNumber == 1){
 
 DataManager->count = DataManager->count+1;
 CCLog("count = %d",DataManager->count);
 CCLOG("TILE COUNT = %d", DataManager->opponentCount);
 
 if(DataManager->count == 5) {       // youngbunny panel empty
 
 //                       CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
 //
 DataManager->isGameOver = true;
 CCObject* pObj = NULL;
 CCLOG("TILE COUNT = %d", DataManager->opponentCount);
 
 this->youngBunnyExcited();
 this->playerPanel1->giraffePass();
 
 CCARRAY_FOREACH(dominoesArray, pObj) {  // front tiles visible
 
 DNDomino *aDomino = (DNDomino *)pObj;
 aDomino->setVisible(true);
 }
 CCARRAY_FOREACH(backTileArray, pObj) {  // back tiles not visible
 
 DNDomino *aDomino = (DNDomino *)pObj;
 aDomino->setVisible(false);
 }
 
 opponentOneScore = 0;
 CCObject* pobj = NULL;
 playerScore = 0;
 
 CCARRAY_FOREACH(this->playerArray,pobj) {
 
 DNDomino *aDomino = (DNDomino *)pobj;
 playerScore = playerScore + aDomino->totalValue;
 }
 
 CCLOG("totalscoreofplayer = %d", playerScore);
 
 CCDelayTime *delay = CCDelayTime::create(1.0f);
 
 CCCallFunc *callback = CCCallFunc::create(this, callfunc_selector(DNDominoManager::callback));
 
 CCCallFunc *callback1 = CCCallFunc::create(this, callfunc_selector(DNDominoManager::pause));
 
 this->gameLayer->runAction(CCSequence::create(delay,callback1,callback,NULL));
 }
 else
 {
 CCObject* pobj = NULL;
 opponentOneScore = 0;
 
 CCARRAY_FOREACH(opponentOneArray,pobj) {
 
 DNDomino *aDomino = (DNDomino *)pobj;
 opponentOneScore = opponentOneScore + aDomino->totalValue;
 }
 CCLOG("totalscoreofopponent1 = %d",opponentOneScore);
 }
 }
 
 if(this->gameLayer->scheduleManager->currentPlayerNumber == 2) {
 
 DataManager->opponenttilecount = DataManager->opponenttilecount + 1;
 CCLog("opponenttilecount = %d",DataManager->opponenttilecount);
 CCLOG("TILE COUNT = %d",DataManager->count);
 
 if(DataManager->opponenttilecount == 5) {   // giraffe panel empty
 
 //                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
 
 DataManager->isGameOver = true;
 CCObject* pObj = NULL;
 CCLOG("TILE COUNT = %d",DataManager->count);
 
 this->giraffeExcited();
 this->playerPanel1->youngBunnyPass();
 
 CCARRAY_FOREACH(dominoesArray, pObj) {
 
 DNDomino *aDomino = (DNDomino *)pObj;
 aDomino->setVisible(true);
 }
 
 CCARRAY_FOREACH(backTileArray, pObj) {
 
 DNDomino *aDomino = (DNDomino *)pObj;
 aDomino->setVisible(false);
 }
 
 opponentTwoScore = 0;
 CCObject* pobj = NULL;
 
 playerScore = 0;
 
 CCARRAY_FOREACH(playerArray,pobj){
 
 DNDomino *aDomino = (DNDomino *)pobj;
 playerScore = playerScore + aDomino->totalValue;
 }
 
 CCLOG("totalscoreofplayer = %d", playerScore);
 
 CCDelayTime *delay = CCDelayTime::create(1.0f);
 
 CCCallFunc *callback = CCCallFunc::create(this, callfunc_selector(DNDominoManager::callback));
 
 CCCallFunc *callback1 = CCCallFunc::create(this, callfunc_selector(DNDominoManager::pause));
 
 this->gameLayer->runAction(CCSequence::create(delay,callback1,callback,NULL));
 }
 else {
 
 CCObject* pobj = NULL;
 opponentTwoScore = 0;
 
 CCARRAY_FOREACH(opponentTwoArray,pobj) {
 
 DNDomino *ab =(DNDomino *)pobj;
 opponentTwoScore = opponentTwoScore + ab->totalValue;
 }
 CCLOG("totalscoreofopponent2 = %d", opponentTwoScore);
 }
 }
 }
 
 else if(DataManager->opponentCount == 1){
 
 if(this->gameLayer->scheduleManager->currentPlayerNumber == 1){
 
 DataManager->count = DataManager->count + 1;
 CCLog("count = %d",DataManager->count);
 
 if(DataManager->count == 7){  // youngbunny panel empty
 
 aDomino->setVisible(true);
 DataManager->isGameOver = true;
 
 CCObject* pObj = NULL;
 
 DominoManager->youngBunnyExcited();
 
 CCARRAY_FOREACH(dominoesArray, pObj) {
 
 DNDomino *aDomino = (DNDomino *)pObj;
 aDomino->setVisible(true);
 }
 
 CCARRAY_FOREACH(backTileArray, pObj) {
 
 DNDomino *aDomino = (DNDomino *)pObj;
 aDomino->setVisible(false);
 }
 
 opponentOneScore = 0;
 CCObject* pobj = NULL;
 playerScore = 0;
 
 CCARRAY_FOREACH(this->playerArray,pobj) {
 
 DNDomino *aDomino = (DNDomino *)pobj;
 playerScore = playerScore + aDomino->totalValue;
 }
 
 CCLOG("totalscoreofplayer = %d", playerScore);
 
 CCDelayTime *delay = CCDelayTime::create(1.0f);
 
 CCCallFunc *callback = CCCallFunc::create(this, callfunc_selector(DNDominoManager::callback));
 
 CCCallFunc *callback1 = CCCallFunc::create(this, callfunc_selector(DNDominoManager::pause));
 
 this->gameLayer->runAction(CCSequence::create(delay,callback1,callback,NULL));
 }
 else {
 
 CCObject* pobj = NULL;
 opponentOneScore = 0;
 
 CCARRAY_FOREACH(opponentOneArray,pobj) {
 
 DNDomino *aDomino = (DNDomino *)pobj;
 opponentOneScore = opponentOneScore + aDomino->totalValue;
 }
 CCLOG("totalscoreofopponent1 = %d", opponentOneScore);
 }
 }
 }
 
 if(aDomino->movementDetail.isHorizontal) {
 
 aDomino->isVertical = false;
 aDomino->isHorizontal = true;
 }
 else {
 
 aDomino->isVertical = false;
 aDomino->isHorizontal = true;
 }
 
 aDomino->updateValuesForTile();
 
 if (aDomino->movementDetail.isAvailableForLeftMovement) {
 
 aDomino->arrangeTileOnBoard(true);
 aDomino->rotateTileForAI(aDomino->movementDetail.leftRotationAngle);
 }
 else {
 
 aDomino->arrangeTileOnBoard(false);
 aDomino->rotateTileForAI(aDomino->movementDetail.rightRotationAngle);
 }
 }
 }
 else {
 
 int panelTag = UIManager->getCurrentPlayerPanelTag(ScheduleManager->currentPlayerNumber);
 CCLog("tag is %d",panelTag);
 
 //      CCMenu *tempItem = (CCMenu *)(DataManager->UILayer->getChildByTag(panelTag+1000));
 //      tempItem->setVisible(true);
 
 if(ScheduleManager->currentPlayerNumber == 1){  // opponent1 pass
 
 //            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle Word Balloon Sound_1.mp3");
 
 tempItem1 = (CCMenu *)(DataManager->UILayer->getChildByTag(panelTag+1000));
 tempItem1->setVisible(true);
 
 CCSprite *spr = (CCSprite*)(DataManager->UILayer->getChildByTag(panelTag+100));
 spr->setVisible(true);
 
 passcount++;
 CCLOG("PASS COUNT1 = %d",passcount);
 
 playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
 playerPanel2->setColor(ccc3(255,0,0));
 
 playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
 playerPanel1->setColor(ccc3(255,255,255));
 
 if(DataManager->opponentCount == 2)
 {
 playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
 playerPanel3->setColor(ccc3(255,255,255));
 }
 
 CCObject* pobj = NULL;
 opponentOneScore = 0;
 
 CCARRAY_FOREACH(opponentOneArray,pobj) {
 
 DNDomino *aDomino = (DNDomino *)pobj;
 opponentOneScore = opponentOneScore  + aDomino->totalValue;
 }
 CCLOG("totalscoreofopponent1 = %d",opponentOneScore);
 }
 if(DataManager->opponentCount == 2) {
 
 if(ScheduleManager->currentPlayerNumber == 2){  // opponent2 pass
 
 tempItem2 = (CCMenu *)(DataManager->UILayer->getChildByTag(panelTag+1000));
 tempItem2->setVisible(true);
 
 CCSprite *spr = (CCSprite*)(DataManager->UILayer->getChildByTag(panelTag+100));
 spr->setVisible(true);
 passcount++;
 CCLOG("PASS COUNT1 = %d", passcount);
 CCObject* pobj = NULL;
 opponentTwoScore = 0;
 
 playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
 playerPanel3->setColor(ccc3(255,0,0));
 
 playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
 playerPanel2->setColor(ccc3(255,255,255));
 
 playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
 playerPanel1->setColor(ccc3(255,255,255));
 
 CCARRAY_FOREACH(opponentTwoArray,pobj) {
 
 DNDomino *ab = (DNDomino *)pobj;
 opponentTwoScore = opponentTwoScore + ab->totalValue;
 }
 CCLOG("totalscoreofopponent2 = %d", opponentTwoScore);
 }
 }
 if(ScheduleManager->currentPlayerNumber == 0){  // player pass
 
 //            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle Word Balloon Sound_1.mp3");
 
 tempItem0 = (CCMenu *)(DataManager->UILayer->getChildByTag(panelTag+1000));
 tempItem0->setVisible(true);
 
 tempItem0->setColor(ccc3(0, 255, 0));
 tempItem0->setEnabled(true);
 
 passcount++;
 CCLOG("PASS COUNT1 = %d", passcount);
 
 CCObject* pobj = NULL;
 playerScore = 0;
 
 playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
 playerPanel1->setColor(ccc3(255,255,255));
 
 if(DataManager->opponentCount == 2)
 {
 playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
 playerPanel3->setColor(ccc3(255,255,255));
 
 }
 playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
 playerPanel2->setColor(ccc3(255,255,255));
 
 CCARRAY_FOREACH(this->playerArray,pobj) {
 
 DNDomino *aDomino = (DNDomino *)pobj;
 playerScore =playerScore + aDomino->totalValue;
 }
 
 CCLOG("totalscoreofplayer = %d", playerScore);
 
 
 //            CCSprite *spr = (CCSprite*)(DataManager->UILayer->getChildByTag(panelTag+100));
 //            spr->setVisible(false);
 }
 if(DataManager->opponentCount == 2){
 
 if(passcount == 4){   // no player has matched tiles to be placed
 
 DataManager->isGameOver = true;
 CCObject* pObj = NULL;
 
 this->playerPanel1->youngBunnyPass();
 this->playerPanel1->giraffePass();
 
 CCARRAY_FOREACH(dominoesArray, pObj) {
 
 DNDomino *aDomino = (DNDomino *)pObj;
 aDomino->setVisible(true);
 }
 
 CCARRAY_FOREACH(backTileArray, pObj) {
 
 DNDomino *aDomino = (DNDomino *)pObj;
 aDomino->setVisible(false);
 }
 CCObject* pobj = NULL;
 playerScore = 0;
 
 CCARRAY_FOREACH(playerArray,pobj) {
 
 DNDomino *aDomino = (DNDomino *)pobj;
 playerScore = playerScore + aDomino->totalValue;
 }
 
 CCLOG("totalscoreofplayer = %d",playerScore);
 
 CCDelayTime *delay = CCDelayTime::create(1.0f);
 
 CCCallFunc *callback = CCCallFunc::create(this,callfunc_selector(DNDominoManager::callback));
 
 CCCallFunc *callback1 = CCCallFunc::create(this,callfunc_selector(DNDominoManager::pause));
 
 this->gameLayer->runAction(CCSequence::create(delay,callback1,callback,NULL));
 }
 }
 else  if(DataManager->opponentCount == 1)
 {
 if(passcount == 3){    // when none of the player has matched tiles to be placed
 
 this->playerPanel1->youngBunnyPass();
 
 DataManager->isGameOver = true;
 CCObject* pObj = NULL;
 
 CCARRAY_FOREACH(dominoesArray, pObj) {
 
 DNDomino *aDomino = (DNDomino *)pObj;
 aDomino->setVisible(true);
 }
 
 CCARRAY_FOREACH(backTileArray, pObj) {
 
 DNDomino *aDomino = (DNDomino *)pObj;
 aDomino->setVisible(false);
 }
 
 CCObject* pobj = NULL;
 playerScore = 0;
 
 CCARRAY_FOREACH(playerArray,pobj) {
 
 DNDomino *aDomino = (DNDomino *)pobj;
 playerScore = playerScore + aDomino->totalValue;
 }
 
 CCLOG("totalscoreofplayer = %d",playerScore);
 
 CCDelayTime *delay = CCDelayTime::create(1.0f);
 CCCallFunc *callback = CCCallFunc::create(this, callfunc_selector(DNDominoManager::callback));
 CCCallFunc *callback1 = CCCallFunc::create(this,callfunc_selector(DNDominoManager::pause));
 
 this->gameLayer->runAction(CCSequence::create(delay,callback1,callback,NULL));
 }
 }
 }
 }
 }
 */

void DNDominoManager::playOpponentMove() {
    
    CCArray *possibleTilesForCurrentPlayer = this->getPossibleTilesForOpponents(ScheduleManager->currentPlayerNumber);
    
    if(DataManager->isGameOver == false){
        
        if (this->possibleTileCount > 0) {
            
            if(DataManager->opponentCount == 2){
                
                if(ScheduleManager->currentPlayerNumber == 1){
                    
                    playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
                    playerPanel2->setColor(ccc3(255,0,0));
                    //                  this->playerPanel2 = this->playerPanel2->spriteWithFrame("opponent_area_01.png");
                    
                    playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
                    playerPanel1->setColor(ccc3(255,255,255));
                    //                  this->playerPanel1 = this->playerPanel1->spriteWithFrame("player_area_not-in-play.png");
                    playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
                    playerPanel3->setColor(ccc3(255,255,255));
                    
                    //                  this->playerPanel3 = this->playerPanel3->spriteWithFrame("opponent_area_02_not_in_play.png");
                }
                else if(ScheduleManager->currentPlayerNumber == 2){
                    
                    
                    playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
                    playerPanel3->setColor(ccc3(255,0,0));
                    //                  this->playerPanel3 = this->playerPanel3->spriteWithFrame("opponent_area_02.png");
                    
                    playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
                    playerPanel2->setColor(ccc3(255,255,255));
                    //                  this->playerPanel2 = this->playerPanel2->spriteWithFrame("opponent_area_01_not_in_play.png");
                    
                    playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
                    playerPanel1->setColor(ccc3(255,255,255));
                    //                  this->playerPanel1 = this->playerPanel1->spriteWithFrame("player_area_not-in-play.png");
                    
                }
                else if(ScheduleManager->currentPlayerNumber == 0){
                    
                    
                    playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
                    playerPanel1->setColor(ccc3(255,0,0));
                    //                  this->playerPanel1 = this->playerPanel1->spriteWithFrame("player_area.png");
                    
                    playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
                    playerPanel3->setColor(ccc3(255,255,255));
                    //                  this->playerPanel3 = this->playerPanel3->spriteWithFrame("opponent_area_02.png");
                    
                    playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
                    playerPanel2->setColor(ccc3(255,255,255));
                    //                  this->playerPanel2 = this->playerPanel2->spriteWithFrame("opponent_area_01_not_in_play.png");
                }
            }
            else if(DataManager->opponentCount == 1)
            {
                if(ScheduleManager->currentPlayerNumber == 1){
                    
                    playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
                    playerPanel2->setColor(ccc3(255,0,0));
                    
                    playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
                    playerPanel1->setColor(ccc3(255,255,255));
                }
                else if(ScheduleManager->currentPlayerNumber == 0){
                    
                    playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
                    playerPanel1->setColor(ccc3(255,0,0));
                    
                    playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
                    playerPanel2->setColor(ccc3(255,255,255));
                }
            }
            
            if (ScheduleManager->currentPlayerNumber != 0) {
                
                CCObject* pObj = NULL;
                
                CCARRAY_FOREACH(possibleTilesForCurrentPlayer, pObj) {
                    
                    DNDomino *aDomino = (DNDomino *)pObj;
                    
                    printf("\n Tile top value = %d bottom value is = %d",aDomino->bottomValue,aDomino->bottomValue);
                }
                
                DNDomino *aDomino = (DNDomino *)possibleTilesForCurrentPlayer->objectAtIndex(0);
                
                // Getting the top dummy tile and remove it
                DNPlayerPanel *holder = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(aDomino->playerID + 1 + kPlayerPanelStartingTag);
                
                DNDomino *tempDomino = (DNDomino *)holder->getChildByTag(aDomino->getTag() + 50);
                DNDomino *tempDominoToRemoveFromPanel = (DNDomino *)holder->getChildByTag(aDomino->getTag() );
                tempDomino->setVisible(false);
                
                CCLOG("TAG IS = %d",aDomino->getTag());
                
                if(ScheduleManager->currentPlayerNumber == 1)
                {
                    this->opponentOneArray->removeObject(tempDominoToRemoveFromPanel);
                    CCLOG("remainingTiles COUNT = %d",this->opponentOneArray->count());
                }
                else if(ScheduleManager->currentPlayerNumber == 2)
                {
                    opponentTwoArray->removeObject(tempDominoToRemoveFromPanel);
                    CCLOG("leftTiles COUNT = %d",this->opponentTwoArray->count());
                }
                
                tempDomino->removeFromParentAndCleanup(true);
                
                aDomino->setVisible(true);
                
                if(DataManager->opponentCount == 2) {
                    
                    if(this->gameLayer->scheduleManager->currentPlayerNumber == 1){
                        
                        DataManager->count = DataManager->count + 1;
                        CCLog("count = %d",DataManager->count);
                        CCLOG("TILE COUNT = %d",  DataManager->opponentCount);
                        
                        
                        if(DataManager->count == 5) {       // youngbunny panel empty
                            
                            //                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
                            
                            DataManager->isGameOver = true;
                            CCObject* pObj = NULL;
                            CCLOG("TILE COUNT = %d", DataManager->opponentCount);
                            
                            this->youngBunnyExcited();
                            this->playerPanel1->giraffePass();
                            
                            CCARRAY_FOREACH(dominoesArray, pObj) {
                                
                                DNDomino *aDomino = (DNDomino *)pObj;
                                aDomino->setVisible(true);
                            }
                            
                            CCARRAY_FOREACH(backTileArray, pObj) {
                                
                                DNDomino *aDomino = (DNDomino *)pObj;
                                aDomino->setVisible(false);
                            }
                            
                            opponentOneScore = 0;
                            CCObject* pobj = NULL;
                            playerScore = 0;
                            
                            CCARRAY_FOREACH(this->playerArray,pobj) {
                                
                                DNDomino *aDomino = (DNDomino *)pobj;
                                playerScore = playerScore + aDomino->totalValue;
                            }
                            CCLOG("totalscoreofplayer = %d",  playerScore);
                            
                            CCDelayTime *delay = CCDelayTime::create(1.0f);
                            
                            CCCallFunc *gameover = CCCallFunc::create(this, callfunc_selector(DNDominoManager::callback));
                            
                            CCCallFunc *pause = CCCallFunc::create(this,callfunc_selector(DNDominoManager::pause));
                            
                            this->gameLayer->runAction(CCSequence::create(delay,gameover,pause,NULL));
                        }
                        else
                        {
                            CCObject* pobj = NULL;
                            opponentOneScore = 0;
                            
                            CCARRAY_FOREACH(opponentOneArray,pobj) {
                                
                                DNDomino *aDomino = (DNDomino *)pobj;
                                opponentOneScore = opponentOneScore + aDomino->totalValue;
                            }
                            CCLOG("totalscoreofopponent1 = %d",opponentOneScore);
                        }
                    }
                    
                    if(this->gameLayer->scheduleManager->currentPlayerNumber == 2) {
                        
                        DataManager->opponenttilecount = DataManager->opponenttilecount + 1;
                        CCLog("opponenttilecount = %d",DataManager->opponenttilecount);
                        CCLOG("TILE COUNT = %d",  DataManager->count);
                        
                        
                        if(DataManager->opponenttilecount == 5) {   // giraffe panel empty
                            
                            //                            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
                            
                            DataManager->isGameOver = true;
                            CCObject* pObj = NULL;
                            CCLOG("TILE COUNT = %d",  DataManager->count);
                            
                            this->giraffeExcited();
                            this->playerPanel1->youngBunnyPass();
                            
                            CCARRAY_FOREACH(dominoesArray, pObj) {
                                
                                DNDomino *aDomino = (DNDomino *)pObj;
                                aDomino->setVisible(true);
                            }
                            
                            CCARRAY_FOREACH(backTileArray, pObj) {
                                
                                DNDomino *aDomino = (DNDomino *)pObj;
                                aDomino->setVisible(false);
                            }
                            
                            opponentTwoScore = 0;
                            CCObject* pobj = NULL;
                            
                            playerScore = 0;
                            
                            CCARRAY_FOREACH(playerArray,pobj){
                                
                                DNDomino *aDomino = (DNDomino *)pobj;
                                playerScore = playerScore + aDomino->totalValue;
                            }
                            CCLOG("totalscoreofplayer = %d", playerScore);
                            
                            
                            CCDelayTime *delay = CCDelayTime::create(1.0f);
                            
                            CCCallFunc *gameover = CCCallFunc::create(this, callfunc_selector(DNDominoManager::callback));
                            
                            CCCallFunc *pause = CCCallFunc::create(this, callfunc_selector(DNDominoManager::pause));
                            
                            this->gameLayer->runAction(CCSequence::create(delay,gameover,pause,NULL));
                        }
                        else {
                            
                            CCObject* pobj = NULL;
                            opponentTwoScore = 0;
                            
                            CCARRAY_FOREACH(opponentTwoArray,pobj) {
                                
                                DNDomino *ab = (DNDomino *)pobj;
                                opponentTwoScore = opponentTwoScore + ab->totalValue;
                            }
                            CCLOG("totalscoreofopponent2 = %d", opponentTwoScore);
                        }
                    }
                }
                
                else if(DataManager->opponentCount == 1)
                {
                    if(this->gameLayer->scheduleManager->currentPlayerNumber == 1)
                    {
                        DataManager->count = DataManager->count + 1;
                        CCLog("count = %d",DataManager->count);
                        
                        if(DataManager->count == 7)
                        {
                            aDomino->setVisible(true);
                            
                            DataManager->isGameOver = true;
                            
                            CCObject* pObj = NULL;
                            
                            DominoManager->youngBunnyExcited();
                            
                            CCARRAY_FOREACH(dominoesArray, pObj) {
                                
                                DNDomino *aDomino = (DNDomino *)pObj;
                                aDomino->setVisible(true);
                            }
                            
                            CCARRAY_FOREACH(backTileArray, pObj) {
                                
                                DNDomino *aDomino = (DNDomino *)pObj;
                                aDomino->setVisible(false);
                            }
                            
                            opponentOneScore = 0;
                            CCObject* pobj = NULL;
                            playerScore = 0;
                            
                            CCARRAY_FOREACH(this->playerArray,pobj) {
                                
                                DNDomino *aDomino = (DNDomino *)pobj;
                                playerScore = playerScore + aDomino->totalValue;
                            }
                            
                            CCLOG("totalscoreofplayer = %d", playerScore);
                            
                            
                            CCDelayTime *delay = CCDelayTime::create(1.0f);
                            
                            CCCallFunc *gameover = CCCallFunc::create(this, callfunc_selector(DNDominoManager::callback));
                            
                            CCCallFunc *pause = CCCallFunc::create(this, callfunc_selector(DNDominoManager::pause));
                            
                            this->gameLayer->runAction(CCSequence::create(delay,gameover,pause,NULL));
                        }
                        else
                        {
                            
                            CCObject* pobj = NULL;
                            opponentOneScore = 0;
                            
                            CCARRAY_FOREACH(opponentOneArray,pobj) {
                                
                                DNDomino *aDomino = (DNDomino *)pobj;
                                opponentOneScore = opponentOneScore + aDomino->totalValue;
                            }
                            CCLOG("totalscoreofopponent1 = %d", opponentOneScore);
                        }
                    }
                }
                
                if(aDomino->movementDetail.isHorizontal)
                {
                    
                    aDomino->isVertical = false;
                    aDomino->isHorizontal = true;
                }
                else
                {
                    
                    aDomino->isVertical = false;
                    aDomino->isHorizontal = true;
                }
                
                aDomino->updateValuesForTile();
                
                if (aDomino->movementDetail.isAvailableForLeftMovement)
                {
                    
                    aDomino->arrangeTileOnBoard(true);
                    aDomino->rotateTileForAI(aDomino->movementDetail.leftRotationAngle);
                }
                else
                {
                    
                    aDomino->arrangeTileOnBoard(false);
                    aDomino->rotateTileForAI(aDomino->movementDetail.rightRotationAngle);
                }
            }
        }
        else {
            
            int panelTag = UIManager->getCurrentPlayerPanelTag(ScheduleManager->currentPlayerNumber);
            CCLog("tag is %d",panelTag);
            
            //      CCMenu *tempItem = (CCMenu *)(DataManager->UILayer->getChildByTag(panelTag+1000));
            //      tempItem->setVisible(true);
            
            if(ScheduleManager->currentPlayerNumber == 1){
                
                
                //                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle Word Balloon Sound_1.mp3");
                
                tempItem1 = (CCMenu *)(DataManager->UILayer->getChildByTag(panelTag+1000));
                tempItem1->setVisible(true);
                CCSprite *spr = (CCSprite*)(DataManager->UILayer->getChildByTag(panelTag+100));
                spr->setVisible(true);
                //tempItem0->setColor(ccc3(255,255,255));
                passcount++;
                CCLOG("PASS COUNT1 = %d", passcount);
                CCObject* pobj = NULL;
                
                playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
                playerPanel2->setColor(ccc3(255,0,0));
                //                  this->playerPanel2 = this->playerPanel2->spriteWithFrame("opponent_area_01.png");
                
                playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
                playerPanel1->setColor(ccc3(255,255,255));
                //                  this->playerPanel1 = this->playerPanel1->spriteWithFrame("player_area_not-in-play.png");
                if(DataManager->opponentCount == 2)
                {
                    playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
                    playerPanel3->setColor(ccc3(255,255,255));
                }
                opponentOneScore = 0;
                
                CCARRAY_FOREACH(opponentOneArray,pobj) {
                    
                    DNDomino *aDomino = (DNDomino *)pobj;
                    opponentOneScore = opponentOneScore + aDomino->totalValue;
                }
                CCLOG("totalscoreofopponent1 = %d", opponentOneScore);
                
                
            }
            if(DataManager->opponentCount == 2)
            {
                if(ScheduleManager->currentPlayerNumber == 2){
                    
                    //                playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
                    //                playerPanel3->setColor(ccc3(255,0,0));
                    
                    tempItem2 = (CCMenu *)(DataManager->UILayer->getChildByTag(panelTag+1000));
                    tempItem2->setVisible(true);
                    //tempItem0->setColor(ccc3(255,255,255));
                    CCSprite *spr = (CCSprite*)(DataManager->UILayer->getChildByTag(panelTag+100));
                    spr->setVisible(true);
                    passcount++;
                    CCLOG("PASS COUNT1 = %d", passcount);
                    CCObject* pobj = NULL;
                    opponentTwoScore = 0;
                    
                    playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
                    playerPanel3->setColor(ccc3(255,0,0));
                    //                  this->playerPanel3 = this->playerPanel3->spriteWithFrame("opponent_area_02.png");
                    
                    playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
                    playerPanel2->setColor(ccc3(255,255,255));
                    //                  this->playerPanel2 = this->playerPanel2->spriteWithFrame("opponent_area_01_not_in_play.png");
                    
                    playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
                    playerPanel1->setColor(ccc3(255,255,255));
                    
                    CCARRAY_FOREACH(opponentTwoArray,pobj) {
                        
                        DNDomino *ab = (DNDomino *)pobj;
                        opponentTwoScore = opponentTwoScore + ab->totalValue;
                    }
                    CCLOG("totalscoreofopponent2 = %d", opponentTwoScore);
                }
                
            }
            
            if(ScheduleManager->currentPlayerNumber == 0){
                
                //                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle Word Balloon Sound_1.mp3");
                
                tempItem0 = (CCMenu *)(DataManager->UILayer->getChildByTag(panelTag+1000));
                tempItem0->setVisible(true);
                tempItem0->setColor(ccc3(0, 255, 0));
                tempItem0->setEnabled(true);
                passcount++;
                CCLOG("PASS COUNT1 = %d", passcount);
                CCObject* pobj = NULL;
                playerScore = 0;
                
                playerPanel1 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel1Tag);
                playerPanel1->setColor(ccc3(255,0,0));
                //                  this->playerPanel1 = this->playerPanel1->spriteWithFrame("player_area.png");
                if(DataManager->opponentCount == 2)
                {
                    playerPanel3 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel3Tag);
                    playerPanel3->setColor(ccc3(255,255,255));
                    //                  this->playerPanel3 = this->playerPanel3->spriteWithFrame("opponent_area_02.png");
                }
                playerPanel2 = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(kPlayerPanel2Tag);
                playerPanel2->setColor(ccc3(255,255,255));
                
                CCARRAY_FOREACH(this->playerArray,pobj) {
                    
                    DNDomino *aDomino = (DNDomino *)pobj;
                    playerScore = playerScore + aDomino->totalValue;
                }
                
                CCLOG("totalscoreofplayer = %d",  playerScore);
                
                
                //            CCSprite *spr = (CCSprite*)(DataManager->UILayer->getChildByTag(panelTag+100));
                //            spr->setVisible(false);
            }
            if(DataManager->opponentCount == 2){
                
                if(passcount == 4){   // no player has matched tiles to be placed
                    
                    DataManager->isGameOver = true;
                    CCObject* pObj = NULL;
                    
                    this->playerPanel1->youngBunnyPass();
                    this->playerPanel1->giraffePass();
                    
                    CCARRAY_FOREACH(dominoesArray, pObj) {
                        
                        DNDomino *aDomino = (DNDomino *)pObj;
                        aDomino->setVisible(true);
                    }
                    
                    CCARRAY_FOREACH(backTileArray, pObj) {
                        
                        DNDomino *aDomino = (DNDomino *)pObj;
                        aDomino->setVisible(false);
                    }
                    CCObject* pobj = NULL;
                    playerScore = 0;
                    
                    CCARRAY_FOREACH(playerArray,pobj) {
                        
                        DNDomino *aDomino = (DNDomino *)pobj;
                        playerScore = playerScore + aDomino->totalValue;
                    }
                    
                    CCLOG("totalscoreofplayer = %d",playerScore);
                    
                    CCDelayTime *delay = CCDelayTime::create(1.0f);
                    
                    CCCallFunc *gameover = CCCallFunc::create(this, callfunc_selector(DNDominoManager::callback));
                    
                    CCCallFunc *pause = CCCallFunc::create(this, callfunc_selector(DNDominoManager::pause));
                    
                    this->gameLayer->runAction(CCSequence::create(delay,gameover,pause,NULL));
                }
            }
            else  if(DataManager->opponentCount == 1)
            {
                if(passcount == 3){    // when none of the player has matched tiles to be placed
                    
                    this->playerPanel1->youngBunnyPass();
                    
                    DataManager->isGameOver = true;
                    CCObject* pObj = NULL;
                    
                    CCARRAY_FOREACH(dominoesArray, pObj) {
                        
                        DNDomino *aDomino = (DNDomino *)pObj;
                        aDomino->setVisible(true);
                    }
                    
                    CCARRAY_FOREACH(backTileArray, pObj) {
                        
                        DNDomino *aDomino = (DNDomino *)pObj;
                        aDomino->setVisible(false);
                    }
                    
                    CCObject* pobj = NULL;
                    playerScore = 0;
                    
                    CCARRAY_FOREACH(playerArray,pobj) {
                        
                        DNDomino *aDomino = (DNDomino *)pobj;
                        playerScore = playerScore + aDomino->totalValue;
                    }
                    
                    CCLOG("totalscoreofplayer = %d",playerScore);
                    
                    CCDelayTime *delay = CCDelayTime::create(1.0f);
                    CCCallFunc *gameover = CCCallFunc::create(this, callfunc_selector(DNDominoManager::callback));
                    CCCallFunc *pause = CCCallFunc::create(this,callfunc_selector(DNDominoManager::pause));
                    
                    this->gameLayer->runAction(CCSequence::create(delay,gameover,pause,NULL));
                }
            }
        }
    }
}


void DNDominoManager::youngBunnyExcited() {
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("dominoes_new.plist");
    
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("youngbunny-excited0001.png");
    sprite->setPosition(ccp(sprite->getContentSize().width/5 + 340,sprite->getPosition().y + 75));
    
    this->gameLayer->uiManager->playerPanel2->addChild(sprite);
    
    CCArray *animFrames = CCArray::create();
    char tmp[50];
    
    for (int j = 1; j <= 6; j++){
        
        sprintf(tmp, "youngbunny-excited000%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        animFrames->addObject(frame);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
    sprite->runAction(CCAnimate::create(animation));
    sprite->setRotation(180);
}


void DNDominoManager::giraffeExcited() {
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("dominoes_new.plist");
    
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("giraffe-excited0001.png");
    sprite->setPosition(ccp(sprite->getContentSize().width/5 + 340,sprite->getPosition().y + 75));
    
    this->gameLayer->uiManager->playerPanel3->addChild(sprite);
    
    CCArray *animFrames = CCArray::create();
    char tmp[50];
    
    for (int j = 1; j <= 6; j++){
        
        sprintf(tmp, "giraffe-excited000%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        animFrames->addObject(frame);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3f);
    sprite->runAction(CCAnimate::create(animation));
    sprite->setRotation(180);
}

void DNDominoManager::callback(){
    
    DataManager->isGameOver = true;
    
    clockLabel = CCLabelTTF::create("", "Arial",50);
    DataManager->UILayer->addChild(clockLabel,1);
    clockLabel->setColor(ccc3(0,255,0));
    clockLabel->setPosition(ccp(650,307));
    clockLabel->setVisible(true);
    
    char clk[1000];
    sprintf(clk,"%d seconds",DataManager->min);
    clockLabel->setString(clk);
    
    this->gameLayer->uiManager->actionMenu->setEnabled(false);
    this->gameLayer->uiManager->mainMenu->setEnabled(false);
    this->gameLayer->uiManager->playersMenu->setEnabled(false);
    //    this->gameLayer->playerpanel->passMenu->setEnabled(false);
    
    CCLOG("playerscore = %d", playerScore);
    CCLOG("opponentOnescore = %d", opponentOneScore);
    CCLOG("opponentTwoscore = %d", opponentTwoScore);
    
    spr = CCSprite::create("end_game_lose_empty.png");
    DataManager->UILayer->addChild(spr);
    spr->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2));
    
    gamerWinBackGrd = CCSprite::create("gamerWinbackgrd.png");
    DataManager->UILayer->addChild(gamerWinBackGrd);
    gamerWinBackGrd->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 ));
    gamerWinBackGrd->setVisible(false);
    
    CCSprite *spr1 = CCSprite::create("bg.png");
    DataManager->UILayer->addChild(spr1);
    spr1->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2));
    
    
    cup = CCSprite::createWithSpriteFrameName("cup.png");
    DataManager->UILayer->addChild(cup);
    cup->setVisible(false);
    
    CCSprite *clock = CCSprite::createWithSpriteFrameName("clock.png");
    clock->setPosition(ccp(DataManager->screenSize.width/2 - 30, DataManager->screenSize.height/2 - 70));
    DataManager->UILayer->addChild(clock,1);
    
    ziraffe = CCSprite::createWithSpriteFrameName("giraffe.png");
    DataManager->UILayer->addChild(ziraffe);
    ziraffe->setVisible(false);
    
    rabit = CCSprite::createWithSpriteFrameName("rabbit.png");
    DataManager->UILayer->addChild(rabit);
    cup->setVisible(false);
    
    
    playerName = CCSprite::createWithSpriteFrameName("irenet.png");
    DataManager->UILayer->addChild(playerName);
    playerName->setVisible(false);
    
    opponentOneName = CCSprite::create("rabbit_txt.png");
    DataManager->UILayer->addChild(opponentOneName);
    opponentOneName->setVisible(false);
    
    opponentTwoName = CCSprite::create("giraffe_txt.png");
    DataManager->UILayer->addChild(opponentTwoName);
    opponentTwoName->setVisible(false);
    
    
    opponentOneLabel = CCLabelTTF::create("", "Arial",50);
    DataManager->UILayer->addChild(opponentOneLabel);
    opponentOneLabel->setColor(ccc3(0,255,0));
    
    opponentTwoLabel = CCLabelTTF::create("", "Arial",50);
    DataManager->UILayer->addChild(opponentTwoLabel);
    opponentTwoLabel->setColor(ccc3(0,255,0));
    
    playerLabel = CCLabelTTF::create("", "Arial",50);
    DataManager->UILayer->addChild( playerLabel);
    playerLabel->setColor(ccc3(0,255,0));
    
    //    set score position for the players
    if(DataManager->opponentCount == 2){
        
        if(playerScore <= opponentOneScore && playerScore <= opponentTwoScore){  // player win
            
            //            zigzag = CCParticleSystemQuad::create("snake.plist");
            //            DataManager->UILayer->addChild(zigzag,0);
            //            zigzag->setPosition(ccp(200, 384));
            
            if(opponentOneScore <= opponentTwoScore){
                
                opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                opponentOneName->setVisible(true);
                opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                rabit->setVisible(true);
                rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 100));
                
                opponentTwoLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                opponentTwoName->setVisible(true);
                opponentTwoName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 10));
                ziraffe->setVisible(true);
                ziraffe->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 10));
            }
            else{
                
                opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                opponentOneName->setVisible(true);
                opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 10));
                rabit->setVisible(true);
                rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 10));
                
                opponentTwoLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                opponentTwoName->setVisible(true);
                opponentTwoName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                ziraffe->setVisible(true);
                ziraffe->setPosition(ccp(DataManager->screenSize.width/2 -  150, DataManager->screenSize.height/2 + 100));
            }
            
            char a[10]={0};
            sprintf(a,"%d",opponentOneScore);
            opponentOneLabel->setString(a);
            
            char b[10]={0};
            sprintf(b,"%d",opponentTwoScore);
            opponentTwoLabel->setString(b);
            
            char c[10]={0};
            sprintf(c,"%d",playerScore);
            playerLabel->setString(c);
            
            spr->setVisible(false);
            gamerWinBackGrd->setVisible(true);
            
            cup->setVisible(true);
            
            cup->setPosition(ccp(DataManager->screenSize.width/2 + 150, DataManager->screenSize.height/2 + 200));
            playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 200));
            playerName->setVisible(true);
            playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 200));
            
            //            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Yay.mp3");
        }
        else if(opponentOneScore <= playerScore && opponentOneScore <= opponentTwoScore){  // opponent1 win
            
            if(playerScore <= opponentTwoScore){
                
                
                playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                playerName->setVisible(true);
                playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                
                opponentTwoLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                opponentTwoName->setVisible(true);
                opponentTwoName->setPosition(ccp(DataManager->screenSize.width/2 -50 , DataManager->screenSize.height/2 + 10));
                ziraffe->setVisible(true);
                ziraffe->setPosition(ccp(DataManager->screenSize.width/2 - 150 , DataManager->screenSize.height/2 + 10));
                
            }
            
            else{
                
                playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                playerName->setVisible(true);
                playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 10));
                
                opponentTwoLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                opponentTwoName->setVisible(true);
                opponentTwoName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                ziraffe->setVisible(true);
                ziraffe->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 100));
            }
            
            char a[10]={0};
            sprintf(a,"%d",opponentOneScore);
            opponentOneLabel->setString(a);
            
            char b[10]={0};
            sprintf(b,"%d",opponentTwoScore);
            opponentTwoLabel->setString(b);
            
            char c[10]={0};
            sprintf(c,"%d",playerScore);
            playerLabel->setString(c);
            
            cup->setVisible(true);
                
            cup->setPosition(ccp(DataManager->screenSize.width/2 + 150, DataManager->screenSize.height/2 + 200));
            
            opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 45,DataManager->screenSize.height/2 + 200));
            opponentOneName->setVisible(true);
            opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50,DataManager->screenSize.height/2 + 200));
            rabit->setVisible(true);
            rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150 ,DataManager->screenSize.height/2 + 200));
            
            //            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
        }
        
        else if(opponentTwoScore <= playerScore && opponentTwoScore <= opponentOneScore){
            
            if(playerScore <= opponentOneScore){  // opponent2 wins
                
                opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                opponentOneName->setVisible(true);
                opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 10));
                rabit->setVisible(true);
                rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 10));
                
                playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                playerName->setVisible(true);
                playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
            }
            else{
                
                opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                opponentOneName->setVisible(true);
                opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                rabit->setVisible(true);
                rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 100));
                
                playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                playerName->setVisible(true);
                playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 10));
            }
            
            char a[10]={0};
            sprintf(a,"%d",opponentOneScore);
            opponentOneLabel->setString(a);
            
            char b[10]={0};
            sprintf(b,"%d",opponentTwoScore);
            opponentTwoLabel->setString(b);
            
            char c[10]={0};
            sprintf(c,"%d",playerScore);
            playerLabel->setString(c);
            
            cup->setPosition(ccp(DataManager->screenSize.width/2 + 200, DataManager->screenSize.height/2 + 100));
            
            opponentTwoLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 200));
            opponentTwoName->setVisible(true);
            opponentTwoName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 200));
            ziraffe->setVisible(true);
            ziraffe->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 200));
            
            //            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
        }
    }
    else if(DataManager->opponentCount == 1) {  //display score for 2 players
        
        if(playerScore <= opponentOneScore){  // player win
            
            //            zigzag = CCParticleSystemQuad::create("snake.plist");
            //            DataManager->UILayer->addChild(zigzag,0);
            //            zigzag->setPosition(ccp(200, 384));
            opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
            opponentOneName->setVisible(true);
            opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
            rabit->setVisible(true);
            rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 100));
            
            playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 200));
            playerName->setVisible(true);
            playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 200));
            
            gamerWinBackGrd->setVisible(true);
            spr->setVisible(false);
            
            //            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Yay.mp3");
        }
        else{
            
            opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 200));
            opponentOneName->setVisible(true);
            opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 200));
            rabit->setVisible(true);
            rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 200));
            
            playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
            playerName->setVisible(true);
            playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
            
            //            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
        }
        
        char a[10]={0};
        sprintf(a,"%d",opponentOneScore);
        opponentOneLabel->setString(a);
        cup->setVisible(true);
        cup->setPosition(ccp(700,570));
        
        char c[10]={0};
        sprintf(c,"%d",playerScore);
        playerLabel->setString(c);
        
    }
    
    CCSprite *ok_normal = CCSprite::createWithSpriteFrameName("ok_btn1.png");
    CCSprite *ok_selected = CCSprite::createWithSpriteFrameName("ok_pressed.png");
    
    CCMenuItemSprite* restartItem = CCMenuItemSprite::create(ok_normal, ok_selected, this, menu_selector(DNDominoManager::restart));
    CCMenu *mainMenu = CCMenu::create(restartItem,NULL);
    mainMenu->alignItemsVerticallyWithPadding(5);
    mainMenu->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2-175));
    
    DataManager->UILayer->addChild(mainMenu);
    DataManager->count = 0;
    DataManager->opponenttilecount = 0;
}


void DNDominoManager::pause()
{
    this->gameLayer->uiManager->onPause = true;
    
    DataManager->UILayer->setTouchEnabled(false);
    
    if(DataManager->isGameOver == true){
        
        if(this->gameLayer->uiManager->onPause){
            
            CCDirector::sharedDirector()->pause();
        }
    }
}


void DNDominoManager::restart()
{
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle_Click.mp3");
    //    playerPanel1->passMenu->setEnabled(true);
    
    DataManager->isGameOver = false;
    DataManager->gameLayer->restartScene();
    DataManager->count = 0;
    DataManager->playerTileCount = 0;
    DataManager->opponenttilecount = 0;
    DataManager->opponentOneTileCount = 0;
    DataManager->opponentTwoTileCount = 0;
    
    DataManager->min = 0;
    DataManager->sec = 0;
    
    CCDirector::sharedDirector()->resume();
    
    //    DataManager->UILayer->removeChild(zigzag, true);
    
    this->gameLayer->uiManager->actionMenu->setEnabled(true);
    this->gameLayer->uiManager->mainMenu->setEnabled(true);
    this->gameLayer->uiManager->playersMenu->setEnabled(true);
}

// Function will get the number of possible tiles to be moved by the opponent (AI)
CCArray* DNDominoManager::getPossibleTilesForOpponents(int playerNumber) {
    
    CCArray *possibleTilesArray = CCArray::create();
    this->possibleTileCount = 0;
    
    // Fast enumeration through the array... For detecting the touched tile...
    CCObject* pObj = NULL;
    
    CCARRAY_FOREACH(this->dominoesArray, pObj) {
        
        DNDomino *aDomino = (DNDomino *)pObj;
        
        if (aDomino->playerID == playerNumber && aDomino->state == kTileWithPlayer) {
            
            // First making sure their properties are resetting
            aDomino->movementDetail.isAvailableForLeftMovement = false;
            aDomino->movementDetail.isAvailableForRightMovement = false;
            aDomino->movementDetail.isVertical = false;
            aDomino->movementDetail.leftRotationAngle = 0;
            aDomino->movementDetail.rightRotationAngle = 0;
            
            // Checking for availability
            aDomino->movementDetail.isAvailableForLeftMovement = this->checkCurrentTileValueForEdgeValues(true, aDomino, possibleTilesArray);
            aDomino->movementDetail.isAvailableForRightMovement = this->checkCurrentTileValueForEdgeValues(false, aDomino, possibleTilesArray);
            
            if (aDomino->movementDetail.isAvailableForLeftMovement || aDomino->movementDetail.isAvailableForRightMovement) {
                
                this->possibleTileCount++;
                passcount = 0;
            }
        }
    }
    return possibleTilesArray;
}

// Helper function for getPossibleTilesForOpponents! It'll return the passed tile will be matched for either side...
bool DNDominoManager::checkCurrentTileValueForEdgeValues(bool isLeft, DNDomino *tile, CCArray *possibleTilesArray) {
    
    bool isMatched = false;
    
    //CCLog("left most value is %d right most value is %d",this->leftTileValue,this->rightTileValue);
    
    if (isLeft) {
        
        if(tile->topValue == tile->bottomValue && tile->topValue == edgeTile.left->getCurrentAnglesTileValues(true, edgeTile.left)) {
            
            tile->movementDetail.leftRotationAngle = 90;
            tile->movementDetail.isVertical = true;
            possibleTilesArray->addObject(tile);
            
            isMatched = true;
        }
        else {
            
            if(tile->topValue == edgeTile.left->getCurrentAnglesTileValues(true, edgeTile.left)) {
                
                isMatched = true;
                tile->movementDetail.leftRotationAngle = 90;
                possibleTilesArray->addObject(tile);
            }
            if (tile->bottomValue == edgeTile.left->getCurrentAnglesTileValues(true, edgeTile.left)) {
                
                isMatched = true;
                tile->movementDetail.leftRotationAngle = 270;
                possibleTilesArray->addObject(tile);
            }
        }
    }
    else {
        
        if(tile->topValue == tile->bottomValue && tile->topValue == edgeTile.right->getCurrentAnglesTileValues(false, edgeTile.right)) {
            
            tile->movementDetail.rightRotationAngle = 90;
            tile->movementDetail.isVertical = true;
            possibleTilesArray->addObject(tile);
            isMatched = true;
        }
        else {
            
            if(tile->topValue == edgeTile.right->getCurrentAnglesTileValues(false, edgeTile.right)) {
                
                isMatched = true;
                tile->movementDetail.rightRotationAngle = 270;
                possibleTilesArray->addObject(tile);
            }
            if (tile->bottomValue == edgeTile.right->getCurrentAnglesTileValues(false, edgeTile.right)) {
                
                isMatched = true;
                tile->movementDetail.rightRotationAngle = 90;
                possibleTilesArray->addObject(tile);
            }
        }
    }
    return isMatched;
}

