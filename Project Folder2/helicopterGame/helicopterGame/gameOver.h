//
//  gameOver.h
//  helicopterGame
//
//  Created by Vivek on 15/11/12.
//
//

#ifndef helicopterGame_gameOver_h
#define helicopterGame_gameOver_h


#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "easyGame.h"
#include "difficultGame.h"
#include "mediumGame.h"
#include "SimpleAudioEngine.h"
#include <iostream>
#include "gameOver.h"
USING_NS_CC;

class gameOver : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void goahead();
       
    // implement the "static node()" method manually
    CREATE_FUNC(gameOver);
};



#endif
