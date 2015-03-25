//
//  HelloWorldScene.h
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "GLES-Render.h"
#include "ZIContactListener.h"

#include "ZIMonsterManager.h"
#include "ZIUIManager.h"

USING_NS_CC;

class PhysicsSprite : public cocos2d::CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;    // strong ref
};

class ZIMainGame : public cocos2d::CCLayer {

public:
    ~ZIMainGame();
    ZIMainGame();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene(); 
    
    // Physics Functions!
    void initPhysics();
    virtual void draw();
    
    // Main Update Method!
    void update(float dt);
    void maintainConstantBox2dWorld(float dt);
    void listenContactCollision();
    
    // adds a new sprite at a given coordinate
    void addNewSpriteAtPosition(cocos2d::CCPoint p);

    // Touch Methods!!!
    void ccTouchesBegan(CCSet* touches, CCEvent *event);
    void ccTouchesMoved(CCSet *touches, CCEvent *event);
    void ccTouchesEnded(CCSet *touches, CCEvent *event);
    void ccTouchesCancelled(CCSet *touches, CCEvent *event);
    
    // Manager Objects!
    ZIMonsterManager *monsterManager;
    ZIUIManager *uiManager;
    
    b2World* world;
    ZIContactListener *_contactListener;
    
private:
    
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref
    GLESDebugDraw *m_debugDraw;
    
};

#endif // __HELLO_WORLD_H__
