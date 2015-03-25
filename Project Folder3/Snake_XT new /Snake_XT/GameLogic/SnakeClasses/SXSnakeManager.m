//
//  SXSnakeManager.m
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SXSnakeManager.h"
#import "SXSnake.h"
#import "SXSnakeStaticBody.h"
#import "SXCustomSprite.h"

#import "SXUtility.h"
#import "SXDataManager.h"
#import "SXMultiplayerManager.h"

#import "SXMessageType.h"

#define SJ_PI 3.14159265359f
#define SJ_PI_X_2 6.28318530718f
#define SJ_RAD2DEG 180.0f/SJ_PI
#define SJ_DEG2RAD SJ_PI/180.0f

@implementation SXSnakeManager
@synthesize movableObjects,staticObjects,pathArray,obstacles,leveldetails,mPreRotateAngle,snakeLength,kRotatingFactor,currentAngle;

@synthesize toDeleteArray,transferArray,obstacleArray,obstacleAtributePointsArray,BossSnakePathArray,NonBossSnakePathArray,NonBossMovableObjects,BossMovableObjects;
@synthesize shieldImage,snakeBodyImage,snakeDullImage,snakeHeadImage;
@synthesize obstacleSprite;


- (id)init
{
    self = [super init];
    if (self)
    {
        
        
        
        self.gameLayer = DataManager.gameLayer;
        
        
        NSMutableArray *temp=[[NSMutableArray alloc]init];
        self.movableObjects=temp;
        [temp release];
        
        temp=[[NSMutableArray alloc]init];
        self.staticObjects=temp;                    //static objects array
        [temp release];
        
        temp=[[NSMutableArray alloc]init];
        self.pathArray=temp;                       // path array
        [temp release];
        temp=[[NSMutableArray alloc]init];
        self.toDeleteArray=temp;                 // delete array 
        [temp release];
        
        temp=[[NSMutableArray alloc]init];
        self.transferArray=temp;                   // transfer array 
        [temp release];
        
        temp=[[NSMutableArray alloc]init];
        self.obstacleArray=temp;               // obstacles array 
        [temp release];
        
        
        temp=[[NSMutableArray alloc]init];
        self.obstacles=temp;               // obstacles array 
        [temp release];
        
        temp=[[NSMutableArray alloc]init];
        self.obstacleAtributePointsArray=temp;               // obstacles array 
        [temp release];
        
        temp=[[NSMutableArray alloc]init];
        self. BossSnakePathArray=temp;               // boss path array 
        [temp release];
        
        temp=[[NSMutableArray alloc]init];
        self.NonBossSnakePathArray=temp;               // nono boss path  array 
        [temp release];
        
        temp=[[NSMutableArray alloc]init];
        self.BossMovableObjects=temp;               // nono boss path  array 
        [temp release];
        
        temp=[[NSMutableArray alloc]init];
        self.NonBossMovableObjects=temp;               // nono boss path  array 
        [temp release];
        kRotatingFactor=20;
        snakeLength=0;
        
        mRotateAngle=1;
        mPreRotateAngle=1;
        mRotateFactor=1;
        mAngleChanged=NO;
        
        
        
        _mainframe = CGRectMake(5, 05, 465, 305);
        //
        headPath=CGPathCreateMutable();     //creatimng CGPath for snake head
        CGPathMoveToPoint(headPath, NULL, 10, 3);      //adding points to head path
        CGPathAddLineToPoint(headPath, NULL, 21, 3);
        CGPathAddLineToPoint(headPath, NULL, 26, 17); 
        CGPathAddLineToPoint(headPath, NULL, 26,23);   
        CGPathAddLineToPoint(headPath, NULL, 22,34);
        CGPathAddLineToPoint(headPath, NULL, 11,34);
        CGPathAddLineToPoint(headPath, NULL,5, 24);
        CGPathAddLineToPoint(headPath, NULL,5, 18);
        CGPathCloseSubpath(headPath); 
        
        pointsArray=[NSMutableArray arrayWithObjects:     //   polygon attribute points when snake head is having shield 
                     [NSValue valueWithCGPoint:ccp(366, 147)],
                     [NSValue valueWithCGPoint:ccp(347, 147)],
                     [NSValue valueWithCGPoint:ccp(344, 138)],
                     [NSValue valueWithCGPoint:ccp(353, 123)],
                     [NSValue valueWithCGPoint:ccp(367,127)],
                     [NSValue valueWithCGPoint:ccp(369,18)],
                     nil];
        
        NSUserDefaults *userdefault=[NSUserDefaults standardUserDefaults];
        isJoystick=[userdefault boolForKey:kPLAYMODE];
        
        if(isJoystick){  // adding joystick 
            
            
            NSUserDefaults *userDefault=[NSUserDefaults standardUserDefaults];
            NSString *pos=[userDefault objectForKey:KJoystickPos];
            joystickBase=[[[SneakyJoystickSkinnedBase alloc]init] autorelease];
            
            joystickBase.position=CGPointFromString(pos);
            // joystickBase.position=ccp(50, 60);
            joystickBase.backgroundSprite=[CCSprite spriteWithFile:@"Joystick_Controller.png"];
            joystickBase.thumbSprite=[CCSprite spriteWithFile:@"movementJoystickMiddle.png"];
            SneakyJoystick *joystick=[[[SneakyJoystick alloc]init] autorelease];
            joystickBase.joystick=joystick;
            joystickBase.joystick.isEnabled = YES;
            [DataManager.gameLayer addChild:joystickBase z:7];   
        }
    }
    return self;
}

#pragma mark - Adding Sprites
//creating initial SnakeHead and SnakeBody
-(void) createSnakeParts:(CGPoint)position withImageName:(NSString*)name 
{
    SXSnakeStaticBody *aSnakeBodyPart = [SXSnakeStaticBody spriteWithSpriteFrameName:self.snakeBodyImage];    // creating snake body parts 
    [aSnakeBodyPart addingSnakePart:position withLayer:self.gameLayer withManager:self];
    [self.transferArray addObject:aSnakeBodyPart];                                                            // adding to transfer array   
    
    aSnakeBodyPart.tag=KStaticbodyTag+staticBodyTag;
    staticBodyTag++;
    for (SXCustomSprite *aSprite in self.transferArray) {
        
        [self.staticObjects addObject:aSprite];              // adding to static body to staticarray 
        [self.toDeleteArray addObject:aSprite];              // adding to toDeleteArray 
    }
    
    for (SXCustomSprite *aSprite in self.toDeleteArray) {         // deleting  sprites from toDeleteArray 
        
        if ([self.transferArray containsObject:aSprite]) {
            
            [self.transferArray removeObject:aSprite];
        }
    }
    
    [self.toDeleteArray removeAllObjects];
}

// creating snake head 
-(void)createSnakeHead:(CGPoint)position withImageName:(NSString *)name withHeadCoordinatesL:(NSArray *)headCoOrdinateArray withCGPathPointsArray:(NSArray *)CGPathArray
{
    
    SXSnake *aSnakePart = [SXSnake spriteWithSpriteFrameName:self.snakeHeadImage];
    
    [aSnakePart addingSnakePart:position withLayer:self.gameLayer withManager:self withPointsArray:headCoOrdinateArray withCGPathPointsArray:CGPathArray];
    
    
    if(DataManager.isMultiplayer ){
        int snakeTag;
        if (DataManager.gameLayer.multiplayerManager.isBoss) {
            snakeTag = KBossSnakeTag;
        }
        else {
            snakeTag = KNonBossSnakeTag;
        }
        
        aSnakePart.tag = snakeTag;
        
        // NSLog(@" sending position to create snake from other device");
        
        [DataManager.gameLayer.multiplayerManager createSnakeWithPosition:aSnakePart.position withAngle:90 withTag:snakeTag];
    }
    
    
    [self.movableObjects addObject:aSnakePart];  
    
    // adding snake haed to movable objects array 
    for (SXCustomSprite *aSprite in self.transferArray) 
    {
        [self.staticObjects addObject:aSprite];              // adding to static body to staticarray 
        [self.toDeleteArray addObject:aSprite];              // adding to toDeleteArray 
    }
    
    for (SXCustomSprite *aSprite in self.toDeleteArray)  // deleting  sprites from toDeleteArray 
    {        
        if ([self.transferArray containsObject:aSprite])
        {
            [self.transferArray removeObject:aSprite];
        }
    }
    
    [self.toDeleteArray removeAllObjects];
}


-(void)createSnakeFromOtherDeviceAtPos:(CGPoint)pos withRotation:(float)rotation withtag:(int)SnakeTag
{
    SXSnake *aSnakePart = [SXSnake spriteWithSpriteFrameName:self.snakeHeadImage];
    aSnakePart.position=pos;
    [DataManager.gameLayer addChild:aSnakePart z:5 tag:SnakeTag];
}


-(void)createSnakeBodyFromOtherDevice:(int)tag{
    CCSprite *bodySprite=[CCSprite spriteWithSpriteFrameName:self.snakeBodyImage];
    [DataManager.gameLayer addChild:bodySprite z:5];
    
    
    if(tag==KBossSnakeTag)
    {
        [self.BossMovableObjects addObject:bodySprite];
    }
    else {
        [self.NonBossMovableObjects addObject:bodySprite];
        
    }
}


-(void)createSnakeStaticBody:(CGPoint)position
{
    SXSnakeStaticBody *aSnakeBodyPart = [SXSnakeStaticBody spriteWithSpriteFrameName:self.snakeBodyImage];    // creating snake body parts 
    [aSnakeBodyPart addingSnakePart:position withLayer:self.gameLayer withManager:self];
    aSnakeBodyPart.tag=KStaticbodyTag+staticBodyTag;
    staticBodyTag++;
    
    
    //[self.staticObjects addObject:aSnakeBodyPart];              // adding to static body to staticarray 
    
    [self.transferArray addObject:aSnakeBodyPart];                                                            // adding to transfer array   
    
    for (SXCustomSprite *aSprite in self.transferArray)
    {
        [self.staticObjects addObject:aSprite];    
        
        // adding to static body to staticarray 
        [self.toDeleteArray addObject:aSprite];   
        
        // adding to toDeleteArray 
    }
    
    for (SXCustomSprite *aSprite in self.toDeleteArray) 
    {         // deleting  sprites from toDeleteArray 
        
        if ([self.transferArray containsObject:aSprite]) {
            
            [self.transferArray removeObject:aSprite];
            
        }
    }
    
    [self.toDeleteArray removeAllObjects];
    
    
    if(DataManager.gameLayer.multiplayerManager.isBoss)
    {
        // sending message to  non boss device to add static body 
        [DataManager.gameLayer.multiplayerManager createSnakeStativBody:position];
    }
    
}



-(void)createBonusfromOtherDevice:(CGPoint)position withtype:(int)type{
    
    
    NSString *glowimage=[NSString stringWithFormat:@"bonus%d_Glow.png",type];
    
    SXBonus *bonus=[SXBonus spriteWithSpriteFrameName:[NSString stringWithFormat:@"bonus%d.png",type]];
    [bonus addingBonus:position withLayer:self.gameLayer withManager:self type:type];
    bonus.type=type;
    bonus.glowImage=glowimage;
    [bonus setShieldGlowEffect];
    [self.staticObjects addObject:bonus ];
    
    
    
}



-(void)removebonus
{
    
    for (SXCustomSprite *aSprite in self.staticObjects) 
    {
        //checking collision with SnakeHead and Bonus
        if([aSprite isKindOfClass:[SXBonus class]]) 
        {
            SXBonus *aBonus = (SXBonus *)aSprite;    
            [self.toDeleteArray addObject:aBonus];
        }
    }
    
}

-(void)removeShieldOtherDevice:(int)tag
{
    
    NSLog(@"tag=%d",tag);
    CCSprite *otherDeviceSnake=(CCSprite *) [DataManager.gameLayer getChildByTag:tag];
    NSLog(@"otherDeviceSnake=%d",otherDeviceSnake.tag);
    
    CCSprite *otherDeviceShield=(CCSprite *) [otherDeviceSnake getChildByTag:1];
    NSLog(@"otherDeviceShield=%d",otherDeviceShield.tag);
    
    [otherDeviceSnake removeChild:otherDeviceShield cleanup:YES];
    
}


-(void)removeStaticBodyFromOtherDevice :(int)Bodytag{
    
    SXSnakeStaticBody *body=(SXSnakeStaticBody *)[DataManager.gameLayer getChildByTag:Bodytag];
    [DataManager.gameLayer removeChild:body cleanup:YES];
    [self.staticObjects removeObject:body];
}


//Adding Bonus
-(void)addingBonusWithPosition:(CGPoint)position withImageName:(NSString*)name type:(int)bonusType withGlowImage:(NSString *)glowImage
{
    
    if(DataManager.isMultiplayer)
    {
        if( DataManager.gameLayer.multiplayerManager.isBoss)
        {
            [self checkRandomPositionWithObstaclePosition];
            SXBonus *aBonus=[SXBonus spriteWithSpriteFrameName:name];
            [aBonus addingBonus:position withLayer:self.gameLayer withManager:self type:bonusType];
            aBonus.type=bonusType;
            aBonus.glowImage=glowImage;
            [aBonus setShieldGlowEffect];
            [self.staticObjects addObject:aBonus ];
            [DataManager.gameLayer.multiplayerManager createBonusWithPosition:position withImageName:name type:bonusType withGlowImage:glowImage];
        }
    }
    
    else{
        [self checkRandomPositionWithObstaclePosition];
        SXBonus *aBonus=[SXBonus spriteWithSpriteFrameName:name];
        [aBonus addingBonus:position withLayer:self.gameLayer withManager:self type:bonusType];
        aBonus.type=bonusType;
        aBonus.glowImage=glowImage;
        [aBonus setShieldGlowEffect];
        [self.staticObjects addObject:aBonus ];
    }
}



// adding obstcales
-(void)addingObstaclesWithPosition:(CGPoint)position withImageName:(NSString *)name withPointsArray:(NSArray *)pointArray
{
    SXObstacle *obstacle=[SXObstacle spriteWithSpriteFrameName:name];
    [DataManager.gameLayer addChild:obstacle z:3];
    obstacle.position=position;
    obstacle.ObstacleImageName=name;
    obstacle.pointsArray=[[NSArray alloc]initWithArray:pointArray];
    [self.obstacles addObject:obstacle];
}


// adding body to snake  after head collide 
-(void)addingtoSnakeHead
{
    CCSprite *snakeBody=[CCSprite spriteWithSpriteFrameName:self.snakeBodyImage];
    SXSnakeStaticBody *preBody=(SXSnakeStaticBody *)[movableObjects objectAtIndex:[movableObjects count]-1];// tail  body 
    SXSnake *snakeHead=(SXSnake *)[movableObjects objectAtIndex:0]; // head 
    [self.movableObjects addObject:snakeBody];
    NSArray *PositionArray ;
    PositionArray =[DataManager.movableBodyPosiitons componentsSeparatedByString:@"|"]; // getting movable object posiiton from datamanager's movableBody Position string and storing in array
    if( DataManager.isSwitchModeInsideGame){              //  if loading game  or switch between modes
        for(int i=0; i<[movableObjects count]-1;i++)
        {
            if(i==0)
            {  
                snakeHead.position=CGPointFromString([PositionArray objectAtIndex:0]);  // setting head posiiton 
                snakeHead.rotation=self.currentAngle;
            }
            snakeBody.position=CGPointFromString([PositionArray objectAtIndex:i+1]);// gettting body position from Posiiton array which we saved 
        }
    }
    
    else 
    {
        if(snakeLength==0)
        { 
            CGSize topRightCornerSize = CGSizeMake(snakeHead.contentSize.width/2+5,0);
            CGPoint topRightPoint = [SXUtility getRotatedPointForPoint:snakeHead.position forAngle:[SXUtility checkTheAngleLimitAngle:snakeHead.rotation]withContentSize:topRightCornerSize forRectCornet:kTopLeft];
            snakeBody.position=topRightPoint;
            snakeBody.rotation=snakeHead.rotation;
            
        }
        else
        {   //adding to body to tail of snake
            snakeBody.position=preBody.position;
        }
    }     
    
    [DataManager.gameLayer addChild:snakeBody z:5];
    id action=[CCScaleTo actionWithDuration:0.1 scale:0];
    id actionReverse=[CCScaleTo actionWithDuration:0 scale:1];
    [snakeBody runAction:[CCSequence actions:action,actionReverse, nil]];
    NoOfPartsCollected++;
    snakeLength++;
}


// movement of snake body parts 
-(void)snakeBodyMovement
{
    SXSnake *snakeHead=(SXSnake *)[self.movableObjects objectAtIndex:0];
    int speedFactor;
    speedFactor=(snakeHead.contentSize.width/2)/DataManager.snakeSpeed;  
    
    if((DataManager.snakeSpeed==8 ||DataManager.snakeSpeed==7) && DataManager.currentLevel<16 &&DataManager.gameMode==KARCADEMODE)
    {
        speedFactor--;
    }
    
    for(int i=1;i<[self.movableObjects count];i++)
    {
        //NSLog(@" first position in   path array=%@ ",[self.pathArray objectAtIndex:0]);
        
        SXSnakeStaticBody *body=(SXSnakeStaticBody*)[self.movableObjects objectAtIndex:i];
        if(DataManager.gameMode==KARCADEMODE)
        {
            if(DataManager.currentLevel<16)
            {
                body.position=CGPointFromString([pathArray objectAtIndex:[pathArray count]-((speedFactor+1)*i+2)]);// gettting body position from Path rray
            }
            else
            {
                body.position=CGPointFromString([pathArray objectAtIndex:[pathArray count]-((speedFactor)*i+1)]);// gettting body position from Path rray
            }
        }
        else
        {
            body.position=CGPointFromString([pathArray objectAtIndex:[pathArray count]-((speedFactor+1)*i+1)]);// gettting body position from Path rray
        }
    }
    
    
    while ([pathArray count]>([movableObjects count]*(speedFactor+DataManager.snakeSpeed)*15))
    {
        // removing elelments from pathArray
        [pathArray removeObjectAtIndex:0];
    }
}


#pragma mark - Update
-(void)updateScene  // updating snake rotation to make smooth rotation 
{
    SXSnake *snakeHead=(SXSnake *)[movableObjects objectAtIndex:0];
    if(isJoystick)
    {
        [self snakeMovement];
    }
    else{
        mRotateAngle = [SXUtility getAngleFromCurrentPoint:snakeHead.position toPoint:mTappedPoint];
        
        currentAngle = snakeHead.rotation;
        float angleDiff;
        if(mRotateAngle > currentAngle)
            angleDiff = (int)mRotateAngle - (int)currentAngle;
        else
            angleDiff = (int)currentAngle - (int)mRotateAngle;
        if(mAngleChanged) // if angle is  changed
        {
            if((int)currentAngle != (int)mRotateAngle)
            {
                if(isLeftTurn) // left turn 
                {                
                    
                    if(angleDiff < kRotatingFactor)  // if angle diff  is less than 
                    {
                        currentAngle = currentAngle - angleDiff; //  subtracting cureent angle with angle diff to make snake  left rotation smoothly 
                        // NSLog(@" currentAngle in left turn after subtracting diff=%f",currentAngle);
                    }
                    else  if( angleDiff>330)  
                    {
                        currentAngle=mRotateAngle;
                        
                    }  
                    
                    else
                    {
                        currentAngle = currentAngle - kRotatingFactor;    // subtractin current angle with kFactor(minimum decrement in curerent angle)
                    }
                    
                    
                    if(currentAngle <= 0) 
                    {
                        currentAngle = 360 + currentAngle;    //adding 360 to current angle if it  is 0
                    }
                    
                    if (((currentAngle > 340 && currentAngle < 360) || (currentAngle >= 0 && currentAngle < kRotatingFactor)) && (mRotateAngle >= 340 && mRotateAngle < 360)) 
                    {
                        
                        if (currentAngle + kRotatingFactor > mRotateAngle) 
                        {
                            currentAngle = (mRotateAngle - currentAngle) + currentAngle;
                            
                        }
                    }
                    
                    if((int)currentAngle == (int)mRotateAngle)   
                    {
                        mAngleChanged = FALSE;
                        currentAngle = (int)mRotateAngle;
                    }
                }
                
                
                else
                { // right turn 
                    
                    
                    
                    if(angleDiff < kRotatingFactor) 
                    {
                        currentAngle = currentAngle + angleDiff; // adding angleDiff to currentAngle to make snake  right  rotation smoothly 
                        
                    }
                    else 
                    {
                        currentAngle = currentAngle + kRotatingFactor; // adding  kRotatingFactor 
                        
                    }
                    
                    currentAngle = (int)currentAngle % 360;
                    
                    if (((currentAngle > 340 && currentAngle < 360) || (currentAngle >= 0 && currentAngle < kRotatingFactor)) && (mRotateAngle >= 0 && mRotateAngle < kRotatingFactor)) 
                    {
                        
                        if (currentAngle - kRotatingFactor < mRotateAngle) 
                        {
                            
                            if (mRotateAngle == 0)
                            {
                                currentAngle = 0;
                            }
                            else 
                                currentAngle = currentAngle - (currentAngle - mRotateAngle);
                            
                        }
                    }
                    
                    if((int)currentAngle == (int)mRotateAngle) 
                    {
                        mAngleChanged = FALSE;
                        currentAngle = (int)mRotateAngle;
                    }
                }
            }
        } 
        
        [self snakeMovement];
    }
}


// snake movement 
-(void)snakeMovement
{
    SXSnake *snakeHead=(SXSnake*)[movableObjects objectAtIndex:0];
    CGPoint prepoint; //snake previous posiiton 
    if(DataManager.isMultiplayer==YES){
        DataManager.snakeSpeed=2;
    }
    int distance=DataManager.snakeSpeed;
    
    CGPoint prepos=snakeHead.position;
    CGPoint scaledVelocity;
    
    //movement using head 
    if(isJoystick)
    {
        if(!(CGPointEqualToPoint(joystickBase.joystick.velocity, CGPointZero)))
        {
            joyStickVelocity=joystickBase.joystick.velocity;
            snakeHead.rotation= [SXUtility getCurrentJoystickAngleForDegree:joystickBase.joystick.degrees]; 
            scaledVelocity=ccpMult(ccpNormalize(joyStickVelocity), 100);
            lastJoystickVelocity=scaledVelocity;
            scaledVelocity=ccpMult(scaledVelocity, DataManager.snakeSpeed);
            float  x=snakeHead.position.x+scaledVelocity.x*0.01;
            float  y=snakeHead.position.y+scaledVelocity.y*0.01;
            snakeHead.position=ccp(x,y);
            lastJoystickRotation=snakeHead.rotation;
            [self.pathArray addObject:NSStringFromCGPoint(snakeHead.position)];
            if(DataManager.isMultiplayer)
            {
                [DataManager.gameLayer.multiplayerManager sendSnakePosition:snakeHead.position withSnakeHeadRotation:snakeHead.rotation withTag:snakeHead.tag];
            }
        }
        else //once you leave joystick 
        {  
            CGPoint velocity=ccp(lastJoystickVelocity.x ,lastJoystickVelocity.y) ;
            
            velocity=ccpMult(velocity, DataManager.snakeSpeed);
            
            float x=snakeHead.position.x+velocity.x*0.01;
            float y=snakeHead.position.y+velocity.y*0.01;
            snakeHead.position=ccp(x,y);
            snakeHead.rotation=lastJoystickRotation;
            [self.pathArray addObject:NSStringFromCGPoint(snakeHead.position)];
            if(DataManager.isMultiplayer)
            {
                [DataManager.gameLayer.multiplayerManager sendSnakePosition:snakeHead.position withSnakeHeadRotation:snakeHead.rotation withTag:snakeHead.tag];
            }
        }
    }
    
    // movemeny using tap 
    else
    {
        float X = snakeHead.position.x + sin(CC_DEGREES_TO_RADIANS(currentAngle))*distance;
        float Y = snakeHead.position.y + cos(CC_DEGREES_TO_RADIANS(currentAngle))*distance;
        
        snakeHead.position = ccp(X, Y);       //moving the snake to position , current snake position plus the distance 
        
        float ang=[SXUtility getAngleFromCurrentPoint:prepos toPoint:snakeHead.position];//angle between previous snakehead  position and current snakehead  posiiton
        snakeHead.rotation=ang;
        prepoint=snakeHead.position;
        
        [self.pathArray addObject:NSStringFromCGPoint(prepoint)]; // adding dsnake position to pathArray
        if(DataManager.isMultiplayer)
        {
            [DataManager.gameLayer.multiplayerManager sendSnakePosition:snakeHead.position withSnakeHeadRotation:snakeHead.rotation withTag:snakeHead.tag];
        }
    }
    
    [self snakeBodyMovement];
}


-(void)otherDeviveSnakeUpdate{
    SXSnake *snakeHead=(SXSnake*)[movableObjects objectAtIndex:0];
    int speedFactor=(snakeHead.contentSize.width/2)/DataManager.snakeSpeed;  
    
    if((DataManager.snakeSpeed==8 ||DataManager.snakeSpeed==7 ||DataManager.snakeSpeed==4) && DataManager.currentLevel<16 &&DataManager.gameMode==KARCADEMODE)
    {
        speedFactor--;
    }
    
    for (int i=0;i<[BossMovableObjects count]; i++)
    {
        CCSprite *body=(CCSprite *)[BossMovableObjects objectAtIndex:i];
        body.position=CGPointFromString([self.BossSnakePathArray objectAtIndex:[self.BossSnakePathArray count]-((speedFactor+1)*i+10)]);//        
    }
    
    
    // for non boss movable objects 
    for (int i=0; i<[NonBossMovableObjects count]; i++) 
    {
        CCSprite *body=(CCSprite *)[NonBossMovableObjects objectAtIndex:i];
        body.position=CGPointFromString([self.NonBossSnakePathArray objectAtIndex:[self.NonBossSnakePathArray count]-((speedFactor+1)*i+10)]);// gettting body position from Path rray
    }
    
}


-(void)setSnakePositionFromOtherDevice:(CGPoint)position withAngle:(float)rotation withTag:(int)tag
{
    CCSprite *snake= (CCSprite *)[DataManager.gameLayer getChildByTag:tag];
    snake.position=position;
    snake.rotation=rotation;
    
    if(tag==KBossSnakeTag)
    {
        [self.BossSnakePathArray addObject:NSStringFromCGPoint(snake.position)];
    }
    else
    {
        
        [self.NonBossSnakePathArray addObject:NSStringFromCGPoint(snake.position)];
    }
}



#pragma -mark set hit effect to snake in other device
-(void)setHitEffectToOtherDeviceSnake:(int)tag
{
    
    CCSprite *sprite=(CCSprite *)[DataManager.gameLayer getChildByTag:tag];
    [sprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:DataManager.gameLayer.snakeManager.snakeDullImage]];
    
    CCSprite * snakeHit=[CCSprite spriteWithSpriteFrameName:@"level_hit_.png"];
    snakeHit.position=ccp(sprite.contentSize.width/2,sprite.contentSize.height/2);
    [sprite addChild:snakeHit];
    
    id rotate1 = [CCRotateTo actionWithDuration:0.5 angle:snakeHit.rotation+180];
    id rotate2 = [CCRotateTo actionWithDuration:0.5 angle:snakeHit.rotation+360];
    id actionSeq = [CCSequence actions:rotate1,rotate2, nil];
    id actionRepeat = [CCRepeatForever actionWithAction:actionSeq];
    [snakeHit runAction:actionRepeat];
    
    
    
    id delayAction = [CCDelayTime actionWithDuration:1.5];
    id blockAction = [CCCallBlockN actionWithBlock:^(CCNode* node){ [snakeHit removeFromParentAndCleanup:YES],[sprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:self.snakeHeadImage]];; }];
    id sequence = [CCSequence actions:delayAction,blockAction, nil];
    [snakeHit runAction:sequence];
}

-(void)setSheildEffectToOtherDeviceSnake:(int)tag{
    
    CCSprite *sprite=(CCSprite *)[DataManager.gameLayer getChildByTag:tag];
    [sprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:self.snakeHeadImage]];
    
    CCSprite *snakeHit=[CCSprite spriteWithSpriteFrameName:self.shieldImage];
    snakeHit.position=ccp(sprite.contentSize.width/2,sprite.contentSize.height/2);
    [sprite addChild:snakeHit z:0 tag:1];
    
    
    id delayAction = [CCDelayTime actionWithDuration:6];
    id blockAction = [CCCallBlockN actionWithBlock:^(CCNode* node){ [snakeHit removeFromParentAndCleanup:YES],[sprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:self.snakeHeadImage]];; }];
    id sequence = [CCSequence actions:delayAction,blockAction, nil];
    [snakeHit runAction:sequence];
}

#pragma -mark redirect methods

-(void)redirectSnake
{	 
    [joystickBase.joystick resetJoyStick];
    id callback=[CCCallFunc actionWithTarget:self selector:@selector(redirectAction)];
    id delay=[CCDelayTime actionWithDuration:2];
    id seq=[CCSequence actions:callback,delay,nil];
    [self.gameLayer runAction:seq];
}


-(void)redirectAction{
    SXSnake *snakeHead=(SXSnake *)[self.movableObjects objectAtIndex:0];
    
    
    CGPoint velocity=joyStickVelocity;
    //bottom 
    if( snakeHead.position.y<15){
        velocity=ccp(velocity.x,-velocity.y);
    }
    
    //top
    if(snakeHead.position.y>=300){
        velocity=ccp(velocity.x,-velocity.y);
    }
    
    //left
    if(snakeHead.position.x<=20){
        velocity=ccp(-velocity.x,velocity.y);
    }
    
    //right 
    if(snakeHead.position.x>=470 ){
        velocity=ccp(-velocity.x,velocity.y);
    }
    
    joyStickVelocity=velocity;
    snakeHead.rotation=[SXUtility getAngleFromVelocity:velocity];
    
    velocity=ccpMult(ccpNormalize(velocity), 100);
    lastJoystickVelocity=velocity;
    lastJoystickRotation=snakeHead.rotation;
    velocity=ccpMult(velocity, DataManager.snakeSpeed);
    float x=snakeHead.position.x+velocity.x*0.01;
    float y=snakeHead.position.y+velocity.y*0.01;
    snakeHead.position=ccp(x,y);
    [self.pathArray addObject:NSStringFromCGPoint(snakeHead.position)];
}



// redirect the snake to the screen once it hit the boundary of screen
- (void)redirectSnakeWithPoint:(CGPoint)newLocation
{	
    CGPoint currentLocation = newLocation;
    SXSnake *SnakeHead=(SXSnake*)[movableObjects objectAtIndex:0];
    
	
    if (SnakeHead.isShieldOn && !SnakeHead.isInSafeMode) { // if head hits the boundary and having shield ,  remove shield 
        [SnakeHead removeShieldEffect];
    }
    
    else if(!SnakeHead.isInSafeMode)
    {
        [(SXSnake*) [movableObjects objectAtIndex:0]setHitEffect];  // set hit animation 
    }
    
	CGPoint point=SnakeHead.position;
	mTappedPoint = currentLocation;
    float angle = [SXUtility getAngleFromCurrentPoint:point toPoint:currentLocation]; // get angle towards center 
	mRotateAngle = angle;
    mAngleChanged = YES;
    [self CheckRotation];
}


#pragma mark - #pragma -mark check collision

//Adding snake body to an Head after collision

// checking collision
-(void)checkCollision 
{
    
    [self checkCollisionWithBonus];    
    [self checkCollisionWithStaticBody];
    [self checkCollisionWithObstacles];
    [self checkCollisionwithItsBody];
    [self isHeadOutsideBounds];
    
    
    // deleting  elements from  toDeleteArray
    for (NSObject *anObject in self.toDeleteArray) 
    {
        
        if ([self.transferArray containsObject:anObject]) 
        {
            
            [self.transferArray removeObject:anObject];
        }
        else if([self.staticObjects containsObject:anObject]) 
        {
            [self.staticObjects removeObject:anObject];
            
            SXCustomSprite *aSprite = (SXCustomSprite *)anObject;
            [DataManager.gameLayer removeChild:aSprite cleanup:YES];
        }
    }
    
    [self.toDeleteArray removeAllObjects];
}


// checking for head outside boundary 
-(void)isHeadOutsideBounds{
    
    SXSnake *snakeHead=(SXSnake *)[movableObjects objectAtIndex:0];
    if(!CGRectContainsPoint(_mainframe, snakeHead.position)){
        if(isJoystick){
            [self redirectSnake]; // joystick redirect methods
            
        }
        else{ 
            [self redirectSnakeWithPoint:ccp(240, 160)]; // methods to redirect snake towards center using tap 
            
        }
       
    }
}

//check collision with its body
-(void)checkCollisionwithItsBody{ 
    
    SXSnake *snakeHead=(SXSnake*)[movableObjects objectAtIndex:0];
    
    //Collision Between Obstacle and Snake Head
    
    CGRect headRect = CGRectMake(snakeHead.position.x-snakeHead.contentSize.width/2, snakeHead.position.y-snakeHead.contentSize.height/2, snakeHead.contentSize.width/2, snakeHead.contentSize.height/2);
    for (int i=3; i<[movableObjects count]; i++) {
        
        SXSnake *snakeBody=(SXSnake*)[movableObjects objectAtIndex:i];
        CGRect bodyRect = CGRectMake(snakeBody.position.x-snakeBody.contentSize.width/2, snakeBody.position.y-snakeBody.contentSize.height/2, snakeBody.contentSize.width/2, snakeBody.contentSize.height/2);
        
        if(CGRectIntersectsRect(headRect, bodyRect))// checking for collision of head with its own body 
        {        
            //Remove the shield if snake has the sheild       
            if (snakeHead.isShieldOn )//&& !snakeHead.isInSafeMode) 
            {
                [snakeHead removeShieldEffect];
            }
            else if(!snakeHead.isInSafeMode)
            {
                [(SXSnake*) [movableObjects objectAtIndex:0]setHitEffect];
            }
        }   
    }
}


//check collision with obstacles
-(void) checkCollisionWithObstacles
{
    SXSnake *snakeHead=(SXSnake*)[movableObjects objectAtIndex:0];
    for(SXObstacle *obstacle in self.obstacles)
    {
        if( [snakeHead IscollideWithObstacle:obstacle])
        {
            if (snakeHead.isShieldOn )//&& !snakeHead.isInSafeMode) 
            {
                [snakeHead removeShieldEffect];
            }
            else if(!snakeHead.isInSafeMode)
            {
                [(SXSnake*) [movableObjects objectAtIndex:0]setHitEffect];
            }
            if(isLeftTurn)
            { 
                
                CGPoint pos=[SXUtility getStraightPointWithRadius:90 withAngle:snakeHead.rotation+10 withStartPoint:snakeHead.position];
                float rotation=[SXUtility getCocosAngleFromCurrentPoint:snakeHead.position toPoint:pos];
                snakeHead.rotation=rotation;
                
                
                //snakeHead.rotation=snakeHead.rotation+10;
                // mRotateAngle=snakeHead.rotation+10;
                // mAngleChanged=YES;
                
                
            }
            
            else
            {
                CGPoint pos=[SXUtility getStraightPointWithRadius:90 withAngle:snakeHead.rotation-10 withStartPoint:snakeHead.position];
                float rotation=[SXUtility getCocosAngleFromCurrentPoint:snakeHead.position toPoint:pos];
                snakeHead.rotation=rotation;
                
                
                //snakeHead.rotation=snakeHead.rotation-10;
                // mRotateAngle=snakeHead.rotation-10;
                //mAngleChanged=YES;
                
            }                      
            
        }
        
    }
    
}




// check collision with static body
-(void)checkCollisionWithStaticBody{
    SXSnake *snakeHead=(SXSnake*)[movableObjects objectAtIndex:0];
    for (SXCustomSprite *aSprite in self.staticObjects) 
    {
        if([aSprite isKindOfClass:[SXSnakeStaticBody class]]) 
        {
            
            SXSnakeStaticBody *snakeBody=(SXSnakeStaticBody*)aSprite;
            BOOL isCollide=[snakeBody isCollission:snakeHead] ;  // check head cillides with body 
            
            
            if(isCollide)
            {                    
                
                if(DataManager.gameMode==KARCADEMODE) { // Arcade Mode
                    
                    if(DataManager.noOfParts -3>0)   // creating pellets till no of partsis 0 
                    {
                        CGPoint point=[self checkRandomPositionWithObstaclePosition];
                        
                        
                        if(DataManager.isMultiplayer)    // is multiplayer 
                        {
                            [DataManager.gameLayer.multiplayerManager createSnakeBody:snakeHead.tag];  // sending  msg to other device to create body parts in other device 
                            
                            if(DataManager.gameLayer.multiplayerManager.isBoss){ // if is boss then create snkke body 
                                [self createSnakeParts:point withImageName:self.snakeBodyImage]; // creating pellets 
                                [DataManager.gameLayer.multiplayerManager createSnakeStativBody:point];
                            }
                            else
                            {   // else send a msg to boss to create body 
                                [DataManager.gameLayer.multiplayerManager createSnakeStativBody:point];
                            }
                            [DataManager.gameLayer.multiplayerManager removeStaticBodyFromOtherDevice:snakeBody.tag];
                            
                        }   // creating pellets in normal play 
                        else
                        {
                            [self createSnakeParts:point withImageName:self.snakeBodyImage]; // creating pellets 
                        }
                    }
                }
                
                else {  
                    
                    CGPoint point=[self checkRandomPositionWithObstaclePosition];    // to check with obstacle position so that pellets not posiiton of obstacles
                    [self createSnakeParts:point withImageName:self.snakeBodyImage];
                }
                
                DataManager.scores+=100;
                if(DataManager.gameMode==1 ||DataManager.gameMode==0){  // for challenge mode increment no of parst 
                    DataManager.noOfParts++;    
                }
                else {
                    DataManager.noOfParts--;    // decrements no of parts in arcade mode 
                    
                }
                [self addingtoSnakeHead];         // add one pellets to snake tail after collision 
                [self.toDeleteArray addObject:snakeBody];  // add collide snake body(pellet to delete array 
                
                break;
            }
        }
    }
    
}



//check collision with bonus
-(void)checkCollisionWithBonus{
    SXSnake *snakeHead=(SXSnake*)[movableObjects objectAtIndex:0];
    
    CGRect headRect = CGRectMake(snakeHead.position.x-snakeHead.contentSize.width/2, snakeHead.position.y-snakeHead.contentSize.height/2, snakeHead.contentSize.width/2, snakeHead.contentSize.height/2);
    
    for (SXCustomSprite *aSprite in self.staticObjects) 
    {
        //checking collision with SnakeHead and Bonus
        if([aSprite isKindOfClass:[SXBonus class]]) 
        {
            
            SXBonus *aBonus = (SXBonus *)aSprite;
            
            CGRect bon=  CGRectMake(aBonus.position.x-aBonus.contentSize.width/2, aBonus.position.y-aBonus.contentSize.height/2, aBonus.contentSize.width/2, aBonus.contentSize.height/2);
            
            
            if(CGRectIntersectsRect(headRect, bon))//condition for head  collision with bonus  
            {
                switch (aBonus.type) {
                    case kBonus1:                                                         //shield bonus
                        [(SXSnake*) [movableObjects objectAtIndex:0]setShieldEffect];
                        snakeHead.isShieldOn=YES;  
                        DataManager.scores+=200;
                        DataManager.bonus+=200;
                        DataManager.nOOfBonusCollected++;
                        [DataManager.gameLayer.multiplayerManager setShieldEffectToOtherDeviceSnake:snakeHead.tag];
                        
                        break;
                        
                    case kBonus2:                                                          //speed up bonus
                        //DataManager.snakeSpeed=DataManager.snakeSpeed+1;
                        if(DataManager.snakeSpeed>10)
                        {
                            DataManager.snakeSpeed=10;
                        }
                        break;                   
                    case kBonus3:                                                        //speed down bonus
                        //DataManager.snakeSpeed=DataManager.snakeSpeed-1;
                        if(DataManager.snakeSpeed<=1)
                        {
                            DataManager.snakeSpeed=2;
                        }
                        break;                   
                        
                        
                    case kBonus6:                                                         // life bonus
                        [DataManager.gameLayer addBonusLife];
                        DataManager.scores+=200;
                        DataManager.bonus+=200;
                        DataManager.nOOfBonusCollected++;
                        DataManager.noOfLifeBonusCollected++;
                        
                        break;   
                        
                    case kBonus7:                                                       // skull bonus
                        [self redirectSnakeWithPoint:CGPointMake(160, 240)];
                        [self CheckRotation];
                        break;
                        
                    default:                                                           //other bonuses 
                        DataManager.bonus+=200;
                        DataManager.scores+=200;
                        DataManager.nOOfBonusCollected++;
                        
                        
                        break;
                }
                
                [self.toDeleteArray addObject:aBonus]; 
                
                [DataManager.gameLayer.multiplayerManager  DeleteBonusFromOtherDeivce];
                
                // adding bonus to delete array 
                break;
            }
            
        }
    }
}


// cheking for rotation
-(void)CheckRotation{
    SXSnake *snake=(SXSnake *)[movableObjects objectAtIndex:0];
    
    float  angleDiff;
    
    if(currentAngle>mRotateAngle)
        angleDiff=currentAngle-mRotateAngle;
    else
        angleDiff=mRotateAngle-currentAngle;
    
    
    float frontAngle = (360-snake.rotation)+mRotateAngle;
    frontAngle = (int)frontAngle % 360;
    float reverseAngle=360-frontAngle;
    
    if(frontAngle<reverseAngle)                                          // checking whether to turn snake left or right 
    {
        isLeftTurn=FALSE;
    }
    else
    {
        isLeftTurn=YES;
    }
    
    float distance1=ccpDistance(snake.position, mTappedPoint);             // for minimum distance  
    
    if(distance1<35)     
    {
        kRotatingFactor=40;                          //kFactor in minimum  decrement/increment in rotation angle   depend on left r right rotatiom 
    }
    else
    {
        kRotatingFactor=20;
    }
    
}



#pragma mark-checking random Position 
-(CGPoint)checkRandomPositionWithObstaclePosition
{
    CGPoint point=[SXUtility getRandomPoint];
    for(int i=0;i<[self.obstacleArray count];i++) 
    {
        CGRect obstacleRect= CGRectFromString([self.obstacleArray objectAtIndex:i] );
        
        if( CGRectContainsPoint(obstacleRect, point)) // checking random position with the obstacles posiiton 
        {
            point=  [SXUtility getRandomPoint];
            [self checkRandomPositionWithObstaclePosition];
        }
    }
    
    
    return point;
}


#pragma mark - Touch

//Handling touches
- (void)handleTap:(NSSet*)touches withEvent:(UIEvent*)event
{
    
    
    
    
    
    DataManager.firstTap=YES;
    
    
    
    UITouch *touch=[touches anyObject];
    CGPoint location=[touch locationInView:[touch view]];
    location=[[CCDirector sharedDirector]convertToGL:location];
    mTappedPoint=location;  
    
    SXSnake *snake=(SXSnake *)[movableObjects objectAtIndex:0];
    mRotateAngle=[SXUtility getAngleFromCurrentPoint:snake.position toPoint:mTappedPoint];// getting angle from Snake position to tapped p;osition
    
    
    
    
    
    CGPoint loc=[snake convertToNodeSpace:mTappedPoint];
    
    
    if(CGPathContainsPoint(headPath, NULL, loc, NO))     // if tapped position is on  Snake head
    {
        mAngleChanged=NO;
    }
    
    
    else
        mAngleChanged=YES;
    
    [self  CheckRotation]; // checking for snake Rotation  whether to right or left rotation
}


//dealloc 
-(void)dealloc 
{
    NSLog(@" snake mamanger dealloc");
    self.movableObjects=nil;
    self.staticObjects=nil;
    self.pathArray=nil;
    self.obstacles=nil;
    self.obstacleArray=nil;
    self.toDeleteArray=nil;
    self.transferArray=nil;
    self.shieldImage=nil;
    self.snakeHeadImage=nil;
    self.snakeDullImage=nil;
    self.snakeBodyImage=nil;
    self.leveldetails=nil;
    self.NonBossSnakePathArray=nil;
    self.BossSnakePathArray=nil;
    joystickBase=nil;
    [joystickBase release];
    [super dealloc];
}

@end
