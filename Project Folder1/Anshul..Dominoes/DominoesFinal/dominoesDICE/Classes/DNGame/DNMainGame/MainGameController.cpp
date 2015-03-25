#include "MainGameController.h"
#include "SimpleAudioEngine.h"
#include "DNGameConstants.h"
#include "DNDataManager.h"
#include "DNUtility.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MainGameController::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
        
    // Creating the UI Layer
    CCLayer *staticLayer = CCLayer::create();
    scene->addChild(staticLayer,5);
    DataManager->UILayer = staticLayer;
    
    // 'layer' is an autorelease object
    MainGameController *layer = MainGameController::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

MainGameController::~MainGameController()
{
    printf("main controller destructor \n\n\n\n");
    
    delete this->dominoManager;
    delete this->uiManager;
    delete this->backgroundManager;
    delete this->scheduleManager;
    delete this->jniCommunicator;
    delete this->playerpanel;
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("btn_animal_timer.plist");
}

// on "init" you need to initialize your instance
bool MainGameController::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // Assigning the main game layer into shared manager...
    DataManager->gameLayer = this;
    DataManager->screenSize = CCDirector::sharedDirector()->getWinSize();
    
    // Enabling touches
    this->setTouchEnabled(true);
     
/* 
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MainGameController::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // Create Backgorund
 
    CCSprite *sprite = CCSprite::create("background.png");
    sprite->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
    this->addChild(sprite);
    
    // create menu, it's an autorelease object
 
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL); 
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
*/    
    // Datamanager Test... Fist run it should print 0 
    printf("score is %d",DNDataManager::sharedManager()->score);
    
    // Scheduling the main tick timer...
    schedule( schedule_selector(MainGameController::mainTimer));

    // Loading the spritesheets
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("dominoes_new.plist");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("btn_animal_timer.plist");
  
//    DNUtility::addGameAnimationsToAnimationCache("dominoes.plist");
    // Initiating the manager
    
    this->uiManager = new DNUIManager();
    this->dominoManager = new DNDominoManager();
    this->backgroundManager = new DNBackgroundManager();
    this->scheduleManager = new DNScheduleManager();
    this->jniCommunicator = new DNJNICommunicator();
    this->playerpanel = new DNPlayerPanel();
    
    CCArray *anArray = CCArray::create();
    
    this->jniCommunicator->getArray(anArray);
    
    return true; 
}

void MainGameController::draw() {
    
    this->backgroundManager->draw();
}

void MainGameController::mainTimer(void) {
    
    // Passing the schedule to the managers!
//    this->dominoManager->dominoManagerTick();
    
    // Datamanager test... 
    DNDataManager::sharedManager()->score = 100;
}

void MainGameController::ccTouchesBegan(cocos2d::CCSet *touches, cocos2d::CCEvent *event){
    
    // Passing the touches to the managers!
    this->dominoManager->dominoesManagerTouchesBegan(touches);
    this->backgroundManager->backgroundManagerTouchesBegan(touches);
    this->uiManager->UIManagerTouchesBegan(touches);
}

void MainGameController::ccTouchesMoved(cocos2d::CCSet *touches, cocos2d::CCEvent *event) {
     
    // Passing the touches to the managers!
    this->dominoManager->dominoesManagerTouchesMoved(touches);
    this->backgroundManager->backgroundManagerTouchesMoved(touches);
    this->uiManager->UIManagerTouchesMoved(touches);
}

void MainGameController::ccTouchesEnded(cocos2d::CCSet *touches, cocos2d::CCEvent *event) {
    
    // Passing the touches to the managers!
    this->dominoManager->dominoesManagerTouchesEnded(touches);
    this->backgroundManager->backgroundManagerTouchesEnded(touches);
    this->uiManager->UIManagerTouchesEnded(touches);
}

void MainGameController::ccTouchesCancelled(cocos2d::CCSet *touches, cocos2d::CCEvent *event) {
    
    // Passing the touches to the managers!
    this->dominoManager->dominoesManagerTouchesCancelled(touches);
    this->backgroundManager->backgroundManagerTouchesCancelled(touches);
    this->uiManager->UIManagerTouchesCancelled(touches);
}

void MainGameController::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainGameController::restartScene() {
    
    CCDirector::sharedDirector()->replaceScene(this->scene());
    
    DataManager->opponentOneTileCount = 0;
    DataManager->opponentTwoTileCount = 0;
    DataManager->playerTileCount = 0;
    
    DataManager->min = 0;
    DataManager->sec = 0;
}
