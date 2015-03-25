#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#define KFREEINDEXTAG 500
using namespace cocos2d;
using namespace CocosDenshion;
#define MAX_NUM1 16
USING_NS_CC;

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
    
    shufflebg->release();
    shuffle->release();
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
    
    /*    /////////////////////////////
     // 3. add your codes below...
     
     // add a label shows "Hello World"
     // create and initialize a label
     CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
     /Users/deepthi/Desktop/Anshul/ArrangeShuffleImages/ArrangeShuffleImages/Resources/shuffle.plist
     // ask director the window size
     CCSize size = CCDirector::sharedDirector()->getWinSize();
     
     // position the label on the center of the screen
     pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
     
     // add the label as a child to this layer
     this->addChild(pLabel, 1);
     */
    
    CCLabelTTF *restartLabel=CCLabelTTF::create("Shuffle", "Arial", 20);
    CCMenuItemLabel *restartMenuItem=CCMenuItemLabel::create(restartLabel, this, menu_selector(HelloWorld::Shuffle));
    CCMenu *restartMenu=CCMenu::create(restartMenuItem,NULL);
    this->addChild(restartMenu ,1);
    restartMenu->setPosition(ccp(190, 20));
    
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shuffle.plist");
    
    this->setTouchEnabled(true);
    
    
    int x1=100;
    int y1=260;
    
    for (int i=0; i<=14; i++) {
        
        index[i]=1;
    }
    index[15]=0;
    
    
    
    shufflebg = CCArray::create();
    shufflebg->retain();
    
    int backTag = 0;
    char *shufflebg1 = new char;
    
    for (int i = 1; i <= 16; i++) {
        
        sprintf(shufflebg1, "i%d.png",i);
        
        CCSprite *SFLb = CCSprite::createWithSpriteFrameName(shufflebg1);
        SFLb->setPosition(ccp(x1, y1));
        SFLb->setOpacity(0);
        SFLb->setTag(backTag);
        CCLog("backtag is %d",backTag);
        backTag++;
        this->addChild(SFLb);
        shufflebg->addObject(SFLb);
        
        x1=x1+50;
        
        if (i % 4 == 0) {
            
            x1=100;
            y1=y1-50;
        }
    }
    
    
    
    int x=100;
    int y=260;
    
    shuffle = CCArray::create();
    shuffle->retain();
    
    //int j=27;
    char *shuffle1 = new char;
    
    for (int i = 1; i <= 15; i++) {
        
        sprintf(shuffle1, "i%d.png",i);
        
        CCSprite *SFL = CCSprite::createWithSpriteFrameName(shuffle1);
        SFL->setPosition(ccp(x, y));
        SFL->setTag(backTag);
        backTag++;
        this->addChild(SFL);
        shuffle->addObject(SFL);
        
        x=x+50;
        
        if (i % 4 == 0) {
            
            x=100;
            y=y-50;
        }
    }
    
    
    
    //    this->schedule(schedule_selector(HelloWorld::Shuffle));
    
    return true;
}


void HelloWorld::Shuffle(){
    
    int num1[MAX_NUM1],n,temp;
    int x = 100;
    int y = 260;
      
    char  array[20];
    
    for(int i=0;i<MAX_NUM1;++i)
        
        num1[i]=i;
    
    for(int i=0;i <= MAX_NUM1;++i){
        
        n= rand() % MAX_NUM1;
        
        temp = num1[n];
        
        num1[n]= num1[i];
        
        num1[i] = temp;
        
    }
    for(int i=1;i<=MAX_NUM1;++i)
    {
        CCLOG("random no = %d",num1[i]);
        
        sprintf(array, "i%d.png",num1[i]);
        
        CCLOG("random no = %d",array);
        
        CCSprite *SFL = CCSprite::createWithSpriteFrameName(array);
        SFL->setPosition(ccp(x, y));
        SFL->setTag(backTag);
        backTag++;
        this->addChild(SFL);
        shuffle->addObject(SFL);
        
        x=x+50;
        
        if (i % 4 == 0) {
            
            x=100;
            y=y-50;
        }
    }
    
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
    
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    CCPoint touchPoint = touch->getLocationInView();
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
    int touchedIndex = 0;
    int freeIndex = 0;
    
    CCObject *bg = NULL;
    CCObject *fg = NULL;
    
    CCARRAY_FOREACH(this->shufflebg, bg){
        
        CCSprite * bgSpr = (CCSprite*)bg;
        
        CCRect bgRect = CCRectMake(bgSpr->getPosition().x - bgSpr->getContentSize().width/2,
                                   bgSpr->getPosition().y - bgSpr->getContentSize().height/2,
                                   bgSpr->getContentSize().width,
                                   bgSpr->getContentSize().height);
        
        if (bgRect.containsPoint(touchPoint)){
            
            touchedIndex = bgSpr->getTag();
            CCLog("touchIndex = %d",touchedIndex);
            break;
        }
    }
    
    CCARRAY_FOREACH(this->shuffle, fg){
        
        CCSprite *fgSpr = (CCSprite *)fg;
        
        CCRect fgRect = CCRectMake(fgSpr->getPosition().x - fgSpr->getContentSize().width/2,
                                   fgSpr->getPosition().y - fgSpr->getContentSize().height/2,
                                   fgSpr->getContentSize().width,
                                   fgSpr->getContentSize().height);
        
        
        if (fgRect.containsPoint(touchPoint)) {
            
            freeIndex= this->getFreeIndexPosition();
            
            if (this->checkForValidMovement(touchedIndex, freeIndex)) { // Checking for corner conditions
                
                // single index movement
                if ((abs(freeIndex - touchedIndex) == 1) && (touchedIndex != 4 && touchedIndex != 8 && touchedIndex != 12)) {
                    
                    CCPoint freePosition = this->returnBackgroundChildByTag(freeIndex);
                    fgSpr->setPosition(ccp(freePosition.x, freePosition.y));
                    this->updateIndex(touchedIndex);
                    this->updateTag(fgSpr, freeIndex);
                }
                else if (abs(freeIndex - touchedIndex) == 4) {
                    
                    CCPoint freePosition = this->returnBackgroundChildByTag(freeIndex);
                    fgSpr->setPosition(ccp(freePosition.x, freePosition.y));
                    this->updateIndex(touchedIndex);
                    this->updateTag(fgSpr, freeIndex);
                }
                else if(freeIndex > touchedIndex) {             // Forward Movement! Multiple sprites
                    
                    if ((freeIndex - touchedIndex) <= 3) {      // Horizontal
                        
                        int startingTag = touchedIndex + (freeIndex - touchedIndex) - 1;
                        
                        for (int i = startingTag ; i >= touchedIndex; i--) {
                            
                            CCSprite *bg = (CCSprite *)this->getChildByTag(i+16);
                            CCPoint nextPosition = this->returnBackgroundChildByTag(i+1);
                            bg->setPosition(nextPosition);
                            this->updateIndex(bg->getTag()-16);
                            this->updateTag(bg, (bg->getTag()-16)+1);
                        }
                    }
                    else {
                        
                        if((freeIndex==15 || freeIndex == 11 || freeIndex == 7) && (touchedIndex==8 ||touchedIndex==9 || touchedIndex==10 || touchedIndex==4 || touchedIndex==5 || touchedIndex==6|| touchedIndex==0 ||touchedIndex==1 || touchedIndex==2)){
                            return;
                            
                        }
                        else if((freeIndex==13 || freeIndex == 9 || freeIndex == 5) && (touchedIndex==2 || touchedIndex==3 || touchedIndex==6 ||touchedIndex==7 || touchedIndex==10 || touchedIndex==11||touchedIndex==0 ||touchedIndex==4 || touchedIndex==8)){
                            return;
                        }
                        else if((freeIndex==14 || freeIndex == 10 || freeIndex == 6) && (touchedIndex==0 ||touchedIndex==1 || touchedIndex==3 ||touchedIndex==4 || touchedIndex==5 || touchedIndex==7 || touchedIndex==8 ||touchedIndex==9||touchedIndex==11)){
                            return;
                        }
                        else if((freeIndex==12 || freeIndex == 4 || freeIndex == 8) && (touchedIndex==1 ||touchedIndex==2 ||touchedIndex==3 ||touchedIndex==5 ||touchedIndex==6 ||touchedIndex==7 || touchedIndex==9 ||touchedIndex==10 ||touchedIndex==11)){
                            return;
                            
                        }
                        else {
                            int difference = freeIndex - touchedIndex;
                            int startingTag = touchedIndex + (difference - 4);
                            
                            for (int i = startingTag ; i >= touchedIndex; i = i-4) {
                                
                                CCSprite *bg = (CCSprite *)this->getChildByTag(i+16);
                                CCPoint nextPosition = this->returnBackgroundChildByTag(i+4);
                                bg->setPosition(nextPosition);
                                this->updateIndex(bg->getTag()-16);
                                this->updateTag(bg, (bg->getTag()-16)+4);
                            }
                        }
                    }
                    
                }
                else {                                              // Backward movement
                    
                    if (abs(freeIndex - touchedIndex) <= 3 && (touchedIndex != 4 && touchedIndex != 8 && touchedIndex != 12  && touchedIndex != 1 && touchedIndex != 5 && touchedIndex != 9 && touchedIndex != 13 && touchedIndex!=2 && touchedIndex!=6 && touchedIndex!=10 &&touchedIndex!=14)) {
                        //  Horizontal
                        
                        for (int i = freeIndex + 1; i <= touchedIndex; i++) {
                            
                            CCSprite *bg = (CCSprite *)this->getChildByTag(i+16);
                            CCPoint nextPosition = this->returnBackgroundChildByTag(i-1);
                            bg->setPosition(nextPosition);
                            this->updateIndex(bg->getTag()-16);
                            this->updateTag(bg, (bg->getTag()-16)-1);
                        }
                    }
                    else {                                           // Vertical
                        
                        int startingIndex = freeIndex + 4;
                        
                        if(((freeIndex==3 || freeIndex ==7||freeIndex ==11) && (touchedIndex==14 || touchedIndex==13 || touchedIndex==12 || touchedIndex==9 || touchedIndex==10 ||touchedIndex ==8 ))){
                            
                            return;
                        }
                        else if((freeIndex==1 || freeIndex==5 || freeIndex==9) && (touchedIndex==4 ||touchedIndex==8|| touchedIndex==12 || touchedIndex==6 || touchedIndex==10 || touchedIndex==14 ||touchedIndex==15 || touchedIndex==7 || touchedIndex==11)){
                            
                            return;
                        }
                        else if ((freeIndex == 2 || freeIndex == 6 || freeIndex == 10) && ( touchedIndex == 7 || touchedIndex == 9 || touchedIndex == 11 || touchedIndex == 12 || touchedIndex == 13 || touchedIndex == 15)) {
                            
                            return;
                        }
                        else if (!((freeIndex == 0 || freeIndex == 4 || freeIndex == 8) && (touchedIndex==15 ||touchedIndex==14 ||touchedIndex==13 || touchedIndex == 11 || touchedIndex == 10 ||touchedIndex == 9 || touchedIndex == 7 || touchedIndex ==6 || touchedIndex == 5))) {
                            
                            for (int i = startingIndex; i <= touchedIndex; i = i+4) {
                                
                                CCSprite *bg = (CCSprite *)this->getChildByTag(i+16);
                                CCPoint nextPosition = this->returnBackgroundChildByTag(i-4);
                                bg->setPosition(nextPosition);
                                this->updateIndex(bg->getTag()-16);
                                this->updateTag(bg, (bg->getTag()-16)-4);
                            }
                        }
                    }
                }
            }
        }
    }
}


bool HelloWorld::checkForValidMovement(int touchedIndex, int freeIndex) {
    
    bool isValid = true;
    
    // +1 coz values starting from 0
    touchedIndex = touchedIndex + 1;
    freeIndex = freeIndex + 1;
    
    if (freeIndex > touchedIndex) {                     // horizontal
        
        if ((freeIndex - touchedIndex) <= 3) {
            
            int startingTag = freeIndex - 1;
            
            for (int i = startingTag ; i >= touchedIndex; i--) {
                
                if (i % 4 == 0) {
                    
                    return false;
                }
            }
        }
    }
    else {
        
        //        if (abs(freeIndex - touchedIndex) > 4) {      // horizontal
        //
        //            return false;
        //        }
    }
    
    return isValid;
}


CCPoint HelloWorld::returnBackgroundChildByTag(int tag) {
    
    CCLog("tag = %d",tag);
    CCSprite *backgroundSprite = (CCSprite *)this->getChildByTag(tag);
    CCPoint position = backgroundSprite->getPosition();
    CCLog("position = %f %f",position.x,position.y);
    return position;
}


void HelloWorld::printCurrentTags() {
    
    CCObject *obj = NULL;
    
    CCARRAY_FOREACH(shuffle, obj) {
        
        CCSprite *spr = (CCSprite *)obj;
        CCLog("spr tag = %d",spr->getTag());
    }
}


void HelloWorld::updateIndex(int indexNum){
    
    for (int i = 0; i <= 15; i++) {
        
        index[i]=1;
    }
    index[indexNum] = 0;
    CCLog("free index = %d",indexNum);
}


void HelloWorld::updateTag(CCSprite *sprite, int toValue){
    
    sprite->setTag(toValue+16);
    
    CCObject *temp = NULL;
    
    CCARRAY_FOREACH(shuffle, temp) {
        
        CCSprite *spr = (CCSprite *)temp;
        CCLog("temp tag is %d",spr->getTag());
    }
}


int HelloWorld::getFreeIndexPosition(){
    
    int positionID = 0;
    
    for (int i = 0; i <= 15; i++) {
        
        if (index[i] == 0) {
            
            positionID = i;
            break;
        }
    }
    return positionID;
}




void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
