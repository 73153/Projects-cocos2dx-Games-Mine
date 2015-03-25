#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    ~HelloWorld();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    
    void updateIndex(int indexNum);
    
    void updateTag(CCSprite *sprite, int toValue);

    int getFreeIndexPosition(); 
    
    void Shuffle();
    
    void printCurrentTags();
    bool checkForValidMovement(int touchedIndex, int freeIndex);
    
    CCPoint returnBackgroundChildByTag(int tag);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
public:
        CCArray *bgArray;
        int index[16];
    
        CCArray *shuffle;
        CCArray *shufflebg;
    
};

#endif // __HELLOWORLD_SCENE_H__
