//
//  GameCompleted.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 6/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXGameCompleted.h"

@implementation SXGameCompleted

-(id)init{
    if((self=[super init])){
        CCSprite *totalScore=[CCSprite spriteWithFile:@"game_finished_display.png"];
        [self addChild:totalScore];
        totalScore.position=ccp(240, 160);
        
        
        
        CCSprite *congrats=[CCSprite spriteWithFile:@"Congratulations.png"];
        [self addChild:congrats];
        congrats.position=ccp(100, 100);
                            
    }
    return self;
}
@end
