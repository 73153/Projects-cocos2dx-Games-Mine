#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CCParallaxNodeExtras.h"
USING_NS_CC ;

class HelloWorld : public cocos2d::CCLayer
{
private:
	cocos2d::CCSpriteBatchNode * _batchNode;
	cocos2d::CCSprite * _ship;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    CCParallaxNodeExtras *_backgroundNode;
    CCSprite *_spacedust1;
    CCSprite *_spacedust2;
    CCSprite *_planetsunrise;
    CCSprite *_galaxy;
    CCSprite *_spacialanomaly;
    CCSprite *_spacialanomaly2;
    
    float randomValueBetween( float low , float high );
    void setInvisible(CCNode * node);
    float getTimeTick();

    int _nextAsteroid ;
    float _nextAsteroidSpawn ;

    CCArray *_asteroids ;
    CCArray *shipLaser;
    float _shipPointsPerSecY;
    int _nextShipLaser ;
    
    
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);
    
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // scheduled Update
    void update(cocos2d::CCTime dt);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
