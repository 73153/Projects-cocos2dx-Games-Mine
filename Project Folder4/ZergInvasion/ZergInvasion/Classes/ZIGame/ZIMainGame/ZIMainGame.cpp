//
//  HelloWorldScene.cpp
//  ZergInvasion
//
//  Created by ICRG LABS on 13/09/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//
#include "ZIMainGame.h"
#include "SimpleAudioEngine.h"
#include "ZIDataManager.h"
#include "ZIMonster.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum {
    kTagParentNode = 1,
};

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{

}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool PhysicsSprite::isDirty(void)
{
    return true;
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();

    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_tAnchorPointInPoints.x;
        y += m_tAnchorPointInPoints.y;
    }

    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);

    if( ! CCPoint::CCPointEqualToPoint(m_tAnchorPointInPoints, CCPointZero) ){
        x += c*-m_tAnchorPointInPoints.x + -s*-m_tAnchorPointInPoints.y;
        y += s*-m_tAnchorPointInPoints.x + c*-m_tAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_tTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_tTransform;
}

ZIMainGame::ZIMainGame()
{
    setTouchEnabled( true );
    setAccelerometerEnabled( true );
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    // Assigning the main game layer to the Datamanager! 
    DataManager->gameLayer = this;
    DataManager->screenSize = s;
    
    // init physics
    this->initPhysics();

    CCSpriteBatchNode *parent = CCSpriteBatchNode::create("blocks.png", 100);
    m_pSpriteTexture = parent->getTexture();

    addChild(parent, 0, kTagParentNode);

    //addNewSpriteAtPosition(ccp(s.width/2, s.height/2));

    // Initializing the managers!
    this->uiManager = new ZIUIManager();
    this->monsterManager = new ZIMonsterManager();
    
    // Triggering the main update method
    scheduleUpdate();
}

ZIMainGame::~ZIMainGame()
{
    CCLog("main game dealloc");
    
    delete world;
    world = NULL;
    
    delete m_debugDraw;
    delete _contactListener;
    
    delete this->monsterManager;
    delete this->uiManager;
}

CCScene* ZIMainGame::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // Creating the UI Layer
    CCLayer *staticLayer = CCLayer::create();
    scene->addChild(staticLayer,5);
    DataManager->UILayer = staticLayer;
       
    // add layer as a child to scene
    CCLayer* layer = new ZIMainGame();
    scene->addChild(layer);
    layer->release();
   
    return scene;
}

void ZIMainGame::initPhysics() 
{
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    b2Vec2 gravity;
    gravity.Set(0.0f, -1.0f);
    world = new b2World(gravity);
    
    // Assigning the world...
    DataManager->gameWorld = world;
    
    world->SetAllowSleeping(false);
    
    world->SetContinuousPhysics(true);
    
    _contactListener = new ZIContactListener();
    world->SetContactListener(_contactListener);
    
    m_debugDraw = new GLESDebugDraw( PTM_RATIO );
    world->SetDebugDraw(m_debugDraw);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    m_debugDraw->SetFlags(flags);
    
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    // bottom
    
    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // top
    //groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    //groundBody->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
}

void ZIMainGame::draw()
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    world->DrawDebugData();

    kmGLPopMatrix();
}

void ZIMainGame::addNewSpriteAtPosition(CCPoint p)
{
    /*
    CCSprite *boxSprite = CCSprite::create("Icon.png");
    this->addChild(boxSprite);
    
    b2BodyDef bd;
    b2Body *m_body1;
    b2PolygonShape m_shape1;
	b2PolygonShape m_shape2;
    b2Fixture* m_piece1;
	b2Fixture* m_piece2;
    
    bd.type = b2_dynamicBody;
    bd.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    //bd.angle = 0.25f * b2_pi;
    //bd.userData = boxSprite;
    m_body1 = world->CreateBody(&bd);
    
    m_shape1.SetAsBox(0.5f, 0.5f, b2Vec2(-0.5f, 0.0f), 0.0f);
    m_piece1 = m_body1->CreateFixture(&m_shape1, 1.0f);
    
    m_shape2.SetAsBox(0.5f, 0.5f, b2Vec2(0.5f, 0.0f), 0.0f);
    m_piece2 = m_body1->CreateFixture(&m_shape2, 1.0f);
    */
    
    
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    CCNode* parent = getChildByTag(kTagParentNode);
    
    //We have a 64x64 sprite sheet with 4 different 32x32 images.  The following code is
    //just randomly picking one of the images
    int idx = (CCRANDOM_0_1() > .5 ? 0:1);
    int idy = (CCRANDOM_0_1() > .5 ? 0:1);
    PhysicsSprite *sprite = new PhysicsSprite();
    sprite->initWithTexture(m_pSpriteTexture, CCRectMake(32 * idx,32 * idy,32,32));
    sprite->autorelease();
    parent->addChild(sprite,1);
    sprite->setPosition(CCPointMake( p.x, p.y));

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;    
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    
    sprite->setPhysicsBody(body);
}

void ZIMainGame::update(float dt) {
    
    // Maintain Box2d world...
    this->maintainConstantBox2dWorld(dt);
    
    // Listening to contact...
    this->listenContactCollision();
}

void ZIMainGame::maintainConstantBox2dWorld(float dt) {
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
    world->Step(dt, velocityIterations, positionIterations);
    
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
}

void ZIMainGame::listenContactCollision() {
    
    this->monsterManager->monsterManagerContactListener();
}

void ZIMainGame::ccTouchesBegan(cocos2d::CCSet *touches, cocos2d::CCEvent *event) { 
    
    this->monsterManager->monsterManagerTouchBegan(touches);
}

void ZIMainGame::ccTouchesMoved(cocos2d::CCSet *touches, cocos2d::CCEvent *event) {
    
    this->monsterManager->monsterManagerTouchMoved(touches);
}

void ZIMainGame::ccTouchesEnded(cocos2d::CCSet *touches, cocos2d::CCEvent *event) {
    
    this->monsterManager->monsterManagerTouchEnded(touches);
}

void ZIMainGame::ccTouchesCancelled(cocos2d::CCSet *touches, cocos2d::CCEvent *event) {
    
    this->monsterManager->monsterManagerTouchCanceled(touches);
}
