#include "HelloWorldScene.h"

#include "cocos-ext.h"

#include "CCBReader.h"

#import "CCBSequence.h"
#include "HelloWorldSceneLoader.h"

using namespace cocos2d;
USING_NS_CC_EXT;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    ccNodeLoaderLibrary->registerCCNodeLoader("HelloWorld", HelloWorldSceneLoader::loader());
    
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    ccbReader->autorelease();
    
    animationsTestNode = ccbReader->readNodeGraphFromFile("dogAnim.ccbi", this);
    animationManager = ccbReader->getAnimationManager();
        
    this->addChild(animationsTestNode);
    
    this->menuCloseCallback(this);
    
    return true;
}
HelloWorld::~HelloWorld()
{
    CC_SAFE_RELEASE(animationManager);
}


void HelloWorld::setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager)
{
    animationManager->runAnimationsForSequenceNamed("dogAnim");
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
//   animationManager->runAnimationsForSequenceNamed("DogClapping");
//    animationManager->runAnimationsForSequenceNamed("BBDogAnim");

}
