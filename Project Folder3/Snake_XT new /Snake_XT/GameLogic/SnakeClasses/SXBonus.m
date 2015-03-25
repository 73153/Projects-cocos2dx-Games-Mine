
//
//  SXBonus.m
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/12/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SXBonus.h"
#import "SXDataManager.h"


@implementation SXBonus
@synthesize snManager,type,glowImage;
- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here
    }
    
    return self;
}

//dealloc 
-(void) dealloc {
    
    self.glowImage=nil;
    [super dealloc];
}

-(void)setShieldGlowEffect
{       
    CCSprite *snakeHit=[CCSprite spriteWithSpriteFrameName:self.glowImage];
    snakeHit.position=ccp(self.contentSize.width/2,self.contentSize.height/2);
    [self addChild:snakeHit z:-4];
    
    id scaleIn = [CCScaleTo actionWithDuration:0.5 scale:1];
    id scaleOut = [CCScaleTo actionWithDuration:0.5 scale:0.5];
    id actionSeq = [CCSequence actions:scaleIn,scaleOut, nil];
    id actionRepeat = [CCRepeatForever actionWithAction:actionSeq];
    [snakeHit runAction:actionRepeat];
    
    
}

-(void)addingBonus:(CGPoint)position withLayer:(SXMainController*)layer withManager:(SXSnakeManager*)manager type:(int)bonusType{
    
        self.gameLayer=layer; 
        self.position=position;
        self.type=bonusType;
        [DataManager.gameLayer addChild:self z:4];
        id delayAction = [CCDelayTime actionWithDuration:5];

        id blockAction = [CCCallBlockN actionWithBlock:^(CCNode* node){ [self removeFromParentAndCleanup:YES]; }];
    
        id sequence = [CCSequence actions:delayAction,blockAction, nil];
        [self runAction: [CCSequence actions:sequence,[CCCallFunc actionWithTarget:self selector:@selector(removingBonus)],nil]];

}


-(void)removingBonus
{
    [SXMainLayer.snakeManager.toDeleteArray addObject:self];
}

@end
