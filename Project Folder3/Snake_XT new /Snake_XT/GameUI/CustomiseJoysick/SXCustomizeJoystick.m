//
//  SXCustomizeJoystick.m
//  Snake_XT
//
//  Created by Pavitra on 29/09/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXCustomizeJoystick.h"
#import "SXGameConstants.h"
#import "SXGameModeMenuScene.h"
#import "SXOptionScene.h"
@implementation SXCustomizeJoystick


+(id)scene{
    CCScene *Scene=[CCScene node];
    SXCustomizeJoystick *layer=[SXCustomizeJoystick node];
    [Scene addChild:layer];
    return  Scene;
}

-(id)init{
    
    if(self=[super init]){
        
        self.isTouchEnabled=YES;
        CCSprite *bg=[CCSprite spriteWithFile:@"bg.png"];
        [self addChild:bg];
        bg.position=ccp(240, 160);
        
        CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt.png"];
        CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt_hvr.png"];
        
        /// new  game menu item 
        CCMenuItemSprite *backItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goBack)];
        backItem.position=ccp(65, 278);
        
        //done item 
        
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"done_bt.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"done_bt_hvr.png"];
        CCMenuItemSprite *doneItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToGameModeScene)];
        doneItem.position=ccp(415, 278);
        
        
        
        CCMenu *menu=[CCMenu menuWithItems:backItem,doneItem, nil];
        [self addChild:menu];
        menu.position=CGPointZero;
        
        
        CCSprite *customizeLabel=[CCSprite spriteWithSpriteFrameName:@"label_customize.png"];
        [self addChild:customizeLabel];
        customizeLabel.position=ccp(240, 278);
        
        
        joystickBase=[CCSprite spriteWithFile:@"Joystick_Controller.png"];
       
        
        CCSprite *joystick=[CCSprite spriteWithFile:@"movementJoystickMiddle.png"];
        [joystickBase addChild:joystick z:2];
        joystick.position=ccp(joystickBase.contentSize.width/2, joystickBase.contentSize.height/2);
        [self addChild:joystickBase z:2];
        
        NSUserDefaults *userDefault=[NSUserDefaults standardUserDefaults];
        
        NSString *joystickPositionString=[userDefault stringForKey:KJoystickPos];
        
        if(CGPointEqualToPoint(CGPointFromString(joystickPositionString),CGPointZero) ){
            
            joystickBase.position=ccp(240, 160);
            
        }
        else
        {
            joystickBase.position=CGPointFromString(joystickPositionString);
            
        }

        
    }
    return  self;
}

-(void)goBack{
    [[CCDirector sharedDirector]replaceScene:[SXOptionScene scene]];
}


-(void)goToGameModeScene{
    [[CCDirector sharedDirector]replaceScene:[SXOptionScene scene]];
    
}

-(void)ccTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    
}



-(void)ccTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
    
    UITouch *touch=[touches anyObject];
    
    CGPoint touchLocation = [self convertTouchToNodeSpace:touch];
    
    CGPoint oldTouchLocation = [touch previousLocationInView:touch.view];
    oldTouchLocation = [[CCDirector sharedDirector] convertToGL:oldTouchLocation];
    oldTouchLocation = [self convertToNodeSpace:oldTouchLocation];
    
    CGPoint translation = ccpSub(touchLocation, oldTouchLocation);   
    
    CGPoint newPos = ccpAdd(joystickBase.position, translation);
    
    joystickBase.position=newPos;
    
}
-(void)dealloc{
    NSString *joystickPosition=NSStringFromCGPoint(joystickBase.position);
    
    NSUserDefaults *userDefault=[NSUserDefaults standardUserDefaults];
    
    [userDefault setObject:joystickPosition forKey:KJoystickPos];
    
    [super dealloc];
}
@end
