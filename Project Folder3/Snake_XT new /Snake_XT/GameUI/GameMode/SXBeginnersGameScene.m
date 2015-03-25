//
//  BeginnersGameScene.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 6/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXBeginnersGameScene.h"
#import "SXOptionScene.h"
#import "SXOtherAppScene.h"
#import "SXGameModeMenuScene.h"
#import "SXMainMenu.h"
@implementation SXBeginnersGameScene
+(id)scene{
    CCScene *scene=[CCScene node];
    SXBeginnersGameScene *layer=[SXBeginnersGameScene node];
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
        
    Scorebg=[CCSprite spriteWithFile:@"scoreBG.png"];
        [self addChild:Scorebg z:1];
        Scorebg.position=ccp(90, 305);
        
        scoreLabel=[CCLabelTTF labelWithString:@"0" fontName:@"Arial" fontSize:15];
        [scoreLabel setColor:ccc3(255, 255, 255)];
        
        [self addChild:scoreLabel z:1];
        scoreLabel.position=ccp(90, 305);
        
        mBodyPartCounter=[CCLabelTTF labelWithString:@"00" fontName:@"Arial" fontSize:15];
        
        mBodyPartCounter.position=ccp(250, 300 );
        [self addChild:mBodyPartCounter];
        
        pauseButton=[CCMenuItemImage itemFromNormalImage:@"Pause_01.png" selectedImage:@"Pause_02.png" target:self selector:@selector(PauseButtonAction)];
        CCMenu *pauseMenu=[CCMenu menuWithItems:pauseButton, nil];
        
        [self addChild:pauseMenu];
        pauseMenu.position=ccp(465, 305);
        CCSprite *lifeBG=[CCSprite spriteWithFile:@"lifeBG.png"];
        [self addChild:lifeBG];
        lifeBG.position=ccp(375, 305);
        
        int x=350;
        int y=305;
        
        for(int i=0;i<5;i++){
            CCSprite *lifefull=[CCSprite spriteWithFile:@"life_full.png"];
            [self addChild:lifefull];
            lifefull.position=ccp(x, y);
            [lifefullArray addObject:lifefull];
            x=x+13;
        }

        self.isTouchEnabled=YES;
        [[CCTouchDispatcher sharedDispatcher]addTargetedDelegate:self priority:1 swallowsTouches:YES];
        
        
    }
    return self;
    
}

-(void)optionButtonAction{


    //[[CCDirector sharedDirector ]replaceScene:[CCTransitionMoveInR transitionWithDuration:.5 scene: [SXGameOptionMenuScene scene]]];
    
}
-(void)PauseButtonAction
{
    
    if(isGamePaused==NO)
    {
        isGamePaused=YES;
        [ self removeChild:pauseButton cleanup:YES];
        
        
        [[CCDirector sharedDirector]pause];
        
        playButton=[CCMenuItemImage itemFromNormalImage:@"Play_01.png" selectedImage:@"Play_02.png" target:self selector:@selector(PlayButtonAction)];
        playMenu=[CCMenu menuWithItems:playButton, nil];
        
        [self addChild:playMenu];
        playMenu.position=ccp(465, 305);
        
        
    }
    
}



-(void) PlayButtonAction{
    
    isGamePaused=NO;
    
    
    [self removeChild:playButton cleanup:YES];
    
    CCMenuItemImage *playItem=[CCMenuItemImage itemFromNormalImage:@"Pause_01.png" selectedImage:@"Pause_02.png" target:self selector:@selector(PauseButtonAction)];
    playMenu=[CCMenu menuWithItems:playItem, nil];
    
    [self addChild:playMenu];
    playMenu.position=ccp(465, 305);
    
    [[CCDirector sharedDirector] resume];
}
    

@end
