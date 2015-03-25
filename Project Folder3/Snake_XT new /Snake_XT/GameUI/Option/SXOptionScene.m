//
//  OptionScene.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXOptionScene.h"
#import "SXMainMenu.h"
#import "SXGameOptionMenuScene.h"
#import "SXMainController.h"
#import "SXCustomizeJoystick.h"
#import "SXGameModeMenuScene.h"
#import "SXArcadeScene.h"
@implementation SXOptionScene

+(id)scene{
    CCScene *scene=[CCScene node];
    SXOptionScene *layer=[SXOptionScene node];
    [scene addChild:layer];
    return scene;
    
}
#pragma  mark-init

-(id)init{
    if((self=[super init])){
        
        //adding aprite
        CCSprite *bg=[CCSprite spriteWithFile:@"bg.png"];
        [self addChild:bg];
        bg.position=ccp(240, 160);
        
        optionBG=[CCSprite spriteWithFile:@"options.png"];
        [self addChild:optionBG];
        optionBG.position=ccp(240, 160);
        
        //addign menu....
        CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt.png"];
        CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt_hvr.png"];
        
        
        CCMenuItemSprite *backMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(gotoMainMenu)];
        backMenuItem.position=ccp(60, 278);
        
        
        
        // option label
        CCSprite *optionLabelSprite=[CCSprite spriteWithSpriteFrameName:@"label_options.png"];
        [self addChild:optionLabelSprite];
        optionLabelSprite.position=ccp(240, 278);
        
        CCControlSlider *musicSlider = [CCControlSlider  sliderWithBackgroundSprite:[CCSprite spriteWithSpriteFrameName:@"slider_bg.png"] progressSprite:[CCSprite spriteWithSpriteFrameName:@"slide.png"] thumbSprite:[CCSprite spriteWithSpriteFrameName:@"slider.png"]];

        musicSlider.position = ccp(315,203);
        
		musicSlider.rotation = 0;
        
		musicSlider.value = 0.5;
        
		[optionBG addChild:musicSlider];        
        
        
        
        CCControlSlider *soundSlider = [CCControlSlider  sliderWithBackgroundSprite:[CCSprite spriteWithSpriteFrameName:@"slider_bg.png"] progressSprite:[CCSprite spriteWithSpriteFrameName:@"slide.png"] thumbSprite:[CCSprite spriteWithSpriteFrameName:@"slider.png"]];

        soundSlider.position = ccp(315,168);
        
		soundSlider.rotation = 0;
        
		soundSlider.value = .5;
        soundSlider.maximumValue=.88;
        
		[optionBG addChild:soundSlider];
        
        
        snakeSpeedSlider=[CCControlSlider sliderWithBackgroundSprite:[CCSprite spriteWithSpriteFrameName:@"slider_bg.png"] progressSprite:[CCSprite spriteWithSpriteFrameName:@"slide.png"] thumbSprite:[CCSprite spriteWithSpriteFrameName:@"slider.png"]];
        //slider_bg
        
		snakeSpeedSlider.position = ccp(315,239);        
		snakeSpeedSlider.rotation = 0;
        snakeSpeedSlider.minimumValue = 2;
        snakeSpeedSlider.maximumValue = 8.5;
        snakeSpeedSlider.value=DataManager.snakeSpeed ;
        [optionBG addChild:snakeSpeedSlider];
        DataManager.snakeSpeed=[snakeSpeedSlider value];
        
        
        SnakeSpeedLabel=[CCLabelTTF labelWithString:[NSString stringWithFormat:@"%f",[snakeSpeedSlider value]] fontName:@"Arial" fontSize:15];
        [optionBG addChild: SnakeSpeedLabel];
        SnakeSpeedLabel.position=ccp(400, 250);
        
        
        NSUserDefaults *playMode=[NSUserDefaults standardUserDefaults];
        BOOL isJoystick=[playMode boolForKey:kPLAYMODE];
        if(isJoystick){
            normalSprite=[CCSprite spriteWithSpriteFrameName:@"joystick_hvr.png"];
        }
        else
        {
            normalSprite=[CCSprite spriteWithSpriteFrameName:@"joystick.png"];
        }
        
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"joystick_hvr.png"];
        
        CCMenuItemSprite *joystickMneuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToJoystickScene)];
        joystickMneuItem.position=ccp(250, 115);
        
        if(isJoystick){
            normalSprite=[CCSprite spriteWithSpriteFrameName:@"touch.png"];
            selectedSprite=[CCSprite spriteWithSpriteFrameName:@"touch_hvr.png"];
        }
        else{
            normalSprite=[CCSprite spriteWithSpriteFrameName:@"touch_hvr.png"];
            selectedSprite=[CCSprite spriteWithSpriteFrameName:@"touch_hvr.png"];
        }
        
        CCMenuItemSprite *touchMneuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(setTouchPlayMode)];
        touchMneuItem.position=ccp(360, 115);
        
        
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"reset_game.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"reset_game.png"];
        CCMenuItemSprite *resetMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(resetGame)];
        resetMenuItem.position=ccp(265, 60);
        
        CCMenu *selectModeToPlayMenu=[CCMenu menuWithItems:backMenuItem,joystickMneuItem,touchMneuItem,resetMenuItem, nil];
        [self addChild:selectModeToPlayMenu ];
        selectModeToPlayMenu.position=CGPointZero;
        
        
        // adding 
        [self schedule:@selector(update)];
        
        
    }
    return  self;
}

-(void)resetGame{
    transparentBG=[CCSprite spriteWithFile:@"trsprnt_bg.png"];
    [self addChild:transparentBG];
    transparentBG.position=ccp(240, 160);
    
    CCSprite *resetBg=[CCSprite spriteWithFile:@"reset_bg.png"];
    [transparentBG addChild:resetBg];
    resetBg.position=ccp(240, 160);
    
    CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"ok_bt.png"];
    CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"ok_bt.png"];
    CCMenuItemSprite *okMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(resetAction)];
    okMenuItem.position=ccp(180, 120);
    
    normalSprite=[CCSprite spriteWithSpriteFrameName:@"cancel_bt.png"];
    selectedSprite=[CCSprite spriteWithSpriteFrameName:@"cancel_bt.png"];
    CCMenuItemSprite *CancelItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(cancelAction)];
    CancelItem.position=ccp(320, 120);
    CCMenu *menu=[CCMenu menuWithItems:okMenuItem,CancelItem, nil];
    [transparentBG addChild:menu];
    menu.position=CGPointZero;
    
}
-(void)cancelAction{
    
    [self removeChild:transparentBG cleanup:YES];
}
-(void)resetAction{
    
    DataManager.totalLevelsCompletd=0;
    NSUserDefaults *userdefault=[NSUserDefaults standardUserDefaults];
    [userdefault  setValue:[NSString stringWithFormat:@"%d",DataManager.totalLevelsCompletd] forKey:KTotalLevelsCompleted];
    [[CCDirector sharedDirector]replaceScene:[SXArcadeScene scene]];
    
}
-(void)goToJoystickScene{
    
    isJoystickMode=YES;
    
    NSUserDefaults *playModeDefault=[NSUserDefaults standardUserDefaults];
    [playModeDefault setBool:isJoystickMode forKey:kPLAYMODE];
    [[CCDirector sharedDirector] replaceScene: [SXCustomizeJoystick scene]];
    DataManager.firstTap=YES;
}

-(void)setTouchPlayMode{
    isJoystickMode=NO;
    NSUserDefaults *playModeDefault=[NSUserDefaults standardUserDefaults];
    [playModeDefault setBool:isJoystickMode forKey:kPLAYMODE];
    [[CCDirector sharedDirector]replaceScene:[CCTransitionMoveInR transitionWithDuration:0.5 scene:[SXGameModeMenuScene scene]]];
    DataManager.firstTap=NO;
}


-(void)update{
    
    [SnakeSpeedLabel setString:[NSString stringWithFormat:@"%f",[snakeSpeedSlider value]]];
    [SXDataManager sharedManager].snakeSpeed=[snakeSpeedSlider value];
    NSLog(@"data manager snake speed=%d",[SXDataManager sharedManager].snakeSpeed);
}





-(void)gotoMainMenu{
    if([SXDataManager  sharedManager] .isOptionInsideGame){
        id action=[CCMoveTo actionWithDuration:.5 position:ccp(480, 160)];
        [optionBG runAction:action];
        [[CCDirector sharedDirector] replaceScene: [CCTransitionMoveInR transitionWithDuration:.5 scene:[SXGameOptionMenuScene scene]]];
        
    }
    else
        [[CCDirector sharedDirector] replaceScene: [CCTransitionSlideInL transitionWithDuration:.5 scene:[SXMainMenu scene]]];
    
}


#pragma  mark- dealloc
-(void)dealloc{
    [self removeAllChildrenWithCleanup:YES];
    [super dealloc];
}
@end
