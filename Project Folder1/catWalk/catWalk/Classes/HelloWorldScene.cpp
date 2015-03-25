#include "HelloWorldScene.h"
#include "CCObject.h"

using namespace cocos2d;

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
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png","CloseSelected.png",this,menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    
    this->setTouchEnabled(true);
    
    CCLabelTTF *labelp = CCLabelTTF::create("RESTART"," ARIAL", 20);
    CCMenuItemLabel *lab = CCMenuItemLabel::create(labelp, this, menu_selector(HelloWorld::restart));
    
    CCMenu *m = CCMenu::create(lab,NULL);
    m->setPosition(ccp(240,100));
    this->addChild(m,2);
    
    bucketSprite = CCSprite::create("bucket.png");
    bucketSprite->setPosition(ccp(400,160));
    this->addChild(bucketSprite);
    
    
    int spriteXPos = 60;
    int spriteYPos = 300;
    char* vv = new char;
    
    aArray = new CCArray();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("a.plist");
    
    for(int j =1; j <=8; j++ )
    {
        sprintf(vv,"a%d.png",j);
        
        CCSprite* sprite = CCSprite::createWithSpriteFrameName(vv);
        
        this->addChild(sprite);
        
        aArray->addObject(sprite);
        CCLog("%d",aArray->count());
        
        sprite->setTag(j);
        
        sprite->setPosition(ccp(spriteXPos,spriteYPos));
        if(j<3)
        {
            spriteXPos = spriteXPos+90;
            spriteYPos = spriteYPos;
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        else if(j>=3 && j<4)
        {
            spriteXPos = spriteXPos-90;
            spriteYPos = spriteYPos-80;
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        else if (j>=4 && j<5)
        {
            spriteXPos = spriteXPos+90;
            spriteYPos = spriteYPos+5;
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
            
        }
        else if(j>=5 && j<6)
        {
            spriteXPos = spriteXPos-90;
            spriteYPos = spriteYPos-60;
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        else if(j>=6 && j<7)
        {
            spriteXPos = spriteXPos+90;
            spriteYPos = spriteYPos-5;
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
        else if(j==7 )
        {
            spriteXPos = spriteXPos-90;
            spriteYPos = spriteYPos-50;
            printf("position %f and %f",sprite->getPositionX(),sprite->getPositionY());
        }
    }
    printf("\n\n");
    
    
    char* v = new char;
    int spriteX = 60;
    int spriteY = 230;
    
    NaArray = new CCArray();
    
    for(int i =9; i <=16; i++ )
    {
        sprintf(v,"na%d.png",i);
        CCSprite *SpriteNa = CCSprite::create(v);
        this->addChild(SpriteNa);
        SpriteNa->setPosition(ccp(spriteX,spriteY));
        
        SpriteNa->setTag(i);
        
        NaArray->addObject(SpriteNa);
        CCLog("%d",NaArray->count());
        
        if(i<11)
        {
            spriteX = spriteX;
            spriteY = spriteY-60;
            printf("position %f and %f",SpriteNa->getPositionX(),SpriteNa->getPositionY());
        }
        else if(i>=11 && i<12)
        {
            spriteX = spriteX;
            spriteY = spriteY-60;
            printf("position %f and %f",SpriteNa->getPositionX(),SpriteNa->getPositionY());
        }
        else if (i>=12 && i<13)
        {
            spriteX = spriteX+90;
            spriteY = spriteY;
            printf("position %f and %f",SpriteNa->getPositionX(),SpriteNa->getPositionY());
            
        }
        else if(i>=13 && i<14)
        {
            spriteX = spriteX+80;
            spriteY = spriteY;
            printf("position %f and %f",SpriteNa->getPositionX(),SpriteNa->getPositionY());
        }
        else if(i>=14 && i<15)
        {
            spriteX = spriteX+80;
            spriteY = spriteY;
            printf("position %f and %f",SpriteNa->getPositionX(),SpriteNa->getPositionY());
        }
        else if(i>=15)
        {
            spriteX = spriteX+80;
            spriteY = spriteY;
            printf("position %f and %f",SpriteNa->getPositionX(),SpriteNa->getPositionY());
        }
     
        
    }
    return true;
}

void HelloWorld::restart()
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void HelloWorld::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( pTouches->anyObject());
    CCPoint location = touch->getLocation();
    
    CCLog("touches began %f %f",location.x,location.y);
        
    bucketRect = CCRectMake(bucketSprite->getPosition().x - bucketSprite->getContentSize().width/2,bucketSprite->getPosition().y - bucketSprite->getContentSize().height/2,bucketSprite->getContentSize().width, bucketSprite->getContentSize().height);
  
    
    char str[20] = {"true"} ;
    CCObject* obj;
    CCARRAY_FOREACH(this->aArray,obj)
    {
        CCSprite *aSpr = (CCSprite *)obj;
        animalRect = CCRectMake(aSpr->getPosition().x - aSpr->getContentSize().width/2,aSpr->getPosition().y - aSpr->getContentSize().height/2,aSpr->getContentSize().width, aSpr->getContentSize().height);
        
        if (animalRect.containsPoint(location))
        {
            CCLOG("%s",str);
            selectedSpr = aSpr;
            isSprSelected = true;
            CCLog(" %f %f",aSpr->getPositionX(),aSpr->getPositionY());
            initialLocation =aSpr->getPosition();
            break;
        }
    }
    char strng[20] = {"false"};
    CCObject *object;
    CCARRAY_FOREACH(this->NaArray,object)
    {
        CCSprite *aSpr = (CCSprite *)object;
        nonanimalRect = CCRectMake(aSpr->getPosition().x - aSpr->getContentSize().width/2,aSpr->getPosition().y - aSpr->getContentSize().height/2,
                                   aSpr->getContentSize().width, aSpr->getContentSize().height);
        if (nonanimalRect.containsPoint(location))
        {
            CCLOG("%s",strng);
            selectedSpr = aSpr;
            isSprSelected = true;
            CCLog(" %f %f",aSpr->getPositionX(),aSpr->getPositionY());
            initialLocation =aSpr->getPosition();
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
    isSprSelected=false;
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
void HelloWorld::random()
{
//    int num[20];
//    int i ,n ,tmp;
//    // srand((unsigned int)time(NULL));
//    for(int i=0;i<20;++i)
//        num[i]=i;
//    
//    for(i=0;i<20;++i)
//    {
//        n= rand()%20;
//        
//        tmp = num[n];
//        
//        num[n]= num[i];
//        
//        num[i] = tmp;
//        
//    }
//    for(i=0;i<20;++i)
//        CCLog("random no is %d",num[i]);
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
//int num[MAX_NUM];
//int i ,n ,tmp;

//for(int i=0;i<MAX_NUM;++i)
//num[i]=i;
//
//for(i=0;i<MAX_NUM;++i)
//{
//    n= rand()%MAX_NUM;
//    
//    tmp = num[n];
//    
//    num[n]= num[i];
//    
//    num[i] = tmp;
//    
//}
//for(i=0;i<MAX_NUM;++i)
//CCLog("random no is %d",num[i]);
//}

