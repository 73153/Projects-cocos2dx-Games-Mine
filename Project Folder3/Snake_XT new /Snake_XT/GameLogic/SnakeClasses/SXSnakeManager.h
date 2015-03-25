//
//  SXSnakeManager.h
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "cocos2d.h"

#import "SXGameManager.h"
#import "SXLevelManager.h"
#import "SXBonus.h"
#import "SXObstacle.h"

#import "SneakyJoystick.h"
#import "SneakyJoystickSkinnedBase.h"
#import "SneakyButton.h"
#import "SneakyButtonSkinnedBase.h"

#import "SXMultiplayerManager.h"


@interface SXSnakeManager : SXGameManager 
{
    SXLevelManager *leveldetails;
    SXMultiplayerManager *multiPlayerManager;
    
    NSMutableArray *staticObjects;
    NSMutableArray *movableObjects;
    NSMutableArray *pathArray;
    NSMutableArray *obstacles;
    
    
    NSMutableArray *BossSnakePathArray;
    NSMutableArray *NonBossSnakePathArray;
    NSMutableArray *NonBossMovableObjects;
    NSMutableArray *BossMovableObjects;



    
    
    NSMutableArray *toDeleteArray;
    NSMutableArray *transferArray;
    NSMutableArray *obstacleArray;
    
    
    NSString *shieldImage;
    NSString *snakeHeadImage;
    NSString *snakeDullImage;
    NSString *snakeBodyImage;
    
    float currentAngle;

    float mRotateAngle;
    float mPreRotateAngle;
    float  lastJoystickRotation; 

    int mRotateFactor;
    int kRotatingFactor;
    int snakeLength;
    int NoOfPartsCollected;
    int mLifesAvailable;
    int snakeTimeCounter;
    int staticBodyTag;
    
    BOOL mAngleChanged;
    BOOL mUnderRotating;
    BOOL mUnderStaticObjectCollition;
    BOOL isLevelCompleted;
    BOOL isBonusAdded;
    BOOL isObsatcleAdded;
    BOOL isLeftTurn;
    BOOL isJoystick;
    CGRect _mainframe;
    CGPoint mTappedPoint;
   
    
    NSMutableArray  *pointsArray;
    
    CGMutablePathRef headPath;
    CGPoint lastJoystickVelocity;
    CGPoint  joyStickVelocity;
    SneakyJoystickSkinnedBase *joystickBase;

    //SXBonus *aSXBonus;
}
@property(nonatomic,retain)SXLevelManager *leveldetails;

@property(nonatomic,retain)NSMutableArray *staticObjects;
@property(nonatomic,retain)NSMutableArray *movableObjects;
@property(nonatomic,retain)NSMutableArray *pathArray;
@property(nonatomic,retain)NSMutableArray *obstacleArray;
@property(nonatomic,retain)NSMutableArray *obstacleAtributePointsArray;
@property(nonatomic,retain)NSMutableArray *BossSnakePathArray;
@property(nonatomic,retain)NSMutableArray *NonBossSnakePathArray;
@property(nonatomic,retain)NSMutableArray *BossMovableObjects;
@property(nonatomic,retain)NSMutableArray *NonBossMovableObjects;





@property(nonatomic,retain)NSMutableArray *toDeleteArray;
@property(nonatomic,retain)NSMutableArray *transferArray;

@property(nonatomic,assign)CCSprite *obstacleSprite;

@property(nonatomic,retain)NSString *shieldImage;
@property(nonatomic,retain)NSString *snakeHeadImage;
@property(nonatomic,retain)NSString *snakeDullImage;
@property(nonatomic,retain)NSString *snakeBodyImage;



@property(nonatomic,retain) NSMutableArray *obstacles;
@property(nonatomic,assign)float mPreRotateAngle;
@property(nonatomic,assign)float currentAngle;



@property(nonatomic,assign) int snakeLength;
@property(nonatomic,assign) int kRotatingFactor;



-(void) createSnakeParts:(CGPoint)position withImageName:(NSString*)name ;
-(void)createSnakeHead:(CGPoint)position withImageName:(NSString *)name withHeadCoordinatesL:(NSArray *)headCoOrdinateArray withCGPathPointsArray:(NSArray *)CGPathArray;




-(void)updateScene;
- (void)handleTap:(NSSet*)touches withEvent:(UIEvent*)event;
-(void)addingtoSnakeHead;

-(void)addingObstaclesWithPosition:(CGPoint)position withImageName:(NSString*)name withPointsArray:(NSArray *)pointArray;
- (void)redirectSnakeWithPoint:(CGPoint)newLocation;

-(void)checkCollision;
-(void)isHeadOutsideBounds;
-(void)snakeMovement;
-(void)otherDeviveSnakeUpdate;

-(void)addingBonusWithPosition:(CGPoint)position withImageName:(NSString*)name type:(int)bonusType   withGlowImage:(NSString *)glowImage;

-(CGPoint)checkRandomPositionWithObstaclePosition;


-(void)sendSnakePosition;
    
-(void)createSnakeFromOtherDeviceAtPos:(CGPoint)pos withRotation:(float)rotation withtag:(int)SnakeTag;
-(void)createSnakeBodyFromOtherDevice:(int)tag;

-(void)setSnakePositionFromOtherDevice:(CGPoint)position withAngle:(float)rotation withTag:(int)tag;

// set hit effect to snake in other device 
-(void)setHitEffectToOtherDeviceSnake:(int)tag;
-(void)setSheildEffectToOtherDeviceSnake:(int)tag;


-(void)createSnakeStaticBody:(CGPoint)position;
-(void)createBonusfromOtherDevice:(CGPoint)posiiton withtype:(int)type;

-(void)removebonus;
-(void)removeStaticBodyFromOtherDevice:(int)staticBodytag;

// remove shield from other device
-(void)removeShieldOtherDevice:(int)tag;


@end
