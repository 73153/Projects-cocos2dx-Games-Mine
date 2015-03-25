//
//  SXSnake.h
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SXCustomSprite.h"
#import "SXSnakeManager.h"
#import "SXObstacle.h"


@interface SXSnake : SXCustomSprite {
    SXSnakeManager *sn;
    BOOL isRunningAnimation;
    BOOL isShieldOn;
    BOOL isInSafeMode;
    NSMutableArray *pointArray;
    CGMutablePathRef headPath;
}
@property(nonatomic,assign)SXSnakeManager *sn;
@property(nonatomic,assign)BOOL isRunningAnimation;
@property(nonatomic,assign)BOOL isShieldOn;
@property(nonatomic,assign)BOOL isInSafeMode;
@property(nonatomic)CGRect shieldRect;
@property(nonatomic,retain)NSMutableArray *pointArray;
@property(nonatomic,assign)CGMutablePathRef headPath;
@property(nonatomic,retain)NSMutableArray *CGPathCoordinatesArray;



-(void)addingSnakePart:(CGPoint)position withLayer:(SXMainController*)layer withManager:(SXSnakeManager*)manager;

-(void)addingSnakePart:(CGPoint)position withLayer:(SXMainController *)layer withManager:(SXSnakeManager *)manager withPointsArray:(NSArray *)pointsArray withCGPathPointsArray:(NSArray *)CGPathArray;



-(void)setHitEffect;
-(void)setShieldEffect;
-(void)removeShieldEffect;
-(BOOL)IscollideWithObstacle:(SXObstacle *)obstacle;



@end
