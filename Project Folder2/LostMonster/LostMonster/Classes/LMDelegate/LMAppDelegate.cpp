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
#include "LMMainScreen.h"
#include "LMDataManager.h"
#include "LMMainScreenLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

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
  
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);
    
    
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    CCSize designSize;
    CCSize resourceSize;
    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
    
    if (screenSize.height > 768)
    {
        resourceSize = CCSizeMake(2048, 1536);
        std::vector<std::string> searchPaths;
        searchPaths.push_back("resources-ipadhd");
        pFileUtils->setSearchPaths(searchPaths);
    }
    else
    {
        resourceSize = CCSizeMake(1024, 768);
        //  CCFileUtils::sharedFileUtils()->setResourceDirectory("sd");
        
    }
    designSize = CCSizeMake(1024, 768);
    pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionExactFit);
    


    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    LMDataManager::sharedManager()->showIntroVideo = true;

    // create a scene. it's an autorelease object
    //CCScene *pScene = LMMainScreen::scene();
    
    CCNodeLoaderLibrary *pNodeLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    pNodeLibrary->registerCCNodeLoader("MenuTestLayer", LMMainScreenLoader::loader());
    
    cocos2d::extension::CCBReader *pReader = new cocos2d::extension::CCBReader(pNodeLibrary);
    LMDataManager::sharedManager()->cocosBuilderReader = pReader;
    pReader->autorelease();
    
    CCScene *mainScene = pReader->createSceneWithNodeGraphFromFile("MainMenu.ccbi");


    // run
    pDirector->runWithScene(mainScene);

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
