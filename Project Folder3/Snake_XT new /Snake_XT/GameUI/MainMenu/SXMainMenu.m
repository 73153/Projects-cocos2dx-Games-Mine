//
//  HelloWorldLayer.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/28/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//


// Import the interfaces
#import "SXMainMenu.h"

#import "SXAppDelegate.h"
#import "RootViewController.h"

#import "SXMainController.h"
#import "SXOptionScene.h"
#import "SXHelpScene.h"
#import "SXOtherAppScene.h"
#import "SXShare.h"
#import "SXGameModeMenuScene.h"

#import "GCHelper.h"

#import "SXGameConstants.h"


@implementation SXMainMenu
#pragma mark-scene

+(CCScene *) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	SXMainMenu *layer = [SXMainMenu node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

- (void)setGameState:(GameState)state {
    
    gameState = state;
    if (gameState == kGameStateWaitingForMatch) {
        [debugLabel setString:@"Waiting for match"];
    } else if (gameState == kGameStateWaitingForRandomNumber) {
        [debugLabel setString:@"Waiting for rand #"];
    } else if (gameState == kGameStateWaitingForStart) {
        [debugLabel setString:@"Waiting for start"];
    } else if (gameState == kGameStateActive) {
        [debugLabel setString:@"Active"];
    } else if (gameState == kGameStateDone) {
        [debugLabel setString:@"Done"];
    } 
    
}

- (void)sendData:(NSData *)data {
    NSError *error;
    BOOL success = [[GCHelper sharedInstance].match sendDataToAllPlayers:data withDataMode:GKMatchSendDataReliable error:&error];
    if (!success) {
        CCLOG(@"Error sending init packet");
        //[self matchEnded];
    }
}

- (void)sendRandomNumber 
{
    MessageRandomNumber message;
    message.message.messageType = kMessageTypeRandomNumber;
    message.randomNumber = ourRandom;
    NSData *data = [NSData dataWithBytes:&message length:sizeof(MessageRandomNumber)];    
    [self sendData:data];
}

- (void)sendGameBegin
{
    MessageGameBegin message;
    message.message.messageType = kMessageTypeGameBegin;
    NSData *data = [NSData dataWithBytes:&message length:sizeof(MessageGameBegin)];    
    [self sendData:data];
}

- (void)sendMove
{
    MessageMove message;
    message.message.messageType = kMessageTypeMove;
    NSData *data = [NSData dataWithBytes:&message length:sizeof(MessageMove)];    
    [self sendData:data];
}

- (void)sendGameOver:(BOOL)player1Won 
{
    MessageGameOver message;
    message.message.messageType = kMessageTypeGameOver;
    message.player1Won = player1Won;
    NSData *data = [NSData dataWithBytes:&message length:sizeof(MessageGameOver)];    
    [self sendData:data];
}


#pragma mark-init

// on "init" you need to initialize your instance
-(id) init
{
	if( (self=[super init]))
    {
        
        [[CCSpriteFrameCache sharedSpriteFrameCache]removeUnusedSpriteFrames];
        [[CCSpriteFrameCache sharedSpriteFrameCache]removeSpriteFrames];
        [[CCTextureCache sharedTextureCache] removeUnusedTextures];
        [[CCTextureCache sharedTextureCache] removeAllTextures];
        
        
        NSUserDefaults *userDefault=[NSUserDefaults standardUserDefaults];
        BOOL isJoystickPlayMode=[userDefault boolForKey:kPLAYMODE];
        if(isJoystickPlayMode){
            DataManager.firstTap=YES;
        }
        
        else
        {
            DataManager.firstTap=NO;
            
        }
        DataManager.isAppInsidesideGameScene=NO;
        DataManager.isLevelCompleted=NO;
        DataManager.isNewGame=YES;
        DataManager.scores=0;
        DataManager.isMainmenuInsideMode=NO;
        DataManager.currentLevel=0;
        DataManager.totalLevelsCompletd=0;
        DataManager.bonus=0;
        DataManager.nOOfBonusCollected=0;
        [DataManager.lifeFullArray removeAllObjects];
        
        
        [[CCSpriteFrameCache sharedSpriteFrameCache]addSpriteFramesWithFile:@"SXMenuImages.plist"];
        
        
        CCSprite *sprite=[CCSprite spriteWithFile:@"Main_bg.png"];
        [self addChild:sprite];
        sprite.position=ccp(240, 160);
        
        CCSprite *mainMenuFrame=[CCSprite spriteWithSpriteFrameName:@"main_menu_frame.png"];
        mainMenuFrame.position=ccp(340, 160);
        [self addChild:mainMenuFrame];
        
        
        CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"playGame.png"];
        CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"playGame_hvr.png"];
        
        /// new  game menu item 
           CCMenuItemSprite *newGameItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToNewGame)];
                newGameItem.position=ccp(340, 240);

        
        
        //game center menu item 
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"game_centre.png"]; 
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"game_centre_hvr.png"];
        CCMenuItemSprite *GameCenterItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToGameCenter)];
        GameCenterItem.position=ccp(340, 205); 
        
        
        
        
        // option menu item 
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"options.png"]; 
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"options_hvr.png"];
        CCMenuItemSprite *optionItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToOptionScene)];
        optionItem.position=ccp(340, 175); 
        
        // help menu item 
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"help.png"]; 
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"help_hvr.png"];
        CCMenuItemSprite *helpItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToHelpScene)];
        helpItem.position=ccp(340, 145); 
        
        // moreApp menu item 
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"more_apps.png"]; 
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"more_apps_hvr.png"];
        CCMenuItemSprite *moreAppItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToMoreAppScene)];
        moreAppItem.position=ccp(340, 115); 
        
        //share
     
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"share.png"]; 
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"share_hvr.png"];
        CCMenuItemSprite *shareItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToShareScene)];
        shareItem.position=ccp(340, 85); 

                CCMenu *menu=[CCMenu menuWithItems:newGameItem,
                              GameCenterItem,
                              optionItem,helpItem,moreAppItem,shareItem,
                              
                              nil];
        [self addChild:menu];
        menu.position=CGPointZero;
        
        
        //connecting to game center 
            }
    return self;
}

- (void)ccTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    [self sendMove];
}

-(void)goToNewGame
{
    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInR transitionWithDuration:0.5 scene:[SXGameModeMenuScene scene]]];
    DataManager.isMultiplayer=NO;
}

-(void)goToGameCenter{
    DataManager.isMultiplayer = YES;
    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInR transitionWithDuration:0.5 scene:[SXMainController scene]]];
}

-(void)goToOptionScene
{
    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInR transitionWithDuration:.5 scene:[SXOptionScene scene]]];
}

-(void)goToMoreAppScene
{
    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInR transitionWithDuration:.5 scene:[SXOtherAppScene scene]]];
}

-(void)goToHelpScene
{
    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInR transitionWithDuration:.5 scene:[SXHelpScene scene]]];
}


-(void)goToShareScene
{
    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInR transitionWithDuration:.5 scene:[SXShare scene]]];
}
// on "dealloc" you need to release all your retained objects
- (void) dealloc
{
	[super dealloc];
}
@end
