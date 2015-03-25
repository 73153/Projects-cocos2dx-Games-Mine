//
//  LostMonsterAppDelegate.cpp
//  LostMonster
//
//  Created by Krithik B on 8/20/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "LMAppDelegate.h"

#include "cocos2d.h"
#include "LMGameLayer.h"
#include "LMMenuScene.h"
#include "LMMainScreen.h"

USING_NS_CC;

LMAppDelegate::LMAppDelegate()
{

}

LMAppDelegate::~LMAppDelegate()
{
}

bool LMAppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    TargetPlatform target = getTargetPlatform();
    
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    pDirector->enableRetinaDisplay(true);
    
    if (target == kTargetIphone)
    {
        // iphone
        if (pDirector->enableRetinaDisplay(true))
        {
            // iphone hd
            CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
        }        else
        {
            // iphone normal
            CCFileUtils::sharedFileUtils()->setResourceDirectory("sd");
       }
    }
    


    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = LMMainScreen::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void LMAppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void LMAppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
