//
//  SXObstacle.m
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/12/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SXObstacle.h"


@implementation SXObstacle
@synthesize snManager,isRunningAnimation,type,pointsArray,ObstacleImageName;
- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here
        
        
    }
    
    return self;
}



-(void)addingObstacles:(CGPoint)position withLayer:(SXMainController*)layer withManager:(SXSnakeManager*)manager{
    self.gameLayer=layer;
    self.position=position;
    [self.gameLayer addChild:self z:4];
    [self setOpacity:0];
    
    id fadeIn = [CCFadeIn actionWithDuration:0.2];
    id delayAction = [CCDelayTime actionWithDuration:4];
    id fadeAction = [CCFadeOut actionWithDuration:0.5];
    id blockAction = [CCCallBlockN actionWithBlock:^(CCNode* node){ [self removeFromParentAndCleanup:YES];[self.gameLayer.snakeManager.obstacles removeObject:self]; }];
    id sequence = [CCSequence actions:fadeIn,delayAction,fadeAction,blockAction, nil];
    [self runAction:sequence];
    
    
}

-(void)setObstacleGlowEffect
{        CCSprite *snakeHit=[CCSprite spriteWithSpriteFrameName:@"bonus7_Glow.png"];
        snakeHit.position=ccp(self.contentSize.width/2,self.contentSize.height/2);
        [self addChild:snakeHit z:-4];
        
        id scaleIn = [CCScaleTo actionWithDuration:0.5 scale:1];
        id scaleOut = [CCScaleTo actionWithDuration:0.5 scale:0.5];
        id actionSeq = [CCSequence actions:scaleIn,scaleOut, nil];
        id actionRepeat = [CCRepeatForever actionWithAction:actionSeq];
        [snakeHit runAction:actionRepeat];
  }
-(void) dealloc {
    self.pointsArray=nil;
    [self.ObstacleImageName release];
    
    [super dealloc];
}

@end
