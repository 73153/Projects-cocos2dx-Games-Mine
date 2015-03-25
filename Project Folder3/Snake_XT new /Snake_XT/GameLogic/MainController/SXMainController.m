//
//  HelloWorldLayer.m
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//


// Import the interfaces
#import "SXMainController.h"
#import "SXLevelManager.h"
#import "SXSnakeManager.h"
#import "SXGameOptionMenuScene.h"
#import "SXDataManager.h"
#import "SXGameConstants.h"
#import "SXSnake.h"
#import "SXObstacle.h"
#import "SXSnakeStaticBody.h"
#import "SXArcadeScene.h"
#import "SXMainMenu.h"
#import "SXOptionScene.h"
#import "SXMultiplayerManager.h"

@implementation SXMainController
@synthesize leveDetails,snakeManager,multiplayerManager,backGround;



+(CCScene *) scene
{
	CCScene *scene = [CCScene node];
	SXMainController *layer = [SXMainController node];
	[scene addChild: layer];
	return scene;
}



// on "init" you need to initialize your instance

-(id) init
{
    if((self=[super init]))
    {
        
    

        self.isTouchEnabled=YES;
        [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"SXSnakeImagesPlist.plist"];
        [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"SXObstacleImages.plist"];
        [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"SXBonusImages.plist"];
        
        
        DataManager.gameLayer = self;

        SXSnakeManager *_SXSnakeManager = [[SXSnakeManager alloc] init];
        self.snakeManager = _SXSnakeManager;
        [_SXSnakeManager release];
        
        SXLevelManager *_SXLevelManager = [[SXLevelManager alloc] init];
        self.leveDetails = _SXLevelManager;
        [_SXLevelManager release];
        

         
        if(!DataManager.isMultiplayer)
        {
            [self startGame];
        }
        else
            
            
        {
            SXMultiplayerManager *_SXMultiplayerManager = [[SXMultiplayerManager alloc] init];
            self.multiplayerManager = _SXMultiplayerManager;
            [_SXMultiplayerManager release];
            
            [self.multiplayerManager startMultiplayerGamePlay];
            
            
           // NSString *Level=[NSString stringWithFormat:@"Level%d",DataManager.currentLevel];
            //[self.leveDetails setUpLevelForTheGame:self WithLevel:Level];
        }
        
                                                                  //adding UI for Game
       
    }    
    return self;
}

 
-(void)startGame{
     // switch  btw modes 
    switch (DataManager.gameMode) 
    {
        case KARCADEMODE: NSLog(@" arcade");                  // arcade mode 
            //DataManager.currentLevel=20;
            
            NSString *Level=[NSString stringWithFormat:@"Level%d",DataManager.currentLevel];
            [self.leveDetails setUpLevelForTheGame:self WithLevel:Level];
            DataManager.isNewArcadeGame=NO;
            break;
        default:  // challenge mode
            
            [self.leveDetails setUpLevelForTheGame:self WithGameMode:DataManager.gameMode]; // loading level details from level manager for challenge mode 
            break;
    }
    
    
    //Add BG
    backGround=[CCSprite spriteWithFile:self.leveDetails.backGroundImage];
    backGround.position=ccp(240,160);
    [self addChild:backGround z:1];
    [self addUI];  
   
    //scheduler methods
    [self schedule:@selector(addBonus) interval:10];
    [self schedule:@selector(SnakeUpdate)];
    [self scheduleUpdate];
    
}


//Adding UI
-(void)addUI
{
    // top menu 
    CCSprite *topMenu;
    mBodyPartCounter=[CCLabelTTF labelWithString:@"00" fontName:@"Arial" fontSize:16];
    
    //................ adding top menus 
    switch (DataManager.gameMode) 
    {
        default :                
            topMenu=[CCSprite spriteWithFile:@"top_menu_02.png"];  // top menu for challenge mode
            mBodyPartCounter.position=ccp(250, 300 );
            
            break;
            
        case 2:                                                   //adding arcade mode top menu
            topMenu=[CCSprite spriteWithFile:@"top_menu_01.png"];
            levelLabel=[CCLabelTTF labelWithString:@"01" fontName:@"Arial" fontSize:16];
            [levelLabel setColor:ccc3(255, 255, 255)];
            
            [self addChild:levelLabel z:8];
            levelLabel.position=ccp(212, 300);
            
            mBodyPartCounter.position=ccp(265, 300 );
            DataManager.noOfParts=self.leveDetails.MaxNoBodies;
            break;
    }
    
    
    // top menu 
    [self addChild:topMenu z:7];
    topMenu.position=ccp(240, 305); 
    
    
    // body counter 
    [self addChild:mBodyPartCounter z:7];
    
    
    //adding  score bg.............
    
    Scorebg=[CCSprite spriteWithFile:@"scoreBG.png"];
    [self addChild:Scorebg z:7];
    Scorebg.position=ccp(90, 305);
    
    
    // scoreLabel ...................
    
    scoreLabel=[CCLabelTTF labelWithString:@"0" fontName:@"Arial" fontSize:15];
    [scoreLabel setColor:ccc3(255, 255, 255)];
    [self addChild:scoreLabel  z:7];
    scoreLabel.position=ccp(90, 305);
    
    
    
    //adding lifes  bg................
    
    CCSprite *lifeBG=[CCSprite spriteWithFile:@"lifeBG.png"];
    [self addChild:lifeBG z:7];
    lifeBG.position=ccp(380, 305);

    if(DataManager.isRestartMode ==YES) // restart mode and resetting lifes available
    {  // lifes in for RestartMode
        [scoreLabel setString:[NSString stringWithFormat:@"%d",DataManager.scores ]];
        [self addlifes];
        DataManager.isRestartMode=NO;
    }
    
    
    else
    {    
        [self addlifes];
    }    
    
    // .....................option button
    
    CCMenuItemImage *optionButtonItem=[CCMenuItemImage itemFromNormalImage:@"option_Button_01.png" selectedImage:@"option_Button_02.png" target:self selector:@selector(optionButtonAction)];
    
    CCMenu *option=[CCMenu menuWithItems:optionButtonItem, nil];                                     // option button 
    [self addChild:option z:3];
    option.position=ccp(19, 305);
    
    
    pauseSprite=[CCSprite spriteWithSpriteFrameName:@"Pause_01.png"];//play
    [self addChild:pauseSprite z:3 ];
    pauseSprite.position=ccp(465, 305);

}



#pragma mark-updatin life full
-(void)addlifes{
    
    int x=350;
    int y=305;
    
    [DataManager.lifeFullArray removeAllObjects]; 
    if(DataManager.noOfLifeAvailable>5){
        DataManager.noOfLifeAvailable=5;
    }
    
    
    // addding life full 
    for(int i=0;i<DataManager.noOfLifeAvailable;i++)
    {
        CCSprite *lifefull=[CCSprite spriteWithFile:@"life_full.png"];           
        [self addChild:lifefull z:8 tag:i];
        lifefull.position=ccp(x, y);
        [DataManager.lifeFullArray addObject:lifefull];
        x=x+15;
    } 
    
    int noOfEmptyLife=5-[DataManager.lifeFullArray count];
    
    
    
    // adding empty lifes 
    for(int i=0;i<noOfEmptyLife;i++){
        CCSprite *lifeEmpltySprite=[CCSprite spriteWithFile:@"life_empty.png"];
        [self addChild:lifeEmpltySprite z:8];
        lifeEmpltySprite.position=ccp(x, y);
        x=x+15;
    }
}


// updating lifes once snake lost its life 
-(void)updateLifeArray
{
    CCSprite *sprite=(CCSprite *)[DataManager.lifeFullArray lastObject];
    CCSprite *lifeEmpltySprite=[CCSprite spriteWithFile:@"life_empty.png"];
    lifeEmpltySprite.position=sprite.position;
    [self addChild:lifeEmpltySprite z:8];
    [self removeChild:sprite cleanup:YES];
    [DataManager.lifeFullArray removeLastObject];
}

// add bonus life
-(void)addBonusLife{
    
    CCSprite *sprite=(CCSprite *)[DataManager.lifeFullArray lastObject];
    CCSprite *lifefull=[CCSprite spriteWithFile:@"life_full.png"];
    
    if([DataManager.lifeFullArray count]<5)
    {
        [self addChild:lifefull z:8];
        lifefull.position=ccp((sprite.position.x)+15, 305);
        [DataManager.lifeFullArray addObject:lifefull];
    }
}

#pragma mark-schedule methods

// snake update 
-(void)SnakeUpdate
{
    
//    if(!DataManager.isGamePaused)
//    {
        if (DataManager.firstTap &&!DataManager.isGamePaused)
        {
            [self.snakeManager updateScene];   
            [self.snakeManager checkCollision]; 
            
            if(DataManager.isMultiplayer)
            {
                [self.snakeManager otherDeviveSnakeUpdate];
            }
        }
    //}
//    [self.snakeManager checkCollision]; 
//    
//    if(DataManager.isMultiplayer)
//    {
//        [self.snakeManager otherDeviveSnakeUpdate];
//    }
}



// adding bonus
-(void)addBonus
{
    int realno=arc4random()%7+1;  // getting random number 
    realno=1;
    NSString *bonusImage=[NSString stringWithFormat:@"bonus%d.png",realno];
    NSString *bonusGlowImage=[NSString stringWithFormat:@"bonus%d_Glow.png",realno];
    [self.snakeManager addingBonusWithPosition:[self.snakeManager checkRandomPositionWithObstaclePosition] withImageName:bonusImage type:realno   withGlowImage:bonusGlowImage];
}



//  tick method
-(void)update:(ccTime)dt
{
    [scoreLabel setString:[NSString stringWithFormat:@"%d",DataManager.scores]];
    [mBodyPartCounter setString:[NSString stringWithFormat:@"%d",DataManager.noOfParts]];
    [levelLabel setString:[NSString stringWithFormat:@"0%d",DataManager.currentLevel]];
    
    
    
    if([DataManager.lifeFullArray count]==0)  //checking for level failed condition
    { 
        [self unscheduleAllSelectors];
        DataManager.isLevelFailed=YES; 
        [self runAction:[CCSequence actions:[CCCallFuncN actionWithTarget:self selector:@selector(goToLevelEndScene)],nil]];
        [self.multiplayerManager sendYouWinMessage];
    }
    
    
    //checking condition for level completed and updating score and bodyParts
    if(DataManager.gameMode==KARCADEMODE)
    {
        
        if(DataManager.noOfParts==0)
        {
           [self unscheduleAllSelectors];
            
            DataManager.isLevelCompleted=YES;
            
            
//            id action=[CCDelayTime actionWithDuration:.1];
//            [self runAction:action];
            [self runAction:[CCSequence actions:[CCDelayTime actionWithDuration:2],[CCCallFuncN actionWithTarget:self selector:@selector(goToLevelEndScene)],nil]]; 
            [self.multiplayerManager sendYouLostMessage ];

            
            if(!(DataManager.currentLevel<DataManager.totalLevelsCompletd))
            {
                DataManager.totalLevelsCompletd+=1;
                DataManager.noOfLifeAvailable=[DataManager.lifeFullArray count];

                NSUserDefaults *userdefault=[NSUserDefaults standardUserDefaults];
                [userdefault  setValue:[NSString stringWithFormat:@"%d",DataManager.totalLevelsCompletd] forKey:KTotalLevelsCompleted];
                [userdefault  setValue:[NSString stringWithFormat:@"%d",DataManager.noOfLifeAvailable] forKey:kLifeAvailable];
                [userdefault  setValue:[NSString stringWithFormat:@"%d",DataManager.scores] forKey:kSavePointScore];
                
            }
            
        }
        
    }
}




//Touch Began
#pragma mark-tapping action
-(void)ccTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
    UITouch *touch=[touches anyObject];
    CGPoint loc=[ touch locationInView:[touch view]];
    loc=[[CCDirector sharedDirector]convertToGL:loc];
    
    if( CGRectContainsPoint(pauseSprite.boundingBox, loc)) // pause sprite rect contains touch location 
    {
        if(DataManager.isGamePaused)
        {
            [[CCDirector sharedDirector] resume];
            DataManager.isGamePaused=NO;
            [pauseSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache]  spriteFrameByName:@"Pause_01.png"]];
            if(DataManager.isMultiplayer)
            {
                [self.multiplayerManager resumeOtherDeviceSnake];
            }
           
            return;
        }
        
        else
        {
            [[CCDirector sharedDirector]pause];
            DataManager.isGamePaused=YES;
            [pauseSprite setDisplayFrame:[[CCSpriteFrameCache sharedSpriteFrameCache]  spriteFrameByName:@"Play_01.png"]];
            if(DataManager.isMultiplayer)
            {
                [self.multiplayerManager pauseOtherDeviceSnake];
            }
        }
    }
    
        [self.snakeManager handleTap:touches withEvent:event];
}



#pragma mark pause
-(void)pauseOtherDevice{
    NSLog(@"pause other device ccDirector");
    [[CCDirector sharedDirector]pause];
    DataManager.isGamePaused=YES;
}

-(void)resumeOtherDevice{
    [[CCDirector sharedDirector]resume];
    DataManager.isGamePaused=NO;
}

#pragma -mark game over
-(void)gameOver{
    [self unscheduleAllSelectors];
    DataManager.isLevelFailed=YES; 
    [self runAction:[CCSequence actions:[CCCallFuncN actionWithTarget:self selector:@selector(goToLevelEndScene)],nil]];
}

-(void)gameWin{
    [self unscheduleAllSelectors];
    
    CCLabelTTF *WinLabel=[CCLabelTTF labelWithString:@"You Win" fontName:@"Arial" fontSize:32];
    [self addChild:WinLabel z:7];
    WinLabel.position=CGPointMake(240, 160);
    id action =[CCBlink actionWithDuration:2 blinks:3];
    [WinLabel runAction:action];
    CCLabelTTF *ReplayLabel=[CCLabelTTF labelWithString:@"Replay" fontName:@"Arial" fontSize:32];

    CCMenuItemLabel *replayMenuItem=[CCMenuItemLabel itemWithLabel:ReplayLabel target:self selector:@selector(replay)];
    CCMenu *replayMenu=[CCMenu menuWithItems:replayMenuItem, nil];
    [self addChild:replayMenu z:7];
    replayMenu.position=CGPointMake(240, 130);
}


// go to level end scene
-(void)goToLevelEndScene
{    

    CCSprite *transparentSprite=[CCSprite spriteWithFile:@"trsprnt_bg.png"];
    [self addChild: transparentSprite z:8];
    transparentSprite.position=ccp(240, 160);
    
    //adding stars
    CCSprite *star=[CCSprite spriteWithSpriteFrameName:@"star_2_hvr.png"];
    //[self addChild:star z:8];
    star.position=ccp(190, 270);
    
    // main menu
    CCMenuItemSprite *mainMenuItem=[CCMenuItemSprite itemFromNormalSprite:[CCSprite spriteWithSpriteFrameName:@"menu_bt.png"] selectedSprite:[CCSprite spriteWithSpriteFrameName:@"menu_bt_hvr.png"] target:self selector:@selector(goToMainMenu)];
    mainMenuItem.position=ccp(90, 225);
    CCMenu *menu=[CCMenu menuWithItems:mainMenuItem, nil];
    menu.position=CGPointZero;
    [self addChild:menu z:10];
    
    
    
    ///adding  score labels
    CCLabelTTF  *totalLabel=[CCLabelTTF labelWithString:@"      00" fontName:@"Arial" fontSize:18];
    [self addChild:totalLabel z:9];
    int total=[SXDataManager sharedManager].scores+[SXDataManager sharedManager].bonus;
    
    [totalLabel setString:[NSString  stringWithFormat:@"%d",total]];
    
    
    //adding bonus label
    CCLabelTTF     *bonusLabel=[CCLabelTTF labelWithString:@"   200" fontName:@"Arial" fontSize:18];
    [self addChild:bonusLabel z:9];
    [bonusLabel setString:[NSString  stringWithFormat:@"%d",[SXDataManager sharedManager].bonus]];
    
    
    //adding points label
    CCLabelTTF * pointLabel=[CCLabelTTF labelWithString:@"    100" fontName:@"Arial" fontSize:18];
    [self addChild:pointLabel z:9];
    [pointLabel setString:[NSString  stringWithFormat:@"%d",[SXDataManager sharedManager].scores]];
    
    
    if(DataManager.isLevelCompleted)
    {
        CCSprite *levelCompletedSprite=[CCSprite spriteWithFile:@"level_completed_bg.png"];
        levelCompletedSprite.position=ccp(240, 160);
        [self addChild:levelCompletedSprite z:8];
        pointLabel.position=ccp(220, 150);
        bonusLabel.position=ccp(340, 150);
        totalLabel.position=ccp(263, 120);
        
        CCSprite  *  normalSprite=[CCSprite spriteWithSpriteFrameName:@"facebook.png"];
        CCSprite  *  selectedSprite=[CCSprite spriteWithSpriteFrameName:@"facebook_hvr.png"];
        CCMenuItemSprite *facebookMenuitem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToFacebook)];
        facebookMenuitem.position=ccp(380, 227);
        
        
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"twitter.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"twitter_hvr.png"];
        CCMenuItemSprite *twitterMenuitem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToFacebook)];
        twitterMenuitem.position=ccp(410, 227);
        
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"nxt.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"nxt_hvr.png"];
        CCMenuItemSprite *nextMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(nextMenuItem)];
        nextMenuItem.position=ccp(190, 65);
        
        //reply menu item 
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"replay.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"replay_hvr.png"];
        CCMenuItemSprite *restatMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(replayAction)];
        restatMenuItem.position=ccp(250, 65);
        
        //level menu item 
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"levelMenu.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"levelMenu_hvr.png"];
        CCMenuItemSprite *levelMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToLevelSelectionScene)];
        levelMenuItem.position=ccp(310, 65);
        
        CCMenu *Menu=[CCMenu menuWithItems: nextMenuItem,restatMenuItem,levelMenuItem,facebookMenuitem,twitterMenuitem, nil];
        Menu.position=ccp(0, 0);
        [self addChild:Menu z:10];
        DataManager.isLevelCompleted=NO;
        
    }
    
    else{
        mainMenuItem.position=ccp(90, 261);// setting main menu position 
        
        CCSprite *levelCompletedSprite=[CCSprite spriteWithFile:@"level_failed_bg.png"];
        levelCompletedSprite.position=ccp(240, 160);
        [self addChild:levelCompletedSprite z:8];
        
        totalLabel.position=ccp(320, 138); // total label
        
        // restart button 
        CCSprite   *normalSprite=[CCSprite spriteWithSpriteFrameName:@"replay.png"];
        CCSprite  *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"replay_hvr.png"];
        CCMenuItemSprite *restatMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(restartAction)];
        restatMenuItem.position=ccp(320, 80);
        
        // levels button 
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"levelMenu.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"levelMenu_hvr.png"];
        CCMenuItemSprite *levelMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToLevelSelectionScene)];
        levelMenuItem.position=ccp(380, 80);
        
        CCMenu *menu=[CCMenu menuWithItems:restatMenuItem,levelMenuItem, nil];
        [self addChild:menu z:10];
        menu.position=CGPointZero;
    }
}

#pragma -mark menu item actions 
-(void)replay{
    [[CCDirector sharedDirector]replaceScene:[SXMainController scene]];

}
-(void)goToMainMenu{
    [[CCDirector sharedDirector]replaceScene:[CCTransitionMoveInL transitionWithDuration:0.5 scene:[SXMainMenu scene]]];
}


-(void)nextMenuItem{
    DataManager.currentLevel++;
   // DataManager.totalLevelsCompletd++;
    DataManager.noOfLifeAvailable=[DataManager.lifeFullArray count];
    NSUserDefaults *userDefault=[NSUserDefaults standardUserDefaults];
    BOOL isJoystick=[userDefault boolForKey:kPLAYMODE];
    [userDefault  setValue:[NSString stringWithFormat:@"%d",DataManager.noOfLifeAvailable] forKey:kLifeAvailable];

    
    if(isJoystick){
        DataManager.firstTap=YES;
        DataManager.isNewGame=NO;
        
    }
    else{
        DataManager.firstTap=NO;
    }    
    [[CCDirector sharedDirector]replaceScene:[SXMainController scene]];
}


-(void)replayAction{
    NSUserDefaults *playModeDefault=[NSUserDefaults standardUserDefaults];
    BOOL isJoystick=[playModeDefault boolForKey:kPLAYMODE];
    if(isJoystick){
        DataManager.firstTap=YES;
        
    }
    else
    {
        DataManager.firstTap=NO;
    }
    
    DataManager.isLevelFailed=NO;
    DataManager.isNewArcadeGame=NO;
    [self runAction:[CCMoveTo actionWithDuration:.5 position:ccp(240, 0)]];
    [[CCDirector sharedDirector]replaceScene:[CCTransitionFade transitionWithDuration:.5 scene:[SXMainController scene]]];
}

-(void)restartAction
{
    NSUserDefaults *playModeDefault=[NSUserDefaults standardUserDefaults];
    BOOL isJoystick=[playModeDefault boolForKey:kPLAYMODE];
    if(isJoystick){
        DataManager.firstTap=YES;
        
    }
    else
    {
        DataManager.firstTap=NO;
        
    }  
    if(DataManager.gameMode==KARCADEMODE){
        DataManager.firstTap=NO;
        DataManager.isLevelFailed=NO;
        DataManager.isRestartMode=YES;  
        
        DataManager.scores=DataManager.scores-((DataManager.maxNoOfBodiesInLevel-DataManager.noOfParts)*100)-DataManager.bonus;  // resetting score
        DataManager.bonus=0;
    }
    
    else{
        DataManager.scores=0;
        DataManager.noOfParts=0;
    }
    
    DataManager.noOfLifeAvailable=DataManager.numOfLifeLost+[DataManager.lifeFullArray count]-DataManager.noOfLifeBonusCollected; // number of life available
    DataManager.numOfLifeLost=0;
    DataManager.noOfLifeBonusCollected=0;
    [self runAction:[CCMoveTo actionWithDuration:.5 position:ccp(240, 0)]];
    [[CCDirector sharedDirector]replaceScene:[CCTransitionFade transitionWithDuration:.5 scene:[SXMainController scene]]];
}



-(void)goToLevelSelectionScene{
    NSUserDefaults *playModeDefault=[NSUserDefaults standardUserDefaults];
    BOOL isJoystick=[playModeDefault boolForKey:kPLAYMODE];

    if(isJoystick)
    {
        DataManager.firstTap=YES;
    }
    
    else
    {
        DataManager.firstTap=NO;
    }

    [[CCDirector sharedDirector] replaceScene:[CCTransitionFlipY  transitionWithDuration:.5 scene:[SXArcadeScene scene] orientation:kOrientationDownOver]];
}

-(void)resumeAction
{
    [self removeChild:gameOptionmodeBG cleanup:YES];
    DataManager.isResumeMode=YES;
    NSUserDefaults *playModeDefault=[NSUserDefaults standardUserDefaults];
    BOOL isJoystick=[playModeDefault boolForKey:kPLAYMODE];
    if(isJoystick){
        DataManager.firstTap=YES;
        [[CCDirector  sharedDirector]resume];
    }
    
    else{
        DataManager.firstTap=NO;
        [[CCDirector  sharedDirector]pause];
        
    }
    
    [self schedule:@selector(SnakeUpdate)];
}

-(void)goToLevels{
    NSUserDefaults *playModeDefault=[NSUserDefaults standardUserDefaults];
    BOOL isJoystick=[playModeDefault boolForKey:kPLAYMODE];
    if(isJoystick){
        DataManager.firstTap=YES;
        //[[CCDirector  sharedDirector]resume];
        
    }
    
    else{
        DataManager.firstTap=NO;
        //[[CCDirector  sharedDirector]pause];
        
    }

    [[CCDirector sharedDirector]replaceScene:[SXArcadeScene scene]];
}

-(void)goToFacebook{
    
}

-(void)goTovolumeScne{
    [[CCDirector sharedDirector] replaceScene :[SXOptionScene scene]];
    
}

#pragma mark-  button actions
//option button action
-(void) optionButtonAction
{
    [[CCDirector sharedDirector]resume];
    DataManager.isGamePaused=NO;
    [self unschedule:@selector(SnakeUpdate)];   
    
    // transparent bg 
    gameOptionmodeBG=[CCSprite spriteWithFile:@"trsprnt_bg.png"];
    [self addChild:gameOptionmodeBG z:8];
    gameOptionmodeBG.position=ccp(240, 160);
    
    // resume bg 
    CCSprite *resumeBg=[CCSprite spriteWithFile:@"Resume_game.png"];
    [gameOptionmodeBG addChild:resumeBg];
    resumeBg.position=ccp(240, 160);
    
    // resume label
    CCSprite *resumeLabelSprite=[CCSprite spriteWithSpriteFrameName:@"label_resume.png"];
    resumeLabelSprite.position=ccp(240, 230);
    [gameOptionmodeBG addChild:resumeLabelSprite z:8];
    
    
    //main menu item 
    CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"menu_bt.png"];
    CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"menu_bt_hvr.png"];
    CCMenuItemSprite *mainMebnuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToMainMenu)];
    mainMebnuItem.position=ccp(90, 228);
    
    
    //play meni item 
    normalSprite=[CCSprite spriteWithSpriteFrameName:@"play.png"];
    selectedSprite=[CCSprite spriteWithSpriteFrameName:@"play_hvr.png"];
    CCMenuItemSprite *playMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(resumeAction)];
    playMenuItem.position=ccp(150, 150);
    
    
    // replay menu item 
    normalSprite=[CCSprite spriteWithSpriteFrameName:@"replay.png"];
    selectedSprite=[CCSprite spriteWithSpriteFrameName:@"replay_hvr.png"];
    CCMenuItemSprite *restartMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(restartAction)];
    restartMenuItem.position=ccp(210, 150);
    
    
    // level menu item 
    normalSprite=[CCSprite spriteWithSpriteFrameName:@"levelMenu.png"];
    selectedSprite=[CCSprite spriteWithSpriteFrameName:@"levelMenu_hvr.png"];
    CCMenuItemSprite *levelMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToLevels)];
    levelMenuItem.position=ccp(270, 150);
    
    
    // volume menu item 
    normalSprite=[CCSprite spriteWithSpriteFrameName:@"volume.png"];
    selectedSprite=[CCSprite spriteWithSpriteFrameName:@"volume_hvr.png"];
    CCMenuItemSprite *volumeMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goTovolumeScne)];
    volumeMenuItem.position=ccp(330, 150);
    
    CCMenu *menu;
    if (DataManager.gameMode==KARCADEMODE) 
    {
        menu=[CCMenu menuWithItems:mainMebnuItem,playMenuItem,restartMenuItem,levelMenuItem,volumeMenuItem, nil];
    }
    else
    {
        menu=[CCMenu menuWithItems:mainMebnuItem,playMenuItem,restartMenuItem,volumeMenuItem, nil];  
        playMenuItem.position=ccp(180, 150);
        restartMenuItem.position=ccp(240, 150);
        
        volumeMenuItem.position=ccp(300, 150);
    }
    
    [gameOptionmodeBG addChild:menu z:9];
    menu.position=CGPointZero;
}



#pragma mark dealloc
// on "dealloc" you need to release all your retained objects
- (void) dealloc
{
    NSLog(@" dealloc in main controller ");
    self.leveDetails = nil;
    self.snakeManager = nil;
    self.multiplayerManager = nil;
    [super dealloc];
}

@end
