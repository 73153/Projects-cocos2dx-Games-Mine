//
//  SXObstacle.h
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/12/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SXCustomSprite.h"
#import "SXSnakeManager.h"
@interface SXObstacle : SXCustomSprite 
{
    SXSnakeManager *snManager; 
    BOOL isRunningAnimation;
    int type;
    NSArray *pointsArray;
}
@property(nonatomic,assign)SXSnakeManager *snManager;
@property(nonatomic,assign)int type;
@property(nonatomic,retain)NSArray *pointsArray;
@property(nonatomic,retain)NSString *ObstacleImageName;

@property(nonatomic,assign)BOOL isRunningAnimation;
-(void)addingObstacles:(CGPoint)position withLayer:(SXMainController*)layer withManager:(SXSnakeManager*)manager;
-(void)setObstacleGlowEffect;
@end
