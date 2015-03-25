//
//  BaccizBooksAppDelegate.cpp
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 21/01/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "BBGameSelection.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    CCSize designSize;
    CCSize resourceSize;
    
    if (screenSize.height > 768)
    {
        
       resourceSize = CCSizeMake(2048, 1536);
        CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
        
    }
    else
    {
        
      resourceSize = CCSizeMake(1024, 768);
        CCFileUtils::sharedFileUtils()->setResourceDirectory("sd");
        
    }
    designSize = CCSizeMake(1024, 768);
    pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    //    CCFileUtils::sharedFileUtils()->setResourceDirectory("sd");
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);
    


    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = BBGameSelection::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->stopAnimation();
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
