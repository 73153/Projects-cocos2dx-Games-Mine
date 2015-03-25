//
//  DNUIManager.cpp
//  Dominoes
//
//  Created by ICRG LABS on 28/08/12.
//
//

#include "DNUIManager.h"
#include "DNDataManager.h"
#include "DNGameConstants.h"
#include "MainGameController.h"
#include "DNBackgroundManager.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC;

CCScene* DNUIManager::scene()
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


DNUIManager::DNUIManager(void) {
    
    this->gameLayer = DataManager->gameLayer;
    score = CCLabelTTF::create("", "Arial",50);
    //this->gameLayer->dominoManager->addChild(score);
    DataManager->UILayer->addChild(this->score);
    score->setPosition(ccp(500,500));

    
    // Creating Side Bar
    this->gameBar = this->gameBar->spriteWithFrame("game_bar.png");
    this->gameBar->setPosition(ccp(0 + this->gameBar->getContentSize().width/2, DataManager->screenSize.height/2));
    this->gameBar->setVisible(true);
    DataManager->UILayer->addChild(this->gameBar);
    
    // Setup gamebar UI
    this->setupGameBarMenuBtns();
    
    // Initialize Values
    DataManager->boardCenterRect = CCRectMake(100, 100, DataManager->screenSize.width - 100, DataManager->screenSize.height - 100);
    
    this->playerPanel1 = NULL;
    this->playerPanel2 = NULL;
    this->playerPanel3 = NULL;

    // Initiating Arrays...
    this->panelsArray = CCArray::create();
    this->panelsArray->retain();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("btn_animal_timer.plist");
    
    // Getting Number of tiles per head
    if (DataManager->opponentCount == 1) {
        
        this->numberOfTilesPerHead = 7;
    }
    else {
        
        this->numberOfTilesPerHead = 5;
    }
    
    this->onPause = false;
    this->onResume = true;    // Setting up UI for Players
    
    this->setupPlayer();
    
    this->setupOpponents();
    
    this->startTimerAnimation();
    
//    schedule_selector(DNUIManager::startTimerAnimation());
}


DNUIManager::~DNUIManager(void) {
    
    CC_SAFE_RELEASE_NULL(this->panelsArray);
    CCLog("ui manager destructor is called");
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("btn_animal_timer.plist");
}


// Players Panel
void DNUIManager::setupPlayer() {
    
    float startingPoint = this->gameBar->getContentSize().width;
    
    this->playerPanel1 = this->playerPanel1->spriteWithFrame("player_area_not-in-play.png");
    this->playerPanel1->createPanel(ccp(startingPoint + (DataManager->screenSize.width - startingPoint)/2, 0), ccp(0.5, 0), false, kPlayerPanel1Tag);
    this->panelsArray->addObject(this->playerPanel1);
}


#pragma mark -Animatiuon
void DNUIManager::startTimerAnimation(){
    
    playerPanel1->setColor(ccc3(255, 0, 0));
    
    yellow = CCSprite::createWithSpriteFrameName("yellow.png");
    yellow->setPosition( ccp(this->gameBar->getContentSize().width/5 + 3,this->gameBar->getPosition().y + 102));
    yellow->setAnchorPoint(CCPointZero);
    gameBar->addChild(yellow);

    CCScaleTo *scaleYellow = CCScaleTo::create(6.0f, 1, 0.9);
    CCScaleTo *scaleYellow1 = CCScaleTo::create(6.0f, 1, 0.8);
    CCScaleTo *scaleYellow2 = CCScaleTo::create(6.0f, 1, 0.7);
    CCScaleTo *scaleYellow3 = CCScaleTo::create(6.0f, 1, 0.6);
    CCScaleTo *scaleYellow4 = CCScaleTo::create(6.0f, 1, 0.5);
    CCScaleTo *scaleYellow5 = CCScaleTo::create(6.0f, 1, 0.4);
    CCScaleTo *scaleYellow6 = CCScaleTo::create(6.0f, 1, 0.3);
    CCScaleTo *scaleYellow7 = CCScaleTo::create(6.0f, 1, 0.2);
    CCScaleTo *scaleYellow8 = CCScaleTo::create(6.0f, 1, 0.1);
    CCScaleTo *scaleYellow9 = CCScaleTo::create(6.0f, 1, 0.0);
    
    CCFiniteTimeAction *yellowSeq = CCSequence::create(scaleYellow, scaleYellow1,scaleYellow2,scaleYellow3,scaleYellow4,scaleYellow5,scaleYellow6,scaleYellow7,scaleYellow8,scaleYellow9,NULL);
    yellow->runAction(yellowSeq);
    
    
    orange = CCSprite::createWithSpriteFrameName("orange.png");
    orange->setPosition( ccp(this->gameBar->getContentSize().width/5 + 3,this->gameBar->getPosition().y + 26) );
    gameBar->addChild(orange);
    orange->setAnchorPoint(CCPointZero);

    CCScaleTo *scaleOrange = CCScaleTo::create(6.0f, 1, 0.9);
    CCScaleTo *scaleOrange1 = CCScaleTo::create(6.0f, 1, 0.8);
    CCScaleTo *scaleOrange2 = CCScaleTo::create(6.0f, 1, 0.7);
    CCScaleTo *scaleOrange3 = CCScaleTo::create(6.0f, 1, 0.6);
    CCScaleTo *scaleOrange4 = CCScaleTo::create(6.0f, 1, 0.5);
    CCScaleTo *scaleOrange5 = CCScaleTo::create(6.0f, 1, 0.4);
    CCScaleTo *scaleOrange6 = CCScaleTo::create(6.0f, 1, 0.3);
    CCScaleTo *scaleOrange7 = CCScaleTo::create(6.0f, 1, 0.2);
    CCScaleTo *scaleOrange8 = CCScaleTo::create(6.0f, 1, 0.1);
    CCScaleTo *scaleOrange9 = CCScaleTo::create(6.0f, 1, 0.0);
    
    CCFiniteTimeAction *orangeSeq = CCSequence::create(CCDelayTime::create(60.0f),scaleOrange, scaleOrange1,scaleOrange2,scaleOrange3,scaleOrange4,scaleOrange5,scaleOrange6,scaleOrange7,scaleOrange8,scaleOrange9,NULL);
    orange->runAction(orangeSeq);
    
    
    red = CCSprite::createWithSpriteFrameName("red.png");
    red->setPosition( ccp(this->gameBar->getContentSize().width/5 + 3,this->gameBar->getPosition().y - 46));
    gameBar->addChild(red);
    red->setAnchorPoint(CCPointZero);

    CCScaleTo *scaleRed = CCScaleTo::create(6.0f, 1, 0.9);
    CCScaleTo *scaleRed1 = CCScaleTo::create(6.0f, 1, 0.8);
    CCScaleTo *scaleRed2 = CCScaleTo::create(6.0f, 1, 0.7);
    CCScaleTo *scaleRed3 = CCScaleTo::create(6.0f, 1, 0.6);
    CCScaleTo *scaleRed4 = CCScaleTo::create(6.0f, 1, 0.5);
    CCScaleTo *scaleRed5 = CCScaleTo::create(6.0f, 1, 0.4);
    CCScaleTo *scaleRed6 = CCScaleTo::create(6.0f, 1, 0.3);
    CCScaleTo *scaleRed7 = CCScaleTo::create(6.0f, 1, 0.2);
    CCScaleTo *scaleRed8 = CCScaleTo::create(6.0f, 1, 0.1);
    CCScaleTo *scaleRed9 = CCScaleTo::create(6.0f, 1, 0.0);
    
    CCFiniteTimeAction *RedSeq = CCSequence::create(CCDelayTime::create(120.0f), scaleRed, scaleRed1, scaleRed2, scaleRed3, scaleRed4, scaleRed5, scaleRed6, scaleRed7, scaleRed8, scaleRed9, NULL);
    red->runAction(RedSeq);

    
    CCCallFunc *opponentsTilOpen = CCCallFunc::create(this,callfunc_selector(DNUIManager::opponentsTilesOpen));
    
    CCCallFunc *gameover = CCCallFunc::create(this,callfunc_selector(DNUIManager::callback));
    
    CCCallFunc *pause = CCCallFunc::create(this,callfunc_selector(DNUIManager::pause));
    
    CCFiniteTimeAction *Seq = CCSequence::create(CCDelayTime::create(180.0f),opponentsTilOpen,CCDelayTime::create(0.5f) ,gameover, pause, NULL);
    
    this->gameBar->runAction(Seq);
}


void DNUIManager::opponentsTilesOpen()
{
    CCObject *pObj;  // open tiles for the opponents without placing any tiles
    
    CCARRAY_FOREACH(this->gameLayer->dominoManager->opponentOneArray, pObj) {
        
        DNDomino *aDomino = (DNDomino *)pObj;
        aDomino->setVisible(true);
    }
    CCARRAY_FOREACH(this->gameLayer->dominoManager->opponentTwoArray, pObj) {
        
        DNDomino *aDomino = (DNDomino *)pObj;
        aDomino->setVisible(true);
    }
    CCARRAY_FOREACH(this->gameLayer->dominoManager->backTileArray, pObj) {
        
        DNDomino *aDomino = (DNDomino *)pObj;
        aDomino->setVisible(false);
    }
}


void DNUIManager::callback(){
    
    DataManager->isGameOver = true;
    
//    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Aww.mp3");

    CCSprite *spr = CCSprite::create("end_game_lose_empty.png");
    DataManager->UILayer->addChild(spr);
    spr->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2));
    
    actionMenu->setEnabled(false);
    mainMenu->setEnabled(false);
    playersMenu->setEnabled(false);
//    this->gameLayer->playerpanel->passMenu->setEnabled(false);
    
    CCSprite *gamerWinBackGrd = CCSprite::create("popup_bg.png");
    DataManager->UILayer->addChild(gamerWinBackGrd,1);
    gamerWinBackGrd->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2));
    
//    this->gameLayer->dominoManager->gamerWinBackGrd->setVisible(false);
    
    
    CCSprite *ok_normal = CCSprite::createWithSpriteFrameName("ok_btn1.png");
    CCSprite *ok_selected = CCSprite::createWithSpriteFrameName("ok_pressed.png");
    
    CCMenuItemSprite* restartItem = CCMenuItemSprite::create(ok_normal, ok_selected, this, menu_selector(DNUIManager::restart));
    CCMenu *mainMenu = CCMenu::create(restartItem,NULL);
    mainMenu->alignItemsVerticallyWithPadding(5);
    mainMenu->setPosition(ccp(DataManager->screenSize.width/2 + 50, DataManager->screenSize.height/2 - 175));
    
    DataManager->UILayer->addChild(mainMenu,1);
    
    DataManager->count = 0;
    DataManager->opponenttilecount = 0;
}


void DNUIManager::pause(){
    
    this->gameLayer->uiManager->onPause = true;
    
    DataManager->UILayer->setTouchEnabled(false);
    
    if(DataManager->isGameOver == true){

        if(this->gameLayer->uiManager->onPause){
            
            CCDirector::sharedDirector()->pause();
        }
    }
}
void DNUIManager::restart()
{    
//    this->gameLayer->playerpanel->passMenu->setEnabled(true);
    
    DataManager->isGameOver = false;
    DataManager->gameLayer->restartScene();
    DataManager->count = 0;
    DataManager->playerTileCount = 0;
    DataManager->opponenttilecount = 0;
    DataManager->opponentOneTileCount = 0;
    DataManager->opponentTwoTileCount = 0;
    
    DataManager->min = 0;
    DataManager->sec = 0;
    
    CCDirector::sharedDirector()->resume();
    
    this->gameLayer->uiManager->actionMenu->setEnabled(true);
    this->gameLayer->uiManager->mainMenu->setEnabled(true);
    this->gameLayer->uiManager->playersMenu->setEnabled(true);
}


void DNUIManager::setupOpponents() {
    
    float startingPoint = this->gameBar->getContentSize().width;
    
    if (DataManager->opponentCount == 1) {    // Opponent one panel
        
        this->playerPanel2 = this->playerPanel2->spriteWithFrame("opponent_area_01_not_in_play.png");
        
        DNCustomSprite *rabbit = rabbit->spriteWithFrame("youngbunny-neutral.png");
        rabbit->setRotation(180);
        this->playerPanel2->addChild(rabbit);
        rabbit->setPosition(ccp(rabbit->getContentSize().width/5 + 340,rabbit->getPosition().y + 75));
        
        CCLabelTTF *dragLabel = CCLabelTTF::create("Rabbit", "Helvetica", 40);
        dragLabel->setPosition(ccp(dragLabel->getContentSize().width/5 + 180, dragLabel->getPosition().y+ 80));
        dragLabel->setRotation(180);
        this->playerPanel2->addChild(dragLabel);
        
        this->playerPanel2->createPanel(ccp(startingPoint + (DataManager->screenSize.width - startingPoint)/2, DataManager->screenSize.height - 173), ccp(0.5, 1), true, kPlayerPanel2Tag);
        this->playerPanel2->setRotation(180);
        this->playerPanel2->setFlipX(true);
        this->panelsArray->addObject(this->playerPanel2);
    }
    else if(DataManager->opponentCount == 2) {
        // Opponent one panel
        
        this->playerPanel2 = this->playerPanel2->spriteWithFrame("opponent_area_01_not_in_play.png");

        DNCustomSprite *rabbit = rabbit->spriteWithFrame("youngbunny-neutral.png");
        rabbit->setRotation(180);
        this->playerPanel2->addChild(rabbit);
        rabbit->setPosition(ccp(rabbit->getContentSize().width/5 + 340,rabbit->getPosition().y + 75));
        
        CCLabelTTF *dragLabel = CCLabelTTF::create("Rabbit", "Helvetica", 40);
        dragLabel->setPosition(ccp(dragLabel->getContentSize().width/5 + 180,dragLabel->getPosition().y + 50));
        dragLabel->setRotation(180);
        this->playerPanel2->addChild(dragLabel);
        
        this->playerPanel2->createPanel(ccp(startingPoint + ((DataManager->screenSize.width - startingPoint)/2)/2, DataManager->screenSize.height - 173), ccp(0.5, 1), true, kPlayerPanel2Tag);
        this->playerPanel2->setRotation(180);
        this->playerPanel2->setFlipX(true);
        this->panelsArray->addObject(this->playerPanel2);
        
        // Opponent two panel
        this->playerPanel3 = this->playerPanel3->spriteWithFrame("opponent_area_02_not_in_play.png");
        
        DNCustomSprite *giraffe = giraffe->spriteWithFrame("giraffe-neutral.png");
        giraffe->setRotation(180);
        this->playerPanel3->addChild(giraffe);
        giraffe->setPosition(ccp(giraffe->getContentSize().width/5 + 340,giraffe->getPosition().y + 75));
        
        CCLabelTTF *dragLabel1 = CCLabelTTF::create("Giraffe", "Helvetica", 40);
        dragLabel1->setPosition(ccp(dragLabel1->getContentSize().width/5 + 180,dragLabel1->getPosition().y + 50));
        dragLabel1->setRotation(180);
        this->playerPanel3->addChild(dragLabel1);
        
        this->playerPanel3->createPanel(ccp(startingPoint + (DataManager->screenSize.width - startingPoint)/2 + ((DataManager->screenSize.width - startingPoint)/2)/2, DataManager->screenSize.height - 173), ccp(0.5, 1), true, kPlayerPanel3Tag);
        this->playerPanel3->setRotation(180);
        this->playerPanel3->setFlipX(true);
        this->panelsArray->addObject(this->playerPanel3);
    }
}

void DNUIManager::setupGameBarMenuBtns() {
    
    /*restartItem= CCMenuItemToggle::createWithTarget(this, menu_selector(DNUIManager::menuCallback),
                                              CCMenuItemImage::create("restart_red.png", "restart_red.png"),
                                              CCMenuItemImage::create("restart_hvr.png","restart_hvr.png"),NULL);*/
    
    CCSprite *restart_normal = CCSprite::createWithSpriteFrameName("restart_red.png");
    CCSprite *restart_selected = CCSprite::createWithSpriteFrameName("restart_hvr.png");
    
    restartItem = CCMenuItemSprite::create(restart_normal, restart_selected , this, menu_selector(DNUIManager::menuCallbacks));
    restartItem->setTag(2);
    mainMenu = CCMenu::create(restartItem,NULL);
    mainMenu->alignItemsVerticallyWithPadding(5);
    mainMenu->setPosition(ccp(this->gameBar->getContentSize().width/2,this->gameBar->getContentSize().height - 670));
    DataManager->UILayer->addChild(mainMenu);   
    
/*  
    CCMenuItemToggle *item1 = CCMenuItemToggle::create(    this,
                                                       menu_selector(DNUIManager::menuCallbacks),
                                                       CCMenuItemImage::create("easy_but.png", "easy_but_hvr.png"),
                                                       CCMenuItemImage::create("medium_but.png", "medium_but_hvr.png"),
                                                       CCMenuItemImage::create( "hard_but.png", "hard_but_hvr.png"),
                                                       NULL );
    
    
    CCMenu *difficultyMenu = CCMenu::create(item1,NULL);
    difficultyMenu->setPosition(ccp(this->gameBar->getContentSize().width/2,this->gameBar->getContentSize().height - 300));
    DataManager->UILayer->addChild(difficultyMenu);
*/
    
    CCSprite *pause_normal = CCSprite::createWithSpriteFrameName("pause_btn1.png");
    CCSprite *pause_selected = CCSprite::createWithSpriteFrameName("button_pause.png");
    
    CCSprite *play_normal = CCSprite::createWithSpriteFrameName("play_btn1.png");
    CCSprite *play_selected = CCSprite::createWithSpriteFrameName("button_play.png");
    
    item2= CCMenuItemToggle::createWithTarget(this, menu_selector(DNUIManager::menuCallback),                             
                                              CCMenuItemSprite::create(pause_normal, pause_selected),
                                              CCMenuItemSprite::create(play_normal,play_selected),NULL);

    actionMenu = CCMenu::create(item2,NULL);
    actionMenu->setPosition(ccp(this->gameBar->getContentSize().width/2,this->gameBar->getContentSize().height - 90));
    
    DataManager->UILayer->addChild(actionMenu);

    
    CCSprite *Player2_normal = CCSprite::createWithSpriteFrameName("Player2_blue.png");
    CCSprite *Player2_selected = CCSprite::createWithSpriteFrameName("Player2_blue_hvr.png");
    
    twoPlayersItem = CCMenuItemSprite::create(Player2_normal, Player2_selected, this, menu_selector(DNUIManager::menuCallbacks));
    twoPlayersItem->setTag(3);
    
    
    CCSprite *Player3_normal = CCSprite::createWithSpriteFrameName("Player3_blue.png");
    CCSprite *Player3_selected = CCSprite::createWithSpriteFrameName("Player3_blue_hvr.png");
    
    threePlayersItem = CCMenuItemSprite::create(Player3_normal, Player3_selected, this, menu_selector(DNUIManager::menuCallbacks));
    threePlayersItem->setTag(4);
    
    playersMenu = CCMenu::create(twoPlayersItem,threePlayersItem,NULL);
    playersMenu->alignItemsHorizontallyWithPadding(5);
    playersMenu->setPosition(ccp(this->gameBar->getContentSize().width/2 + 2 ,this->gameBar->getContentSize().height - 530));
    DataManager->UILayer->addChild(playersMenu);

/*
    CCMenuItemImage *leftArrow = CCMenuItemImage::create("Arrow.png", "Arrow.png", this, menu_selector(DNUIManager::menuCallbacks));
    leftArrow->setTag(5);
    
    CCMenuItemImage *rightArrow = CCMenuItemImage::create("Arrow.png", "Arrow.png", this, menu_selector(DNUIManager::menuCallbacks));
    rightArrow->setRotation(180);
    rightArrow->setTag(6);
    
    CCMenu *movementMenu = CCMenu::create(leftArrow,rightArrow,NULL);
    movementMenu->alignItemsHorizontallyWithPadding(60);
    movementMenu->setPosition(ccp(this->gameBar->getContentSize().width/2,this->gameBar->getContentSize().height - 700));
    DataManager->UILayer->addChild(movementMenu);
*/
}


void DNUIManager::menuCallback(){
    
    if (CCDirector::sharedDirector()->isPaused()){
        
        CCDirector::sharedDirector()->resume();
        onPause=false;
        onResume=true;
    }
    else{
    
        CCDirector::sharedDirector()->pause();
        onPause=true;
        onResume = false;
    }
}


void DNUIManager::menuCallbacks(CCObject* sender) {
    
    if(DataManager->isGameOver == false){
        
    CCMenuItemImage *tempItem = (CCMenuItemImage *)sender;
    
    switch (tempItem->getTag()) {
            
        case 1:
                break;
            
        case 2:
            if (!CCDirector::sharedDirector()->isPaused()) {
                
                DataManager->playerTileCount = 0;
                DataManager->opponentOneTileCount = 0;
                DataManager->opponentTwoTileCount = 0;
                
                DataManager->min = 0;
                DataManager->sec = 0;
                
                DataManager->count = 0;
                DataManager->opponenttilecount = 0;
                
                CCLOG("playerTileCount = %d", DataManager->playerTileCount);
                DataManager->gameLayer->restartScene();

                DataManager->isGameOver = false;
                
                playersMenu->setEnabled(true);
                actionMenu->setEnabled(true);
                mainMenu->setEnabled(true);
            }
            break;
            
        case 3:
            if (!CCDirector::sharedDirector()->isPaused()) {
                
                DataManager->opponentCount = 1;
                
                twoPlayersItem->selected();
                threePlayersItem->unselected();
                
                DataManager->opponentOneTileCount = 0;
                DataManager->playerTileCount = 0;
                
                DataManager->min = 0;
                DataManager->sec = 0;
                
                DataManager->gameLayer->restartScene();
                
                DataManager->count = 0;
                DataManager->opponenttilecount = 0;
                
                DataManager->isGameOver = false;
                
                playersMenu->setEnabled(true);
                actionMenu->setEnabled(true);
                mainMenu->setEnabled(true);
            }
            break;
        case 4:
            if (!CCDirector::sharedDirector()->isPaused()) {
                
                DataManager->opponentCount = 2;
                
                twoPlayersItem->unselected();
                threePlayersItem->selected();
                
                DataManager->playerTileCount = 0;
                DataManager->opponentOneTileCount = 0;
                DataManager->opponentTwoTileCount = 0;
                
                DataManager->min = 0;
                DataManager->sec = 0;
                
                DataManager->gameLayer->restartScene();
                
                DataManager->count = 0;
                DataManager->opponenttilecount = 0;
                
                DataManager->isGameOver=false;
                
                playersMenu->setEnabled(true);
                actionMenu->setEnabled(true);
                mainMenu->setEnabled(true);
                
            }
                break;
            
            this->gameLayer->dominoManager->playOpponentMove();
            
/*
        case 5:
            BackgroundManager->adjustBackgroundToTilePosition(true, DominoManager->leftMostEdgeSize,DominoManager->rightMostEdgeSize);
            break;
            
        case 6:
            BackgroundManager->adjustBackgroundToTilePosition(false, DominoManager->leftMostEdgeSize,DominoManager->rightMostEdgeSize);
            break;
*/
        default:
            break;
        }
    }
}

// Function is to avoid the scale down at the beginning!
// It'll get call after all tiles are setup...
// For getting the tiles world coordinate correctly!
void DNUIManager::scaleDownPanels() {
    
    CCObject* pObj = NULL;
    
    CCARRAY_FOREACH(this->panelsArray, pObj) {
        
        DNPlayerPanel *panel = (DNPlayerPanel *)pObj;
        panel->setScale(kPanelsScaleValue);
    }
}

int DNUIManager::getCurrentPlayerPanelTag(int playerNumber) {
    
    int panelTag = 0;
    
    switch (playerNumber){
            
        case 0:
            panelTag = kPlayerPanel1Tag;
            break;
        case 1:
            panelTag = kPlayerPanel2Tag;
            break;
        case 2:
            panelTag = kPlayerPanel3Tag;
            break;
        default:
            break;
    }
    return panelTag;
}

// Touch Methods
void DNUIManager::UIManagerTouchesBegan(CCSet *touches) {
    
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint touchPoint = touch->getLocationInView();
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    this->xDifference = MainGameLayer->getPosition().x + MainGameLayer->getContentSize().width/2 - touchPoint.x;
    
    CCObject* pObj = NULL;
    
    CCARRAY_FOREACH(this->panelsArray, pObj){
        
        DNPlayerPanel *panel = (DNPlayerPanel *)pObj;
        CCRect aTileRect = panel->boundingBox();
        
        CCRect gameBarRect = gameBar->boundingBox();

        if (((aTileRect.containsPoint(touchPoint) && panel->getTag() == kPlayerPanel1Tag ) || 
             (aTileRect.containsPoint(touchPoint) && panel->getTag() == kPlayerPanel2Tag) ||
             (aTileRect.containsPoint(touchPoint) && panel->getTag() == kPlayerPanel3Tag) ||(gameBarRect.containsPoint(touchPoint)) || DataManager->isGameOver == true))  {
            
            this->gameLayer->backgroundManager->istouchedPanel = true;

            panel->expandPanel();
            break;
        }
    }
}

void DNUIManager::UIManagerTouchesMoved(CCSet *touches) {
    
    
}

void DNUIManager::UIManagerTouchesEnded(CCSet *touches) {
    
    CCTouch *touch = (CCTouch*)touches->anyObject();
    CCPoint touchPoint = touch->getLocationInView();
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    if (!DominoManager->selectedTile ){
        
        this->gameLayer->backgroundManager->istouchedPanel = false;
    }
    if(DataManager->isGameOver == true){
        
      this->gameLayer->backgroundManager->istouchedPanel = false;  
    }
}

void DNUIManager::UIManagerTouchesCancelled(CCSet *touches) {
    
    
}
