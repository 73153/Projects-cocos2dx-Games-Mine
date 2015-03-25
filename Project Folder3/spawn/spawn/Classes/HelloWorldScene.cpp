#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

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
    if (!CCLayer::init())
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
    
    //Create menu, it's an autorelease object
    CCMenu *pMenu = CCMenu::create(pCloseItem,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu,1);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    m_grossini = CCSprite::create("cat.png");
    m_grossini->setPosition( CCPointMake(60, size.height/2));
    this->addChild(m_grossini);
    m_grossini->setPosition(CCPointMake(80,160));
    
    m_tamara = CCSprite::create("dog.png");
    m_tamara->setPosition(CCPointMake(60, size.height/2));
    this->addChild(m_tamara);
    m_tamara->setPosition(CCPointMake(80,160));
    
//    this->move();
/*
    //Spawn Action
    CCAction *action = CCSpawn::create(CCJumpBy::create(2, ccp(450,50), 50, 3),
                                        CCRotateBy::create(2,720),
                                        NULL);
    CCActionInterval *move1 = CCMoveBy::create(1, CCPointMake(250,0));
    CCActionInterval *move2 = CCMoveBy::create(1, CCPointMake(0,50));
    CCFiniteTimeAction *seq = CCSequence::create(move1, move2, move1->reverse(), NULL);
    CCFiniteTimeAction *action = CCSequence::create(seq, seq->reverse(), NULL);
    
    m_grossini->runAction(action);
*/


/*
    //EaseIn/Out Action
    CCActionInterval *actionTo = CCScaleTo::create(0.8f, 2.5f);
//    CCAction *easeIn = CCEaseIn::actionWithAction(actionTo, 5);
    CCAction *easeIn = CCEaseIn::create(actionTo, 5);
    m_grossini->runAction(easeIn);
    
    CCActionInterval *actionFro = CCScaleTo::create(0.8f, 2.5f);
    CCAction *easeOut = CCEaseOut::create(actionFro,5);
    m_grossini->runAction(easeOut);
*/


/*
    //CardinalSplineBy Action
    // Create an array of points ....
    CCPointArray *pArray = CCPointArray::create (20);
    
    //Add control points
    pArray->addControlPoint(ccp(0,0));
    pArray->addControlPoint(ccp(size.width/2-30,0));
    pArray->addControlPoint(ccp(size.width/2-30,size.height-80));
    pArray->addControlPoint(ccp(0,size.height-80));
    pArray->addControlPoint(ccp(0,0));
    
    //Create(parameters: duration, parameters: Points group Parameter 3: Tension can be understood as the inertia, the greater the value, the greater the inertia)
    CCCardinalSplineBy *action = CCCardinalSplineBy::create(6,pArray,7);
//    CCCatmullRomBy *actionCatMul = CCCatmullRomBy::create(6,pArray);
    CCActionInterval *reverse = action->reverse();
    
    //Create a sequence of actions ....
    CCFiniteTimeAction * seq = CCSequence::create(action, reverse, NULL);
    m_grossini->runAction(seq);
*/


/*
    //Bezier Action
    ccBezierConfig *bezier;
    
    //Bezier curve
    bezier->controlPoint_1 = CCPointMake(1002.0f,475.0f);
    bezier->controlPoint_2 = CCPointMake(454.0f, 281.0f);
    bezier->endPosition = CCPointMake(-20.0f,490.0f);
    
    CCBezierBy *bezierForward = CCBezierBy::create(3,bezier);
    CCActionInterval *bezierBack = bezierForward->reverse();
    CCAction *rep = CCRepeatForever::create((CCActionInterval*)CCSequence::create(bezierForward, bezierBack, NULL));
    
    m_grossini->runAction(rep);
*/

/*  //EaseInOut Action
    CCMoveBy *actionMove = CCMoveBy::create(0.2, CCPointMake(0, 100));
    
    CCEaseInOut *inout = CCEaseInOut::create(actionMove, 3);
    CCAction *reverse = inout->reverse();
    CCFiniteTimeAction *seq = CCSequence::create(inout, reverse, NULL);
    
    m_grossini->runAction(seq);
    
    //to run Action forever
    CCAction *rep = CCRepeatForever::create((CCActionInterval*)seq);
    m_grossini->runAction(rep);
*/

/*
    //load a spriteSheet with respective names and play the animation
    CCAnimation* animation = CCAnimation::create();
    char frameName[100] = {0};
 
    for(int i=1;i<15;i++){
        
        sprintf(frameName, "Images/grossini_dance_%02d.png", i);
        animation->addSpriteFrameWithFileName(frameName);
    }

    CCActionInterval* action = CCAnimate::create(animation);
    CCActionInterval* action_back = action->reverse();
    CCFiniteTimeAction *seq = CCSequence::create(action, action_back, NULL);
 
    m_grossini->runAction(seq);
*/
    return true;
}


/*
void HelloWorld::move() {
    
    CCMoveBy *actionMove = CCMoveBy::create(3, CCPointMake(200, 200));
    
    CCCallFuncN *callToMoveReverse = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::moveReverse));
    
    CCSequence *seq1 = (CCSequence*)CCSequence::create(actionMove,actionMove->reverse(),callToMoveReverse,NULL);
    m_grossini->runAction(seq1);
}


void HelloWorld::moveReverse() {
    
    CCActionInterval *skew = CCSkewBy::create(1.0, 45, 180);
    CCActionInterval *by = skew->reverse();
    
    CCCallFuncN *callToMove = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::move));
    
    CCSequence *seq2 = (CCSequence*)CCSequence::create(skew, by, callToMove, NULL);
    m_tamara->runAction(seq2);
}
*/

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

