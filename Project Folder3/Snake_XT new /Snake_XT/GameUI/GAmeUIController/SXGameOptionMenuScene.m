//
//  GameOptionMenuScene.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 6/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXOptionScene.h"
#import "SXOtherAppScene.h"
#import "SXGameModeMenuScene.h"
#import "SXMainMenu.h"
#import "SXGameScene.h"
#import "SXDataManager.h"
#import "SXMainController.h"
#import "SXGameConstants.h"
#import "SXArcadeScene.h"

@implementation SXGameOptionMenuScene
+(id)scene{
    
    CCScene *Scene=[CCScene node];
    SXGameOptionMenuScene *Layer=[SXGameOptionMenuScene node];
    [Scene addChild:Layer];
    return Scene;
}

-(id)init{
    if((self=[super init])){
        DataManager.isLevelFailed=NO;
        gameOptionmodeBG=[CCSprite spriteWithFile:@"trsprnt_bg.png"];
        [self addChild:gameOptionmodeBG];
        gameOptionmodeBG.position=ccp(240, 160);
        
        CCSprite *resumeBg=[CCSprite spriteWithFile:@"Resume_game.png"];
        [self addChild:resumeBg];
        resumeBg.position=ccp(240, 160);
        
        
        CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"menu_bt.png"];
        CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"menu_bt_hvr.png"];
        CCMenuItemSprite *mainMebnuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToMainMenu)];
        mainMebnuItem.position=ccp(90, 228);
        
        
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"play.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"play.png"];
        
        
        CCMenuItemSprite *playMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(resumeAction)];
        playMenuItem.position=ccp(170, 150);
        
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"replay.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"replay_hvr.png"];
        CCMenuItemSprite *restartMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(resumeAction)];
        restartMenuItem.position=ccp(230, 150);

        
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"levelMenu.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"levelMenu_hvr.png"];
        CCMenuItemSprite *levelMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToLevels)];
        levelMenuItem.position=ccp(290, 150);
        
        CCMenu *menu=[CCMenu menuWithItems:mainMebnuItem,playMenuItem,restartMenuItem,levelMenuItem, nil];
        [self addChild:menu];
        menu.position=CGPointZero;
     }
    return self;
    
}

//Resume button action
-(void)resumeAction
{
    
    [[CCDirector sharedDirector] popScene];
    DataManager.isResumeMode=YES;
    //DataManager.firstTap=NO;
    [[CCDirector  sharedDirector]pause];

   }


//Restart Buttons Action
-(void)restartAction{
    
     [[CCDirector sharedDirector]replaceScene:[CCTransitionFade transitionWithDuration:.5 scene: [SXMainController scene]]];

}

-(void)goToMainMenu{
    
}

-(void)goToLevels{
    
    [[CCDirector sharedDirector]replaceScene:[SXArcadeScene scene]];
}

#pragma  mark- dealloc
-(void)dealloc{
    NSLog(@"dealloc");
    [self removeAllChildrenWithCleanup:YES];
    [super dealloc];
}




@end


