//
//  ZIMonster.cpp
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#include "ZIMonster.h"
#include "ZIDataManager.h"
#include "ZIUtility.h"

ZIMonster::ZIMonster() {
    
    // Assigning the layer
    this->gameLayer = DataManager->gameLayer;
}

ZIMonster::~ZIMonster() {
    
    CCLog("Monster is removed");
}

// To create separate sprite from file...
ZIMonster* ZIMonster::spriteWithFile(const char *pszFileName) {
    
    ZIMonster *pobSprite = new ZIMonster();
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
ZIMonster* ZIMonster::spriteWithFrame(const char *pszFileName) {
    
    //CCLog("name is %s",pszFileName);
    
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszFileName);
    
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszFileName);
    CCAssert(pFrame != NULL, msg);
    
    ZIMonster *tempSpr = ZIMonster::create(pFrame);
    
    return tempSpr;
}

ZIMonster* ZIMonster::create(CCSpriteFrame *pSpriteFrame) {
    
    ZIMonster *pobSprite = new ZIMonster();
    if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
    
}

void ZIMonster::createMonsterContainer(float gridWidth) {
    
    this->setPosition(ccp(((this->getContentSize().width * 3) - this->getContentSize().width/2) + 2 , DataManager->screenSize.height/2));
    MainGameLayer->addChild(this);

    //CCLog("size in monster is %f monster contentsize %f",gridWidth,this->getContentSize().width);
    
    ZIMonster *aMonster = aMonster->spriteWithFile("Monster1.png");
    aMonster->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height + aMonster->getContentSize().height/2));
    this->addChild(aMonster);
    this->state.isReachedGround = false;
    this->setBox2dPropertiesForContainer();
} 

void ZIMonster::setBox2dPropertiesForContainer() {

    b2BodyDef monsterBodyDef;
    monsterBodyDef.type = b2_dynamicBody;
    monsterBodyDef.position.Set(this->getPosition().x/PTM_RATIO, this->getPosition().y/PTM_RATIO);
    monsterBodyDef.userData = this;
    
    b2Body *monsterBody = DataManager->gameWorld->CreateBody(&monsterBodyDef);
    this->body = monsterBody;
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox((this->getContentSize().width-1)/2/PTM_RATIO, this->getContentSize().height/PTM_RATIO, b2Vec2((this->getContentSize().width-1)/2/PTM_RATIO - 0.6, this->getContentSize().height/2/PTM_RATIO), 0);
    
    b2FixtureDef monsterShapeDef;
    monsterShapeDef.shape = &boxShape;
    monsterShapeDef.restitution = 0.0f;
    monsterShapeDef.density = 100.0f;
    monsterShapeDef.friction = 0.0f;
    monsterBody->CreateFixture(&monsterShapeDef);
}

void ZIMonster::changeToStatic() {

    this->body->SetType(b2_staticBody);
    this->state.isReachedGround = true;
}

void ZIMonster::moveMonster(bool isLeft) {
    
    if (isLeft) {
        
        //this->body->SetTransform(b2Vec2(this->body->GetPosition().x + MonsterManager->gridSize.width/PTM_RATIO,this->body->GetPosition().y), 0);
        
        CCPoint bodyPosition=ccp(this->body->GetPosition().x/PTM_RATIO,this->body->GetPosition().y/PTM_RATIO);
        //CCFloat distance = ccpDistance(bodyPosition, ccp((this->body->GetPosition().x/PTM_RATIO) + MonsterManager->gridSize.width,this->body->GetPosition().y/PTM_RATIO)) * 0.5; 
        
        //this->body->ApplyForce(b2Vec2(cosf(90) * distance, sinf(90) * distance), this->body->GetPosition());
        
        b2Vec2 currentPosition = this->body->GetPosition();
        b2Vec2 desiredPosition = b2Vec2(this->body->GetPosition().x  + (MonsterManager->gridSize.width/PTM_RATIO),this->body->GetPosition().y);
        b2Vec2 necessaryMovement = desiredPosition - currentPosition;
        float forceMagnitude = this->body->GetMass() * 60;
        b2Vec2 force = forceMagnitude * necessaryMovement;
        this->body->ApplyForce( force, this->body->GetWorldCenter());
        //b2Vec2 force1=b2Vec2(4,0);
        //this->body->SetLinearVelocity(force);   
     
        
           
    }
    else {
        CCPoint bodyPosition=ccp(this->body->GetPosition().x/PTM_RATIO,this->body->GetPosition().y/PTM_RATIO);
        //CCFloat distance = ccpDistance(bodyPosition, ccp((this->body->GetPosition().x/PTM_RATIO) + MonsterManager->gridSize.width,this->body->GetPosition().y/PTM_RATIO)) * 0.5; 
        
        //this->body->ApplyForce(b2Vec2(cosf(90) * distance, sinf(90) * distance), this->body->GetPosition());
        
        b2Vec2 currentPosition = this->body->GetPosition();
        b2Vec2 desiredPosition = b2Vec2(this->body->GetPosition().x  - (MonsterManager->gridSize.width/PTM_RATIO),this->body->GetPosition().y);
        b2Vec2 necessaryMovement = desiredPosition - currentPosition;
        float forceMagnitude = this->body->GetMass() * 60;
        b2Vec2 force = forceMagnitude * necessaryMovement;
        this->body->ApplyForce( force, this->body->GetWorldCenter());
        //b2Vec2 force1=b2Vec2(4,0);
        //this->body->SetLinearVelocity(force);   

        
       // this->body->SetTransform(b2Vec2(this->body->GetPosition().x - MonsterManager->gridSize.width/PTM_RATIO,this->body->GetPosition().y), 0);
    }
}

void ZIMonster::rotateMonster(bool isLeft) {
    
    if (isLeft) {
        
        //this->body->SetTransform(this->body->GetPosition(), this->body->GetAngle() - CC_DEGREES_TO_RADIANS(90));
    }
    else {
        
        //this->body->SetTransform(this->body->GetPosition(), this->body->GetAngle() + CC_DEGREES_TO_RADIANS(90));
    }
}
