//
//  DNUtility.cpp
//  Dominoes
//
//  Created by ICRG LABS on 25/07/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "DNUtility.h"

USING_NS_CC;

DNUtility::DNUtility(void) { }

DNUtility::~DNUtility(void) { }

int DNUtility::getRandomNumberBetween(int min, int max) {
       
    int toNumber = max + 1;
    int fromNumber = min;
    
    int randomNumber = (arc4random()%(toNumber-fromNumber))+fromNumber;
    
    return randomNumber;
}

float DNUtility::getAngleBetweenPoints(CCPoint startPoint,CCPoint ePoint) {
    
    CCPoint difference = ccpSub(ePoint,startPoint);
    double angle = -1 * (atan2(difference.y, difference.x) * 180 / M_PI + 90) + 180;
    
    // Making the negative values into positive+...
    if(angle < 0) {
        
        angle = 270 + (90 + angle);
    }
    
    return angle;
}

CCRect DNUtility::rectForSprite(CCSprite* sprite) {

    float w = sprite->getContentSize().width;
    float h = sprite->getContentSize().height;
	float x = sprite->getPosition().x - w/2;
	float y = sprite->getPosition().y - h/2;
    
	CCRect rect = CCRectMake(x,y,w,h);
	return rect;
}

