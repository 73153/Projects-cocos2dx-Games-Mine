//
//  LegendaryGameScene.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 6/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXLegendaryGameScene.h"

@implementation SXLegendaryGameScene
+(id)scene{
    CCScene *scene=[CCScene node];
    SXLegendaryGameScene *layer=[SXLegendaryGameScene node];
    [scene addChild:layer];
    return scene;
    
}

-(id)init{
    if((self=[super init])){
        CCSprite *sprite=[CCSprite spriteWithFile:@"top_menu_02.png"];
        [self addChild:sprite];
        sprite.position=ccp(240, 305);
        
        CCMenuItemImage *optionButtonItem=[CCMenuItemImage itemFromNormalImage:@"option_Button_01.png" selectedImage:@"option_Button_02.png" target:self selector:@selector(optionButtonAction)];
        CCMenu *option=[CCMenu menuWithItems:optionButtonItem, nil];
        [self addChild:option];
        option.position=ccp(20, 305);
        

    }
        
    return self;
    
}
@end
