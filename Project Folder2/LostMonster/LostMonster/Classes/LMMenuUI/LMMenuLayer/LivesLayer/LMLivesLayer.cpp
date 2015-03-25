//
//  LMLivesLayer.cpp
//  LMGame
//
//  Created by Pavitra on 03/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMLivesLayer.h"
#include "LMMainScreen.h"
#include "LMDataManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "LMObjectiveCCalls.h"

#else

#endif

using namespace cocos2d;


CCScene* LMLivesLayer::scene(){
    
    CCScene *Scene=CCScene::create();
    
    LMLivesLayer *livesScene = new LMLivesLayer();
    Scene->addChild(livesScene);
    livesScene->release();
    
    return Scene;
}




LMLivesLayer::LMLivesLayer(){
    
    float width=CCDirector::sharedDirector()->getWinSize().width;
    float height=CCDirector::sharedDirector()->getWinSize().height;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LMStoreScene.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("LMStoreScene.plist");

    //bg
    CCSprite *liveseBG=CCSprite::create("ui_popup_bg.png");
    liveseBG->setPosition(CCPointMake(width/2, height/2));
    this->addChild(liveseBG,10);
    
    //live icon on top
    CCSprite *topLiveIcon=CCSprite::createWithSpriteFrameName("lives_icon_big.png");
    topLiveIcon->setPosition(CCPointMake(width/2-130, height-190));
    this->addChild(topLiveIcon,11);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    int totalLives = LMObjectiveCCalls::getTotalLivesCount();
    int totalRegenaratedLives = LMObjectiveCCalls::getTotalRegeneratedLivesCount();
    int totalAcquiredLives = LMObjectiveCCalls::getTotalAcquiredLives();
#else
    
#endif

    
    //my live label
    CCLabelTTF *myLiveslabel=CCLabelTTF::create("My Lives", "LMVeraHumana95Bold", 35);
    myLiveslabel->setPosition(CCPointMake( width/2+10, height-190));
    myLiveslabel->setColor(ccc3(76,54,12));
    this->addChild(myLiveslabel,12);

    
    
    //lives colm
    CCSprite *livesColumn=CCSprite::createWithSpriteFrameName("my_lives_colm_bg.png");
    livesColumn->setPosition(CCPointMake(width/2+5, height/2-30));
    livesColumn->setScale(0.95);
    this->addChild(livesColumn,12);
    
    //total Lives label
    
    CCLabelTTF *totalLiveslabel=CCLabelTTF::create("My Lives Total", "LMVeraHumana95Bold", 25);
    totalLiveslabel->setPosition(CCPointMake( width/2-225, height/2+90));
    totalLiveslabel->setColor(ccc3(236, 213, 139));
    this->addChild(totalLiveslabel,12);
    
    char  noOfTotalLivesNumber[5];
    sprintf(noOfTotalLivesNumber, "%d",totalLives);
    CCLabelTTF *totalLivesNumberLabel=CCLabelTTF::create(noOfTotalLivesNumber, "LMVeraHumana95Bold", 25);
    totalLivesNumberLabel->setPosition(CCPointMake(770, height/2+90));
    totalLivesNumberLabel->setColor(ccc3(236, 213, 139));
    this->addChild(totalLivesNumberLabel,12);
    
    float xOffset=515;
    float yOffset=395;
    for(int i=0;i<2;i++)
    {
        CCSprite *storeColumn=CCSprite::createWithSpriteFrameName("store_colm.png");
        storeColumn->setPosition(CCPointMake(xOffset, yOffset));
        this->addChild(storeColumn,11);
        
        //live icon
        CCSprite *livesIcon=CCSprite::createWithSpriteFrameName("lives_icon.png");
        livesIcon->setPosition(CCPointMake(xOffset-275, yOffset));
        this->addChild(livesIcon,12);
        yOffset=yOffset-75;

    }
    //store column
      
    //Regenerated lives label
    
    CCLabelTTF *regeneratedLiveslabel=CCLabelTTF::create("Regenerated Lives (max 5)", "LMVeraHumana95Bold", 32);
    regeneratedLiveslabel->setColor(ccc3(181, 141, 60));
    regeneratedLiveslabel->setPosition(CCPointMake( 480, 390));
    this->addChild(regeneratedLiveslabel,13);

    
    char  noOfLivesNumber[5];
    sprintf(noOfLivesNumber, "%d",totalRegenaratedLives);
    CCLabelTTF *regeneratedNumberLabel=CCLabelTTF::create(noOfLivesNumber, "LMVeraHumana95Bold", 32);
   regeneratedNumberLabel->setPosition(CCPointMake(775, 390));
    regeneratedNumberLabel->setColor(ccc3(76,54,13));
    this->addChild(regeneratedNumberLabel,13);
    
    
    //acquired lives label
    CCLabelTTF *acquiredLiveslabel=CCLabelTTF::create("Acquired Lives", "LMVeraHumana95Bold", 32);
    acquiredLiveslabel->setColor(ccc3(181, 141, 60));
    acquiredLiveslabel->setPosition(CCPointMake( 390, 320));
    this->addChild(acquiredLiveslabel,13);
    

    char noOfAcquiredLivesNumber[5];
    sprintf(noOfAcquiredLivesNumber, "%d",totalAcquiredLives);
    CCLabelTTF *acquiredLivesNumberLabel=CCLabelTTF::create(noOfAcquiredLivesNumber, "LMVeraHumana95Bold", 32);
    acquiredLivesNumberLabel->setPosition(CCPointMake(775, 320));
    acquiredLivesNumberLabel->setColor(ccc3(76,54,12));
    this->addChild(acquiredLivesNumberLabel,13);

        
    //bottom label
    CCLabelTTF *livesText=CCLabelTTF::create("Lives regenerated will be used first", "LMVeraHumana95Bold", 22);
    livesText->setPosition(CCPointMake( width/2, height/2-215));
    livesText->setColor(ccc3(76,54,12));
    this->addChild(livesText,11);
    
}


LMLivesLayer::~LMLivesLayer(){
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("LMStoreScene.plist");

}
