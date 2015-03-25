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

//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
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
//
//    // add "HelloWorld" splash screen"
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    pSprite->setPosition( ccp(size.width/2, size.height/2) );
//
//    // add the sprite as a child to this layer
//    this->addChild(pSprite, 0);
    
    
    _batchNode = CCSpriteBatchNode::batchNodeWithFile("Sprites.pvr.ccz");
    this->addChild(_batchNode);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");
    
    _ship = CCSprite::spriteWithSpriteFrameName("SpaceFlier_sm_1.png");
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _ship->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
    _batchNode->addChild(_ship, 1);
    
    
    
    // 1) Create the CCParallaxNode
    _backgroundNode = CCParallaxNodeExtras::node() ;
    this->addChild(_backgroundNode,-1) ;
    
    // 2) Create the sprites we'll add to the CCParallaxNode
    _spacedust1 = CCSprite::spriteWithFile("bg_front_spacedust.png");
    _spacedust2 = CCSprite::spriteWithFile("bg_front_spacedust.png");
    _planetsunrise = CCSprite::spriteWithFile("bg_planetsunrise.png");
    _galaxy = CCSprite::spriteWithFile("bg_galaxy.png");
    _spacialanomaly = CCSprite::spriteWithFile("bg_spacialanomaly.png");
    _spacialanomaly2 = CCSprite::spriteWithFile("bg_spacialanomaly2.png");
    
    // 3) Determine relative movement speeds for space dust and background
    CCPoint dustSpeed = ccp(0.1, 0.1);
    CCPoint bgSpeed = ccp(0.05, 0.05);
    
    // 4) Add children to CCParallaxNode
    _backgroundNode->addChild(_spacedust1, 0 , dustSpeed , ccp(0,winSize.height/2) ); // 2
    _backgroundNode->addChild(_spacedust2, 0 , dustSpeed , ccp( _spacedust1->getContentSize().width,winSize.height/2));
    _backgroundNode->addChild(_galaxy,-1, bgSpeed , ccp(0,winSize.height * 0.7));
    _backgroundNode->addChild(_planetsunrise,-1 , bgSpeed,ccp(600,winSize.height * 0));
    _backgroundNode->addChild(_spacialanomaly,-1, bgSpeed,ccp(900,winSize.height * 0.3));
    _backgroundNode->addChild(_spacialanomaly2,-1, bgSpeed,ccp(1500,winSize.height * 0.9));
    
    HelloWorld::addChild(CCParticleSystemQuad::particleWithFile("Stars1.plist")) ;
    HelloWorld::addChild(CCParticleSystemQuad::particleWithFile("Stars2.plist")) ;
    HelloWorld::addChild(CCParticleSystemQuad::particleWithFile("Stars3.plist")) ;
    
    
    
#define KNUMASTEROIDS 15
    _asteroids = new CCArray();
    for(int i = 0; i < KNUMASTEROIDS; ++i) {
        CCSprite *asteroid = CCSprite::spriteWithSpriteFrameName("asteroid.png");
        asteroid->setVisible(false) ;
        _batchNode->addChild(asteroid);
        _asteroids->addObject(asteroid);
    }

    this->scheduleUpdate();
    
    this->setAccelerometerEnabled(true);
    
    return true;
 
}
void HelloWorld::update(CCTime dt) {
    CCPoint backgroundScrollVert = ccp(-1000,0);
    _backgroundNode->setPosition(ccp(0,-1000)) ;
    
    
    
    CCArray *spaceDusts = CCArray::arrayWithCapacity(2) ;
    spaceDusts->addObject(_spacedust1) ;
    spaceDusts->addObject(_spacedust2) ;
    for ( int ii = 0  ; ii <spaceDusts->count() ; ii++ ) {
        CCSprite * spaceDust = (CCSprite *)(spaceDusts->objectAtIndex(ii)) ;
        float xPosition = _backgroundNode->convertToWorldSpace(spaceDust->getPosition()).x  ;
        float size = spaceDust->getContentSize().width ;
        if ( xPosition < -size ) {
            _backgroundNode->incrementOffset(ccp(spaceDust->getContentSize().width*2,0),spaceDust) ;
        }
    }
    
    CCArray *backGrounds = CCArray::arrayWithCapacity(4) ;
    backGrounds->addObject(_galaxy) ;
    backGrounds->addObject(_planetsunrise) ;
    backGrounds->addObject(_spacialanomaly) ;
    backGrounds->addObject(_spacialanomaly2) ;
    for ( int ii = 0 ; ii <backGrounds->count() ; ii++ ) {
        CCSprite * background = (CCSprite *)(backGrounds->objectAtIndex(ii)) ;
        float xPosition = _backgroundNode->convertToWorldSpace(background->getPosition()).x ;
        float size = background->getContentSize().width ;
        if ( xPosition < -size ) {
            _backgroundNode->incrementOffset(ccp(2000,0),background) ; 
        }
    }
    
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float maxY = winSize.height - _ship->getContentSize().height/2;
    float minY = _ship->getContentSize().height/2;
    
    float diff = (maxY + minY) ;
    float newY = _ship->getPosition().y + diff;
    newY = MIN(MAX(newY, minY), maxY);
    _ship->setPosition(ccp(_ship->getPosition().x, newY));


    float curTimeMillis = getTimeTick();
    if (curTimeMillis > _nextAsteroidSpawn) {
        
        float randMillisecs = randomValueBetween(0.20,1.0) * 1000;
        _nextAsteroidSpawn = randMillisecs + curTimeMillis;
        
        float randY = randomValueBetween(0.0,winSize.height);
        float randDuration = randomValueBetween(2.0,10.0);
        

        _nextAsteroid++;
        
        if (_nextAsteroid >= _asteroids->count())
            _nextAsteroid = 0;
#define KNUMLASERS 5
        
        for(int i = 0; i < KNUMLASERS; ++i) {
            CCSprite *shipLaser = CCSprite::spriteWithSpriteFrameName("laserbeam_blue.png");
            shipLaser->setVisible(false) ;
            _batchNode->addChild(shipLaser);
           
        }
        
        this->setTouchEnabled(true) ;
            
    }

}
void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize() ;
    
 
  
}

void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue) {
#define KFILTERINGFACTOR 0.1
#define KRESTACCELX -0.6
#define KSHIPMAXPOINTSPERSEC (winSize.height*0.5)
#define KMAXDIFFX 0.2
    
    double rollingX ;
    
    // Cocos2DX inverts X and Y accelerometer depending on device orientation
    // in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
    pAccelerationValue->x = pAccelerationValue->y ;
    rollingX = (pAccelerationValue->x * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));
    float accelX = pAccelerationValue->x - rollingX ;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float accelDiff = accelX - KRESTACCELX;
    float accelFraction = accelDiff / KMAXDIFFX;
    _shipPointsPerSecY = KSHIPMAXPOINTSPERSEC * accelFraction;
}

float HelloWorld::randomValueBetween( float low , float high ) {
    return (((float) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}

float HelloWorld::getTimeTick() {
    timeval time;
    gettimeofday(&time, NULL);
    unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (float) millisecs;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
