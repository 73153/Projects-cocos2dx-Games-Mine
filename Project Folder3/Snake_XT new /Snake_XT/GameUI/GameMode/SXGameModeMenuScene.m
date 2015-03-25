//
//  GameModeMenuScene.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#import "SXMainMenu.h"
#import "SXGameModeMenuScene.h"
#import "SXArcadeScene.h"
#import "SXGameOptionMenuScene.h"
#import "SXMainController.h"
#import "SXAppDelegate.h"
@implementation SXGameModeMenuScene
+(id)scene{
    CCScene *scene=[CCScene node];
    SXGameModeMenuScene *layer=[SXGameModeMenuScene node];
    [scene addChild:layer];
    return scene;
}
-(id)init{
    if((self=[super init])){
       
        CCSprite *bgSprite=[CCSprite spriteWithFile:@"Main_bg.png"];
        [self addChild:bgSprite];
        bgSprite.position=ccp(240, 160);
        
        //aqdding  new game frame 
        CCSprite *newGameFrame=[CCSprite spriteWithSpriteFrameName:@"new_game_frame.png"];
        newGameFrame.position=ccp(340, 160);
        [self addChild:newGameFrame];
        
        CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"arcade.png"];
        CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"arcade_hvr.png"];
        
        /// new  game menu item 
        CCMenuItemSprite *arcadeItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goT0ArcadeScene)];
        arcadeItem.position=ccp(345, 200);

        
        /// new  game menu item 
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"survival.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"survival_hvr.png"];
        CCMenuItemSprite *survivalItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToSurvivalScene)];
        survivalItem.position=ccp(345, 160);
        
        
        // main menu item 
        
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"back.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"back_hvr.png"];
        CCMenuItemSprite *mainMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToMainScene)];
        mainMenuItem.position=ccp(345, 115);
        
        
        CCMenu *gameModeMenu=[CCMenu menuWithItems:arcadeItem,survivalItem,mainMenuItem, nil];
        [self addChild:gameModeMenu];
        gameModeMenu.position=CGPointZero;
        
        
        
        
       

    }
    return self;
}

-(void)goT0ArcadeScene{
        [[CCDirector sharedDirector]replaceScene:[ CCTransitionFlipY transitionWithDuration:.5 scene:[SXArcadeScene scene] orientation:kOrientationDownOver]];   

        DataManager.isNewArcadeGame=YES;
        DataManager.gameMode=KARCADEMODE;
       

    
}

-(void)goToMainScene{
    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInL transitionWithDuration:.5 scene:[SXMainMenu scene]]];

}
-(void)goToSurvivalScene{
    DataManager.gameMode=kBEGINNERMODE;
       [[CCDirector sharedDirector]replaceScene:[ CCTransitionFlipY transitionWithDuration:.5 scene:[SXMainController scene] orientation:kOrientationDownOver]];
}

#pragma  mark- dealloc
-(void)dealloc{
    
    [self removeAllChildrenWithCleanup:YES];
    [super dealloc];
}
@end
