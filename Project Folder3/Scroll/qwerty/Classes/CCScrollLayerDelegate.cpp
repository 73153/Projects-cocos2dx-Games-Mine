//  CCScrollLayer.cpp
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010. All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011

#include "CCScrollLayer.h"

using namespace cocos2d;

CCScrollLayer* CCScrollLayer::nodeWithLayers(CCArray*  layers, int widthOffset)
{
    CCScrollLayer *pRet = new CCScrollLayer();
    if (pRet && pRet->initWithLayers(layers, widthOffset))
    {
        pRet->autorelease();
        return pRet;
    }
    CCX_SAFE_DELETE(pRet);
    return NULL;
}

bool CCScrollLayer::initWithLayers(CCArray* layers, int widthOffset)
{
    if (CCLayer::init())
    {
        // Make sure the layer accepts touches
        CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
        
        // Set up the starting variables
        //if(!widthOffset)
        {
            //  widthOffset = 0;
        }
        currentScreen = 1;
        
        // offset added to show preview of next/previous screens
        scrollWidth  = (int)CCDirector::sharedDirector()->getWinSize().width - widthOffset;
        scrollHeight = (int)CCDirector::sharedDirector()->getWinSize().height;
        startWidth = scrollWidth;
        startHeight = scrollHeight;
        
        // Loop through the array and add the screens
        unsigned int i;
        for (i=0; i<layers->count(); i++)
        {
            CCLayer* l = (CCLayer*)layers->objectAtIndex(i);
            //l->setAnchorPoint(ccp(0,0));
            //l->setPosition(ccp((i*scrollWidth),0));
            addChild(l);
        }
        
        // Setup a count of the available screens
        totalScreens = layers->count();
        return true;
    }
    else
    {
        return false;
    }
}

void CCScrollLayer::setMaximumScrollHeight(float maxHeight)
{
    //Make the offset match expected pixels (include the current screen if at ccp(0,0)
    maxHeight -= CCDirector::sharedDirector()->getWinSize().height;
    maximumScrollHeight = maxHeight;
}

CCScrollLayer::~CCScrollLayer()
{
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

bool CCScrollLayer::ccTouchBegan(CCTouch *touch, CCEvent *withEvent)
{
    //
    //  CCPoint touchPoint = touch->locationInView();
    //  touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    //
    //  startSwipe = (int)touchPoint.y;
    return true;
}

void CCScrollLayer::ccTouchMoved(CCTouch *touch, CCEvent *withEvent)
{
    CCPoint touchPoint = touch->locationInView();
    CCPoint prevPoint = touch->previousLocationInView();
    
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    prevPoint = CCDirector::sharedDirector()->convertToGL(prevPoint);
    
    CCPoint difference = ccp( touchPoint.x - prevPoint.x , touchPoint.y - prevPoint.y);
    CCPoint currentPos = this->getPosition();
    
    currentPos = ccp( currentPos.x, currentPos.y+difference.y);
    
    if (currentPos.y > maximumScrollHeight)
    {
        currentPos.y = maximumScrollHeight;
        //this->setPositionY(maximumScrollHeight);
    }
    else if (currentPos.y < 0)
    {
        currentPos.y = 0;
        // this->setPositionY(0);
    }
    this->setPosition(currentPos);
}

/*
 void CCScrollLayer::ccTouchEnded(CCTouch *touch, CCEvent *withEvent)
 {
 
 //CCPoint touchPoint = touch->locationInView();
 //touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
 
 int newX = (int)touchPoint.x;
 
 if ( (newX - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
 {
 //  this->moveToNextPage();
 }
 else if ( (newX - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
 {
 //  this->moveToPreviousPage();
 }
 else
 {
 //  this->moveToPage(currentScreen);
 }   
 
 }
 */