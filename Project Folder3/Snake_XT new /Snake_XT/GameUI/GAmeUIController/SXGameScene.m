//
//  GameScene.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXGameScene.h"

//#include <CCScrollLayer.h>
#import "SXDataManager.h"
#import "SXMainController.h"

@implementation SXGameScene

@synthesize optionLayer;
#pragma mark-scene

+(id)scene{
    
    CCScene *Scene=[CCScene node];
    SXGameScene *gameLayer=[SXGameScene node];
    [Scene addChild:gameLayer];
    return Scene;
}

#pragma mark-init

-(void)addUI{
    
    lifefullArray=[[NSMutableArray alloc] init];
    scoreLabel=[CCLabelTTF labelWithString:@"0" fontName:@"Arial" fontSize:15];
    
    CCSprite *topMenu=[CCSprite spriteWithFile:@"top_menu_01.png"];
    [self addChild:topMenu];
    topMenu.position=ccp(240, 305);
    

    //adding option button
    CCMenuItemImage *optionButtonItem=[CCMenuItemImage itemFromNormalImage:@"option_Button_01.png" selectedImage:@"option_Button_02.png" target:self selector:@selector(optionButtonAction)];
    CCMenu *option=[CCMenu menuWithItems:optionButtonItem, nil];
    
    [self addChild:option];
    option.position=ccp(19, 305);

    
    //adding  score bg
    Scorebg=[CCSprite spriteWithFile:@"scoreBG.png"];
    [self addChild:Scorebg ];
    Scorebg.position=ccp(90, 305);
    
    scoreLabel=[CCLabelTTF labelWithString:@"0" fontName:@"Arial" fontSize:15];
    [scoreLabel setColor:ccc3(255, 255, 255)];
    
    [self addChild:scoreLabel  ];
    scoreLabel.position=ccp(90, 305);
    
    mBodyPartCounter=[CCLabelTTF labelWithString:@"15" fontName:@"Arial" fontSize:16];
    
    mBodyPartCounter.position=ccp(265, 300 );
    [self addChild:mBodyPartCounter];
    
    
    //adding level textfield
    
    
    levelLabel=[CCLabelTTF labelWithString:@"01" fontName:@"Arial" fontSize:16];
    [levelLabel setColor:ccc3(255, 255, 255)];
    
    [self addChild:levelLabel];
    levelLabel.position=ccp(212, 300);
    
    
    
    //adding pause  button
    pauseButton=[CCMenuItemImage itemFromNormalImage:@"Pause_01.png" selectedImage:@"Pause_02.png" target:self selector:@selector(PauseButtonAction)];
    CCMenu *pauseMenu=[CCMenu menuWithItems:pauseButton, nil];
    
    [self addChild:pauseMenu];
    pauseMenu.position=ccp(465, 305);
    CCSprite *lifeBG=[CCSprite spriteWithFile:@"lifeBG.png"];
    [self addChild:lifeBG];
    lifeBG.position=ccp(410, 305);
    
    int x=350;
    int y=305;
    
    for(int i=0;i<5;i++){
        CCSprite *lifefull=[CCSprite spriteWithFile:@"life_full.png"];
        [self addChild:lifefull];
        lifefull.position=ccp(x, y);
        [lifefullArray addObject:lifefull];
        x=x+15;
    }
    
    CCSprite *sprite1=[CCSprite spriteWithFile:@"clay_01.png"];
    [self addChild:sprite1];
    sprite1.position=ccp(100, 100);
    // id action=[CCRotateBy actionWithDuration:1 angle:10
    // ];
    id action1=[CCJumpTo actionWithDuration:1 position:ccp(300, 100) height:30 jumps:4];
    
    //id reverse=[action1 reverse];
    
    id seq=[CCSequence actions:action1 ,nil];
    
    [sprite1 runAction:[CCRepeatForever actionWithAction: seq]];

}
-(id)init{
    if((self=[super init]))
    {
        self.isTouchEnabled=YES;
        [[CCTouchDispatcher sharedDispatcher] addTargetedDelegate:self priority:1 swallowsTouches:YES];
         [self addUI];
           }      
    
    return self;
    
}

-(id)initWith:(int)score:(int)part{
    if((self=[super init])){
        [self addUI];
        [scoreLabel setString:[NSString stringWithFormat:@"%d",[SXDataManager sharedManager].scores]];
        [levelLabel setString:[NSString stringWithFormat:@"%d",[SXDataManager sharedManager].totalLevelsCompletd]];
        


    }

    
    
    return self;
}

#pragma mark-  button actions
-(void) optionButtonAction{
    
    if([SXDataManager sharedManager].isGamePaused==YES){
        [[CCDirector sharedDirector]resume];

        
    }
    [[CCDirector sharedDirector]replaceScene:[CCTransitionMoveInR transitionWithDuration:.5 scene:[SXGameOptionMenuScene scene]]];


     
}


-(void)PauseButtonAction
{
    
    if([SXDataManager  sharedManager].isGamePaused ==NO){
      [SXDataManager  sharedManager].isGamePaused =YES;
        [ self removeChild:pauseButton cleanup:YES];
        
        
        [[CCDirector sharedDirector]pause];
        
        playButton=[CCMenuItemImage itemFromNormalImage:@"Play_01.png" selectedImage:@"Play_02.png" target:self selector:@selector(PlayButtonAction)];
        playMenu=[CCMenu menuWithItems:playButton, nil];
        
        [self addChild:playMenu];
        playMenu.position=ccp(460, 305);
        
        
    }
    
}

-(void)addGameOptionLayer{
    optionLayer.position=ccp(240, 160);
}

-(void) PlayButtonAction{
    
    [SXDataManager  sharedManager].isGamePaused =NO;    
    [self removeChild:playButton cleanup:YES];
    
    CCMenuItemImage *playItem=[CCMenuItemImage itemFromNormalImage:@"Pause_01.png" selectedImage:@"Pause_02.png" target:self selector:@selector(PauseButtonAction)];
   playMenu=[CCMenu menuWithItems:playItem, nil];
    
    [self addChild:playMenu];
    playMenu.position=ccp(460, 305);
    
    [[CCDirector sharedDirector] resume];
    
    
}
#pragma mark-cctouches
-(BOOL) ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event
{
    CCSprite *sprite=[CCSprite spriteWithFile:@"menu_selection.png"];
    
    CGPoint touchlocation=[touch locationInView:[touch view]];
    
    touchlocation=[[CCDirector sharedDirector] convertToGL:touchlocation];
    int miny;
    int maxy;
    //for( miny=240,maxy=270;miny>=60;miny=miny-30,maxy=maxy-30)
   // if(count==2){
        
    for( miny=235,maxy=245;miny>=75;miny=miny-30,maxy=maxy-30){
        if(( touchlocation.y>=miny && touchlocation.y<=maxy) && (touchlocation.x>=250 && touchlocation.x<390))
        {
            [optionLayer addChild:sprite];
            sprite.position=ccp(325, miny+5);
            
            int index=touchlocation.y/30;
            switch (index) {
                case 2:
                    [optionLayer runAction:[CCMoveTo actionWithDuration:1 position:ccp(840, 160)]];
                   // [DataManager sharedManager].isAppInsidesideGameScene=YES;

                    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInR transitionWithDuration:.5 scene:[SXOtherAppScene scene]]];
                    
                    break;
                    
                case 3:
                    
                    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInL transitionWithDuration:.5 scene:[SXMainMenu scene]]];
                    break;
                    
                    
                case 4:
                    [optionLayer runAction:[CCMoveTo actionWithDuration:1 position:ccp(840, 160)]];
                    [SXDataManager sharedManager].isMainmenuInsideMode=YES;
                    [[CCDirector sharedDirector]replaceScene:[CCTransitionMoveInR transitionWithDuration:.5 scene:[SXGameModeMenuScene scene]]];
                    break;
                    
                case 5:
//                
//
                    [SXDataManager sharedManager].isOptionInsideGame=YES;
                    
                    
                    [[CCDirector sharedDirector]replaceScene:[CCTransitionMoveInR transitionWithDuration:.5 scene:[SXOptionScene scene]]];
                    break;
                    
                case 6:
                    [self removeAllChildrenWithCleanup:YES];
                    [SXDataManager sharedManager].isAppInsidesideGameScene=NO;

                    [[CCDirector sharedDirector]replaceScene:[CCTransitionMoveInL transitionWithDuration:.5 scene:[SXGameScene
                                                                                                                   scene]]];
                    break;
                    
                case 7:
                    //[self removeChild:optionLayer cleanup:YES];
                    [self removeAllChildrenWithCleanup:YES];
                    [SXDataManager sharedManager].isAppInsidesideGameScene=NO;

                    
                    [[CCDirector sharedDirector]replaceScene:[CCTransitionMoveInL transitionWithDuration:.5 scene:[SXGameScene
                                                                                                                   scene]]];
                    break;
                    
                case 8:
                    
                    [SXDataManager sharedManager].isAppInsidesideGameScene=NO;
                    scoreLabel.visible=YES;
                    Scorebg.visible=YES;
                    levelLabel.visible=YES;
                    partsLabel.visible=YES;
                    id action=[CCMoveTo actionWithDuration:.5 position:ccp(840,160)];
                    [optionLayer runAction:action];            
                    count=1;
                    
                    
                    break;
                    
                    
                default:
                    break;
            }
            
            
            
        //}
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
