//
//  DNDomino.cpp
//  Dominoes
//
//  Created by ICRG LABS on 23/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DNDomino.h"
#include "DNGameConstants.h"
#include "DNBackgroundManager.h"
#include "DNPlayerPanel.h"
#include "DNDataManager.h"
#include "DNBackground.h"
#include "DNGameManager.h"
#include "SimpleAudioEngine.h" 

//PlacementDetailsObject::PlacementDetailsObject(void) { }

//PlacementDetailsObject::~PlacementDetailsObject() {}

DNDomino::DNDomino(void) { 
    
    this->gameLayer = DataManager->gameLayer;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("btn_animal_timer.plist");
    
    schedule(schedule_selector(DNDomino::startTimer),1.0f);
}

DNDomino::~DNDomino(void) {

    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("btn_animal_timer.plist");
}

// To create separate sprite from file...
DNDomino* DNDomino::spriteWithFile(const char *pszFileName) {
    
    DNDomino *pobSprite = new DNDomino();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        //pobSprite->scheduleUpdate();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

// To create sprite from sprite sheet!
DNDomino* DNDomino::spriteWithFrame(const char *pszFileName) {
    
    //CCLog("name is %s",pszFileName);
    
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszFileName);
    
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszFileName);
    CCAssert(pFrame != NULL, msg);
    
    DNDomino *tempSpr = DNDomino::create(pFrame);
    
    return tempSpr;
}

DNDomino* DNDomino::create(CCSpriteFrame *pSpriteFrame) {
    
    DNDomino *pobSprite = new DNDomino();
    if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void DNDomino::createSpriteAtPosition(CCPoint position,int tag, int zOrder, int topValue, int bottomValue, int locationInRow, int playerID, int panelTag, int numberOfTilesPerPlayer) {
    
    DNPlayerPanel *holder = (DNPlayerPanel*)DataManager->UILayer->getChildByTag(panelTag);
    
    CCPoint startingPoint = CCPointZero;
    
    if (playerID == 0) {
        
        startingPoint = ccp(holder->getContentSize().width/2 - (numberOfTilesPerPlayer/2 * this->getContentSize().width),(holder->getContentSize().height - 20) - this->getContentSize().height/2);
        this->setPosition(ccp(startingPoint.x + (locationInRow * this->getContentSize().width) , startingPoint.y));
        this->position = ccp(startingPoint.x + (locationInRow * this->getContentSize().width) , startingPoint.y);
    }
    else {
        
        startingPoint = ccp(holder->getContentSize().width/2 - (numberOfTilesPerPlayer/2 * this->getContentSize().width), this->getContentSize().height/2+155);
        
        this->setPosition(ccp(startingPoint.x + (locationInRow % numberOfTilesPerPlayer * (this->getContentSize().width+10)-25) , startingPoint.y));
        
        this->position = ccp(startingPoint.x + (locationInRow % numberOfTilesPerPlayer * this->getContentSize().width) , startingPoint.y);
    }
       this->setTag(tag);
    this->state = kTileWithPlayer;
    
    this->topValue = topValue;
    this->bottomValue = bottomValue;
    this->totalValue = topValue + bottomValue;
    this->location = locationInRow;
    this->playerID = playerID;
    
    this->isLeftCollidable = true;
    this->isRightCollidable = true;
    
    this->tilesOwnerPanel = holder;
    
    holder->addChild(this);
    
    this->worldPosition = holder->convertToWorldSpace(this->getPosition());
}


void DNDomino::startTimer()
{
    DataManager->sec++;
    
    if (DataManager->sec % 20 == 0) {
        
        DataManager->min++;
        CCLog("min = %d minutes",DataManager->min);
    }
}

// Main Collision Detection between the tiles on board!
void DNDomino::checkCollision() {
    
    bool isPlaced = false;
   
    if (DominoManager->isFirstThrow && DataManager->boardCenterRect.containsPoint(this->getPosition())) {                           // for first throw...
                
        DominoManager->isHorizontal = true;
        DominoManager->isVertical = false;

        this->gameLayer->backgroundManager->istouchedPanel = false;
        isPlaced = true;
        
//         CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle Thud.mp3");
        
        this->gameLayer->dominoManager->playerArray->removeObject(this);
        
        CCLOG("remainingTiles COUNT = %d",this->gameLayer->dominoManager->playerArray->count());
        
        this->gameLayer->dominoManager->passcount = 0;
        this->gameLayer->dominoManager->selectedtilecount = 0;
        
        int tiles = --UIManager->numberOfTilesPerHead;
        this->gameLayer->dominoManager->playerScore = 0;
        
        CCObject* pobj = NULL;
        CCARRAY_FOREACH(this->gameLayer->dominoManager->playerArray,pobj){
       
            DNDomino *aDomino =(DNDomino *)pobj;
            this->gameLayer->dominoManager-> playerScore = this->gameLayer->dominoManager->playerScore+ aDomino->totalValue;
        }
        CCLog("playerscore = %d",this->gameLayer->dominoManager->playerScore);
              
        CCLog("tiles = %d",tiles);
        
        this->state = kTileInBoard;
        
        this->isLeftCollidable = true;
        this->isRightCollidable = true;
        
        DominoManager->isFirstThrow = false;
        
        DominoManager->slots[this->location] = 0;
        
        // Removing the label
        DataManager->gameLayer->removeChildByTag(4444, true);
        
        CCPoint convertedPosition = MainGameLayer->convertToNodeSpace(this->getPosition());
        
        // Removing from UILayer and adding into background layer
        DataManager->UILayer->removeChild(this, false);
        MainGameLayer->addChild(this);
        
        this->setPosition(convertedPosition);
        
        CCActionInterval *actionMove = CCMoveTo::create(0.2, ccp(MainGameLayer->getContentSize().width/2+UIManager->gameBar->getContentSize().width/2,MainGameLayer->getContentSize().height/2));
        
        this->runAction(actionMove);
        
        this->tilePlacementIndicator(true);
        
        this->tilesOwnerPanel->closePanel(); // Closing the panel once it's placed correctly...
               
        DominoManager->edgeTile.left = this;
        DominoManager->edgeTile.right = this;
        
        // Adding the first tile into the line of play array...
        DominoManager->lineOfPlayArray->addObject(this);
         
        scheduleOnce(schedule_selector(DNDomino::updateCallBack), 3.0f); // Giving turn to the next player...
    }
    else if(!DominoManager->isFirstThrow) { // Checking collision with the other tiles
        
        // Fast enumuration through the array... For detecting the touched tile...
        CCObject* pObj = NULL;

        CCARRAY_FOREACH(DominoManager->dominoesArray, pObj) {
        
            DNDomino *aDomino = (DNDomino *)pObj;
            
            CCPoint aTilePosition = MainGameLayer->convertToWorldSpace(aDomino->getPosition());
            CCRect aTileRect = CCRectMake(aTilePosition.x - aDomino->getContentSize().width/2,aTilePosition.y - aDomino->getContentSize().height/2, aDomino->getContentSize().width, aDomino->getContentSize().height);
            
            if (aDomino->isEqual(this) || aDomino->state != kTileInBoard) { // Don't check collision with the same tile and check collision only with the tiles on the board...
                
                continue;
            }
            else if (aTileRect.intersectsRect(this->boundingBox())) {
                
                PlacementDetailsObject obj = this->checkTileEdgePointsMatched(aDomino);
                CCLog("top value is %d bottom value is %d",aDomino->topValue,aDomino->bottomValue);
                isPlaced = obj.isPlaced;
                
                this->gameLayer->backgroundManager->istouchedPanel=true;
                
                if (isPlaced) {
                    
//                     CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle Thud.mp3");
                    
                int tiles = -- UIManager->numberOfTilesPerHead;
                CCLog("tiles = %d",tiles);
                    
                this->gameLayer->dominoManager->playerArray->removeObject(this);
                    
                CCLOG("remainingTiles COUNT = %d",this->gameLayer->dominoManager->playerArray->count());
                  
                this->gameLayer->dominoManager->selectedtilecount = 0;
                this->gameLayer->dominoManager->passcount = 0;
                this->gameLayer->dominoManager->playerScore = 0;
                    
                CCObject* pobj = NULL;
                CCARRAY_FOREACH( this->gameLayer->dominoManager->playerArray,pobj){
                        
                    DNDomino *aDomino = (DNDomino *)pobj;
                    this->gameLayer->dominoManager-> playerScore = this->gameLayer->dominoManager->playerScore + aDomino->totalValue;
                                                
                }
                CCLog("playerscore = %d",this->gameLayer->dominoManager-> playerScore);

                if(tiles == 0){  // gamer wins
                        
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Yay.mp3");

                    this->gameLayer->dominoManager->playerScore = 0;
                    DataManager->isGameOver = true;
                    
                    CCObject* pObj = NULL;
                        
                    if (DataManager->opponentCount == 2) {
                            
                        this->playerWinAnimation();
                    }
                    else if (DataManager->opponentCount == 1) {
                            
                        this->playerWinAnimationForOneOpponent();
                    }
                    
                    CCARRAY_FOREACH(this->gameLayer->dominoManager->dominoesArray, pObj) {
                           
                        DNDomino *aDomino = (DNDomino *)pObj;
                        aDomino->setVisible(true);
                        valuecount = this->totalValue;
                        CCLog("valuecount = %d",valuecount);
                    }  
                    CCARRAY_FOREACH(this->gameLayer->dominoManager->backTileArray, pObj) {
                            
                        DNDomino *aDomino = (DNDomino *)pObj;
                        aDomino->setVisible(false);
                    }
                    
                    CCObject* pobj = NULL;
                    this->gameLayer->dominoManager->opponentOneScore = 0;
                        
                    CCARRAY_FOREACH(this->gameLayer->dominoManager->opponentOneArray,pobj) {
                        
                        DNDomino *aDomino = (DNDomino *)pobj;
                        this->gameLayer->dominoManager->opponentOneScore = this->gameLayer->dominoManager->opponentOneScore + aDomino->totalValue;   
                    }
                        
                    CCLOG("totalscoreofopponent1 = %d",this->gameLayer->dominoManager->opponentOneScore);
                        
                    CCObject* pOBj = NULL;
                    this->gameLayer->dominoManager->opponentTwoScore = 0;
                        
                    CCARRAY_FOREACH(this->gameLayer->dominoManager->opponentTwoArray,pOBj) {
                        
                        DNDomino *aDomino = (DNDomino *)pOBj;
                        this->gameLayer->dominoManager-> opponentTwoScore = this->gameLayer->dominoManager->opponentTwoScore + aDomino->totalValue;  
                    }
                    CCLOG("totalscoreofopponent1 = %d",this->gameLayer->dominoManager->opponentTwoScore);

                    CCDelayTime *delay = CCDelayTime::create(1.0f);

                    CCCallFunc *gameover = CCCallFunc::create(this,callfunc_selector(DNDomino::callback));
                        
                    CCCallFunc *pause = CCCallFunc::create(this,callfunc_selector(DNDomino::pause));
                        
                    this->gameLayer->runAction(CCSequence::create(delay,gameover,pause,NULL));
                }
                    
                CCPoint convertedPosition = MainGameLayer->convertToNodeSpace(this->getPosition());
                    
                // Removing from UILayer and adding into background layer
                DataManager->UILayer->removeChild(this, false);
                MainGameLayer->addChild(this);
                this->setPosition(convertedPosition);
                    
                this->arrangeTileOnBoard(obj.isLeft);
                this->state = kTileInBoard;
                DominoManager->slots[this->location] = 0;
                    
                this->tilePlacementIndicator(true);
                
                this->tilesOwnerPanel->closePanel(); //Closing the panel once it's placed correctly..
                    //DominoManager->arrangeTilesOfPlayer(this->playerID,this->location);
                    
                scheduleOnce(schedule_selector(DNDomino::updateCallBack), 3.0f); // Giving turn to the next player...
                }
                break;
            }
        }
    }
    if (!isPlaced) { // If tile isn't matched properly then move it to old location!
        
        // Turn on indicators
        this->tilePlacementIndicator(false);
        //this->moveBackToPlayer();
    }
}

void DNDomino::callback(){
   
        DataManager->isGameOver = true;
    
        this->unschedule(schedule_selector(DNDomino::startTimer));

        this->gameLayer->dominoManager->clockLabel = CCLabelTTF::create("", "Arial",50);
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->clockLabel,2);
    
        this->gameLayer->dominoManager->clockLabel->setColor(ccc3(0,255,0));
        this->gameLayer->dominoManager->clockLabel->setVisible(true);
        
        char point[1000]={};
        sprintf(point,"%d seconds",DataManager->min);
        CCLOG("minute %s",point);
    
        this->gameLayer->dominoManager->clockLabel->setString(point);
        this->gameLayer->dominoManager->clockLabel->setPosition(ccp(650,307));
     
        this->gameLayer->uiManager->actionMenu->setEnabled(false);
        this->gameLayer->uiManager->mainMenu->setEnabled(false);
        this->gameLayer->uiManager->playersMenu->setEnabled(false);
//        this->gameLayer->playerpanel->passMenu->setEnabled(false);
    
        CCLOG("playerscore = %d",this->gameLayer->dominoManager->playerScore);
        CCLOG("opponentOnescore = %d",this->gameLayer->dominoManager->opponentOneScore);
        CCLOG("opponentTwoscore = %d",this->gameLayer->dominoManager->opponentTwoScore);

        this->gameLayer->dominoManager->spr = CCSprite::create("end_game_lose_empty.png");
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->spr);
        this->gameLayer->dominoManager->spr->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 ));
    
        CCSprite *spr1 = CCSprite::create("bg.png");
        DataManager->UILayer->addChild(spr1,1);
        spr1->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2));

        this->gameLayer->dominoManager->cup = CCSprite::createWithSpriteFrameName("cup.png");
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->cup,1);
        this->gameLayer->dominoManager->cup->setVisible(false);
    
        CCSprite *clock = CCSprite::createWithSpriteFrameName("clock.png");
        clock->setPosition(ccp(DataManager->screenSize.width/2 - 30 , DataManager->screenSize.height/2 - 70));
        DataManager->UILayer->addChild(clock,1);
    
        this->gameLayer->dominoManager->gamerWinBackGrd = CCSprite::create("gamerWinbackgrd.png");
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->gamerWinBackGrd);
        this->gameLayer->dominoManager->gamerWinBackGrd->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2));
        this->gameLayer->dominoManager->gamerWinBackGrd->setVisible(false);
    
        this->gameLayer->dominoManager->opponentOneName = CCSprite::createWithSpriteFrameName("rabbit_txt.png");
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->opponentOneName,1);
        this->gameLayer->dominoManager->opponentOneName->setVisible(false);

        this->gameLayer->dominoManager->rabit = CCSprite::createWithSpriteFrameName("rabbit.png");
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->rabit,1);
        this->gameLayer->dominoManager->rabit->setVisible(false);
        
        this->gameLayer->dominoManager->playerName = CCSprite::createWithSpriteFrameName("irenet.png");
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->playerName,1);
        this->gameLayer->dominoManager->playerName->setVisible(false);
    
        this->gameLayer->dominoManager->ziraffe = CCSprite::createWithSpriteFrameName("giraffe.png");
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->ziraffe,1);
        this->gameLayer->dominoManager->ziraffe->setVisible(false);
        
        this->gameLayer->dominoManager->opponentTwoName = CCSprite::createWithSpriteFrameName("giraffe_txt.png");
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->opponentTwoName,1);
        this->gameLayer->dominoManager->opponentTwoName->setVisible(false);
        
        this->gameLayer->dominoManager->opponentOneLabel = CCLabelTTF::create("", "Arial",50);
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->opponentOneLabel,1);
        this->gameLayer->dominoManager->opponentOneLabel->setColor(ccc3(0, 255, 0));
        
        this->gameLayer->dominoManager->opponentTwoLabel = CCLabelTTF::create("", "Arial",50);
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->opponentTwoLabel,1);
        this->gameLayer->dominoManager->opponentTwoLabel->setColor(ccc3(0, 255, 0));
        
        this->gameLayer->dominoManager->playerLabel = CCLabelTTF::create("", "Arial",50);
        DataManager->UILayer->addChild(this->gameLayer->dominoManager->playerLabel,1);
        this->gameLayer->dominoManager->playerLabel->setColor(ccc3(0, 255, 0));
        
//        setting position for the players in ascending order based on their scores
        if(DataManager->opponentCount == 2)
        {
            if(this->gameLayer->dominoManager->playerScore <= this->gameLayer->dominoManager->opponentOneScore && this->gameLayer->dominoManager->playerScore <= this->gameLayer->dominoManager->opponentTwoScore){ // player is the winner
                
//                CCParticleSystem *shootinStarTrail = CCParticleSystemQuad::create("snake.plist");
//                DataManager->UILayer->addChild(shootinStarTrail,0);
//                shootinStarTrail->setPosition(ccp(200, 384));

                if(this->gameLayer->dominoManager->opponentOneScore <= this->gameLayer->dominoManager->opponentTwoScore){   
                    
                    this->gameLayer->dominoManager->opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                    this->gameLayer->dominoManager->opponentOneName->setVisible(true);
                    this->gameLayer->dominoManager->opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                    this->gameLayer->dominoManager->rabit->setVisible(true);
                    this->gameLayer->dominoManager->rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 100));
                    
                    this->gameLayer->dominoManager->opponentTwoLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                    this->gameLayer->dominoManager->opponentTwoName->setVisible(true);
                    this->gameLayer->dominoManager->opponentTwoName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 10));
                    this->gameLayer->dominoManager->ziraffe->setVisible(true);
                    this->gameLayer->dominoManager->ziraffe->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 10));
                }
                else {
                    
                    this->gameLayer->dominoManager->opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                    this->gameLayer->dominoManager->opponentOneName->setVisible(true);
                    this->gameLayer->dominoManager->opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 10));
                    this->gameLayer->dominoManager->rabit->setVisible(true);
                    this->gameLayer->dominoManager->rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 10));
                    
                    this->gameLayer->dominoManager->opponentTwoLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                    this->gameLayer->dominoManager->opponentTwoName->setVisible(true);
                    this->gameLayer->dominoManager->opponentTwoName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                    this->gameLayer->dominoManager->ziraffe->setVisible(true);
                    this->gameLayer->dominoManager->ziraffe->setPosition(ccp(DataManager->screenSize.width/2 -  150, DataManager->screenSize.height/2 + 100));
                }
                
                
                char a[10]={0};
                sprintf(a,"%d",this->gameLayer->dominoManager->opponentOneScore);
                this->gameLayer->dominoManager->opponentOneLabel->setString(a);
                
                char b[10]={0};
                sprintf(b,"%d",this->gameLayer->dominoManager->opponentTwoScore);
                this->gameLayer->dominoManager->opponentTwoLabel->setString(b);

                char c[10]={0};
                sprintf(c,"%d",this->gameLayer->dominoManager->playerScore);
                this->gameLayer->dominoManager->playerLabel->setString(c);
                
                this->gameLayer->dominoManager->gamerWinBackGrd->setVisible(true);
                this->gameLayer->dominoManager->spr->setVisible(false);
                
                this->gameLayer->dominoManager->cup->setVisible(true);
                
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Yay.mp3");

                this->gameLayer->dominoManager->cup->setPosition(ccp(DataManager->screenSize.width/2 + 150, DataManager->screenSize.height/2 + 200));
                this->gameLayer->dominoManager-> playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 200));
                this->gameLayer->dominoManager->playerName->setVisible(true);
                this->gameLayer->dominoManager->playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 200));
            }
            else if(this->gameLayer->dominoManager->opponentOneScore <= this->gameLayer->dominoManager->playerScore && this->gameLayer->dominoManager->opponentOneScore <= this->gameLayer->dominoManager->opponentTwoScore){ // opponent one is winner
                
                if(this->gameLayer->dominoManager->playerScore <= this->gameLayer->dominoManager->opponentTwoScore){
                    
                    this->gameLayer->dominoManager-> playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                    this->gameLayer->dominoManager->playerName->setVisible(true);
                    this->gameLayer->dominoManager->playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                    
                    this->gameLayer->dominoManager-> opponentTwoLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                    this->gameLayer->dominoManager->opponentTwoName->setVisible(true);
                    this->gameLayer->dominoManager->opponentTwoName->setPosition(ccp(DataManager->screenSize.width/2 -50 , DataManager->screenSize.height/2 + 10));
                    this->gameLayer->dominoManager->ziraffe->setVisible(true);
                    this->gameLayer->dominoManager->ziraffe->setPosition(ccp(DataManager->screenSize.width/2 - 150 , DataManager->screenSize.height/2 + 10));
                }
                
                else{
                    
                    this->gameLayer->dominoManager->playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                    this->gameLayer->dominoManager->playerName->setVisible(true);
                    this->gameLayer->dominoManager->playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 10));
                    
                    this->gameLayer->dominoManager->opponentTwoLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                    this->gameLayer->dominoManager->opponentTwoName->setVisible(true);
                    this->gameLayer->dominoManager->opponentTwoName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                    this->gameLayer->dominoManager->ziraffe->setVisible(true);
                    this->gameLayer->dominoManager->ziraffe->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 100));
                }
                
                char a[10]={0};
                sprintf(a,"%d",this->gameLayer->dominoManager->opponentOneScore);
                this->gameLayer->dominoManager->opponentOneLabel->setString(a);

                char b[10]={0};
                sprintf(b,"%d",this->gameLayer->dominoManager->opponentTwoScore);
                this->gameLayer->dominoManager-> opponentTwoLabel->setString(b);

                char c[10]={0};
                sprintf(c,"%d",this->gameLayer->dominoManager->playerScore);
                this->gameLayer->dominoManager-> playerLabel->setString(c);
                
                this->gameLayer->dominoManager->cup->setVisible(true);
                this->gameLayer->dominoManager->cup->setPosition(ccp(DataManager->screenSize.width/2 + 160, DataManager->screenSize.height/2 + 200));
                
                this->gameLayer->dominoManager->opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 110,DataManager->screenSize.height/2 + 200));
                this->gameLayer->dominoManager->opponentOneName->setVisible(true);
                this->gameLayer->dominoManager->opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 ,DataManager->screenSize.height/2 + 200));
                this->gameLayer->dominoManager->rabit->setVisible(true);
                this->gameLayer->dominoManager->rabit->setPosition(ccp(DataManager->screenSize.width/2 -50,DataManager->screenSize.height/2 + 200));
                
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
            }
            else if(this->gameLayer->dominoManager->opponentTwoScore <= this->gameLayer->dominoManager->playerScore && this->gameLayer->dominoManager->opponentTwoScore <=this->gameLayer->dominoManager-> opponentOneScore){ // opponent two winner
                
                if(this->gameLayer->dominoManager->playerScore <= this->gameLayer->dominoManager->opponentOneScore){
                    
                    this->gameLayer->dominoManager-> opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                    this->gameLayer->dominoManager->opponentOneName->setVisible(true);
                    this->gameLayer->dominoManager->opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 10));
                    this->gameLayer->dominoManager->rabit->setVisible(true);
                    this->gameLayer->dominoManager->rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 10));
                    
                    this->gameLayer->dominoManager->playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                    this->gameLayer->dominoManager->playerName->setVisible(true);
                    this->gameLayer->dominoManager-> playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                }
                else {
                    
                    this->gameLayer->dominoManager-> opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                    this->gameLayer->dominoManager->opponentOneName->setVisible(true);
                    this->gameLayer->dominoManager->opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                    this->gameLayer->dominoManager->rabit->setVisible(true);
                    this->gameLayer->dominoManager->rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 100));
                    
                    this->gameLayer->dominoManager->playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 10));
                    this->gameLayer->dominoManager-> playerName->setVisible(true);
                    this->gameLayer->dominoManager->playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 10));
                }
                
                char a[10]={0};
                sprintf(a,"%d",this->gameLayer->dominoManager->opponentOneScore);
                this->gameLayer->dominoManager->opponentOneLabel->setString(a);
                
                char b[10]={0};
                sprintf(b,"%d",this->gameLayer->dominoManager->opponentTwoScore);
                this->gameLayer->dominoManager->opponentTwoLabel->setString(b);
                
                char c[10]={0};
                sprintf(c,"%d",this->gameLayer->dominoManager->playerScore);
                this->gameLayer->dominoManager->playerLabel->setString(c);
                
                this->gameLayer->dominoManager->cup->setVisible(true);
                this->gameLayer->dominoManager->cup->setPosition(ccp(DataManager->screenSize.width/2 + 200, DataManager->screenSize.height/2 + 100));
                
                this->gameLayer->dominoManager-> opponentTwoLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 200));
                this->gameLayer->dominoManager->opponentTwoName->setVisible(true);
                this->gameLayer->dominoManager->opponentTwoName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 200));
                this->gameLayer->dominoManager->ziraffe->setVisible(true);
                this->gameLayer->dominoManager->ziraffe->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 200));
                
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
            }
        }
        else if(DataManager->opponentCount == 1)
        {
            if(this->gameLayer->dominoManager->playerScore <= this->gameLayer->dominoManager->opponentOneScore){  // player one is the winner
                
//                this->gameLayer->dominoManager->zigzag = CCParticleSystemQuad::create("snake.plist");
//                DataManager->UILayer->addChild(this->gameLayer->dominoManager->zigzag,0);
//                this->gameLayer->dominoManager->zigzag->setPosition(ccp(200, 384));
                
                this->gameLayer->dominoManager->opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                this->gameLayer->dominoManager->opponentOneName->setVisible(true);
                this->gameLayer->dominoManager->opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                this->gameLayer->dominoManager->rabit->setVisible(true);
                this->gameLayer->dominoManager->rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 100));
                
                this->gameLayer->dominoManager->playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 200));
                this->gameLayer->dominoManager->playerName->setVisible(true);
                this->gameLayer->dominoManager->playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 200));
                
                this->gameLayer->dominoManager->gamerWinBackGrd->setVisible(true);
                this->gameLayer->dominoManager->spr->setVisible(false);
                
//                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Yay.mp3");
            }
            else {
                
                this->gameLayer->dominoManager->opponentOneLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 200));
                this->gameLayer->dominoManager->opponentOneName->setVisible(true);
                this->gameLayer->dominoManager->opponentOneName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 200));
                this->gameLayer->dominoManager->rabit->setVisible(true);
                this->gameLayer->dominoManager->rabit->setPosition(ccp(DataManager->screenSize.width/2 - 150, DataManager->screenSize.height/2 + 200));
                
                this->gameLayer->dominoManager->playerLabel->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 + 100));
                this->gameLayer->dominoManager->playerName->setVisible(true);
                this->gameLayer->dominoManager->playerName->setPosition(ccp(DataManager->screenSize.width/2 - 50, DataManager->screenSize.height/2 + 100));
                
//                 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");
            }

            
            char a[10]={0};
            sprintf(a,"%d",this->gameLayer->dominoManager->opponentOneScore);
            this->gameLayer->dominoManager->opponentOneLabel->setString(a);
            this->gameLayer->dominoManager->cup->setVisible(true);
            this->gameLayer->dominoManager->cup->setPosition(ccp(DataManager->screenSize.width/2 + 200, DataManager->screenSize.height/2 + 100));
            
            char c[10]={0};
            sprintf(c,"%d",this->gameLayer->dominoManager->playerScore);
            this->gameLayer->dominoManager->playerLabel->setString(c);
        }
    
        CCSprite *ok_normal = CCSprite::createWithSpriteFrameName("ok_btn1.png");
        CCSprite *ok_selected = CCSprite::createWithSpriteFrameName("ok_pressed.png");
    
        CCMenuItemSprite* restartItem = CCMenuItemSprite::create(ok_normal ,ok_selected ,this, menu_selector(DNDomino::restart));
        CCMenu *mainMenu = CCMenu::create(restartItem,NULL);
        mainMenu->alignItemsVerticallyWithPadding(5);
        mainMenu->setPosition(ccp(DataManager->screenSize.width/2 + 50 , DataManager->screenSize.height/2 - 175 ));
        
        DataManager->UILayer->addChild(mainMenu,1);
        DataManager->count = 0;
        DataManager->opponenttilecount = 0;
}

void DNDomino::pause(){
    
    this->gameLayer->uiManager->onPause = true;
    DataManager->UILayer->setTouchEnabled(false);
    
    if(DataManager->isGameOver == true){

        if(this->gameLayer->uiManager->onPause){
            
            CCDirector::sharedDirector()->pause();
        }
    }
}

void DNDomino::restart()
{
    DataManager->isGameOver = false;
    
    DataManager->gameLayer->restartScene();

    DataManager->count = 0;
    DataManager->opponenttilecount = 0;
    
    CCDirector::sharedDirector()->resume();
    
//    DataManager->UILayer->removeChild(this->gameLayer->dominoManager->zigzag, true);
    
    this->gameLayer->uiManager->actionMenu->setEnabled(true);
    this->gameLayer->uiManager->mainMenu->setEnabled(true);
    this->gameLayer->uiManager->playersMenu->setEnabled(true);
//    this->gameLayer->playerpanel->passMenu->setEnabled(true);
}

// For AI Move
void DNDomino::updateValuesForTile() {

    CCPoint convertedPosition = MainGameLayer->convertToNodeSpace(this->worldPosition);
    
    this->removeFromParentAndCleanup(false);
    MainGameLayer->addChild(this);
    this->setPosition(convertedPosition);

    this->state = kTileInBoard;
    DominoManager->slots[this->location] = 0;
    
    this->tilePlacementIndicator(true);
    this->tilesOwnerPanel->closePanel(); // Closing the panel once it's placed correctly...
    //DominoManager->arrangeTilesOfPlayer(this->playerID,this->location);
    
    scheduleOnce(schedule_selector(DNDomino::updateCallBack), 3.0f); // Giving turn to the next player...
}

void DNDomino::updateCallBack() {

    ScheduleManager->passTurnToNextPlayer();
}

// If not matched move back to the old position
void DNDomino::moveBackToPlayer() {
    
//    label->setVisible(false);
    illegalpos->setVisible(false);
    
    CCFiniteTimeAction *actionMove = NULL;
    
    // If the tiles panel is already opened, make sure it remains open until tile reaches!
    if (this->tilesOwnerPanel->state == kPanelOpened) {
        
        this->gameLayer->dominoManager->selectedtilecount = 1;
        this->tilesOwnerPanel->expandPanel();
        actionMove = CCMoveTo::create(0.4, this->worldPosition);
    }
    else if(this->tilesOwnerPanel->state == kPanelClosed) {
        
        actionMove = CCMoveTo::create(0.4, this->scaleDownWorldCoordinate);
        CCFiniteTimeAction *actionScale = CCScaleTo::create(0.4, 0.5);
        this->runAction(actionScale);
    }
    
    CCFiniteTimeAction *actionRotate = CCRotateTo::create(0.4, 0);
//    CCFiniteTimeAction *actionSpan = CCSpawn::create(actionMove,actionRotate); /* (2.0.3 version) */
    CCFiniteTimeAction *actionSpan = CCSpawn::createWithTwoActions(actionMove,actionRotate);
    CCFiniteTimeAction *actionCallBack = CCCallFuncN::create(this, callfuncN_selector(DNDomino::addToOwner));
    CCFiniteTimeAction *actionSequence = CCSequence::create(actionSpan,actionCallBack,NULL);
    this->runAction(actionSequence);
    
//    CCFiniteTimeAction *actionScale = CCScaleTo::create(0.4, 0.5);
//    this->runAction(actionScale);
}

void DNDomino::addToOwner() {
    
    this->removeFromParentAndCleanup(false);
    
    this->tilesOwnerPanel->addChild(this);
    this->setPosition(this->position);
    
    if(this->tilesOwnerPanel->state == kPanelClosed) {
        
        this->setScale(1);
    }
}

void DNDomino::playerWinAnimation(){
    
    DataManager->isGameFinished = true;

    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("dominoes_new.plist");

    CCSprite *sprite = CCSprite::createWithSpriteFrameName("giraffe-disappointed0001.png");
    sprite->setPosition(ccp(sprite->getContentSize().width/5 + 340,sprite->getPosition().y + 75));
    
    this->gameLayer->uiManager->playerPanel3->addChild(sprite);
    
    CCArray *animFrames = CCArray::create();
    char tmp[50];
    
    for (int j = 1; j <= 7; j++){
        
        sprintf(tmp, "giraffe-disappointed000%d.png",j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        animFrames->addObject(frame);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames,0.3f);
    sprite->runAction(CCAnimate::create(animation));
    sprite->setRotation(180);

    CCSpriteFrameCache *cache1 = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache1->addSpriteFramesWithFile("dominoes_new.plist");

    CCSprite *sprite1 = CCSprite::createWithSpriteFrameName("youngbunny-disappointed0001.png");
    sprite1->setPosition(ccp(sprite1->getContentSize().width/5 + 340,sprite1->getPosition().y + 75));
    
    this->gameLayer->uiManager->playerPanel2->addChild(sprite1);
    
    CCArray *animFrames1 = CCArray::create();
    char tmp1[50];
    
    for (int j = 1; j <= 7; j++){
        
        sprintf(tmp1, "youngbunny-disappointed000%d.png", j);
        CCSpriteFrame *frame1 = cache1->spriteFrameByName(tmp1);
        animFrames1->addObject(frame1);
    }
    
    CCAnimation *animation1 = CCAnimation::createWithSpriteFrames(animFrames1,0.3f);
    sprite1->runAction(CCAnimate::create(animation1));
    sprite1->setRotation(180);
    
    CCDelayTime *delay = CCDelayTime::create(4.0f);
    CCCallFunc *gameover = CCCallFunc::create(this,callfunc_selector(DNDominoManager::callback));
    this->gameLayer->runAction(CCSequence::create(delay,gameover,NULL));
}

void DNDomino::playerWinAnimationForOneOpponent(){
    
    CCSpriteFrameCache *cache1 = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache1->addSpriteFramesWithFile("dominoes_new.plist");
    
    CCSprite *sprite1 = CCSprite::createWithSpriteFrameName("youngbunny-disappointed0001.png");
    sprite1->setPosition(ccp(sprite1->getContentSize().width/5 + 340,sprite1->getPosition().y + 75));
    
    this->gameLayer->uiManager->playerPanel2->addChild(sprite1);
    
    CCArray *animFrames1 = CCArray::create();
    char tmp1[50];
    
    for (int j = 1; j <= 7; j++){
        
        sprintf(tmp1, "youngbunny-disappointed000%d.png", j);
        CCSpriteFrame *frame1 = cache1->spriteFrameByName(tmp1);
        animFrames1->addObject(frame1);
    }
    
    CCAnimation *animation1 = CCAnimation::createWithSpriteFrames(animFrames1, 0.3f);
    sprite1->runAction(CCAnimate::create(animation1));
    sprite1->setRotation(180);
    
    
    CCDelayTime *delay = CCDelayTime::create(4.0f);
    CCCallFunc *gameover = CCCallFunc::create(this, callfunc_selector(DNDominoManager::callback));
    CCCallFunc *pause = CCCallFunc::create(this,callfunc_selector(DNDomino::pause));
    this->gameLayer->runAction(CCSequence::create(delay,gameover,pause,NULL));
}

// Returns whether the sides of the tiles having equal values!
PlacementDetailsObject DNDomino::checkTileEdgePointsMatched(DNDomino *aTile) {
    
    PlacementDetailsObject obj;
    obj.isPlaced = false;
    
    CCPoint aTilePosition = MainGameLayer->convertToWorldSpace(aTile->getPosition());
    
    if (this->getPosition().x < aTilePosition.x && aTile->isLeftCollidable) { // Placing the tile in left side
        
        CCLog("left value is %d right value is %d",aTile->getCurrentAnglesTileValues(true,aTile),aTile->getCurrentAnglesTileValues(false,aTile));
        CCLog("current tile left is %d right is %d",this->getCurrentAnglesTileValues(true,this),this->getCurrentAnglesTileValues(false,this));
        
        if (aTile->getCurrentAnglesTileValues(true,aTile) == this->getCurrentAnglesTileValues(false,this)) {
            
            obj.isPlaced = true;
            obj.isLeft = true;
            obj.isTargetVertical = aTile->isVertical;
            
            obj.targetPosition = aTile->getPosition();
            
            aTile->isLeftCollidable = false;
            this->isRightCollidable = false;
        }
    }
    else if(aTile->isRightCollidable) { // Collision with right side...
        
        if (aTile->getCurrentAnglesTileValues(false,aTile) == this->getCurrentAnglesTileValues(true,this)) {
            
            obj.isPlaced = true;
            obj.isLeft = false;
            obj.isTargetVertical = aTile->isVertical;
            
            obj.targetPosition = aTile->getPosition();
            
            aTile->isRightCollidable = false;
            this->isLeftCollidable = false;
        }
    }
    return obj;
}

// After collision successful arranging the current tile next to the collided tile...
void DNDomino::arrangeTileOnBoard(bool isLeft) {
    
    CCFiniteTimeAction *actionMove = NULL;
    
    if (isLeft) { // Placing Left Side...
        
        if(DominoManager->edgeTile.left->isVertical) { // Target tile is vertical
            
            //-------------------------------,-----(targetTiles X Position - target TIles contentsize width) - current tiles height or width)
//            actionMove1 = CCRotateTo::create(0.2, -90);
            
            actionMove = CCMoveTo::create(0.2, ccp((DominoManager->edgeTile.left->getPosition().x - this->getContentSize().width/2) - this->getAdjacentValue(),DominoManager->edgeTile.left->getPosition().y));
            
            //CCLog("\n target position is %f edge is %f current value %f",DominoManager->edgeTile.left->getPosition().x,this->getContentSize().width/2,this->getAdjacentValue());
            
            DominoManager->leftMostEdgeSize = ((DominoManager->edgeTile.left->getPosition().x - this->getContentSize().width/2) - (this->getAdjacentValue() * 2));
            DominoManager->edgeTile.left = this;
        }
        else { // Target tile is horizontal
            
            actionMove = CCMoveTo::create(0.2, ccp((DominoManager->edgeTile.left->getPosition().x - this->getContentSize().height/2) - this->getAdjacentValue(),DominoManager->edgeTile.left->getPosition().y));
            
            //CCLog("\n target position is %f edge is %f current value %f",DominoManager->edgeTile.left->getPosition().x,this->getContentSize().height/2,this->getAdjacentValue());
            
            DominoManager->leftMostEdgeSize = ((DominoManager->edgeTile.left->getPosition().x - this->getContentSize().height/2) - (this->getAdjacentValue() * 2));
            DominoManager->edgeTile.left = this;
        }
        
        // Adding tile at the front in line of play array...
        DominoManager->lineOfPlayArray->insertObject(this, 0);
    }
    else { // Placing Right Side...
        
        if(DominoManager->edgeTile.right->isVertical) { // Target tile is vertical
            
            actionMove = CCMoveTo::create(0.2, ccp((DominoManager->edgeTile.right->getPosition().x + this->getContentSize().width/2) + this->getAdjacentValue(),DominoManager->edgeTile.right->getPosition().y));

            DominoManager->rightMostEdgeSize = ((DominoManager->edgeTile.right->getPosition().x + this->getContentSize().width/2) + (this->getAdjacentValue() * 2));
            DominoManager->edgeTile.right = this;
        }
        else { // Target tile is horizontal
            
            actionMove = CCMoveTo::create(0.2, ccp((DominoManager->edgeTile.right->getPosition().x + this->getContentSize().height/2) + this->getAdjacentValue(),DominoManager->edgeTile.right->getPosition().y));
    
            DominoManager->rightMostEdgeSize = ((DominoManager->edgeTile.right->getPosition().x + this->getContentSize().height/2) + (this->getAdjacentValue() * 2));
            DominoManager->edgeTile.right = this;
        }
        
        // Adding object at last index to line of play array...
        DominoManager->lineOfPlayArray->addObject(this);
    }
    
    this->runAction(actionMove);
    
    // Adjusting layer for current tile... Automatic
    //printf("\n isleft is %d leftMostEdge is %f rightMostEdge is %f \n",obj.isLeft,DominoManager->leftMostEdgeSize,DominoManager->rightMostEdgeSize);
    BackgroundManager->adjustBackgroundToTilePosition(isLeft,DominoManager->leftMostEdgeSize,DominoManager->rightMostEdgeSize);
}

void DNDomino::rotateTileForAI(float angle) {
    
    CCFiniteTimeAction *rotationAction = CCRotateTo::create(0.2, angle);
    this->runAction(rotationAction);
    this->toRotateAngle = angle;
}

/*
// After collision successful arranging the current tile next to the collided tile...
void DNDomino::arrangeTileOnBoard(PlacementDetailsObject obj) {
    
    CCFiniteTimeAction *actionMove = NULL;
    
    if (obj.isLeft) { // Placing Left Side...
        
        if(obj.isTargetVertical) { // Target tile is vertical
            
            //-------------------------------,-----(targetTiles X Position - target TIles contentsize width) - current tiles height or width)
            actionMove = CCMoveTo::create(0.2, ccp((obj.targetPosition.x - this->getContentSize().width/2) - this->getAdjacentValue(),obj.targetPosition.y));
            
            DominoManager->leftMostEdgeSize = ((obj.targetPosition.x - this->getContentSize().width/2) - (this->getAdjacentValue() * 2));
            DominoManager->leftTileValue = this->getCurrentAnglesTileValues(true,this);
            DominoManager->edgeTile.left = this;
        }
        else { // Target tile is horizontal
            
            actionMove = CCMoveTo::create(0.2, ccp((obj.targetPosition.x - this->getContentSize().height/2) - this->getAdjacentValue(),obj.targetPosition.y));
            
            DominoManager->leftMostEdgeSize = ((obj.targetPosition.x - this->getContentSize().height/2) - (this->getAdjacentValue() * 2));
            DominoManager->leftTileValue = this->getCurrentAnglesTileValues(true,this);
            DominoManager->edgeTile.left = this;
        }
    }
    else { // Placing Right Side...
        
        if(obj.isTargetVertical) { // Target tile is vertical
            
            actionMove = CCMoveTo::create(0.2, ccp((obj.targetPosition.x + this->getContentSize().width/2) + this->getAdjacentValue(),obj.targetPosition.y));
            
            DominoManager->rightMostEdgeSize = ((obj.targetPosition.x + this->getContentSize().width/2) + (this->getAdjacentValue() * 2));
            DominoManager->rightTileValue = this->getCurrentAnglesTileValues(false,this);
            DominoManager->edgeTile.right = this;
        }
        else { // Target tile is horizontal
            
            actionMove = CCMoveTo::create(0.2, ccp((obj.targetPosition.x + this->getContentSize().height/2) + this->getAdjacentValue(),obj.targetPosition.y));
          
            DominoManager->rightMostEdgeSize = ((obj.targetPosition.x + this->getContentSize().height/2) + (this->getAdjacentValue() * 2));
            DominoManager->rightTileValue = this->getCurrentAnglesTileValues(false,this);
            DominoManager->edgeTile.right = this;
        }
    }
    
    //printf("\n left most value is %d right most value is %d",DominoManager->leftTileValue,DominoManager->rightTileValue);
    
    this->runAction(actionMove);
    
    // Adjusting layer for current tile... Automatic
    //printf("\n isleft is %d leftMostEdge is %f rightMostEdge is %f \n",obj.isLeft,DominoManager->leftMostEdgeSize,DominoManager->rightMostEdgeSize);
    BackgroundManager->adjustBackgroundToTilePosition(obj.isLeft,DominoManager->leftMostEdgeSize,DominoManager->rightMostEdgeSize);
}
*/

void DNDomino::tilePlacementIndicator(bool isCorrect) {
    
    char name[15];
    sprintf(name, "glow%d.png",isCorrect);
    
    DNDomino *glo = DNDomino::spriteWithFrame(name);
    glo->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
    this->addChild(glo);
    
    if (!isCorrect) {

        illegalpos = CCSprite::createWithSpriteFrameName("illegal position.png");
      
        this->addChild(illegalpos,1,10);
        
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle Error1.mp3");

        illegalpos->setPosition(ccp(this->getContentSize().width/2 + 200, this->getContentSize().height/2));
        
        CCFiniteTimeAction *actionFade1 = CCFadeTo::create(0.2,100);
        CCFiniteTimeAction *actionFade2 = CCFadeTo::create(0.2,255);
        CCFiniteTimeAction *actionFade3 = CCFadeTo::create(0.2,0);
        CCFiniteTimeAction *actionSequence = CCSequence::create(actionFade1,actionFade2,actionFade3,NULL);
        CCFiniteTimeAction *actionRepeat = CCRepeat::create(actionSequence, 5);
        glo->runAction(actionRepeat);
        
        
        CCFiniteTimeAction *actionDelay = CCDelayTime::create(3.0f);
        CCFiniteTimeAction *callBack = CCCallFuncN::create(this, callfuncN_selector(DNDomino::moveBackToPlayer));
        CCFiniteTimeAction *actionSeq1 = CCSequence::create(actionDelay,callBack,NULL);
        this->runAction(actionSeq1);
    return;
    }
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Subtle Error2.mp3");
    
    CCFiniteTimeAction *actionFade1 = CCFadeTo::create(0.2, 100);
    CCFiniteTimeAction *actionFade2 = CCFadeTo::create(0.2, 255);
    CCFiniteTimeAction *actionFade3 = CCFadeTo::create(0.2, 0);
    CCFiniteTimeAction *actionCallBack = CCCallFuncN::create(this, callfuncN_selector(DNDomino::removeTileGlow));
    
    CCFiniteTimeAction *actionSequence = CCSequence::create(actionFade1,actionFade2,actionFade3,actionCallBack,NULL);
    glo->runAction(actionSequence);
}

void DNDomino::removeTileGlow(CCObject* sender) {
    
    CCSprite *tempGlow = (CCSprite*)sender;
    this->removeChild(tempGlow,true);
}

/////////// Helper Functions!

float DNDomino::getCurrentAngle() {
    
    float rotation = 0;
    
    rotation = this->getRotation();
    
    if (rotation < 0) {
        
        rotation = 360 + this->getRotation();
    }
    else if(rotation > 360) {
        
        rotation = (int)rotation % 360;
    }
    
    return rotation;
}

void DNDomino::rotateToAppropriateAngle(float currentAngle) {
    
    //CCLog("this->isVertical is %d",this->isVertical);
    
    //clock wise... 0,90,180,270,360...
    
    this->toRotateAngle = 0;
    this->isVertical = false;
    this->isHorizontal = false;
    bool isAngleAdjustable = false;
    
    if (currentAngle >= 0 && currentAngle < 15) {
        
        this->toRotateAngle = 0;
        isAngleAdjustable = true;
        this->isVertical = true;
    }
    else if(currentAngle >= 75 && currentAngle < 90) {
        
        this->toRotateAngle = 90;
        isAngleAdjustable = true;
        this->isHorizontal = true;
    }
    else if(currentAngle >= 90 && currentAngle < 105) {
        
        this->toRotateAngle = 90;
        isAngleAdjustable = true;
        this->isHorizontal = true;
    }
    else if(currentAngle >= 165 && currentAngle < 180) {
        
        this->toRotateAngle = 180;
        isAngleAdjustable = true;
        this->isVertical = true;
    }
    else if(currentAngle >= 180 && currentAngle < 195) {
        
        this->toRotateAngle = 180;
        isAngleAdjustable = true;
        this->isVertical = true;
    }
    else if(currentAngle >= 255 && currentAngle < 270) {
        
        this->toRotateAngle = 270;
        isAngleAdjustable = true;
        this->isHorizontal = true;
    }
    else if(currentAngle >= 270 && currentAngle < 285) {
        
        this->toRotateAngle = 270;
        isAngleAdjustable = true;
        this->isHorizontal = true;
    }
    else if(currentAngle >= 345 && currentAngle < 360) {
        
        this->toRotateAngle = 0;
        isAngleAdjustable = true;
        this->isVertical = true;
    }
    
    if(isAngleAdjustable) {
        
        CCActionInterval *actionRotate = CCRotateTo::create(0.2, this->toRotateAngle);
        this->runAction(actionRotate);
    }
}

bool DNDomino::checkForCorrectRotation() {
    
    bool isCorrect = false;
    
    if (this->topValue == this->bottomValue) {
        
        isCorrect = false;
    }
    else if (this->isVertical) {
            
           isCorrect = false;
            //this->isHorizontal=true;
    }
    if(this->isHorizontal) {
            
            isCorrect = true; 
    }
    return isCorrect;
}

// After rotation get the values for left and right... No Need to values for the vertical sprites! Coz values are same!
int DNDomino::getCurrentAnglesTileValues(bool isLeft,DNDomino *aTile) {
    
    int value = 0;
    
    if (!isLeft) { // Right side...
        
        if (aTile->isHorizontal && aTile->toRotateAngle == 90) {
            
            value = aTile->topValue;
        }
        else if(aTile->isHorizontal && aTile->toRotateAngle == 270) {
            
            value = aTile->bottomValue;
        }
        else if(aTile->isVertical) {
            
            value = aTile->topValue;
        }
    }
    else { // Left side...
        
        if(aTile->isHorizontal && aTile->toRotateAngle == 90) {
            
            value = aTile->bottomValue;
        }
        else if(aTile->isHorizontal && aTile->toRotateAngle == 270) {
            
            value = aTile->topValue;
        }
        else if(aTile->isVertical) {
            
            value = aTile->topValue;
        }
    }

    return value;
}

float DNDomino::getAdjacentValue() {
    
    float value = 0;
    
    if (this->isVertical) {
        
        value = this->getContentSize().width/2;
    }
    else if(this->isHorizontal) {
        
        value = this->getContentSize().height/2;
    }

    return value;
}

