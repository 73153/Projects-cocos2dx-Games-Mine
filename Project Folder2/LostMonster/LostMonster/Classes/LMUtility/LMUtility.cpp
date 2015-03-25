//
//  LMUtility.cpp
//  Dominoes
//
//  Created by ICRG LABS on 25/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "LMUtility.h"
#include "LMConfig.h"
#include "LMDataManager.h"

USING_NS_CC;

LMUtility::LMUtility(void) { }

LMUtility::~LMUtility(void) { }

int LMUtility::getRandomNumberBetween(int min, int max) {
       
    int toNumber = max + 1;
    int fromNumber = min;
    
    int randomNumber = (arc4random()%(toNumber-fromNumber))+fromNumber;
    
    return randomNumber;
}

float LMUtility::getAngleBetweenPoints(CCPoint startPoint,CCPoint ePoint) {
    
    CCPoint difference = ccpSub(ePoint,startPoint);
    double angle = -1 * (atan2(difference.y, difference.x) * 180 / M_PI + 90) + 180;
    
    // Making the negative values into positive+...
    if(angle < 0) {
        
        angle = 270 + (90 + angle);
    }
    angle= angle+180;
    
    
//    float angle = atan2(startPoint.y - ePoint.y, startPoint.x - ePoint.x) * (180 / M_PI);
//	angle = angle < 0 ? angle + 360 : angle;
   // angle = angle+270;
    return angle;
}

CCRect LMUtility::rectForSprite(CCSprite* sprite) {

    float w = sprite->getContentSize().width;
    float h = sprite->getContentSize().height;
	float x = sprite->getPosition().x - w/2;
	float y = sprite->getPosition().y - h/2;
    
	CCRect rect = CCRectMake(x,y,w,h);
	return rect;
}

CCPoint LMUtility::convertVectortoPixels(b2Vec2 vec)
{
    return ccpMult(CCPointMake(vec.x, vec.y), PTM_RATIO);
}


bool LMUtility::bodiesAreTouching( b2Body* body1, b2Body* body2 )
{
	for (b2ContactEdge* edge = body1->GetContactList(); edge; edge = edge->next)
	{
		if ( !edge->contact->IsTouching() )
			continue;
		b2Body* bA = edge->contact->GetFixtureA()->GetBody();
		b2Body* bB = edge->contact->GetFixtureB()->GetBody();
		if ( ( bA == body1 && bB == body2 ) || ( bB == body1 && bA == body2 ) )
			return true;
	}
	return false;
}

bool LMUtility::doSpriteExistWithTag(int sprTag,CCLayer *inLayer)
{
    CCSprite *lockSpr = (CCSprite *)inLayer->getChildByTag(sprTag);
    if (lockSpr) {
        return true;
    }
    return false;
}

void LMUtility::loadCocosBuilderFileWithPathAndLoader(const char *inPath,const char *loaderName, CCNodeLoader * pCCNodeLoader)
{
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    CCNodeLoaderLibrary *pNodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    pNodeLibrary->registerCCNodeLoader(loaderName,pCCNodeLoader);
    
    cocos2d::extension::CCBReader *pReader = new cocos2d::extension::CCBReader(pNodeLibrary);
    LMDataManager::sharedManager()->cocosBuilderReader = pReader;
    pReader->autorelease();
    
    CCScene *mainScene = pReader->createSceneWithNodeGraphFromFile(inPath);
    
    // run
    pDirector->replaceScene(CCTransitionFade::create(0.5, mainScene, ccc3(0,0,0)));
    
}

void LMUtility::rotateNodeWithClockwiseDirection(CCNode *inNode,bool isClockWise,float duration)
{
    float startAngle = 180;
    float endAngle = 360;
    if (!isClockWise) {
        startAngle = startAngle*-1;
        endAngle = endAngle *-1;
    }
    
    CCRotateTo *rotateActOne = CCRotateTo::create(duration, startAngle);
    CCRotateTo *rotateActTwo = CCRotateTo::create(duration, endAngle);
    CCSequence *rotateSequence = CCSequence::createWithTwoActions(rotateActOne, rotateActTwo);
    CCRepeatForever *repeatAction = CCRepeatForever::create(rotateSequence);
    inNode->runAction(repeatAction);
    
}


