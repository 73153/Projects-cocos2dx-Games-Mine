//
//  LMLine.cpp
//  LostMonster
//
//  Created by Krithik B on 8/23/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#include <iostream>
#include "LMLine.h"

using namespace cocos2d;


LMLine::LMLine()
{
    this->isActive = false;
}

LMLine::~LMLine()
{
    CCLog("Dealloc in LMLine");
}


#pragma mark - Draw
void LMLine::draw()
{
    //
    // DRAWS THE LINE FROM START POINT TO END POINT ONLY WHEN ACTIVE:
    //
    
    if(this->isActive)
    {
        CCNode::draw();
        
        ccDrawColor4B(0.0,0.0,0.0,255.0);
        glLineWidth(2);
        
        ccDrawLine(this->startPoint,this->endPoint);	
    }
}


#pragma mark - Reset Line

void LMLine::startWithLocation(CCPoint startPosition)
{
    this->startPoint = startPosition;
    this->endPoint = startPosition;
    this->isActive = true;
}

void LMLine::resetLine()
{
    this->startPoint = CCPointZero;
    this->endPoint = CCPointZero;
    this->isActive = false;
}