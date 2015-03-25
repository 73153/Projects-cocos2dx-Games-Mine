//
//  DNBackground.cpp
//  Dominoes
//
//  Created by ICRG LABS on 08/08/12.
//
//

#include "DNBackground.h"
#include "DNDataManager.h"
#include "DNGameConstants.h"

DNBackground::DNBackground() {
    
    this->gameLayer = DNDataManager::sharedManager()->gameLayer;
}

DNBackground::~DNBackground() {}

DNBackground* DNBackground::spriteWithFile(const char *pszFileName) {
    
    DNBackground *pobSprite = new DNBackground();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        //pobSprite->scheduleUpdate();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void DNBackground::createBackground(CCPoint position, int tag) {
    
    /*
    mineBackGround = [[CCRenderTexture renderTextureWithWidth:480 height:160]retain];
    [mineBackGround setPosition:ccp(240, 100)];
    [[mineBackGround sprite] setBlendFunc: (ccBlendFunc) { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA }];
    [self addChild:mineBackGround z:2];
    
    //Visit Once
    [mineBackGround begin];
    [background2 visit];
    [mineBackGround end];
    */
    
    this->backgroundTexture = CCRenderTexture::create(2000, 800);
    this->backgroundTexture->setPosition(DataManager->screenSize.width/2,DataManager->screenSize.height/2);
    
    this->gameLayer->addChild(this->backgroundTexture);
    
    this->setPosition(position);
    this->setTag(tag);
    this->gameLayer->addChild(this);
}
