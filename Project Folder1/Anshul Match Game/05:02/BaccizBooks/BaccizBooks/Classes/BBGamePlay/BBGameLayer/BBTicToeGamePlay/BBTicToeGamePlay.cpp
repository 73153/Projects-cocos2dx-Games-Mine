//
//  BBTicToeGamePlay.cpp
//  BaccizBooks
//
//  Created by Manjunatha Reddy on 24/01/13.
//
//

#include "BBTicToeGamePlay.h"
#include "SimpleAudioEngine.h"
#include "CCNumber.h"
#include "BBUtility.h"
#define kCpuSpriteAdded 555
#define kPlayerSpriteAdded 666
#define kNoSprite  0
#define kNoDangerousIndex 999
using namespace cocos2d;

USING_NS_CC;

#pragma mark - Scene
CCScene* BBTicToeGamePlay::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new BBTicToeGamePlay();
    scene->addChild(layer);
    layer->release();
     return scene;
}


#pragma mark - Init
BBTicToeGamePlay::BBTicToeGamePlay()
{
    this->setTouchEnabled(true);
}

void BBTicToeGamePlay::onEnter()
{
    CCLayer::onEnter();
    
    //loading plist
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GamePlay/GamePlaySpriteSheets/ticToeSpriteSheet.plist");
     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/UISpriteSheets/BBDogClappingAndNOAnim.plist");
     CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/UISpriteSheets/BBDogYesAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/UISpriteSheets/BBTryAgainAnim.plist");

    BBUtility::addGameAnimationsToAnimationCache("AnimationData.plist");
    //initialise variables
    this->initialiseVariables();
    
    //add ticToe background
    this->addTicToeBackGround();
    
    
    //add menu layer
    menuLayer = new BBMenuLayer();
    this->addChild(menuLayer,0);

}

void BBTicToeGamePlay::initialiseVariables()
{
    //array initialisation
    
    this->ticToePointArray=CCPointArray::create(10);
    this->ticToePointArray->retain();
    //
    this->freeSlotsArray=CCArray::create();
    this->freeSlotsArray->retain();
    
    //two player
    this->isFirstPlayeTurn=true;
    
    //single player
    this->isCpuTurn=false;
    this->isSpriteAddedInitiallyInIpadVsPlayerMode=false;
    
    this->noOfBoxsFilled=0;
    this->isGameOver=false;
    this->isLabelAdded=false;
    
    //default sprite
    this->isPlayerSelectedXsprite=true;
          
    this->isDifficultModePlay=true;
     
    for(int i=0;i<9;i++)
    {
        index[i]=kNoSprite;
    }
   
    this->isPlayerVsIad=true;
    this->isTwoPlayer=false;
    this->isIpadVsPlayer=false;
    
    
    //for storing 9 points in array
    float xPos=355;
    float yPos=528;
    CCPoint touchPoint;
    for(int i=1;i<10;i++)
    {
        
        touchPoint.x=xPos;
        touchPoint.y=yPos;
        
        this->ticToePointArray->addControlPoint(touchPoint);
        
        if(i%3==0)
        {
            xPos=355;
            yPos=yPos-135;
        }
        else{
            xPos=xPos+150;
            
        }
    }
    
    //if ipad/player
    
}

#pragma mark -  Dealloc
void BBTicToeGamePlay::onExit()
{
    CCLayer::onExit();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("GamePlay/GamePlaySpriteSheets/ticToeSpriteSheet.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("UI/UISpriteSheets/BBDogClappingAndNOAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("UI/UISpriteSheets/BBDogYesAnim.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("UI/UISpriteSheets/BBTryAgainAnim.plist");
}

BBTicToeGamePlay::~BBTicToeGamePlay()
{
    CC_SAFE_RELEASE_NULL(this->ticToePointArray);
    CC_SAFE_RELEASE_NULL(this->freeSlotsArray);
        
    this->removeChild(menuLayer, 1);
    delete menuLayer;
     
    CCLog("destructor called in tictoe gameplay");

}

#pragma mark - Add UI
void BBTicToeGamePlay::addTicToeBackGround()
{
    winsize=CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *ticToeBg=CCSprite::createWithSpriteFrameName("tictactoe_copy.png");
    ticToeBg->setPosition(CCPointMake(winsize.width/2, winsize.height/2+10));
    
    this->addChild(ticToeBg,2);
    
    selectPlayerBg=CCSprite::createWithSpriteFrameName("playerVsIpad.png");
    selectPlayerBg->setPosition(CCPointMake(winsize.width/2+355, winsize.height/2+160));
    this->addChild(selectPlayerBg,2);
    
    
      
    
    
    //add x button
    CCSprite *normalSprite=CCSprite::createWithSpriteFrameName("X_OFF.png");
    CCSprite *selectedSprite=CCSprite::createWithSpriteFrameName("X_ON.png");
    
    xMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(BBTicToeGamePlay::action));
    xMenuItem->setPosition(CCPointMake(winsize.width/2+355, winsize.height/2+10));
    xMenuItem->setTag(1);
 
    
    //add o button
    normalSprite=CCSprite::createWithSpriteFrameName("o_Off.png");
    selectedSprite=CCSprite::createWithSpriteFrameName("o_ON.png");
    
    oMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(BBTicToeGamePlay::action));
    oMenuItem->setPosition(CCPointMake(winsize.width/2+355, winsize.height/2-140));
    
    oMenuItem->setTag(2);
       
    
    //add restart button
    
    normalSprite=CCSprite::create("UI/CommonBG/PlayAgain_restart.png");
    selectedSprite=CCSprite::create("UI/CommonBG/PlayAgain_restart_off.png");
    
    restartMenuItem=CCMenuItemSprite::create(normalSprite, selectedSprite, this, menu_selector(BBTicToeGamePlay::action));
    restartMenuItem->setPosition(CCPointMake(winsize.width/2-400, winsize.height/2+80));
    restartMenuItem->setTag(3);
    
    

        
    //menu
    buttonMenu=CCMenu::create(xMenuItem,oMenuItem,NULL);
    buttonMenu->setPosition(CCPointZero);
    this->addChild(buttonMenu, 2);
    
    //temp restart button menu
    CCMenu *tempMenu=CCMenu::create(restartMenuItem,NULL);
    tempMenu->setPosition(CCPointZero);
    this->addChild(tempMenu,2);
    
    
    dogAnim=CCSprite::create("UI/CommonBG/DogAnimations.png");
    dogAnim->setPosition(CCPointMake(winsize.width/2-400, winsize.height/2-270));
    this->addChild(dogAnim,2);
    
    
    
    this->schedule(schedule_selector(BBTicToeGamePlay::applyBlinkAction), 0.5);
    
    

    
        //iniatial play turn
//    int randomNumber=(arc4random()%8);
//    CCPoint point=this->ticToePointArray->getControlPointAtIndex(randomNumber);
//    CCSprite *xSprite=CCSprite::createWithSpriteFrameName("X_ON.png");
//    
//    xSprite->setPosition(point);
//    this->addChild(xSprite,1);
//    index[randomNumber]=1;
}

#pragma mark - Two Player Function
void BBTicToeGamePlay::addSpriteOnTouchedPoint(int currentIndex)
{
    if(this->isFirstPlayeTurn)
    {
        this->addSpriteOfType(this->isPlayerSelectedXsprite, currentIndex, kPlayerSpriteAdded);
        this->isFirstPlayeTurn=false;
    }
    else {
        
        this->addSpriteOfType(!this->isPlayerSelectedXsprite, currentIndex, kCpuSpriteAdded);
        this->isFirstPlayeTurn=true;
    }
}

#pragma mark - Single Player Functions
void BBTicToeGamePlay:: addDelayActionAfterPlayerTurn()
{
    CCDelayTime *actionDelay = CCDelayTime::create(0.5f);
    CCSequence *actionSequence = CCSequence::createWithTwoActions(actionDelay, CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addComputerPlayedSprite)));
    this->runAction(actionSequence);
}

void BBTicToeGamePlay::addComputerPlayedSprite()
{
    if(this->isGameOver)
    {
        return;
    }
    
    int currentIndex=this->getFreeIndex();
    
    this->addSpriteOfType(!this->isPlayerSelectedXsprite, currentIndex, kCpuSpriteAdded);
    
   
    this->isCpuTurn=false;
}

int BBTicToeGamePlay::getFreeIndex()
{
     int selectedFreeIndex;
   
    //select Random value if only 2 boxes filled
    if(noOfBoxsFilled<2)
    {
         return selectedFreeIndex=this->getEasyModeIndex();
    }
    if(this->isDifficultModePlay)
    {
        selectedFreeIndex=this->getDangerIndex(kCpuSpriteAdded);
        
        if(selectedFreeIndex==kNoDangerousIndex)
        {
            selectedFreeIndex=this->getDangerIndex(kPlayerSpriteAdded);
        }
        if(selectedFreeIndex==kNoDangerousIndex)
        {
            selectedFreeIndex=this->getEasyModeIndex();
        }
    }
    
    return selectedFreeIndex;
}

int BBTicToeGamePlay::getEasyModeIndex()
{
    if(this->freeSlotsArray->count()>0)
    {
        this->freeSlotsArray->removeAllObjects();
    }
    for(int i=0;i<9;i++)
    {
        if(index[i]==kNoSprite)
        {
            cocos2d_extensions::CCNumber<int> *intOne = cocos2d_extensions::CCNumber<int>::numberWithValue(i);
            this->freeSlotsArray->addObject(intOne);
        }
    }
    int randomNumber=(arc4random()%this->freeSlotsArray->count());
        
    cocos2d_extensions::CCNumber<int> * selectedCoordinateInt = (cocos2d_extensions::CCNumber<int> *)freeSlotsArray->objectAtIndex(randomNumber);
    int value = selectedCoordinateInt->getValue();
    
    return value;

}


int BBTicToeGamePlay::getDangerIndex(int type)
{
    int compIndex=0;
    
    //1
    if(index[0]==type&&index[1]==type)
    {
        if(index[2]==kNoSprite)
        {
            return compIndex=2;
        }
        else
            goto step2;
              
    }
    //2
step2:
    if(index[1]==type&&index[2]==type)
    {
        if(index[0]==kNoSprite)
        {
            return compIndex=0;
        }
        else
            goto step3;
    }
    //3
step3:
    if(index[0]==type&&index[3]==type)
    {
        if(index[6]==kNoSprite)
        {
            return compIndex=6;
        }
        else
            goto step4;
    }
    //4
  step4:
    if(index[3]==type&&index[6]==type)
    {
        if(index[0]==kNoSprite)
        {
            return compIndex=0;
        }
        else
            goto step5;
    }
    //5
step5:
    if(index[6]==type&&index[7]==type)
    {
        if(index[8]==kNoSprite)
        {
            return compIndex=8;
        }
        else
            goto step6;
    }
    //6
step6:if(index[7]==type&&index[8]==type)
    {
        if(index[6]==kNoSprite)
        {
            return compIndex=6;
        }
        else
            goto step7;
    }
    //7
step7:if(index[5]==type&&index[8]==type)
    {
        if(index[2]==kNoSprite)
        {
            return compIndex=2;
        }
        else
            goto step8;
    }
    //8
step8: if(index[2]==type&&index[5]==type)
    {
        if(index[8]==kNoSprite)
        {
            return compIndex=8;
        }
        else
            goto step9;
    }
    //9
step9: if(index[1]==type&&index[4]==type)
    {
        if(index[7]==kNoSprite)
        {
            return compIndex=7;
        }
        else
            goto step10;
    }
    //10
step10: if(index[4]==type&&index[7]==type)
    {
        if(index[1]==kNoSprite)
        {
            return compIndex=1;
        }
        else
            goto step11;
    }
    //11
step11: if(index[3]==type&&index[4]==type)
    {
        if(index[5]==kNoSprite)
        {
            return compIndex=5;
        }
        else
            goto step12;
    }
    //12
step12: if(index[4]==type&&index[5]==type)
    {
        if(index[3]==kNoSprite)
        {
            return compIndex=3;
        }
        else
            goto step13;
    }
    //13
step13: if(index[0]==type&&index[4]==type)
    {
        if(index[8]==kNoSprite)
        {
            return compIndex=8;
        }
        else
            goto step14;
    }
    //14
step14: if(index[4]==type&&index[8]==type)
    {
        if(index[0]==kNoSprite)
        {
            return  compIndex=0;
        }
        else
            goto step15;
    }
    //15
step15: if(index[2]==type&&index[4]==type)
    {
        if(index[6]==kNoSprite)
        {
            return compIndex=6;
        }
        else
            goto step16;
    }
    //16
step16: if(index[4]==type&&index[6]==type)
    {
        if(index[2]==kNoSprite)
        {
            return compIndex=2;
        }
        else
            goto step17;
    }
    //17
step17: if(index[0]==type&&index[2]==type)
    {
        if(index[1]==kNoSprite)
        {
            return compIndex=1;
        }
        else
            goto step18;
    }
    //18
step18:if(index[0]==type&&index[6]==type)
    {
        if(index[3]==kNoSprite)
        {
            return compIndex=3;
        }
        else
            goto step19;
    }
    //19
step19: if(index[6]==type&&index[8]==type)
    {
        if(index[7]==kNoSprite)
        {
            return compIndex=7;
        }
        else
            goto step20;
    }
    //20
step20: if(index[2]==type&&index[8]==type)
    {
        if(index[5]==kNoSprite)
        {
            return compIndex=5;
        }
        else
            goto step21;
    }
    //21
step21: if(index[1]==type&&index[7]==type)
    {
        if(index[4]==kNoSprite)
        {
            return compIndex=4;
        }
        else
            goto step22;
    }
    //22
step22: if(index[3]==type&&index[5]==type)
    {
        if(index[4]==kNoSprite)
        {
            return compIndex=4;
        }
        else
            goto step23;
    }
    //23
step23: if(index[1]==type&&index[8]==type)
    {
        if(index[4]==kNoSprite)
        {
            return compIndex=4;
        }
        else
            goto step24;
    }
    //24
step24:if(index[2]==type&&index[6]==type)
    {
        if(index[4]==kNoSprite)
        {
            return compIndex=4;
        }
        
    }
    
    //if no matches
    return kNoDangerousIndex;
    
}

#pragma mark - Common Functions
void BBTicToeGamePlay::addSpriteOfType(bool isXType,int currentIndex,int filledIndexType)
{
    CCSprite *aSprite;
    if(isXType)
    {
        
        aSprite=CCSprite::createWithSpriteFrameName("X_ON.png");
        this->oMenuItem->selected();
        this->xMenuItem->unselected();
    }
    else{
        aSprite=CCSprite::createWithSpriteFrameName("o_ON.png");
        this->xMenuItem->selected();
        this->oMenuItem->unselected();
        
    }
    
    CCPoint pos=this->ticToePointArray->getControlPointAtIndex(currentIndex);
    aSprite->setPosition(pos);
    this->addChild(aSprite,1);
    index[currentIndex]=filledIndexType;
    
    this->noOfBoxsFilled++;
      
        bool isWon=this->checkGameResult(filledIndexType);
        if(isWon)
        {
            if(filledIndexType==kPlayerSpriteAdded)
            {
                if(this->isPlayerSelectedXsprite)
                {
                    this->addLabel("X Wins!");
                    
                }
                else{
                    this->addLabel("O Wins!");
                }
                //first
                CCAnimationCache *animCache1 = CCAnimationCache::sharedAnimationCache();
                CCAnimation *animation1 = animCache1->animationByName("DogYes");
                CCAnimate *animN1 = CCAnimate::create(animation1);
               
                
                //second
                CCAnimationCache *animCache2 = CCAnimationCache::sharedAnimationCache();
                CCAnimation *animation2 = animCache2->animationByName("DogClapping");
                CCAnimate *animN2 = CCAnimate::create(animation2);
                
                CCSequence *seq=CCSequence::createWithTwoActions(animN1, animN2);
                
                dogAnim->runAction(seq);

            }
            else{
                
                if(this->isPlayerSelectedXsprite)
                {
                    this->addLabel("O Wins!");
                }
                else{
                    
                    this->addLabel("X Wins!");
                }
                               
                //first
                CCAnimationCache *animCache1 = CCAnimationCache::sharedAnimationCache();
                CCAnimation *animation1 = animCache1->animationByName("DogNo");
                CCAnimate *animN1 = CCAnimate::create(animation1);
                
                
                //second
                CCAnimationCache *animCache2 = CCAnimationCache::sharedAnimationCache();
                CCAnimation *animation2 = animCache2->animationByName("TryAgain");
                CCAnimate *animN2 = CCAnimate::create(animation2);
                
                CCSequence *seq=CCSequence::createWithTwoActions(animN1, animN2);
                
                dogAnim->runAction(seq);


                            
            }
            this->isGameOver=true;
            this->isLabelAdded=true;
            this->schedule(schedule_selector(BBTicToeGamePlay::addBlinkActionForRefreshButton), 0.5);
          
                    
        }
    if(this->noOfBoxsFilled==9&&!isWon)
    {
        this->addLabel("You tied!");
        this->isGameOver=true;
        
        this->isLabelAdded=true;
        this->schedule(schedule_selector(BBTicToeGamePlay::addBlinkActionForRefreshButton), 0.5);
    
    }

        
    
}
void BBTicToeGamePlay::applyBlinkAction(float dt)
{
    if(this->oMenuItem->isSelected())
    {
        this->oMenuItem->unselected();
        this->xMenuItem->selected();
    }
    else{
        this->oMenuItem->selected();
        this->xMenuItem->unselected();
    }
 
}

void BBTicToeGamePlay::addBlinkActionForRefreshButton(float dt)
{
    if(this->restartMenuItem->isSelected())
    {
        this->restartMenuItem->unselected();
    }
    else{
        this->restartMenuItem->selected();
    }
}

void BBTicToeGamePlay::action(cocos2d::CCMenuItemImage *sender)
{
    int tag=sender->getTag();
    winsize=CCDirector::sharedDirector()->getWinSize();
    switch (tag)
    {
        case 1: //xMenu item
            
            this->xMenuItem->selected();
            this->oMenuItem->unselected();
            
            
            this->unschedule(schedule_selector(BBTicToeGamePlay::applyBlinkAction));
            xMenuItem->setPosition(CCPointMake(winsize.width/2+355, winsize.height/2+10));
            oMenuItem->setPosition(CCPointMake(winsize.width/2+355, winsize.height/2-140));
            
            this->isPlayerSelectedXsprite=true;
            //disable Menu
            this->buttonMenu->setEnabled(false);
            //Add Initial Sprite If ipadVsPlayer Mode
            if(this->isIpadVsPlayer)
            {
                CCDelayTime *actionDelay = CCDelayTime::create(0.5f);
                CCSequence *actionSequence = CCSequence::createWithTwoActions(actionDelay, CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addComputerPlayedSprite)));
                this->runAction(actionSequence);
                this->isSpriteAddedInitiallyInIpadVsPlayerMode=true;
            }
            break;
        case 2://oMenu item
            
            this->xMenuItem->unselected();
            this->oMenuItem->selected();
            
            this->unschedule(schedule_selector(BBTicToeGamePlay::applyBlinkAction));
            this->oMenuItem->setPosition(CCPointMake( winsize.width/2+355, winsize.height/2+10));
            this->xMenuItem->setPosition(CCPointMake(winsize.width/2+355, winsize.height/2-140));
            
            this->isPlayerSelectedXsprite=false;
            //disable Menu
            this->buttonMenu->setEnabled(false);
            if(this->isIpadVsPlayer)
            {
                CCDelayTime *actionDelay = CCDelayTime::create(0.5f);
                CCSequence *actionSequence = CCSequence::createWithTwoActions(actionDelay, CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addComputerPlayedSprite)));
                this->runAction(actionSequence);
                this->isSpriteAddedInitiallyInIpadVsPlayerMode=true;
            }
            
            break;
        case 3://temp restart
            
            CCDirector::sharedDirector()->replaceScene(BBTicToeGamePlay::scene());
            break;
        case 4://firstPlayer ToggleMenu
            break;
        case 5://secondPlayer ToggleMenu
            break;
            
        default:
            break;
    }
    
}

bool BBTicToeGamePlay::checkGameResult(int type)
{
    CCDelayTime *actionDelay = CCDelayTime::create(0.2f);
    if((index[0]==type&&index[1]==type&&index[2]==type))
    {
        this->indexPoint=1;
        this->rotatingAngle=90;
        this->scalingFactor=1.35;
        CCSequence *seq=CCSequence::createWithTwoActions(actionDelay,CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addLine)));
        this->runAction(seq);
        return true;
    }
    else if(index[3]==type&&index[4]==type&&index[5]==type)
    {
        this->indexPoint=4;
        this->rotatingAngle=90;
        this->scalingFactor=1.35;
        CCSequence *seq=CCSequence::createWithTwoActions(actionDelay,CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addLine)));
        this->runAction(seq);
        return true;
    }
    else if(index[6]==type&&index[7]==type&&index[8]==type)
    {
        this->indexPoint=7;
        this->rotatingAngle=90;
        this->scalingFactor=1.35;
        CCSequence *seq=CCSequence::createWithTwoActions(actionDelay,CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addLine)));
        this->runAction(seq);
        return true;
    }
    else if(index[0]==type&&index[3]==type&&index[6]==type)
    {
        this->indexPoint=3;
        this->rotatingAngle=0;
        this->scalingFactor=1.35;
        CCSequence *seq=CCSequence::createWithTwoActions(actionDelay,CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addLine)));
        this->runAction(seq);
        return true;
    }
    else if(index[1]==type&&index[4]==type&&index[7]==type)
    {
        this->indexPoint=4;
        this->rotatingAngle=0;
        this->scalingFactor=1.35;
        CCSequence *seq=CCSequence::createWithTwoActions(actionDelay,CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addLine)));
        this->runAction(seq);
        return true;
    }
    else if(index[2]==type&&index[5]==type&&index[8]==type)
    {
        this->indexPoint=5;
        this->rotatingAngle=0;
        this->scalingFactor=1.35;
        CCSequence *seq=CCSequence::createWithTwoActions(actionDelay,CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addLine)));
        this->runAction(seq);
        return true;
    }
    else if(index[0]==type&&index[4]==type&&index[8]==type)
    {
        this->indexPoint=4;
        this->rotatingAngle=-45;
        this->scalingFactor=1.65;
        CCSequence *seq=CCSequence::createWithTwoActions(actionDelay,CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addLine)));
        this->runAction(seq);
        return true;
    }
    else if(index[2]==type&&index[4]==type&&index[6]==type)
    {
        this->indexPoint=4;
        this->rotatingAngle=45;
        this->scalingFactor=1.65;
        CCSequence *seq=CCSequence::createWithTwoActions(actionDelay,CCCallFuncN::create(this, callfuncN_selector(BBTicToeGamePlay::addLine)));
        this->runAction(seq);
        return true;
    }
    else
        
        return false;
    
}
void BBTicToeGamePlay::addLine()
{
    CCPoint point=this->ticToePointArray->getControlPointAtIndex(this->indexPoint);
    CCSprite *lineSprite=CCSprite::createWithSpriteFrameName("winLine.png");
    lineSprite->setRotation(this->rotatingAngle);
    lineSprite->setPosition(point);
    
    
    lineSprite->setScaleY(this->scalingFactor);
    this->addChild(lineSprite, 3);
    
    CCDelayTime *delayAction=CCDelayTime::create(0.2);
    CCBlink *blinkAction=CCBlink::create(1, 3);
    CCSequence *seq=CCSequence::createWithTwoActions(delayAction, blinkAction);
    lineSprite->runAction(seq);
    
   
    
}
void BBTicToeGamePlay::addLabel(const char *labelname)
{
    if(this->isLabelAdded)
    {
        this->header->removeFromParentAndCleanup(1);
    }
    header=CCLabelTTF::create(labelname, "Noteworthy - 150pt - bold", 50);
    header->setPosition(CCPointMake(512, 650));
    this->addChild(header,2);
    this->isLabelAdded=false;
}
void BBTicToeGamePlay::checkForGameMode(CCPoint location)
{
    CCRect selectGameModeBGRect=selectPlayerBg->boundingBox();
    if(selectGameModeBGRect.containsPoint(location))
    {
        if(this->isPlayerVsIad)
        {
            selectPlayerBg->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ipadVsPlayer.png"));
            this->isIpadVsPlayer=true;
            this->isPlayerVsIad=false;
            this->isTwoPlayer=false;
                     
        }
        else if(this->isIpadVsPlayer)
        {
            selectPlayerBg->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("twoPlayers.png"));
            this->isTwoPlayer=true;
            this->isPlayerVsIad=false;
            this->isIpadVsPlayer=false;
            
        }
        else if(this->isTwoPlayer)
        {
            selectPlayerBg->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("playerVsIpad.png"));
            this->isTwoPlayer=false;
            this->isPlayerVsIad=true;
            this->isIpadVsPlayer=false;
            
        }
        
    }
    

}

#pragma mark - Touches
void BBTicToeGamePlay::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if(this->noOfBoxsFilled==9||this->isGameOver||this->isCpuTurn)
    {
        return;
    }
    CCSetIterator it;
    CCTouch* touch;
    
    bool isPlayerCanAddSprite=true;
    for( it = pTouches->begin(); it != pTouches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        //Add IntialSprite if Mode is IpadVsPlay
        CCRect selectGameModeBGRect=selectPlayerBg->boundingBox();
        if(!this->isSpriteAddedInitiallyInIpadVsPlayerMode&&this->isIpadVsPlayer&&!selectGameModeBGRect.containsPoint(location))
        {
            this->addComputerPlayedSprite();
            this->isSpriteAddedInitiallyInIpadVsPlayerMode=true;
            isPlayerCanAddSprite=false;
        }
        //selectGamePlay Mode
        if(this->buttonMenu->isEnabled())
        {
            this->checkForGameMode(location);
        }
        
        
        //GamePlay
        for(int i=0;i<this->ticToePointArray->count();i++)
        {
            CCPoint point=this->ticToePointArray->getControlPointAtIndex(i);
            CCRect bgRect =CCRectMake(point.x-75, point.y-55, 150, 110);
            
            
            if(bgRect.containsPoint(location)&&index[i]==kNoSprite)
            {
                this->unschedule(schedule_selector(BBTicToeGamePlay::applyBlinkAction));
                this->buttonMenu->setEnabled(false);
                if(this->isTwoPlayer)//--------------------------------------------Two player
                {
                    this->addSpriteOnTouchedPoint(i);
                    
                }
                else
                {
                    if(this->isPlayerVsIad) //----------------------------------------------------------Single player
                    {
                        this->addSpriteOfType(this->isPlayerSelectedXsprite, i, kPlayerSpriteAdded);
                        
                        this->isCpuTurn=true;
                        
                        this->addDelayActionAfterPlayerTurn();
                    }
                    else if(this->isIpadVsPlayer)
                    {
                        if(isPlayerCanAddSprite)
                        {
                            this->addSpriteOfType(this->isPlayerSelectedXsprite, i, kPlayerSpriteAdded);
                            
                            this->isCpuTurn=true;
                            
                            this->addDelayActionAfterPlayerTurn();
                            
                        }
                        
                        
                    }
                }
                
                
            }
        }
        
    }
    
}

