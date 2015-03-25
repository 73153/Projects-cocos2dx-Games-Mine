//
//  SXMultiplayerManager.h
//  Snake_XT
//
//  Created by Pavitra on 17/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SXMainController.h"
#import "SXGameManager.h"
//#import "SXMessageType.h"
@interface SXMultiplayerManager : SXGameManager

{
    SXMainController *mainLayer;
    
    //Random No
    int playerRandomNo;
    
    BOOL didGotMultiplayerDetails;
    NSMutableArray *randomNoQueueArr;
    
    //Boss
    BOOL isBoss;
}

@property(nonatomic,assign) BOOL isBoss;
@property (nonatomic,retain) NSMutableArray *randomNoQueueArr;

-(void)startMultiplayerGamePlay;

//Random
-(void)getRandomLevel;

//Send Snake Position
-(void)sendSnakePosition:(CGPoint )inSnakePosition withSnakeHeadRotation:(float)rotation withTag:(int)snakeTag;
-(void)sendPathArray:(NSMutableArray *)pathArry withTag:(int)tag;

//Send 
-(void)sendData:(NSData *)data;

//create snake from other device 
-(void)createSnakeWithPosition:(CGPoint )inSnakePosition withAngle:(float)rotation withTag:(int)snakeTag;
-(void)createSnakeBody:(int)tag;

// other func
-(void)setHitEffectToOtherD3eviceSnake:(int)tag ;
-(void)setShieldEffectToOtherDeviceSnake :(int)tag ;

// func to send msg to create body and bonus 
-(void)createSnakeStativBody:(CGPoint)position;
-(void)createBonusWithPosition:(CGPoint)position withImageName:(NSString*)name type:(int)bonusType withGlowImage:(NSString *)glowImage;


// func to delete bonus from other device
-(void)DeleteBonusFromOtherDeivce;
-(void)removeStaticBodyFromOtherDevice:(int)staticBodytag;

// remove shield once hit boundary 
-(void)removeShielsFromotherDevice:(int)snakeTag;

-(void)pauseOtherDeviceSnake;
-(void)resumeOtherDeviceSnake;

// gamw over 
-(void)sendYouLostMessage;
-(void)sendYouWinMessage;


@end
