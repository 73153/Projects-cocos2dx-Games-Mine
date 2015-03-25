//
//  LostMonsterAppDelegate.cpp
//  LostMonster
//
//  Created by Krithik B on 25/02/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#include "LMMainScreen.h"
#include "LMMainScreenLoader.h"
#include "LMDataManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace CocosDenshion;

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
    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    
    std::vector<std::string> searchPaths;
    
    if (screenSize.height > 768)
    {
        resourceSize = CCSizeMake(2048,1536);
        searchPaths.push_back("HD");
    }
    else
    {
        resourceSize = CCSizeMake(1024, 768);
        searchPaths.push_back("SD");
    }
    pFileUtils->setSearchPaths(searchPaths);

    designSize = CCSizeMake(1024, 768);
    pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);
    
    
    
    // turn on display FPS
    pDirector->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    LMDataManager::sharedManager()->showIntroVideo = true;
    
 
    CCNodeLoaderLibrary *pNodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    pNodeLibrary->registerCCNodeLoader("LMMainScreen", LMMainScreenLoader::loader());
    
    cocos2d::extension::CCBReader *pReader = new cocos2d::extension::CCBReader(pNodeLibrary);
    LMDataManager::sharedManager()->cocosBuilderReader = pReader;
    pReader->autorelease();
    
    CCScene *mainScene = pReader->createSceneWithNodeGraphFromFile("CocosBuilder/MainMenu/MainMenu.ccbi");
    
    // run
    pDirector->runWithScene(mainScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
