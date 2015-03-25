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
    if ( !CCLayer::init() )
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
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    sprite = CCSprite::create("CloseNormal.png");

    // position the sprite on the center of the screen
    sprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    sprite1= CCSprite::create("CloseNormal.png");
    
    // position the sprite on the center of the screen
    sprite1->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(sprite1, 0);
    
    this->moveSprite();
    
    
    return true;
}
void HelloWorld::moveSprite() {
    
    CCActionInterval *move = CCMoveBy::create(1.0, ccp(50, 100));
    CCActionInterval *moveback = (CCActionInterval*)move->reverse();
    
    CCFiniteTimeAction *callbackk = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::skewSprite));
    
    CCSequence *seq1 = (CCSequence*)CCSequence::create(move,moveback,callbackk,NULL);
    sprite->runAction(seq1);
}

void HelloWorld::skewSprite() {
    
   CCActionInterval *skew = CCSkewBy::create(1.0, 45, 180);
   CCActionInterval *by = skew->reverse();
    
    CCFiniteTimeAction *callbackk = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::moveSprite));
    
    CCSequence *seq2 =(CCSequence*)CCSequence::create(skew,by,callbackk,NULL);
    sprite1->runAction(seq2);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
