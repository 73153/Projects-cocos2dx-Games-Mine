//
//  ZIMonsterManager.cpp
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#include "ZIMonsterManager.h"
#include "ZIDataManager.h"
#include "ZIUIManager.h"
#include "ZIMonster.h"

using namespace cocos2d;

ZIMonsterManager::ZIMonsterManager() {
    
    // Assigning the gamelayer
    this->gameLayer = DataManager->gameLayer;
    
    // Initializing
    this->monstersArray = CCArray::create();
    this->monstersArray->retain();
    
    // Initialalize functions
    this->computeGridSize();
    this->createMonster();
}

ZIMonsterManager::~ZIMonsterManager() {
    
    delete this->monstersArray;
}

void ZIMonsterManager::computeGridSize() {
    
    float playScreenWidth = DataManager->screenSize.width - UIManager->rightPanelSize.width;
    float playScreenHeight = DataManager->screenSize.height - UIManager->topPanelSize.height;
    
    float aGridWidth = playScreenWidth/6;
    float aGridHeight = playScreenHeight/10;
    
    this->gridSize = CCSizeMake(aGridWidth, aGridHeight);
    CCLog("grid size is %f %f",this->gridSize.width,this->gridSize.height);
}

void ZIMonsterManager::createMonster() {
    
    ZIMonster *aMonster = aMonster->spriteWithFile("Monster1.png");
    aMonster->createMonsterContainer(this->gridSize.width);
    this->monstersArray->addObject(aMonster);
}

void ZIMonsterManager::monsterManagerContactListener() {
    
    std::vector<b2Body *>toDestroy;
    std::vector<MyContact>::iterator pos;
    
    for(pos = MainGameLayer->_contactListener->_contacts.begin();
        pos != MainGameLayer->_contactListener->_contacts.end(); ++pos) {
        
        MyContact contact = *pos;
        
        if(contact.fixtureA != NULL && contact.fixtureB != NULL)
        {
            b2Body *bodyA = contact.fixtureA->GetBody();
            b2Body *bodyB = contact.fixtureB->GetBody();
            
            if (bodyA->GetUserData() != NULL) {
                
                ZIMonster *monst = (ZIMonster *)bodyA->GetUserData();
                
                if (!monst->state.isReachedGround) {
                    
                    monst->changeToStatic();
                    this->createMonster();
                }
            }
            
            if (bodyB->GetUserData() != NULL) {
                
                ZIMonster *monst = (ZIMonster *)bodyB->GetUserData();
                
                if (!monst->state.isReachedGround) {
                    
                    monst->changeToStatic();
                    this->createMonster();
                }
            }
        }
    }
}

void ZIMonsterManager::monsterManagerTouchBegan(CCSet *touches) {
    
    // Getting the touched location...
    CCTouch *touch = (CCTouch *)touches->anyObject();
	CCPoint location = touch->locationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

    this->isTouchStarted = true;
    this->touchStartPoint = location;
    
    // Rotation
    ZIMonster *aMonster = (ZIMonster *)this->monstersArray->objectAtIndex(this->monstersArray->count() - 1);
    aMonster->rotateMonster(true);
}

void ZIMonsterManager::monsterManagerTouchMoved(CCSet *touches) {
    
    // Getting the touched location...
    CCTouch *touch = (CCTouch *)touches->anyObject();
	CCPoint location = touch->locationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
    
    if (this->touchStartPoint.x < location.x && this->isTouchStarted) {
        
        // get the current monster container
        ZIMonster *aMonster = (ZIMonster *)this->monstersArray->objectAtIndex(this->monstersArray->count() - 1);
        aMonster->moveMonster(true);
        
        this->isTouchStarted = false;
    }
    else if(this->touchStartPoint.x > location.x && this->isTouchStarted) {
    
        // get the current monster container
        ZIMonster *aMonster = (ZIMonster *)this->monstersArray->objectAtIndex(this->monstersArray->count() - 1);
        aMonster->moveMonster(false);

        this->isTouchStarted = false;
    }
}

void ZIMonsterManager::monsterManagerTouchEnded(CCSet *touches) {
    
}

void ZIMonsterManager::monsterManagerTouchCanceled(CCSet *touches) {
    
}