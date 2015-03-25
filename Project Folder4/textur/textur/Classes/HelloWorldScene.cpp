#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "CCShaderCache.h"
#include "CCGLProgram.h"

#include "CCActionCatmullRom.h"

#include "CCPointExtension.h"

#include <string.h>

#include <cmath>

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
    
    setTouchEnabled(true);
    

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
    
    this->addTexture();
    
    return true;
    
}


void HelloWorld::addTexture(){
   
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    // create a render texture, this is what we are going to draw into
    m_pTarget = CCRenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888);
    m_pTarget->retain();
    m_pTarget->setPosition(ccp(s.width / 2, s.height / 2));
    
    // note that the render texture is a CCNode, and contains a sprite of its texture for convience,
    // so we can just parent it to the scene like any other CCNode
    this->addChild(m_pTarget, -1);
    
    // create a brush image to draw into the texture with
    m_pBrush = CCSprite::create("11.png");
    m_pBrush->retain();
    m_pBrush->setColor(ccRED);
    m_pBrush->setOpacity(20);
    this->setTouchEnabled(true);

}

void HelloWorld::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCTouch *touch = (CCTouch *)touches->anyObject();
    CCPoint start = touch->getLocation();
    CCPoint end = touch->getPreviousLocation();
    
    // begin drawing to the render texture
    m_pTarget->begin();
    
    // for extra points, we'll draw this smoothly from the last position and vary the sprite's
    // scale/rotation/offset
    float distance = ccpDistance(start, end);
    if (distance > 1)
    {
        int d = (int)distance;
        for (int i = 0; i < d; i++)
        {
            float difx = end.x - start.x;
            float dify = end.y - start.y;
            float delta = (float)i / distance;
            m_pBrush->setPosition(ccp(start.x + (difx * delta), start.y + (dify * delta)));
            m_pBrush->setRotation(rand() % 360);
            float r = (float)(rand() % 50 / 50.f) + 0.25f;
            m_pBrush->setScale(r);
            /*m_pBrush->setColor(ccc3(CCRANDOM_0_1() * 127 + 128, 255, 255));*/
            // Use CCRANDOM_0_1() will cause error when loading libtests.so on android, I don't know why.
            m_pBrush->setColor(ccc3(rand() % 127 + 128, 255, 255));
            // Call visit to draw the brush, don't call draw..
            m_pBrush->visit();
        }
    }
  
    
    // finish drawing and return context back to the screen
    m_pTarget->end();
}


HelloWorld::~HelloWorld()
{
    m_pBrush->release();
}



void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
