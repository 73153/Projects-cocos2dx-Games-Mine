#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "DNDominoManager.h"
#include "DNUIManager.h"
#include "DNBackgroundManager.h"
#include "DNScheduleManager.h"
#include "DNJNICommunicator.h"
#include "DNDomino.h"
#include "DNPlayerPanel.h"


class MainGameController : public cocos2d::CCLayer
{
public:
    
    ~MainGameController();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // Main scheduler...
    void mainTimer();
    
    void restartScene();
    
    void draw();
    
    // Touch Methods!!!
    void ccTouchesBegan(CCSet* touches, CCEvent *event);
    void ccTouchesMoved(CCSet *touches, CCEvent *event);
    void ccTouchesEnded(CCSet *touches, CCEvent *event);
    void ccTouchesCancelled(CCSet *touches, CCEvent *event);
    
    // Manager objects!
    DNDominoManager *dominoManager;
    DNUIManager *uiManager;
    DNBackgroundManager *backgroundManager;
    DNScheduleManager *scheduleManager;
    DNJNICommunicator *jniCommunicator;
    DNPlayerPanel *playerpanel;
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainGameController);
};

#endif // __HELLOWORLD_SCENE_H__
