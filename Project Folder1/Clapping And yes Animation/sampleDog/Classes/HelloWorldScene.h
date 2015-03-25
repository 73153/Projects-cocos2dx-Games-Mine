#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "CCBAnimationManager.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    cocos2d::extension::CCBAnimationManager *animationManager;
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    ~HelloWorld();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    CCNode *animationsTestNode;
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
