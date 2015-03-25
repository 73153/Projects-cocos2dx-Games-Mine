//
//  SXSnakeBody.h
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SXCustomSprite.h"
#import"cocos2d.h"
#import"SXMainController.h"
#import"SXSnakeManager.h"
#import "SXSnake.h"

@interface SXSnakeStaticBody : SXCustomSprite {

    SXSnakeManager *snManager;
    CGMutablePathRef BodyPath;
    
}
@property(nonatomic,assign)SXSnakeManager *snManager;
@property(nonatomic)CGMutablePathRef BodyPath;
@property(nonatomic,retain)NSString *staticBodyANme;


-(void)addingSnakePart:(CGPoint)position withLayer:(SXMainController*)layer withManager:(SXSnakeManager*)manager;
-(BOOL)isCollission:(SXSnake *)otherActor;
@end
