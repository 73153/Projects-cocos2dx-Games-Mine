#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
USING_NS_CC;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
  

    ~HelloWorld();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    void update(float dt);
    void restart();
    
    void callBackFunc();
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(HelloWorld);
    
public:
    
    CCArray *sprites;
    CCArray *stoneSpr;
    CCSprite *red,*blue;
    
    int index[7];
    
    void updateIndex(int indexNum);
    
    int getFreeIndexPosition();
};

#endif // __HELLOWORLD_SCENE_H__
