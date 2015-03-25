#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    
    virtual bool init();  
    
    HelloWorld();
    ~HelloWorld();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(HelloWorld);
    void draw();
    
    int timeKeeper;
    int count;
    int miss;
    
    int gameOverCount;
    
    CCArray *bulletArray;
    CCArray *monstersArray;
    
    void mainTimer();
    void createbullet(CCPoint toMovePoint);
    void createMonster();
    void deleteMonster(CCObject *sender);
    void deleteBullet(CCObject *sender);
    void nextGame();
    
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    
};

#endif // __HELLOWORLD_SCENE_H__
