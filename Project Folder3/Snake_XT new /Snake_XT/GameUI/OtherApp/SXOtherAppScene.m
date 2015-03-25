//
//  OtherAppScene.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXOtherAppScene.h"
#import "SXMainMenu.h"
#import "SXGameOptionMenuScene.h"

@implementation SXOtherAppScene

+(id)scene{
    CCScene *scene=[CCScene node];
    SXOtherAppScene *layer=[SXOtherAppScene node];
    [scene addChild:layer];
    return scene;
    
    
}

-(id)init{
    if((self=[super init])){

        
      otherAppBG=[CCSprite spriteWithFile:@"bg.png"];
        [self addChild:otherAppBG];
        otherAppBG.position=ccp(240, 160);
        // back  menu 
        CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt.png"];
        CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt_hvr.png"];
        
        
        CCMenuItemSprite *backMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goBackAction)];
        CCMenu *backMenu=[CCMenu menuWithItems:backMenuItem, nil];
        backMenu.position=ccp(60, 278);
        [self addChild:backMenu z:2];

        
        CCSprite *customizeLabel=[CCSprite spriteWithSpriteFrameName:@"label_moreapps.png"];
        [self addChild:customizeLabel];
        customizeLabel.position=ccp(240, 278);
    }
    return  self;
}



-(void)goBackAction
{
    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInL transitionWithDuration:.5 scene:[SXMainMenu scene]]];
}

-(BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event
{
    CCSprite *sprite=[CCSprite spriteWithFile:@"menu_selection.png"];
    
    CGPoint touchlocation=[touch locationInView:[touch view]];
    
    touchlocation=[[CCDirector sharedDirector] convertToGL:touchlocation];
    int miny;
    int maxy;
   
    
    for( miny=200,maxy=220;miny>=120;miny=miny-40,maxy=maxy-40){
        
        int index=touchlocation.y/40;
        if(( touchlocation.y>miny && touchlocation.y<maxy) && (touchlocation.x>=280 && touchlocation.x<390))
        {
            [self addChild:sprite];
            
            sprite.position=ccp(325, miny+10);
            switch (index) {
                case 5:
                    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://itunes.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=310063886&mt=8"]];
                                       break;
                case 4: 
                    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://itunes.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=298824426&mt=8"]];
                    
                    
                    break;
                    
                case 3:

                    if([SXDataManager sharedManager].isAppInsidesideGameScene==NO)
                        
                    {
                        
                      [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInL transitionWithDuration:.5 scene:[SXMainMenu scene]]];
                    }
                    else
                    {
                        [otherAppBG runAction:[CCMoveTo actionWithDuration:.5 position:ccp(400, 160 )]] ;
                                                                                                

                        
                        [[CCDirector sharedDirector]replaceScene:[CCTransitionMoveInR transitionWithDuration:.5 scene:[SXGameOptionMenuScene scene]]];
                        
                    }
                    
                    break;
                    
                    
                default:
                    break;
            }
            
        
            
        }
    }
    return YES;
    
}
#pragma  mark- dealloc
-(void)dealloc{
    [self removeAllChildrenWithCleanup:YES];
    [super dealloc];
}

@end
