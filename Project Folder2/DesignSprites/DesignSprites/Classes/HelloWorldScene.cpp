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
    
    
    int x=260;
    int y=250;
    
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
        
    for(int i =1; i <=8; i++ )
    {
        CCSprite *p = CCSprite::create("CloseNormal.png");
        this->addChild(p,1);
        p->setPosition(ccp(x,y));
        
        if(i<3)
        {
            x = x+60;
            y = y-40;
            printf("position %f and %f",p->getPositionX(),p->getPositionY());
        }
        else if(i>=3 && i<5)
        {
            x = x-60;
            y = y-40;
            printf("position %f and %f",p->getPositionX(),p->getPositionY());
        }
        else if(i>=5 && i<7)
        {
            x = x-60;
            y = y+40;
            printf("position %f and %f",p->getPositionX(),p->getPositionY());
            
        }
        else if (i>=7)
        {
            x = x+60;
            y = y+40;
            printf("position %f and %f",p->getPositionX(),p->getPositionY());
        }
    }

       return true;
}



//for(int i =1; i <=5; i++ )
//{
//    CCSprite *sprite = CCSprite::create("CloseNormal.png");
//    this->addChild(sprite,1);
//    sprite->setPosition(ccp(x,y));
//    
//    if(i<3)
//    {
//        x = x+80;
//        y = y-40;
//    }
//    else
//    {
//        x = x-80;
//        y = y-40;
//    }
//}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
