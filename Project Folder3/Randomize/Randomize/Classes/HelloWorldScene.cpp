#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#define MAX_NUM1 17

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

    CCLabelTTF *labelp = CCLabelTTF::create("RESTART"," ARIAL", 20);
    CCMenuItemLabel *lab = CCMenuItemLabel::create(labelp, this, menu_selector(HelloWorld::restart));
    
    CCMenu *m = CCMenu::create(lab,NULL);
    m->setPosition(ccp(240,100));
    this->addChild(m,2);
    
    bucketSprite = CCSprite::create("bucket.png");
    bucketSprite->setPosition(ccp(400,100));
    this->addChild(bucketSprite);
    
     aArray = new CCArray();

    int num[MAX_NUM1];

    this->setTouchEnabled(true);
    
    int i ,n ,tmp;
    int spriteXPos = 60;
    int spriteYPos = 300;

    // srand((unsigned int)time(NULL));
    for(int i=0;i<MAX_NUM1;++i)
        num[i]=i;
    
    for(i=0;i<MAX_NUM1;++i)
    {
        n= rand()%MAX_NUM1;
        
        tmp = num[n];
        
        num[n]= num[i];
        
        num[i] = tmp;
        
    }
    for(i=0;i<MAX_NUM1;++i)
    {
        CCLOG("%d",num[i]);
     
        sprintf(vv,"a%d.png",num[i]);
        
        CCLOG("random %s",vv);
        
        CCSprite* sprite = CCSprite::create(vv);
 
        sprite->setPosition(ccp(spriteXPos,spriteYPos));
        
        this->addChild(sprite);
        
        aArray->addObject(sprite);
        CCLog("%d",aArray->count());
        
        sprite->setTag(i);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        
        if(i==1)
        {
            spriteXPos = spriteXPos+60;
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if(i==2)
        {
            spriteXPos = spriteXPos+60;
            
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if (i==3)
        {
            spriteXPos = spriteXPos+60;
          
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
            
        }
        if(i==4)
        {
            spriteXPos = spriteXPos-200;
            spriteYPos = spriteYPos-70;
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if(i==5)
        {
            spriteXPos = spriteXPos+60;
           
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if(i==6)
        {
            spriteXPos = spriteXPos+60;
           
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if(i==7)
        {
            spriteXPos = spriteXPos+60;
            
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if(i==8)
        {
            
            spriteXPos = spriteXPos-180;
            spriteYPos = spriteYPos-70;

            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if(i==9)
        {
            spriteXPos = spriteXPos+60;
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if(i==10)
        {
            spriteXPos = spriteXPos+60;
           
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }if(i==11)
        {
          spriteXPos = spriteXPos+60;
           
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }if(i==12)
        {
            spriteXPos = spriteXPos+60;
           
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }if(i==13)
        {
            spriteXPos = spriteXPos-220;
            spriteYPos = spriteYPos-70;
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if(i==14)
        {
           spriteXPos = spriteXPos+60;

            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if(i==15)
        {
            spriteXPos = spriteXPos+60;

            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        if(i==16)
        {
            spriteXPos = spriteXPos+60;

            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
       
        
    }
    
    return true;
}
void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( pTouches->anyObject());
    CCPoint location = touch->getLocation();
    
    CCLog("touches began %f %f",location.x,location.y);
    
    bucketRect = CCRectMake(bucketSprite->getPosition().x - bucketSprite->getContentSize().width/2,bucketSprite->getPosition().y - bucketSprite->getContentSize().height/2,bucketSprite->getContentSize().width, bucketSprite->getContentSize().height);
    initialLocation = location;
    
    char str[20] = {"true"} ;
    CCObject* obj;
    CCARRAY_FOREACH(this->aArray,obj)
    {
        CCSprite *aSpr = (CCSprite *)obj;
        animalRect = CCRectMake(aSpr->getPosition().x - aSpr->getContentSize().width/2,aSpr->getPosition().y - aSpr->getContentSize().height/2,aSpr->getContentSize().width, aSpr->getContentSize().height);
        
        if (CCRect::CCRectContainsPoint(animalRect,location))
        {
            CCLOG("%s",str);
            selectedSpr = aSpr;
            isSprSelected = true;
            break;
        }
    }

}

void HelloWorld::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
    
    CCPoint location = touch->getLocationInView();
    
    location = CCDirector::sharedDirector()->convertToGL(location);
    if (isSprSelected)
    {
        selectedSpr->setPosition(location);
        CCLOG("%f and %f",selectedSpr->getPosition().x,selectedSpr->getPosition().y);
    }
}


void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    
    if(selectedSpr->getTag()<=8)
    {
        CCLabelTTF *label = CCLabelTTF::create("TRUE"," ARIAL", 20);
        label->setPosition(ccp(385,300));
        this->addChild(label,2);
        CCScaleTo *scaleBig = CCScaleTo::create(0.4,1);
        CCScaleTo *scaleSmall = CCScaleTo::create(0.4,0);
        CCAction *sequenceAction  = CCSequence::create(scaleBig,scaleSmall,NULL);
        label->runAction(sequenceAction);
        
        CCMoveTo *SprPos=CCMoveTo::create(1, CCPoint(initialLocation));
        selectedSpr->runAction(SprPos);
        
    }
    else if(selectedSpr->getTag()>=9)
    {
        CCLabelTTF *label = CCLabelTTF::create("FALSE"," ARIAL", 20);
        label->setPosition(ccp(385,270));
        this->addChild(label,2);
        CCScaleTo *scaleLarge = CCScaleTo::create(0.4,1);
        CCScaleTo *scaleLess = CCScaleTo::create(0.4,0);
        CCAction *sequenceAction  = CCSequence::create(scaleLarge,scaleLess,NULL);
        label->runAction(sequenceAction);
        CCMoveTo *SprPos=CCMoveTo::create(1, CCPoint(initialLocation));
        selectedSpr->runAction(SprPos);
    }
}

void HelloWorld::restart()
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
