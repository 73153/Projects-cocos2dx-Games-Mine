//
//  ZIUtility.cpp
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//
//

#include "ZIUtility.h"
#include "box2d.h"

USING_NS_CC;

ZIUtility::ZIUtility(void) { }

ZIUtility::~ZIUtility(void) { }

int ZIUtility::getRandomNumberBetween(int min, int max) {
    
    int toNumber = max + 1;
    int fromNumber = min;
    
    int randomNumber = (arc4random()%(toNumber-fromNumber))+fromNumber;
    
    return randomNumber;
}

float ZIUtility::getAngleBetweenPoints(CCPoint startPoint,CCPoint ePoint) {
    
    CCPoint difference = ccpSub(ePoint,startPoint);
    double angle = -1 * (atan2(difference.y, difference.x) * 180 / M_PI + 90) + 180;
    
    // Making the negative values into positive+...
    if(angle < 0) {
        
        angle = 270 + (90 + angle);
    }
    
    return angle;
}

CCRect ZIUtility::rectForSprite(CCSprite* sprite) {
    
    float w = sprite->getContentSize().width;
    float h = sprite->getContentSize().height;
	float x = sprite->getPosition().x - w/2;
	float y = sprite->getPosition().y - h/2;
    
	CCRect rect = CCRectMake(x,y,w,h);
	return rect;
}

//Box 2d
//bool ZIUtility::checkCollisionWithBox2dBody(b2Body* inBody, CCPoint touchLocationPoint)
//{
//    b2Vec2 locationWorld = b2Vec2(touchLocationPoint.x/PTM_RATIO, touchLocationPoint.y/PTM_RATIO);
//    
//    b2AABB aabb;
//    b2Vec2 d;
//    d.Set(0.001f, 0.001f);
//    aabb.lowerBound = locationWorld - d;
//    aabb.upperBound = locationWorld + d;
//    
//    MouseJointQueryCallback callback(locationWorld);
//    world->QueryAABB(&callback, aabb);
//    
//    if (callback.m_fixture)
//    {
//        if(callback.m_fixture->GetBody() == inBody)
//        {
//            return true;
//        }
//    }
//    return false;
//}


