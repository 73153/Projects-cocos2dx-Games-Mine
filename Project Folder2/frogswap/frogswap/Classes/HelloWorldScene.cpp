#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "frogover.h"

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
HelloWorld::~HelloWorld(){
    
    sprites->release();
    stoneSpr->release();
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
    CCLabelTTF* pLabel = CCLabelTTF::create("Froggy", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    this->setTouchEnabled(true);
    
    
    //restart menu
    
    CCLabelTTF *restartLabel=CCLabelTTF::create("Restart", "Arial", 20);
    CCMenuItemLabel *restartMenuItem=CCMenuItemLabel::create(restartLabel, this, menu_selector(HelloWorld::restart));
    CCMenu *restartMenu=CCMenu::create(restartMenuItem,NULL);
    this->addChild(restartMenu ,1);
    restartMenu->setPosition(ccp(190, 20));

    // adding texture into the project
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("q.plist");
    CCSprite* pSprite = CCSprite::createWithSpriteFrameName("backgroundUwall.png");
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);
    

    // initializing the index
    
    index[0]=1;
    index[1]=1;
    index[2]=1;
    index[3]=0;
    index[4]=1;
    index[5]=1;
    index[6]=1;
    
    stoneSpr = CCArray::create();
    stoneSpr->retain();
    
    int backTag = 11;
    
    int a=50;
    int b=182;
    
    for (int i=0;i<=6;i++)        // background red sprites
    {
        CCSprite *backgroundRed = CCSprite::createWithSpriteFrameName("na1.png");
        this->addChild(backgroundRed, 1);
        backgroundRed->setPosition(ccp(a,b));
        backgroundRed->setOpacity(0);
        a=a+60;
        printf("%f & %f",backgroundRed->getPositionX(),backgroundRed->getPositionY());
        backgroundRed->setTag(backTag);
        backTag++;
        stoneSpr->addObject(backgroundRed);
    }
    
    int x=50;
    int y=160;
    
    for (int i=0;i<=6;i++)        // black stones sprites
    {
        CCSprite *black = CCSprite::createWithSpriteFrameName("na3.png");
        this->addChild(black, 1);
        black->setPosition(ccp(x,y));
        x=x+60;
        printf("%f",black->getPositionX());
    }
    
    int j=1;
    a=50;
    b=195;
    
    sprites = CCArray::create();
    sprites->retain();

    
    for(int i=1;i<=3;i++){       // red sprites array
        
        red = CCSprite::createWithSpriteFrameName("na6.png");
        this->addChild(red, 1);
        red->setPosition(ccp(a, b));
        a=a+60;
        red->setTag(j);
        j++;
        sprites->addObject(red);
    }
    
    int k=4;
    int p=290;
    int q=195;
    
    for(int i=1;i<=3;i++){       // blue sprites array
        
        blue = CCSprite::createWithSpriteFrameName("na7.png");
        this->addChild(blue, 1);
        blue->setPosition(ccp(p, q));
        p=p+60;
        blue->setTag(k);
        k++;
        sprites->addObject(blue);
    }
    
    this->schedule(schedule_selector(HelloWorld::update));

    return true;
}


void HelloWorld::update(float dt){

    CCSprite *lastBlueSpr= (CCSprite *) this->getChildByTag(6);
    
    CCSprite *firstRedSpr=(CCSprite *) this->getChildByTag(1);
    
    if(lastBlueSpr->getPosition().x == 170 && firstRedSpr->getPosition().x == 290)
    {
        CCDelayTime *delay=CCDelayTime::create(1);
        
        CCCallFunc *callback=CCCallFunc::create(this, callfunc_selector(HelloWorld::callBackFunc));
        
        this->runAction(CCSequence::create(delay,callback,NULL));
    }
}
                   
           
void HelloWorld::callBackFunc(){
    
    CCDirector::sharedDirector()->replaceScene(frogover::scene());
    CCLog(" you won the game ");
}


void HelloWorld::restart(){
    
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}


void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
    
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    CCPoint touchPoint = touch->locationInView();
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    int touchedIndex = 0;
    
    CCObject *spriteRR = NULL;
    CCObject *spriteBB = NULL;
    
    int freeIndexB;
    
    CCARRAY_FOREACH(this->stoneSpr, spriteRR) {          // get size of backgroundred sprites from stoneSpr array
        
        CCSprite *redSpr = (CCSprite *)spriteRR;
        
        CCRect redRect = CCRectMake(redSpr->getPosition().x - redSpr->getContentSize().width/2,
                                    redSpr->getPosition().y - redSpr->getContentSize().height/2,
                                    redSpr->getContentSize().width,
                                    redSpr->getContentSize().height);
        
        if (CCRect::CCRectContainsPoint(redRect, touchPoint)) {

                touchedIndex = redSpr->getTag();
                break; 
        }
    }

    CCARRAY_FOREACH(this->sprites, spriteBB) {            // get size of red & blue sprites from sprites array
        
        CCSprite *blueSpr = (CCSprite *)spriteBB;
        
        CCRect blueRect = CCRectMake(blueSpr->getPosition().x - blueSpr->getContentSize().width/2, 
                                     blueSpr->getPosition().y - blueSpr->getContentSize().height/2,
                                     blueSpr->getContentSize().width,
                                     blueSpr->getContentSize().height);
        
        if(CCRect::CCRectContainsPoint(blueRect, touchPoint)) {
         
            freeIndexB = this->getFreeIndexPosition();
            CCSprite *tempB = (CCSprite *)this->getChildByTag(freeIndexB);
            
            if(freeIndexB - touchedIndex <= abs(2))  // difference; general condition for red and blue sprites for     
                                                //   to take jump
            {
                if (blueSpr->getTag() <= 3) 
                {
                    if (freeIndexB > touchedIndex)
                    {                                               // forward touch index for red sprites
                        blueSpr->setPosition(tempB->getPosition());
                        this->updateIndex(touchedIndex-11);
                        break;
                    }
                }
                else if(blueSpr->getTag() > 3)
                {
                    float diff=blueSpr->getPosition().x-tempB->getPosition().x;

                    if (freeIndexB < touchedIndex && diff <= 120) 
                    {                                               // backward touch index for blue sprites
                        blueSpr->setPosition(tempB->getPosition());
                        this->updateIndex(touchedIndex-11);
                        break;
                    }
                }
            }  
        }
    }
}


void HelloWorld::updateIndex(int indexNum) {
    
    for (int i = 0; i <= 6; i++) {
        
        index[i]=1;
    }
    index[indexNum] = 0;
}


int HelloWorld::getFreeIndexPosition() {
        
    int positionID = 0;
    
    for (int i = 0; i <= 6; i++) {
        
        if (index[i] == 0) {
            
            positionID = i + 11;
            break;
        }
    }
    return positionID;
}


void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

}


void HelloWorld::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    
} 

 
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
