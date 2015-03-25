//
//  SXSnakeBody.m
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SXSnakeStaticBody.h"
#import "SXSnake.h"
#import "SXDataManager.h"

@implementation SXSnakeStaticBody
@synthesize snManager,BodyPath,staticBodyANme;

- (id)init
{
    self = [super init];
    if (self) {
        
        self.BodyPath=CGPathCreateMutable();
        CGPathMoveToPoint(BodyPath, NULL, 10, 3);
        CGPathAddLineToPoint(BodyPath, NULL, 20, 3);
        CGPathAddLineToPoint(BodyPath, NULL, 24, 9);
        
        CGPathAddLineToPoint(BodyPath, NULL, 24, 16);
        CGPathAddLineToPoint(BodyPath, NULL, 19, 23);
        
        CGPathAddLineToPoint(BodyPath, NULL, 10, 23);
        
        CGPathAddLineToPoint(BodyPath, NULL,4, 17);
        CGPathAddLineToPoint(BodyPath, NULL,4, 10);
        CGPathCloseSubpath(BodyPath);
        
        //10,3,18,3,24,9,24,16,19,23,10,23,4,17,4,10
        
      }
    
    return self;
}

-(void)addingSnakePart:(CGPoint)position withLayer:(SXMainController*)layer withManager:(SXSnakeManager*)manager {
    
    self.gameLayer = layer;
    self.position = position;
    [DataManager.gameLayer addChild:self z:4];
}

-(BOOL)isCollission:(SXSnake *)otherActor {
    // check if any point of otherActor is inside my path 
    BOOL isCollided = FALSE;
    
       NSMutableArray *points=otherActor.pointArray;   
    //NSLog(@" points array=%@",points);
    for (int i=0; i<[points count]; i++) {
        CGPoint loc=[[points objectAtIndex:i] CGPointValue];       
        loc=[otherActor convertToWorldSpace:loc];
        loc=[self convertToNodeSpace:loc];
        if (CGPathContainsPoint(BodyPath, NULL, loc, NO)) {
            
            //return i;
            isCollided = TRUE;
            break;
        }
        else
            isCollided = FALSE;
    }
    return isCollided;
}



-(void)dealloc 
{
  
    CGPathRelease(BodyPath);
    self.staticBodyANme=nil;
    [super dealloc];
}



@end
