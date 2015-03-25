//
//  SXSnake.m
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SXSnake.h"
#import "SXDataManager.h"
@implementation SXSnake 
@synthesize sn,isRunningAnimation,isShieldOn,isInSafeMode,shieldRect,pointArray,headPath,CGPathCoordinatesArray;

- (id)init
{
    self = [super init];
    if (self)
    {
        
       
    }
    
    return self;
}




-(void)addingSnakePart:(CGPoint)position withLayer:(SXMainController*)layer withManager:(SXSnakeManager*)manager
{  
    DataManager.gameLayer = layer;
    self.position = position;
    [DataManager.gameLayer addChild:self z:5];
    self.isRunningAnimation = false;
    self.isInSafeMode = false;
}

//creating snake head 

-(void)addingSnakePart:(CGPoint)position withLayer:(SXMainController *)layer withManager:(SXSnakeManager *)manager withPointsArray:(NSArray *)pointsArray withCGPathPointsArray:(NSArray *)CGPathArray
{
    //self.gameLayer = layer;
    self.position = position;
    [DataManager.gameLayer addChild:self z:5];
    self.isRunningAnimation = false;
    self.isInSafeMode = false;
    
    if(!DataManager.IsLoadingGame)
    {
        // adding points to points array .................
        NSMutableArray *tempArray=[[NSMutableArray alloc]init];
        for(int i=0;i<[pointsArray count];i++)
        { 
            CGPoint pos=CGPointFromString([pointsArray objectAtIndex:i]);
            
            NSValue *value=[NSValue valueWithCGPoint:pos];
            [tempArray addObject:value];
        }
        
        self.pointArray=[[NSMutableArray alloc]initWithArray:tempArray]; // points array used for check collision with static objects 
        [tempArray release];
        
        headPath=CGPathCreateMutable();
        
        
        self.CGPathCoordinatesArray=[[NSMutableArray alloc]initWithArray:CGPathArray]; // cgpath array is used for check collision with obstacles
        
        CGPathMoveToPoint(headPath, NULL, [[CGPathArray objectAtIndex:0]intValue], [[CGPathArray objectAtIndex:1]intValue]);      //adding points to head path
        
        
        for(int i=2;i<[CGPathArray count]-1;i=i+2)
        {
            
            CGPathAddLineToPoint(headPath, NULL, [[CGPathArray objectAtIndex:i] intValue], [[CGPathArray objectAtIndex:i + 1] intValue]);
        }
        
        CGPathCloseSubpath(headPath); 
    }
    else
    {
        self.pointArray= [[NSMutableArray alloc]initWithArray:pointsArray];
        self.CGPathCoordinatesArray=[[NSMutableArray alloc]initWithArray:CGPathArray];
        
        
    }
}




-(void)setHitEffect  // hit feect 
{
    if(!self.isRunningAnimation)
    {
        
        
        self.isRunningAnimation = TRUE;
        self.isInSafeMode = false;

        
        [self setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:DataManager.gameLayer.snakeManager.snakeDullImage]];
        
         CCSprite * snakeHit=[CCSprite spriteWithSpriteFrameName:@"level_hit_.png"];
        snakeHit.position=ccp(self.contentSize.width/2,self.contentSize.height/2);
        [self addChild:snakeHit];
        
        id rotate1 = [CCRotateTo actionWithDuration:0.5 angle:snakeHit.rotation+180];
        id rotate2 = [CCRotateTo actionWithDuration:0.5 angle:snakeHit.rotation+360];
        id actionSeq = [CCSequence actions:rotate1,rotate2, nil];
        id actionRepeat = [CCRepeatForever actionWithAction:actionSeq];
        [snakeHit runAction:actionRepeat];
        
        id delayAction = [CCDelayTime actionWithDuration:1.5];
        id blockAction = [CCCallBlockN actionWithBlock:^(CCNode* node){ [snakeHit removeFromParentAndCleanup:YES],self.isRunningAnimation = FALSE,[self setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:DataManager.gameLayer.snakeManager.snakeHeadImage]];; }];
        id sequence = [CCSequence actions:delayAction,blockAction, nil];
        [snakeHit runAction:sequence];
        [DataManager.gameLayer updateLifeArray];
        DataManager.numOfLifeLost++;
        [DataManager.gameLayer.multiplayerManager setHitEffectToOtherD3eviceSnake:self.tag ];

    }
}


-(void)setShieldEffect // set Shield effect 
{
    self.isShieldOn=YES;
    [self setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:DataManager.gameLayer.snakeManager.snakeHeadImage]];
    
    CCSprite *snakeHit=[CCSprite spriteWithSpriteFrameName:DataManager.gameLayer.snakeManager.shieldImage];
    snakeHit.position=ccp(self.contentSize.width/2,self.contentSize.height/2);
    [self addChild:snakeHit z:0 tag:1];
    
    self.shieldRect=CGRectMake(snakeHit.position.x-snakeHit.contentSize.width/2, snakeHit.position.y-snakeHit.contentSize.height/2, snakeHit.contentSize.width/2, snakeHit.contentSize.height/2);
    
      
    id delayAction = [CCDelayTime actionWithDuration:6];
    id blockAction = [CCCallBlockN actionWithBlock:^(CCNode* node){ [snakeHit removeFromParentAndCleanup:YES],self.isRunningAnimation = FALSE,[self setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:DataManager.gameLayer.snakeManager.snakeHeadImage]];; }];
    id sequence = [CCSequence actions:delayAction,blockAction, nil];
    [snakeHit runAction:sequence];
    
}


-(void)removeShieldEffect  // removing shield once it obstacles when having shield on its head
{   
    self.isInSafeMode = TRUE;
    self.isShieldOn=NO;
    [self removeChildByTag:1 cleanup:YES]; // removing sheild sprite 
    
    
    id delayAction = [CCDelayTime actionWithDuration:1.5];
    id blockAction = [CCCallBlockN actionWithBlock:^(CCNode* node){ [self setIsInSafeMode:FALSE];}]; 
    id sequence = [CCSequence actions:delayAction,blockAction, nil];
    [self runAction:sequence];
    NSLog(@"snake tag=%d",self.tag);
    [DataManager.gameLayer.multiplayerManager removeShielsFromotherDevice:self.tag];
    
}


-(void)setSafeModeOff 
{
    
    [[CCScheduler sharedScheduler] unscheduleSelector:@selector(setSafeModeOff) forTarget:self];
    self.isInSafeMode = FALSE;
    
}

-(BOOL)IscollideWithObstacle:(SXObstacle *)obstacle{
     
    
    NSArray *obstaclesPointsString=obstacle.pointsArray;
    
    BOOL isCollided = FALSE;
    NSMutableArray *array=[[NSMutableArray alloc]init];
    for(int i=0;i<[obstaclesPointsString count];i++)
    { 
        CGPoint pos=CGPointFromString([obstaclesPointsString objectAtIndex:i]);
        
        NSValue *value=[NSValue valueWithCGPoint:pos];
        

        [array addObject:value];
        

    }
   
    for (int i=0; i<[array count];i++) 
    {
        CGPoint loc=[[array objectAtIndex:i] CGPointValue];  
        loc=[obstacle convertToWorldSpace:loc];
        loc=[self convertToNodeSpace:loc];

        
        
        if(CGPathContainsPoint(headPath, NULL, loc, NO))
        {
            isCollided=YES;
            //[(SXSnake*) [movableObjects objectAtIndex:0]setHitEffect];
        }
    }

    
    return isCollided;
    [array release];
    
}


-(void) dealloc 
{
    [pointArray release];
    [CGPathCoordinatesArray release];
    [super dealloc];
}
@end
