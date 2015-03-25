//
//  LMGameLayer.cpp
//  LostMonster
//
//  Created by Krithik B on 8/20/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//
#include "LMGameLayer.h"
#include "SimpleAudioEngine.h"
#include "b2DebugDraw.h"

#include "LMLevelSelection.h"

#include "LMDataManager.h"

#ifdef CC_PLATFORM_IOS

#include "LMObjectiveCCalls.h"

#else

#endif

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* LMGameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new LMGameLayer();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

#pragma mark - Init

LMGameLayer::LMGameLayer()
{
    setTouchEnabled( true );
    
    LMDataManager::sharedManager()->gameLayer = this;

    CCSize s = CCDirector::sharedDirector()->getWinSize();
  
    // init physics
    this->initPhysics();
    
    //Load all the Managers
    this->levelManager = new LMLevelManager();
    this->levelManager->initialize();
    this->maxSliceCount = this->levelManager->maxCuts;
    
    this->gameUIManager = new LMGameUIManager();
    this->gameUIManager->intialiseUI();
    
    //Level Helper
    this->initLevelHelper();
    
    //Initialise  Variables

    this->initialiseVariables();
        
    //Create a Line Node
    cuttingLineNode = new LMLine();
    this->addChild(cuttingLineNode,10);
    
       
    //Schedule a Update
    scheduleUpdate();
    this->schedule(schedule_selector(LMGameLayer::updateSecondTimer), 1);

    //Add Blade
    this->trailLayer = TouchTrailLayer::create();
    addChild(this->trailLayer);
    
       
    //If the level contains Tutorial show it
    if (this->levelManager->containsTutorial) {
        
        #ifdef CC_PLATFORM_IOS
        
        if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)  //IOS related
        {
//            cocos2d::CCDirector::sharedDirector()->pause();
//            LMDataManager::sharedManager()->isTutorialPlaying = true;
//            LMObjectiveCCalls::showVideo(this->levelManager->tutorialVideoFileName->getCString(),this->levelManager->tutorialHeading->getCString());
        }
        #endif
        
        #ifdef CC_PLATFORM_ANDROID
        if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)  //Android Related
        {
            
        }
        #endif
    }
}

void LMGameLayer::initialiseVariables()
{
    windowSize = CCDirector::sharedDirector()->getWinSize();
    
    this->currentSplitedSpritesArr = CCArray::create();
    this->currentSplitedSpritesArr->retain();

    this->rolloSpr = loader->spriteWithUniqueName("rollo");
    
    this->rolloStarAnimationSpr = this->loader->createSpriteWithName("questionMarkAnim1","Spritesheet", "Common.pshs",this);
    this->rolloStarAnimationSpr->setVisible(false);
    
    //This Sprite is Used for Rollo Idle Animation
    this->animationRolloSpr = this->loader->createSpriteWithName("rolloStandingPositions1","Spritesheet", "Common.pshs",this);
    this->animationRolloSpr->setVisible(false);
    
    // If gravity is set in plist then apply it for ROLLO
    if (this->levelManager->rolloGravity!=0)
    {
        this->rolloSpr->getBody()->SetGravityScale(this->levelManager->rolloGravity);
    }
    
    this->isGameWon = false;
    this->isGameLost = false;
    this->isRolloMoving = false;   
    this->isRolloIdle = true;
    this->didRolloReachedExit = false;
    this->didRolloTouched = false;
    this->didGetRollosInitialPosition = false;
    this->sliceCount = 0;
    this->checkWoodCollisionWithBolt = false;
    this->isTimerRunning = false;
    this->runDieAnimation = false;
    this->gameTimer = 0;
}


void LMGameLayer::initLevelHelper()
{
    //Get the file name of the level
    char levelHelperFileName[20];
    sprintf(levelHelperFileName,"%s.plhs",this->levelManager->levelName);
    
    loader = new LevelHelperLoader(levelHelperFileName);
	loader->addObjectsToWorld(world, this);
    
    loader->useLevelHelperCollisionHandling();//necessary or else collision in LevelHelper will not be performed
    
    //Register for Rollo & Exit Door Collision
    loader->registerBeginOrEndCollisionCallbackBetweenTagA(ROLLO, EXITDOOR, this, callfuncO_selector(LMGameLayer::rolloReachedExit));
    
    //Level 5 Special
    loader->registerBeginOrEndCollisionCallbackBetweenTagA(ROLLO, FIRE, this, callfuncO_selector(LMGameLayer::rolloContactWithFire));
}

void LMGameLayer::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    
    world->SetContinuousPhysics(true);
    
    b2DebugDraw *debugDraw = new b2DebugDraw(PTM_RATIO);
    world->SetDebugDraw(debugDraw);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //    flags += b2Draw::e_jointBit;
    //    flags += b2Draw::e_centerOfMassBit;
    //    flags += b2Draw::e_aabbBit;
    //    flags += b2Draw::e_pairBit;
    debugDraw->SetFlags(flags);
}


#pragma mark - Dealloc
LMGameLayer::~LMGameLayer()
{
    CCLog("Dealloc in ~LMGameLayer");
    delete world;
    world = NULL;
    
    //Remove All Managers
    delete levelManager;
    delete gameUIManager;
    
    //delete m_debugDraw;
    CC_SAFE_RELEASE_NULL(this->currentSplitedSpritesArr);
}


#pragma mark - Draw
void LMGameLayer::draw()
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

#pragma mark - Tick

void LMGameLayer::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
    
    //Iterate over the bodies in the physics world
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) 
        {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
            
        }    
    }
    
    
    if(this->checkWoodCollisionWithBolt)
    {
        CCObject* aSplitedObj = NULL;
        CCARRAY_FOREACH(this->currentSplitedSpritesArr,aSplitedObj)
        {
            LHSprite *aSplitedSpr = (LHSprite *)aSplitedObj;
            
            //Get all the BOLT in Scene
            CCArray *boltsInSceneArr = loader->spritesWithTag(BOLT);
            
            CCObject *aBoltObj = NULL;
            CCARRAY_FOREACH(boltsInSceneArr,aBoltObj)
            {
                LHSprite *aBoltSpr = (LHSprite *)aBoltObj;
                
                  //NSMutableArray *nutContentsArr = [(LMNut*)[nut userInfo] contacts];
                //LMBolt *boltInfo = (LMBolt *)aBoltSpr->userInfo();
                //boltInfo->currentBoltContacts.push_back(aBoltObj);
                
                //bool isCollideWithBolt = LMUtility::bodiesAreTouching(aSplitedSpr->getBody(), aBoltSpr->getBody());
                bool isCollideWithBolt = this->isBodyTouchingAnotherBody(aSplitedSpr->getBody(), aBoltSpr->getBody());
                if(isCollideWithBolt)
                    this->createJointBetweenNutAndWood(aBoltSpr, aSplitedSpr);
            }
        }
        this->checkForFloatingBolts();
    }
    
        
    
    //Set the gravity again back to 1 for all the sliced woods
    CCObject* aSplitedObj = NULL;
    CCARRAY_FOREACH(this->currentSplitedSpritesArr,aSplitedObj)
    {
        LHSprite *aSplitedSpr = (LHSprite *)aSplitedObj;
        aSplitedSpr->getBody()->SetGravityScale(4);
    }
    this->checkWoodCollisionWithBolt = false;
    this->currentSplitedSpritesArr->removeAllObjects();
    
    
    //If the Level Contains Any ropes Then move it along with their respective BOLTS
    CCObject *aRopeObj = NULL;
    CCArray *ropeInSceneArr = loader->spritesWithTag(ROPE);
    
    CCARRAY_FOREACH(ropeInSceneArr, aRopeObj)
    {
        LHSprite *aRopeSpr = (LHSprite *)aRopeObj;
        LMRope *ropeInfo = (LMRope *)aRopeSpr->userInfo();
        
        //CCLog("ropeInfo->topBoltName is %s",ropeInfo->topBoltName.c_str());
        //CCLog("ropeInfo->bottomBoltName is %s",ropeInfo->bottomBoltName.c_str());
        LHSprite *topBolt = loader->spriteWithUniqueName(ropeInfo->topBoltName);
        LHSprite *bottomBolt = loader->spriteWithUniqueName(ropeInfo->bottomBoltName);
        
        aRopeSpr->setAnchorPoint(CCPoint(0.5,1));
        aRopeSpr->setPosition(topBolt->getPosition());
        aRopeSpr->setRotation(LMUtility::getAngleBetweenPoints(topBolt->getPosition(), bottomBolt->getPosition()));
        aRopeSpr->setScaleY(ccpDistance(bottomBolt->getPosition(), topBolt->getPosition())/aRopeSpr->getContentSize().height);
        
        
        // get the local node space coordinate of the center
        CCPoint centerOfSpriteInLocalNodeSpace = CCPoint(aRopeSpr->getContentSize().width *0.5,aRopeSpr->getContentSize().height *0.5);
        
        // convert the local coordinate within the node to the world space
        CCPoint centerOfSpriteInWorldSpace = aRopeSpr->convertToWorldSpace(centerOfSpriteInLocalNodeSpace);
        
        CCPoint ropePosition = CCPoint(	centerOfSpriteInWorldSpace.x/PTM_RATIO,centerOfSpriteInWorldSpace.y/PTM_RATIO);
        
        
        b2Vec2 b2Position = b2Vec2(ropePosition.x,ropePosition.y);//*(aRopeSpr->getContentSize().height/2))
        float32 b2Angle = -1 * CC_DEGREES_TO_RADIANS(aRopeSpr->getRotation());

        
        aRopeSpr->getBody()->SetTransform(b2Position,b2Angle);//CC_DEGREES_TO_RADIANS(aRopeSpr->getRotation())
        
       // CCLog("Rope Body Angle is %f",aRopeSpr->getBody()->GetAngle());
       // CCLog("Rope  Angle is %f",aRopeSpr->getRotation());

    }
    
    //Rollo Struck Condition
    if (this->isRolloMoving) 
    {
        if(this->isGameWon==false&&this->isGameLost==false)
        {
            //LMRollo *rolloInfo = (LMRollo *)rolloSpr->userInfo();
                        
            float xVelocity = fabs(rolloSpr->getBody()->GetLinearVelocity().x);
            float yVelocity = fabs(rolloSpr->getBody()->GetLinearVelocity().y);
            //CCLog("velocity x is %f and y is %f",rolloSpr->getBody()->GetLinearVelocity().x,rolloSpr->getBody()->GetLinearVelocity().y);

            if(xVelocity<0.001&&yVelocity<0.001)
            {
                rolloStuck();
            }
        }
    }
    
    //Check to see rollo gets setled
    if(this->didRolloReachedExit==true)
    {
        float xVelocity = fabs(rolloSpr->getBody()->GetLinearVelocity().x);
        float yVelocity = fabs(rolloSpr->getBody()->GetLinearVelocity().y);
        
        LHSprite *exitDoorSpr = loader->spriteWithUniqueName("levelExit");
        
        if((xVelocity<0.00001f&&yVelocity<0.00001f)||(this->rolloSpr->getPositionY()<exitDoorSpr->getPositionY()-10)) //Here 10 is the error factor
        {
            this->didRolloReachedExit = false;
            this->rolloSpr->getBody()->SetType(b2_staticBody);
            
            //This small correction is position is because the radius of box 2d body of rollo is smaller.
            b2Vec2 newPosition = b2Vec2(this->rolloSpr->getBody()->GetPosition().x, this->rolloSpr->getBody()->GetPosition().y+kRolloExitPositionCorrectionFactor);
            this->rolloSpr->getBody()->SetTransform(newPosition, 0 );
            
            //Show Win Animation
            this->runRolloWinAnimation();
        }
    }
    
    //Check for Dying Condition Out of Bounds
    //Less than Zero
    //More than Width Of the Device
    
    if(this->isGameWon==false)
    {
        if(this->isGameLost == false)
        {
            if(this->rolloSpr->getPositionX()<0||this->rolloSpr->getPositionX()>windowSize.width||this->rolloSpr->getPositionY()<0)
            {
                this->isGameLost = true;
                this->rolloDieAnimation();
            }
        }
    }
    
    //Get the rollos initial Position
    //This function will be useful for running idle animation
    if(this->didGetRollosInitialPosition == false)
    {
        float xVelocity = fabs(rolloSpr->getBody()->GetLinearVelocity().x);
        float yVelocity = fabs(rolloSpr->getBody()->GetLinearVelocity().y);
        if(xVelocity<0.00001f&&yVelocity<0.00001f) //Rollo has settled
        {
            this->didGetRollosInitialPosition = true;
            this->getRollosInitialPosition();
        }
    }
    
    //Spring Platform USED IN WORLD 3
   
    CCArray *allJointArr = loader->allJoints();
    if (allJointArr->count()>0) {
        CCObject *aJointObj = NULL;
        CCArray *springPlatformJointsArr = loader->jointsWithTag(SPRINGPLATFORMJOINT);
        
        CCARRAY_FOREACH(springPlatformJointsArr, aJointObj)
        {
            LHJoint *aJoint = (LHJoint *)aJointObj;
            
            b2RevoluteJoint *aSpringPlatformJoint = (b2RevoluteJoint *)aJoint->getJoint();
            
//            var rj:b2RevoluteJoint = joint as b2RevoluteJoint;
//            var rja:Number = rj.GetJointAngle();
//            rj.SetMaxMotorTorque(Math.abs((rja * 5000) + (rj.GetJointSpeed() * 100)));
//            rj.SetMotorSpeed(rja > 0 ? -10000 : +10000);
            
            float angle = aSpringPlatformJoint->GetJointAngle();
            aSpringPlatformJoint->SetMaxMotorTorque(kSpringMotorTorgue);
            aSpringPlatformJoint->SetMotorSpeed(angle > 0 ? -kSpringMotorSpeed : +kSpringMotorSpeed);
            
        }
    }
    
    //Condition to check when whether rollo is Moving ! If rollo is playing idle animation and then rollo moves than stop that animations !
    float xVelocity = fabs(rolloSpr->getBody()->GetLinearVelocity().x);
    float yVelocity = fabs(rolloSpr->getBody()->GetLinearVelocity().y);
    if(xVelocity>0.00001f||yVelocity>0.00001f)
    {
        this->rolloIdleAnimationEnd();
    }
    
    //This condition is necessary , we cannot call die animation directly in the collision call back , it will crash since box2d world is locked
    if(this->runDieAnimation)
    {
        this->runDieAnimation = false;
        this->rolloDieAnimation();
    }
}

//This timer calls once every second
void LMGameLayer::updateSecondTimer(float dt)
{
    this->gameTimer++;
    if(this->isRolloIdle&&this->didRolloTouched==false&&this->didGetRollosInitialPosition==true)
    {
        if(this->gameTimer%10==0) //IDLE
        {
            this->runRolloIdleAnimation();
        }
    }
}

#pragma mark - Touches

void LMGameLayer::ccTouchesBegan(CCSet* touches,CCEvent* event)
{
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        this->startCuttingPoint = location;
        cuttingLineNode->startWithLocation(location);
        this->trailLayer->startPoint = location;

        //Detect Touch for Rollo
        
        if(this->didRolloTouched==false)
        {
            
            bool isTouch = LMUtility::rectForSprite(this->rolloSpr).containsPoint(location);//CCRect::CCRectContainsPoint(LMUtility::rectForSprite(this->rolloSpr), location);
            if(isTouch)
            {
                this->rolloTouchDetected();
            }
        }
    }
}


void LMGameLayer::ccTouchesMoved(CCSet* touches,CCEvent *event)
{
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        this->endCuttingPoint = location;
        this->cuttingLineNode->endPoint = location;
    }
}


void LMGameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        this->endCuttingPoint = location;
        this->trailLayer->endPoint = location;
        
        //Reset The Line
        cuttingLineNode->resetLine();
        
        if(this->sliceCount<this->maxSliceCount)
        {
            //Check for the distance between Start Point & End Point
            float distance = ccpDistance(startCuttingPoint, endCuttingPoint);
            if(distance>8)
            {
                //HardWood & SoftWood & BOLTWOOD
                bool didSlideSoftWood = LHCuttingEngineMgr::sharedInstance()->cutAllSpritesWithTag(SOFTWOOD, this->startCuttingPoint, this->endCuttingPoint, world);
                bool didSlideHardWood = LHCuttingEngineMgr::sharedInstance()->cutAllSpritesWithTag(HARDWOOD, this->startCuttingPoint, this->endCuttingPoint, world);
                bool didSlideBoltWood = LHCuttingEngineMgr::sharedInstance()->cutAllSpritesWithTag(BOLTWOOD, this->startCuttingPoint, this->endCuttingPoint, world);
                
                //Check For Ropes
                CCObject *aRopeObj = NULL;
                CCArray *ropeInSceneArr = loader->spritesWithTag(ROPE);

                bool didSliceAnyRope = false;
                CCARRAY_FOREACH(ropeInSceneArr, aRopeObj)
                {
                    LHSprite *aRopeSpr = (LHSprite *)aRopeObj;
                    bool didSliceRopes = LHCuttingEngineMgr::sharedInstance()->cutSprite(aRopeSpr, this->startCuttingPoint, this->endCuttingPoint);
                    
                    if(didSliceRopes)
                    {
                        didSliceAnyRope = true;
                        this->removeJointsForRope(aRopeSpr);
                    }
                }
                
                if(didSlideSoftWood||didSlideHardWood||didSliceAnyRope||didSlideBoltWood)
                {
                    this->sliceCount++;
                    this->gameUIManager->updateLabel(this->sliceCount);
                    
                    //Create Slice Blade
                    this->trailLayer->createBlade();
                }
            }
            else
            {                        
                //Destroy Wood if the touchPoint is in Any soft wood in the scene
                this->removeTouchedSpriteWithTag(SOFTWOOD, location);
                this->removeTouchedSpriteWithTag(BOLTWOOD, location);
            }
        }
        else {
            this->gameUIManager->blinkSliceCount();
        }
    }
}

void LMGameLayer::ccTouchesCancelled(CCSet* touches, CCEvent* event)
{
}


#pragma mark - Splited Sprites

void LMGameLayer::splitedSprites(LHSprite *spriteA,LHSprite *spriteB)
{
    //Code to Handle ROPES Cutting
    if(spriteA->getTag()==ROPE||spriteB->getTag()==ROPE||spriteA->getTag()==BOLTWOOD||spriteB->getTag()==BOLTWOOD)
    {
        spriteA->removeBodyFromWorld();
        spriteA->removeSelf();
        
        spriteB->removeBodyFromWorld();
        spriteB->removeSelf();
        
    }
    
    //Code to Handle Hard Wood & Soft Wood
    if(spriteA->getTag()==HARDWOOD||spriteA->getTag()==SOFTWOOD||spriteB->getTag()==HARDWOOD||spriteB->getTag()==SOFTWOOD)
    {
        //Make the sprites stationary
        spriteA->getBody()->SetGravityScale(0.0f);
        spriteB->getBody()->SetGravityScale(0.0f);
        
        
        //Get the Right Sprite
        LHSprite *rightSprite =  NULL;
        
        if(spriteA->getBody()->GetWorldCenter().x>spriteB->getBody()->GetWorldCenter().x)
        {
            rightSprite = spriteA;
        }
        else {
            rightSprite = spriteB;
        }
        
        //Move Right sprite slightly right :)     
        b2Vec2 newPosition = b2Vec2(rightSprite->getBody()->GetPosition().x+kWoodSliceMargin, rightSprite->getBody()->GetPosition().y);
        
        rightSprite->getBody()->SetTransform(newPosition,spriteB->getBody()->GetAngle()); // Reposition the body
        rightSprite->getBody()->SetAwake(true); // Make sure the object hasn't fallen "asleep," which would make it unresponsive    
        
        
        //Add to Array
        currentSplitedSpritesArr->addObject(spriteA);
        currentSplitedSpritesArr->addObject(spriteB);
        
    }
    
    checkWoodCollisionWithBolt = true;
}

//This function is called when u touch the sprite which is to be removed
//Wood Ice Wood Bolt Remove When touched
void LMGameLayer::removeTouchedSpriteWithTag(int tag,CCPoint location)
{
    
    LevelHelper_TAG spriteTag = (LevelHelper_TAG)tag;
    
    //Get all the SOFT WOOD in Scene
    CCObject *aSpriteObj = NULL;
    CCArray *spriteArr = loader->spritesWithTag(spriteTag);
    
    CCARRAY_FOREACH(spriteArr, aSpriteObj)
    {
        LHSprite *aSprite = (LHSprite *)aSpriteObj;
        if(aSprite)
        {
            if(aSprite->getTag()==spriteTag)
            {
                bool isTouch = this->checkCollisionWithBox2dBody(aSprite->getBody(), location);
                if(isTouch)
                {
                    this->runWoodAnimationAtPosition(location);
                    aSprite->removeBodyFromWorld();
                    aSprite->removeSelf();
                    
                    //Check for floating Bolts
                    this->checkForFloatingBolts();
                    
                    this->sliceCount++;
                    this->gameUIManager->updateLabel(this->sliceCount);
                }
            }
        }
    }
}


#pragma mark - Create Revolute Joint

void LMGameLayer::createJointBetweenNutAndWood(LHSprite *inNut,LHSprite *inWood)
{
    b2RevoluteJointDef revoluteJointDef;
    revoluteJointDef.bodyA = inNut->getBody();
    revoluteJointDef.bodyB = inWood->getBody();
    
    b2RevoluteJoint *armJoint;
    b2RevoluteJointDef armJointDef;
    
    armJointDef.Initialize(inNut->getBody(),inWood->getBody(), inNut->getBody()->GetPosition());
    
    armJoint = (b2RevoluteJoint*)world->CreateJoint(&armJointDef);
}


#pragma mark - Ropes

//This function removes the Rope associated with the Bolt
void LMGameLayer::removeRopesJoinedWithBolt(LHSprite * inBolt)
{
    CCObject *aRopeObj = NULL;
    CCArray *ropeInSceneArr = loader->spritesWithTag(ROPE);
    
    int count = ropeInSceneArr->count(); 
    
    if(count>0)
    {
        CCARRAY_FOREACH(ropeInSceneArr, aRopeObj)
        {
            LHSprite *aRopeSpr = (LHSprite *)aRopeObj;
            LMRope *ropeInfo = (LMRope *)aRopeSpr->userInfo();
            
            //Checking the BoltName with Ropes Bottom Bolt Name
            if (ropeInfo->getBottomBoltName()==inBolt->getUniqueName())
            {
                //Remove the Joints of the Rope
                this->removeJointsForRope(aRopeSpr);
                
                //Remove the Rope From the Scene
                aRopeSpr->removeBodyFromWorld();
                aRopeSpr->removeSelf();
            }
        }
    }
}

//Removes the Distance Joint Associated with the Rope
void LMGameLayer::removeJointsForRope(LHSprite *inRope)
{
    LMRope *ropeInfo = (LMRope *)inRope->userInfo();
    ropeInfo->getJointName();
    
    LHJoint *distanceJoint = loader->jointWithUniqueName(ropeInfo->getJointName());
    distanceJoint->removeSelf();
}

#pragma mark - Bolt
//This function will check for floating Bolts , if it found Bolt will get removed
//Also if bolt has any ropes it will remove the ropes along with its joints
void LMGameLayer::checkForFloatingBolts()
{
    //Check whether any BOLTS is not with contact with any wood !!!
    
    //Get all the BOLT in Scene
    CCArray *boltsInSceneArr = loader->spritesWithTag(BOLT);
    
    CCObject *aBoltObj = NULL;
    CCARRAY_FOREACH(boltsInSceneArr,aBoltObj)
    {
        LHSprite *aBoltSpr = (LHSprite *)aBoltObj;
        bool boltCollideWithWood = false;
        
        //Check with soft wood
        CCArray *softWoodArr = loader->spritesWithTag(SOFTWOOD);
        CCObject* aSoftWoodObj = NULL;
        CCARRAY_FOREACH(softWoodArr,aSoftWoodObj)
        {
            LHSprite *aSplitedSpr = (LHSprite *)aSoftWoodObj;
            
            aSplitedSpr->getBody()->SetAwake(true); 
            
            bool isCollideWithBolt = this->isBodyTouchingAnotherBody(aSplitedSpr->getBody(), aBoltSpr->getBody());
            
            if(isCollideWithBolt)
                boltCollideWithWood = true;
        }
        
        //Check with HARD wood
        CCArray *hardWoodArr = loader->spritesWithTag(HARDWOOD);
        CCObject* aHardWoodObj = NULL;
        CCARRAY_FOREACH(hardWoodArr,aHardWoodObj)
        {
            LHSprite *aSplitedSpr = (LHSprite *)aHardWoodObj;
            
            bool isCollideWithBolt = this->isBodyTouchingAnotherBody(aSplitedSpr->getBody(), aBoltSpr->getBody());
            
            if(isCollideWithBolt)
                boltCollideWithWood = true;
        }
        
        //Check with BOLTWOOD wood
        CCArray *boltWoodArr = loader->spritesWithTag(BOLTWOOD);
        CCObject* aBoltWoodObj = NULL;
        CCARRAY_FOREACH(boltWoodArr,aBoltWoodObj)
        {
            LHSprite *aBoltWoodSpr = (LHSprite *)aBoltWoodObj;
            
            bool isCollideWithBolt = this->isBodyTouchingAnotherBody(aBoltWoodSpr->getBody(), aBoltSpr->getBody());
            
            if(isCollideWithBolt)
                boltCollideWithWood = true;
        }
        
        //False means Bolt is floating
        if(boltCollideWithWood == false)
        {
            //Check if Bolt is associated with any Ropes !!!
            this->removeRopesJoinedWithBolt(aBoltSpr);
            
            aBoltSpr->removeBodyFromWorld();
            aBoltSpr->removeSelf();
        }
    }
}


#pragma mark - Rollo 

void LMGameLayer::getRollosInitialPosition()
{
    CCPoint rolloBodyPosition = LMUtility::convertVectortoPixels(this->rolloSpr->getBody()->GetPosition());
    this->animationRolloSpr->setPosition(CCPoint(rolloBodyPosition.x+kRolloIdleAnimPosCorrectionFactor.x,rolloBodyPosition.y+kRolloIdleAnimPosCorrectionFactor.y));
    
    //Run Rollo Idle Animation
    if(this->isRolloIdle&&this->didRolloTouched==false&&this->didGetRollosInitialPosition==true)
    {
        this->runRolloIdleAnimation();
    }
}


//Rollo Touch Detected so start moving
void LMGameLayer::rolloTouchDetected()
{    
    this->didRolloTouched = true;
    
    //Stop Idle Animation if it is running
    //this->animationRolloSpr->stopAllActions();
    this->animationRolloSpr->setVisible(false);
    
    //Stop All previous Animations & Actions
    this->rolloSpr->stopAllActions();
    this->rolloSpr->stopAnimation();
    
    this->rolloSpr->setVisible(true);
    
    //Start Rolling Animation
    this->rolloSpr->prepareAnimationNamed("RolloStartMoveAnimation","Common.pshs");
    this->rolloSpr->playAnimation();
    
    CCDelayTime *actionDelay = CCDelayTime::create(this->rolloSpr->animationDuration());
    CCSequence *actionSequence = CCSequence::createWithTwoActions(actionDelay,CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::moveRollo)));
    this->rolloSpr->runAction(actionSequence);
       
    //Start the timer to show clock after 12 sec
    this->schedule(schedule_selector(LMGameLayer::startTimer),kClockTime, false,0);
}




//Rollo Got stuck
void LMGameLayer::rolloStuck()
{
    this->isRolloMoving = false;
    LMRollo *rolloInfo = (LMRollo *)this->rolloSpr->userInfo();
    
    //this->rolloSpr->getBody()->SetType(b2_staticBody);
    this->rolloSpr->getBody()->SetLinearVelocity(b2Vec2(0,0));
    this->rolloSpr->getBody()->SetAngularVelocity(0);
    
    CCPoint questionMarkPos;     
    if(rolloInfo->isMovingRight)
    {
        this->rolloStarAnimationSpr->prepareAnimationNamed("RolloQuestionMark","Common.pshs");
        questionMarkPos = CCPoint(this->rolloSpr->getPositionX()+ kRolloRightQuesMarkAnimPosCorrectionFactor.x, this->rolloSpr->getPositionY()+kRolloRightQuesMarkAnimPosCorrectionFactor.y);
    }
    else 
    {
        this->rolloStarAnimationSpr->prepareAnimationNamed("RolloQuestionMarkFlip","Common.pshs");
        questionMarkPos = CCPoint(this->rolloSpr->getPositionX()+kRolloLeftQuesMarkAnimPosCorrectionFactor.x, this->rolloSpr->getPositionY()+kRolloLeftQuesMarkAnimPosCorrectionFactor.y);
    }
    
    this->rolloStarAnimationSpr->setPosition(questionMarkPos);
    this->rolloStarAnimationSpr->setVisible(true);
    this->rolloStarAnimationSpr->playAnimation();
    
    CCDelayTime *actionDelay = CCDelayTime::create(this->rolloStarAnimationSpr->animationDuration());
    CCSequence *questionMarkSeq = CCSequence::createWithTwoActions(actionDelay, CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::moveRollo)));
    this->rolloSpr->runAction(questionMarkSeq);
}

//Called When Rollo wants to move , it also handles whether rollo should move left or right
void LMGameLayer::moveRollo()
{
    //Hide the Rollo Question Mark
    this->rolloStarAnimationSpr->setVisible(false);
    
    //Move Rollo
    LMRollo *rolloInfo = (LMRollo *)this->rolloSpr->userInfo();
    
    this->rolloSpr->getBody()->SetType(b2_dynamicBody);
    this->rolloSpr->getBody()->SetLinearVelocity(b2Vec2(0,0));
    this->rolloSpr->getBody()->SetAngularVelocity(0);
    

    if(rolloInfo->isMovingRight)
    {
        rolloInfo->isMovingRight = false;  
        this->rolloSpr->getBody()->SetAngularVelocity(15);
    }
    else 
    {
        rolloInfo->isMovingRight = true;    
        this->rolloSpr->getBody()->SetAngularVelocity(-15);
    }
    this->isRolloMoving = true;
}


//Rollo reached Home !!!
void LMGameLayer::rolloReachedExit(LHContactInfo *contactInfo)
{
    if (contactInfo->contactType == LH_BEGIN_CONTACT)
    {
        this->isGameWon = true;
        this->isRolloMoving = false;
        this->didRolloReachedExit = true;
        
        this->rolloSpr->getBody()->SetLinearVelocity(b2Vec2(0,0));
        this->rolloSpr->getBody()->SetAngularVelocity(0);
        
        //Rollo reached home , stop the timer
        this->stopTimer();
    }
}

void LMGameLayer::rolloContactWithFire(LHContactInfo *contactInfo)
{
    if (contactInfo->contactType == LH_BEGIN_CONTACT)
    {
        this->isGameLost = true;
        this->runDieAnimation = true;
    }
}


#pragma mark - Timer

void LMGameLayer::startTimer()
{

    this->isTimerRunning = true;
    timerCount = 10;

    //Tell UI Manager to start a timer
    this->gameUIManager->showTimer();
    
    this->schedule(schedule_selector(LMGameLayer::updateTimer), 1);
}

void LMGameLayer::updateTimer()
{
    timerCount --; 
    this->gameUIManager->updateTimerLabel(timerCount);
    if(timerCount<=0)
    {
        this->stopTimer();
    }
}

void LMGameLayer::stopTimer()
{
    if (this->isTimerRunning) {
        this->unschedule(schedule_selector(LMGameLayer::updateTimer));
       
        //Remove the timer sprite
        this->gameUIManager->removeTimer();
        this->gameOver();
    }
}


#pragma mark - Game Won & Game Over
void LMGameLayer::gameWon()
{
    //Remove Rollo & Star Animation
    rolloStarAnimationSpr->stopAnimation();
    rolloStarAnimationSpr->removeSelf();
    
    //Show Game Won related things
    
    this->gameUIManager->gameWon(true);
}

void LMGameLayer::gameOver()
{
    //If game won at the same time dont do anything
    if(this->isGameWon==false)
    {
        //Show Level Fail !!!
        this->isGameLost = true;
        
        //Show level Fail Related Things
        this->gameUIManager->gameLoss();
    }
}

#pragma mark - Wood Destroy animation
void LMGameLayer::runWoodAnimationAtPosition(CCPoint woodPosition)
{
    LHSprite *woodDestroySpr = this->loader->createSpriteWithName("woodTouch1","Spritesheet", "Common.pshs",this);
    woodDestroySpr->setPosition(woodPosition);
    woodDestroySpr->prepareAnimationNamed("woodTouchAnimation","Common.pshs");
    
    woodDestroySpr->playAnimation();
    
    CCDelayTime *actionDelay = CCDelayTime::create(woodDestroySpr->animationDuration());
    CCSequence *actionSequence = CCSequence::createWithTwoActions(actionDelay, CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::removeWoodAnimation)));
    woodDestroySpr->runAction(actionSequence);    
}

void LMGameLayer::removeWoodAnimation(LHSprite* senderSpr)
{
    senderSpr->stopAnimation();
    senderSpr->removeSelf();
}


#pragma mark - Box2d Utility

bool LMGameLayer::isBodyTouchingAnotherBody(b2Body* bodyOne,b2Body* bodyTwo)
{
    bool overlap = b2TestOverlap(bodyOne->GetFixtureList()->GetShape(), 0, bodyTwo->GetFixtureList()->GetShape(), 0, bodyOne->GetTransform(), bodyTwo->GetTransform());
    return overlap;
}

//Box 2d 
bool LMGameLayer::checkCollisionWithBox2dBody(b2Body* inBody, CCPoint touchLocationPoint)
{
    b2Vec2 locationWorld = b2Vec2(touchLocationPoint.x/PTM_RATIO, touchLocationPoint.y/PTM_RATIO);
      
    b2AABB aabb;
    b2Vec2 d;
    d.Set(0.001f, 0.001f);
    aabb.lowerBound = locationWorld - d;
    aabb.upperBound = locationWorld + d;
    
    MouseJointQueryCallback callback(locationWorld);
    world->QueryAABB(&callback, aabb);
    
    if (callback.m_fixture)
    {
        if(callback.m_fixture->GetBody() == inBody)
        {
            return true;
        }
    }
    return false;
}


#pragma mark - Rollo Animations

void LMGameLayer::runRolloIdleAnimation()
{
    this->isRolloIdle = false;

    this->getRollosInitialPosition();
    
    this->rolloSpr->setVisible(false);
    this->animationRolloSpr->setVisible(true);
    
    int random = arc4random()%2;
    if(random==0) //Whistle Animation
    {
        this->runRolloWhistleAnimation();
    }
    else //Walking Animation
    {
        this->runRolloLookUpAnimation();
    }
}


void LMGameLayer::runRolloWhistleAnimation()
{
    this->animationRolloSpr->prepareAnimationNamed("RolloWhistleAnimation","Common.pshs");
    this->animationRolloSpr->playAnimation();
    
    CCDelayTime *actionWhistleDelay = CCDelayTime::create(2.2f);
    CCDelayTime *actionLookDownDelay = CCDelayTime::create(0.7f); 
    
    CCFiniteTimeAction *actionSequence = CCSequence::create(actionWhistleDelay,CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::runRolloLookDownAnimation)),actionLookDownDelay,CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::rolloIdleAnimationEnd)),NULL);
    this->animationRolloSpr->runAction(actionSequence); 
}

//Run 3 animations back to back

void LMGameLayer::runRolloLookUpAnimation()
{
    this->animationRolloSpr->prepareAnimationNamed("RolloLookUpAnimation","Common.pshs");
    this->animationRolloSpr->playAnimation();
    
    CCDelayTime *actionLookUpDelay = CCDelayTime::create(1.2f); 
    CCDelayTime *actionWalkingDelay = CCDelayTime::create(2.0f); 
    CCDelayTime *actionLookDownDelay = CCDelayTime::create(0.7f); 
    
    CCFiniteTimeAction *actionSequence = CCSequence::create(actionLookUpDelay,CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::runRolloWalkingAnimation)),actionWalkingDelay,CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::runRolloLookDownAnimation)),actionLookDownDelay,CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::rolloIdleAnimationEnd)),NULL);
    this->animationRolloSpr->runAction(actionSequence);    
}

void LMGameLayer::runRolloWalkingAnimation()
{
    this->animationRolloSpr->prepareAnimationNamed("RolloWalkingAnimation","Common.pshs");
    this->animationRolloSpr->playAnimation();
}

void LMGameLayer::runRolloLookDownAnimation()
{
    this->animationRolloSpr->prepareAnimationNamed("RolloLookDownAnimation","Common.pshs");
    this->animationRolloSpr->playAnimation();
}

void LMGameLayer::rolloIdleAnimationEnd()
{
    this->animationRolloSpr->stopAllActions();
    this->animationRolloSpr->setVisible(false);
    this->rolloSpr->setVisible(true);
    this->isRolloIdle = true;
}

//Run Rollo Win Animation
void LMGameLayer::runRolloWinAnimation()
{
    //Get the duration of 2nd animation
    this->rolloSpr->prepareAnimationNamed("RolloWinAnimOne","Common.pshs");
    
    CCDelayTime *actionDelay = CCDelayTime::create(this->rolloSpr->animationDuration()*2); //2 Repeat
    CCFiniteTimeAction *actionSequence = CCSequence::create(CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::rolloWinAnimOne)),actionDelay,CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::rolloWinAnimTwo)),NULL);
    this->rolloSpr->runAction(actionSequence);    
}

void LMGameLayer::rolloWinAnimOne()
{
    this->rolloSpr->playAnimation();
    
    //Add Star Animation
    rolloStarAnimationSpr = this->loader->createSpriteWithName("RolloWin_stars1","Spritesheet", "Common.pshs");
    rolloStarAnimationSpr->setPosition(CCPoint(this->rolloSpr->getPositionX()+kRolloWinAnimPosCorrectionFactor.x, this->rolloSpr->getPositionY()+kRolloWinAnimPosCorrectionFactor.y));
    rolloStarAnimationSpr->prepareAnimationNamed("RolloWinStarAnimation","Common.pshs");
    rolloStarAnimationSpr->playAnimation();
}

void LMGameLayer::rolloWinAnimTwo()
{
    this->rolloSpr->prepareAnimationNamed("RolloWinAnimTwo","Common.pshs");
    this->rolloSpr->playAnimation();
    
    //Call Game Won after delay!
    CCDelayTime *actionDelay = CCDelayTime::create(3.0f);  //Hardcoded 3 secs of animation
    CCSequence *actionSequence = CCSequence::createWithTwoActions(actionDelay, CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::gameWon)));
    this->rolloSpr->runAction(actionSequence);  
}

void LMGameLayer::rolloDieAnimation()
{
    //Stop the rollo
    this->rolloSpr->getBody()->SetLinearVelocity(b2Vec2(0,0));
    this->rolloSpr->getBody()->SetAngularVelocity(0);
    
    this->rolloSpr->getBody()->SetType(b2_staticBody);
    //Make rollo straight
    this->rolloSpr->getBody()->SetTransform(this->rolloSpr->getBody()->GetPosition(), 0 );
    
    //Play Die Animation
    this->rolloSpr->prepareAnimationNamed("RolloDyingAnimation","Common.pshs");
    this->rolloSpr->playAnimation();
    
    CCDelayTime *actionDelay = CCDelayTime::create(this->rolloSpr->animationDuration());
    CCSequence *dieAnimationSeq = CCSequence::createWithTwoActions(actionDelay, CCCallFuncN::create(this, callfuncN_selector(LMGameLayer::gameOver)));
    this->rolloSpr->runAction(dieAnimationSeq);
}


