//
//  BBMatchGamePlay.cpp
//  BaccizBooks
//
//  Created by Anshul on 22/01/13.
//
//

#include "BBMatchGamePlay.h"
#include "BBMainDataManager.h"
#include "BBGameSelection.h"
#include "cocos2d.h"
#include "BBUtility.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
USING_NS_CC;

CCScene* BBMatchGamePlay::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    CCLayer *layer = new BBMatchGamePlay();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    layer->release();
    return scene;
}


BBMatchGamePlay::BBMatchGamePlay() {
    
    this->setTouchEnabled(true);
}


#pragma mark - initialize
void BBMatchGamePlay::onEnter()
{
    CCLayer::onEnter();
    
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
   
    //Background image
    this->gameBackground = CCSprite::create("UI/CommonBG/BGmatchV.png");
    this->gameBackground->setPosition(ccp(winsize.width/2, winsize.height/2));
    this->addChild(this->gameBackground,2,11);
   
    //Add Game Menu
    menuLayer = new BBMenuLayer();
    this->addChild(menuLayer, 0);
    
    //Add spritesheets for matchGame
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GamePlay/GamePlaySpriteSheets/BBColorCards.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/UISpriteSheets/BBDogClappingAndNOAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/UISpriteSheets/BBDogYesAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/UISpriteSheets/BBTryAgainAnim.plist");
    
    //loading plist for Animation
    BBUtility::addGameAnimationsToAnimationCache("AnimationData.plist");
    
    //call to initialize variables
    this->initializeVariables();
    
    //Add Game UI
    this->initializeGameUI();
    
    //call to last gameLevel played
    int lastLevelPlayed = CCUserDefault::sharedUserDefault()->getIntegerForKey("lastLevelPlayed");
    this->loadLevel(lastLevelPlayed);
}


void BBMatchGamePlay::initializeVariables() {
    
    //Creating Cards Array
    this->cardsArr = CCArray::create();
    this->cardsArr->retain();
    
    this->cardsToBeShuffleArr = CCArray::create();
    this->cardsToBeShuffleArr->retain();
    
    //touch enable for next sprite to get opened
    this->canTouch = true;
    
    //set selectedCardCount
    this->selectedCardCount = 0;
    this->correctMatches = 0;
    this->wrongMatches = 0;
}


void BBMatchGamePlay::initializeGame(const char *type)
{
    //stop all the previous actions
    this->stopAllActions();
    
    //Remove all previous cards if present
    this->removeCards();
    
    //loading plist
    const char *pszPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("BBColorCards.plist");
    
    CCDictionary *allCardInfoDict = CCDictionary::createWithContentsOfFileThreadSafe(pszPath);
    
    aCardLevelDict = (CCDictionary *)allCardInfoDict->valueForKey(type);
    
    CCArray *aLevelGameCards = (CCArray *)allCardInfoDict->valueForKey("GameCards");

    //set the default card Index
    int cardIndex = 1;
    
    //loading split and skip Index from plist
    int skipIndex = aCardLevelDict->valueForKey("SkipIndex")->intValue();
    int splitIndex = aCardLevelDict->valueForKey("splitIndex")->intValue();
    
    //scale cards
    float scaleCard = aCardLevelDict->valueForKey("scaleCard")->floatValue();
    
    //loading X and Y position from plist
    int xPos = aCardLevelDict->valueForKey("cardStartingPosX")->intValue();
    int yPos = aCardLevelDict->valueForKey("cardStartingPosY")->intValue();
    
    //difference of height and width between the cards
    int diffX = aCardLevelDict->valueForKey("diffX")->intValue();
    int diffY = aCardLevelDict->valueForKey("diffY")->intValue();
    
    //loading uniqueCards from plist
    int uniqueCardsCount = aCardLevelDict->valueForKey("uniqueCards")->intValue();
    CCLog("uniqueCards = %d",uniqueCardsCount);
    
    //store unique no's into array
    int no_to_randomize[15];
    for (int i = 0 ; i <= 14; i++) {
        
        no_to_randomize[i] = i;
    }
    
    //call to randomize method
    this->randomizeInt(no_to_randomize);
    
    //remove all previous cards if present
    cardsToBeShuffleArr->removeAllObjects();
    
    //randomize the indexes
    for (int i = 0; i < uniqueCardsCount; i++) {
    
        int randomIndex = no_to_randomize[i];
        
        CCDictionary *aLevelDictCards = (CCDictionary*)aLevelGameCards->objectAtIndex(randomIndex);
    
        //adding items twice into the Array
        cardsToBeShuffleArr->addObject(aLevelDictCards);
        cardsToBeShuffleArr->addObject(aLevelDictCards);
    }
    
    //call to shuffleCards method
    CCArray *shuffledCardsArr = this->shuffleArray(cardsToBeShuffleArr);
    
    CCObject *aCardObj;
    
    CCARRAY_FOREACH(shuffledCardsArr, aCardObj)
    {
        //Skip the position if we get Skip Index
        if(cardIndex == skipIndex)
        {
            xPos = xPos + diffX + 100;
            cardIndex++;
        }
        
        aCardDict = (CCDictionary *)aCardObj;
        
        //Add top Card to Hide Match Card
        BBMGSprite * atopCard = BBMGSprite::createWithSpriteFrameName(aCardLevelDict->valueForKey("topCard")->getCString());
        
        this->gameBackground->addChild(atopCard, 2);
        atopCard->setPosition(ccp(xPos,yPos));
        
        atopCard->matchID = aCardDict->valueForKey("matchID")->intValue();
        atopCard->bottomCardTag = aCardDict->valueForKey("bottomCardTag")->intValue();
        atopCard->bottomImageName =  aCardDict->valueForKey("imageName")->getCString();
        atopCard->soundName = aCardDict->valueForKey("soundName")->getCString();
        atopCard->setScale(scaleCard);
        atopCard->isFlipped = false;
        cardsArr->addObject(atopCard);
        
        //Increase X
        xPos = xPos + diffX + 100;
        
        //Go to Next Row
        if (cardIndex % splitIndex == 0)
        {
            xPos = aCardLevelDict->valueForKey("cardStartingPosX")->intValue();
            yPos = yPos - diffY - 60;
        }
        cardIndex++;
    }
}


# pragma mark - Game UI
void BBMatchGamePlay::initializeGameUI() {
    
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *twoByTwo = CCSprite::create("UI/CommonBG/2x2_menu.png");
    
    CCMenuItemSprite *twoByTwoMenu = CCMenuItemSprite::create(twoByTwo, twoByTwo, this, menu_selector(BBMatchGamePlay::gotoLevel));
    twoByTwoMenu->setPosition(ccp(winsize.width/2 + 400, winsize.height/2 + 200));
    twoByTwoMenu->setTag(1);
    twoByTwoMenu->setScale(0.98);
    
    
    CCSprite *twoByThree = CCSprite::create("UI/CommonBG/2x3_menu.png");
    
    CCMenuItemSprite *twoByThreeMenu = CCMenuItemSprite::create(twoByThree, twoByThree, this, menu_selector(BBMatchGamePlay::gotoLevel));
    twoByThreeMenu->setPosition(ccp(winsize.width/2 + 400, winsize.height/2 + 70));
    twoByThreeMenu->setTag(2);
    twoByThreeMenu->setScale(0.98);
    
    
    CCSprite *threeByThree = CCSprite::create("UI/CommonBG/3x3_menu.png");
    
    CCMenuItemSprite *threeByThreeMenu = CCMenuItemSprite::create(threeByThree, threeByThree, this, menu_selector(BBMatchGamePlay::gotoLevel));
    threeByThreeMenu->setPosition(ccp(winsize.width/2 + 400, winsize.height/2 - 70));
    threeByThreeMenu->setTag(3);
    threeByThreeMenu->setScale(0.98);
    
    
    CCSprite *threeByFour = CCSprite::create("UI/CommonBG/3x4_menu.png");
    
    CCMenuItemSprite *threeByFourMenu = CCMenuItemSprite::create(threeByFour, threeByFour, this, menu_selector(BBMatchGamePlay::gotoLevel));
    threeByFourMenu->setPosition(ccp(winsize.width/2 + 400, winsize.height/2 - 200));
    threeByFourMenu->setTag(4);
    threeByFourMenu->setScale(0.98);
    
       
    CCMenu *selectMenu = CCMenu::create(twoByTwoMenu,twoByThreeMenu,threeByThreeMenu,threeByFourMenu,NULL);
    selectMenu->setPosition(CCPointZero);
    selectMenu->setScale(0.98);
    this->addChild(selectMenu,2);
    
    
    //Add restart button
    CCSprite *normalSprite=CCSprite::create("UI/CommonBG/PlayAgain_restart.png");
    CCSprite *selectedSprite=CCSprite::create("UI/CommonBG/PlayAgain_restart_off.png");
    
    restartMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(BBMatchGamePlay::gotoLevel));
    restartMenuItem->setPosition(CCPointMake(winsize.width/2 - 400, winsize.height/2 + 80));
    restartMenuItem->setTag(5);

    CCMenu *tempMenu = CCMenu::create(restartMenuItem,NULL);
    tempMenu->setPosition(CCPointZero);
    this->addChild(tempMenu,2);
    
    //Add dogAnimation sprite 
    dogAnim = CCSprite::create("UI/CommonBG/DogAnimations.png");
    dogAnim->setPosition(CCPointMake(winsize.width/2 - 400, winsize.height/2 - 270));
    this->addChild(dogAnim,2);
}


void BBMatchGamePlay::addBlinkActionForRefreshButton(float dt){
    
    if(this->restartMenuItem->isSelected()){
        
        this->restartMenuItem->unselected();
    }
    else{
        
        this->restartMenuItem->selected();
    }
}


void BBMatchGamePlay::openCard(BBMGSprite *fgSpr) {
    
    this->selectedCardCount++;
    
    if(this->selectedCardCount == 1) {
        
        this->firstSelectedSprite = fgSpr;
        
        //call to flip cards method
        this->flipCards(this->firstSelectedSprite);
        
        //sound-Effect for particular images
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(this->firstSelectedSprite->soundName);
    }
    else if (this->selectedCardCount == 2) {
        
        this->secondSelectedSprite = fgSpr;
        
        //call to flip cards method
        this->flipCards(this->secondSelectedSprite);
        
        //sound-Effect for particular images
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(this->secondSelectedSprite->soundName);
    }
    
    //We touched 2 Cards //So check the cards
    if(this->selectedCardCount == 2) {
        
        this->canTouch = false;
        
        CCActionInterval *delayObj = CCDelayTime::create(1.0);
        CCCallFuncN* checkCardsObj = CCCallFuncN::create(this,callfuncN_selector(BBMatchGamePlay::checkCards));
        CCFiniteTimeAction *timeToViewCards = CCSequence::create(delayObj,checkCardsObj,NULL);
        this->runAction(timeToViewCards);
    }
}


void BBMatchGamePlay::flipCards(BBMGSprite *topCard){
    
    if (topCard->isFlipped) {
        
        topCard->isFlipped = false;
    }
    else {
        
        topCard->isFlipped = true;
    }
    
    float d = 0.25f;
    
    CCOrbitCamera *firstHalfFlip = CCOrbitCamera::create(d/2, 1, 0, 0, 90, 0, 0);
    CCOrbitCamera *secondHalfFlip = CCOrbitCamera::create(d/2, 1, 0, 270, 90, 0, 0);

    CCCallFuncN* changeMatchCardImageFunc = CCCallFuncN::create(this,callfuncN_selector(BBMatchGamePlay::changeImageOfTopCard));

    CCFiniteTimeAction *flipSequence = CCSequence::create(firstHalfFlip, changeMatchCardImageFunc,secondHalfFlip, NULL);
    topCard->runAction(flipSequence);
}


void BBMatchGamePlay::changeImageOfTopCard(BBMGSprite *matchCard)
{
    if(matchCard->isFlipped)
    {
        //Change the image of Top Card to bottom Card
        CCSpriteFrame *newImage = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(matchCard->bottomImageName);
        matchCard->setDisplayFrame(newImage);
    }
    else
    {
        //Change the image of bottom Card to Top Card
        CCSpriteFrame *newImage = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(aCardLevelDict->valueForKey("topCard")->getCString());
        matchCard->setDisplayFrame(newImage);
    }
}

//void BBMatchGamePlay::shineAnimation(BBMGSprite *Sprite) {
//    
//    CCParticleSystem *SelectedSprite = CCParticleSystemQuad::create("ShineAnimation.plist");
//    this->gameBackground->addChild(SelectedSprite,2);
//    SelectedSprite->setPosition(ccp(this->Sprite->getPositionX(), this->Sprite->getPositionY()));
//}

void BBMatchGamePlay::checkCards() {
    
    if(this->firstSelectedSprite->matchID == this->secondSelectedSprite->matchID)
    {
        //matchCards ShineAnimation
        CCParticleSystem *ShinefirstSelectedSprite = CCParticleSystemQuad::create("ShineAnimation.plist");
        this->gameBackground->addChild(ShinefirstSelectedSprite,2);
        ShinefirstSelectedSprite->setPosition(ccp(this->firstSelectedSprite->getPositionX(), this->firstSelectedSprite->getPositionY()));
        
        CCParticleSystem *ShinesecondSelectedSprite = CCParticleSystemQuad::create("ShineAnimation.plist");
        this->gameBackground->addChild(ShinesecondSelectedSprite,2);
        ShinesecondSelectedSprite->setPosition(ccp(this->secondSelectedSprite->getPositionX(), this->secondSelectedSprite->getPositionY()));
        
//        this->shineAnimation(this->firstSelectedSprite);
//        this->shineAnimation(this->secondSelectedSprite);
        
        //remove top Card images from the layer and array
        this->removeChild(firstSelectedSprite,true);
        this->removeChild(secondSelectedSprite,true);
        
        cardsArr->removeObject(firstSelectedSprite,true);
        cardsArr->removeObject(secondSelectedSprite,true);

        //incrementing matched cards count
        correctMatches++;
        CCLog("this->correctMatches = %d",this->correctMatches);
        
        if (correctMatches == 3) {
            
            //call to dogAnimationYes
            this->dogAnimation("DogYes");
            
            //play sound for the match Cards
//            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("soundName");
        }
        
        //check if gameOver
        if(this->cardsArr->count() <= 0) {
            
            this->gameOver();
        }
    }
    else //if card not matches then hide the match Card
    {
        //call to flipCards method
        this->flipCards(this->firstSelectedSprite);
        this->flipCards(this->secondSelectedSprite);
        
        //incrementing unmatched cards count
        this->wrongMatches++;
        CCLog("this->wrongMatches = %d",this->wrongMatches);
        
        if (this->wrongMatches == 3) {
            
            //call to dogAnimationNo
            this->dogAnimation("DogNo");
            
            //play sound for the match Cards
//            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("soundName");
        }
    }
    
    //reset the count
    this->selectedCardCount = 0;
    this->canTouch = true;
}


void BBMatchGamePlay::dogAnimation(const char *dogName) {
    
    //Dog Animation
    CCAnimationCache *animCacheDog = CCAnimationCache::sharedAnimationCache();
    CCAnimation *animationDog = animCacheDog->animationByName(dogName);
    CCAnimate *animDog = CCAnimate::create(animationDog);
    dogAnim->runAction(animDog);
    
    //reset the count for correct and incorrect match Cards
    this->correctMatches = 0;
    this->wrongMatches = 0;
}


void BBMatchGamePlay::gameOver() {
    
    //gameOver label
    pLabel = CCLabelTTF::create("You Won", "Noteworthy - 150pt - bold", 75);
    pLabel->setPosition(ccp(320,638));
    this->gameBackground->addChild(pLabel,2);
    this->getChildByTag(1);
    
    //call to dogClapAnimation
    this->dogAnimation("DogClapping");
    
    //unscheduling the blinkActionForRefreshButton
    this->schedule(schedule_selector(BBMatchGamePlay::addBlinkActionForRefreshButton), 0.5);
}


#pragma mark - Touch
void BBMatchGamePlay::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //If disable touch return
    if (this->canTouch == false) {
        
        return;
    }
    
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        CCObject *fgCards = NULL;
        
        CCARRAY_FOREACH(this->cardsArr, fgCards){
            
            BBMGSprite *fgSpr = (BBMGSprite *)fgCards;
            
            if (fgSpr->isFlipped) { 
                
                continue;
            }
                      
            if(fgSpr->boundingBox().containsPoint(this->gameBackground->convertTouchToNodeSpace(touch)))
            {
                this->openCard(fgSpr);
            }
        }
    }
}


#pragma mark - level Selection
void BBMatchGamePlay::gotoLevel(cocos2d::CCMenuItemImage *sender)
{
    if (this->canTouch == false) {
        
        return;
    }
    
    int tag = sender->getTag();
    
    if(tag != 5){
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey("lastLevelPlayed", tag);
    }
    
    switch (tag)
    {
        case 1: this->initializeGame("2x2"); // Menu to select 2x2 level
                break;
        
        case 2: this->initializeGame("2x3"); // Menu to select 2x3 level
                break;
        
        case 3: this->initializeGame("3x3"); // Menu to select 3x3 level
                break;
        
        case 4: this->initializeGame("3x4"); // Menu to select 3x4 level
                break;
        
        case 5:
                CCDirector::sharedDirector()->replaceScene(BBMatchGamePlay::scene());
        
        default: break;
    }
}


void BBMatchGamePlay::loadLevel(int tag) {
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("lastLevelPlayed", tag);

    this->gameBackground->removeAllChildrenWithCleanup(true);
    this->cardsArr->removeAllObjects();
    
    if (tag == 1 || tag == 0) {
        
        this->initializeGame("2x2");
    }
    else if (tag == 2) {
        
        this->initializeGame("2x3");
    }
    else if (tag == 3) {
        
        this->initializeGame("3x3");
    }
    else if (tag == 4) {
        
        this->initializeGame("3x4");
    }
}


#pragma mark - Remove Card
void BBMatchGamePlay::removeCards() {
    
    //Remove all the cards from the gameBackground
    this->gameBackground->removeAllChildrenWithCleanup(true);
    
    this->cardsArr->removeAllObjects();
    
    this->unschedule(schedule_selector(BBMatchGamePlay::addBlinkActionForRefreshButton));
    
    //Reset the selectedCards count
    this->selectedCardCount = 0;
    this->correctMatches = 0;
    this->wrongMatches = 0;
    
    //set the Card touch
    this->canTouch = true;
    this->removeChild(pLabel, true);
}


#pragma mark - Utility
CCArray* BBMatchGamePlay::shuffleArray(CCArray *cardsToShuffle) {
    
    for (int x = 0; x < cardsToShuffle->count(); x++) {
 
        int randInt = (arc4random() % (cardsToShuffle->count() - x)) + x;
        cardsToShuffle->exchangeObjectAtIndex(x, randInt);
    }
    return cardsToShuffle;
    
    //Reset the Cards count
    this->selectedCardCount = 0;
}


int BBMatchGamePlay::randomizeInt(int GameCards[15]) {
    
    //variables used for swapping
    int temp;
    int rand_no;
    
    //randomize the array
    for(int i = 0; i <= 14; i++){
        
        rand_no = arc4random() % 15;
        
        temp = GameCards[rand_no];
        GameCards[rand_no]= GameCards[i];
        GameCards[i] = temp;
    }
    return GameCards[15];
}


#pragma mark - Dealloc
void BBMatchGamePlay::onExit() {
    
    CCLayer::onExit();
    
    //Remove spritesheet of matchGame
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrameByName("GamePlay/GamePlaySpriteSheets/BBColorCards.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("UI/UISpriteSheets/BBDogClappingAndNOAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("UI/UISpriteSheets/BBDogYesAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("UI/UISpriteSheets/BBTryAgainAnim.plist");
}


BBMatchGamePlay::~BBMatchGamePlay() {
    
    CCLog("destructor called in MatchGamePlay...");
    
    CC_SAFE_RELEASE_NULL(this->cardsArr);
    CC_SAFE_RELEASE_NULL(this->cardsToBeShuffleArr);
    
    this->removeChild(menuLayer, 1);
    delete menuLayer;
}

