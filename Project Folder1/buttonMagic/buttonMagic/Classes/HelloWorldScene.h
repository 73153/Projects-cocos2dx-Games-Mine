#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

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
    cocos2d::CCMenu *item1;
     cocos2d::CCMenu *item2;
     cocos2d::CCMenu *item3;
     cocos2d::CCMenu *item4;
    cocos2d::CCLabelTTF *label;
    
    
    
    void buttonPressed(CCObject *sender);
};

#endif // __HELLOWORLD_SCENE_H__
