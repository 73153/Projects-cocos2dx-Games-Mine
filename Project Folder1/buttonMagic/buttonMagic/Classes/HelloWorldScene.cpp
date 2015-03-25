#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define kButtonOneTag 555

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
//    // create and initialize a label
//    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
//
//    // ask director the window size
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//
//    // position the label on the center of the screen
//    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
//
//    // add the label as a child to this layer
//    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
//    pSprite->setPosition( ccp(size.width/2, size.height/2) );
//
//    // add the sprite as a child to this layer
//    this->addChild(pSprite, 0);
    
    
    CCMenuItemImage* item1 = CCMenuItemImage::create("3.png", "3.png", this, menu_selector(HelloWorld::buttonPressed) );
    item1->setPosition(ccp(180,200));
    item1->setTag(44);
    
    CCMenuItemImage* item2 = CCMenuItemImage::create("6.png", "6.png", this, menu_selector(HelloWorld::buttonPressed) );
    item2->setPosition(ccp(180,100));
    item2->setTag(77);
    
    CCMenuItemImage* item3 = CCMenuItemImage::create("11.png", "11.png", this, menu_selector(HelloWorld::buttonPressed) );
    item3->setPosition(ccp(400,200));
    item3->setTag(kButtonOneTag);
    
    CCMenuItemImage* item4 = CCMenuItemImage::create("33.png", "33.png", this, menu_selector(HelloWorld::buttonPressed) );
    item4->setPosition(ccp(400,100));
    item4->setTag(30);

    CCMenu* menu = CCMenu::create(item1,item2,item3,item4, NULL);
    menu->setPosition(CCPointZero);
    addChild(menu,0);
    
    label = CCLabelTTF::create("gyghghljk ", "ARIAL",40);
    label->setPosition(ccp(240,300));
    this->addChild(label);

    return true;
}
void HelloWorld::buttonPressed(CCObject *sender){
    CCLOG("function called");
     CCMenuItemImage *aMenuItem = (CCMenuItemImage *)sender;
    int ch=aMenuItem->getTag();
    
    switch(ch)
    {
    case 44:
        CCLOG("sender tag %d");
            
            label->setString("3");
            break;
        case 77:
        CCLOG("sender tag %d",aMenuItem->getTag());
            
            label->setString("6");
            break;
        case kButtonOneTag:CCLOG("sender tag %d",aMenuItem->getTag());
            label->setString("11");
            break;
        case 30: CCLOG("sender tag %d",aMenuItem->getTag());
            label->setString("33");
        default : CCLog("WRONG CHOICE");
            break;
            

            
    }

    }
     
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
