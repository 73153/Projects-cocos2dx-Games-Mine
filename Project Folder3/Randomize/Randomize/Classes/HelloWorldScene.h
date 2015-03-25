#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
   
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    //    void label();
    //    void label1();
    void restart();
    void random();
    
    
public:
    
    
    CCRect bucketRect;
    CCSprite *bucketSprite;
    CCSprite *selectedSpr;
    bool isSprSelected;
    CCRect *aRect;
    CCRect *nRect;
    CCSprite *position;
    CCArray *aArray;
    CCPoint initialLocation;
    CCSprite *randomSpr;
    CCArray *NaArray;
    CCSprite *animalSprite;
    CCRect randRect;
    CCRect animalRect;
    CCRect nonanimalRect;
    CCSprite *animalsprite;
    CCSprite *bucketsprite;
    CCPoint dragPos;
    CCSprite* nonanimalsprite;
    int num[20];
  
    char vv[20];

};

#endif // __HELLOWORLD_SCENE_H__
