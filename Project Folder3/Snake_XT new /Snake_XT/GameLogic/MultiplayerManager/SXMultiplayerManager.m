//
//  SXMultiplayerManager.m
//  Snake_XT
//
//  Created by Pavitra on 17/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXMultiplayerManager.h"
#import "SXAppDelegate.h"

#import "SXDataManager.h"
#import "GCHelper.h"

#import "SXMessageType.h"
#import "SXGameConstants.h"


#import "SXMainController.h"
#import "SXSnakeManager.h"

@implementation SXMultiplayerManager

@synthesize   isBoss,randomNoQueueArr;


- (id)init
{
    self = [super init];
    if (self) 
    {
        
        
    }
    return self;
}

#pragma mark - Func

-(void)startMultiplayerGamePlay
{
    SXAppDelegate * delegate = (SXAppDelegate *) [UIApplication sharedApplication].delegate;                
    [[GCHelper sharedInstance] findMatchWithMinPlayers:2 maxPlayers:2 viewController:delegate.viewController delegate:self];
    
    
    self.isBoss = NO;
    
    didGotMultiplayerDetails = NO;
    
    NSMutableArray *tempArr = [[NSMutableArray alloc] init];
    self.randomNoQueueArr = tempArr;
    [tempArr release];
    
}

-(void)sendData:(NSData *)data 
{
    NSError *error;
    BOOL success = [[GCHelper sharedInstance].match sendDataToAllPlayers:data withDataMode:GKMatchSendDataReliable error:&error];
    if (!success) 
    {
        CCLOG(@"Error sending init packet");
        //        [self matchEnded];
    }
}

#pragma mark - Recieve Data
- (void)match:(GKMatch *)match didReceiveData:(NSData *)data fromPlayer:(NSString *)playerID
{
    Message *message = (Message *)[data bytes];
    
    //received random number 
    if(message->messageType == kMessageTypeRandomNumber)
    {
        MessageRandomNumber *messageInit = (MessageRandomNumber *)[data bytes];
        
        if(didGotMultiplayerDetails)
        {
            [self proccessRandomNo:messageInit->randomNumber];
        }
        else {
            [self.randomNoQueueArr addObject:[NSNumber numberWithUnsignedInt:messageInit->randomNumber]];
        }
    }
    
    else if(message->messageType==kMessageInitialiseGame)
    {
        MessageInitialiseGame *messageInit = (MessageInitialiseGame *)[data bytes];
        [self gotRandomLevelFromBoss:messageInit->levelNo];
    }
    
    else if(message->messageType==kMessageCreateSnakeFromOtherDevice)
    {
        MessageCreateOtherDeviceSnake *messageInit = (MessageCreateOtherDeviceSnake *)[data bytes];
        [DataManager.gameLayer.snakeManager createSnakeFromOtherDeviceAtPos:messageInit->snakePosition withRotation:90 withtag:messageInit->tag];
    }
    
    else if(message->messageType==kMessageSnakePosition)
    {
        MessageSnakeMove *messageInit = (MessageSnakeMove *)[data bytes];
        CGPoint snakePOsition=messageInit->snakePosition;
        [DataManager.gameLayer.snakeManager setSnakePositionFromOtherDevice:snakePOsition withAngle:messageInit->angle withTag:messageInit->snakeTag];
    }
    else if(message->messageType==kMessageCreateSnakeBodyFromOtherDevice){
        MessageCreateOtherDeviceSnakeBody *messageInit = ( MessageCreateOtherDeviceSnakeBody *)[data bytes];
        [DataManager.gameLayer.snakeManager createSnakeBodyFromOtherDevice:messageInit->tag];
    }
    
    else if(message->messageType==kMessageSetShieldEffect){
        MessageSetShieldEffect *messageInit = ( MessageSetShieldEffect *)[data bytes];
        [DataManager.gameLayer.snakeManager setSheildEffectToOtherDeviceSnake:messageInit->snakeTag];
    }
    
    else if(message->messageType==kMessageSnakeSetHitEffect){
        MessageSetHitEffect *messageInit = ( MessageSetHitEffect *)[data bytes];
        [DataManager.gameLayer.snakeManager setHitEffectToOtherDeviceSnake:messageInit->snakeTag];
        
    }
    else if(message->messageType==kMessageCreateSnakeStaticBody){
        MessageCreateSnakeStaticBody *messageInit = ( MessageCreateSnakeStaticBody *)[data bytes];
        [DataManager.gameLayer.snakeManager createSnakeStaticBody:messageInit->staticBodyPosition];
    }
    
    else if(message->messageType==kMessageCreateSnakeBonus){
        MessageCreateSnakeBonus *messageInit = ( MessageCreateSnakeBonus *)[data bytes];
        [DataManager.gameLayer.snakeManager createBonusfromOtherDevice:messageInit->bonusPosition withtype:messageInit->type];
    }
    
    else if(message->messageType==kMessageRemoveBonus){
        [DataManager.gameLayer.snakeManager removebonus];
    }
    
    else if(message->messageType==kMessageRemoveShield){
         MessageRemoveShield *messageInit = ( MessageRemoveShield *)[data bytes];
        [DataManager.gameLayer.snakeManager removeShieldOtherDevice:messageInit->tag ];
    }
    
    else if(message->messageType==kMessageRemoveStaticBodyFromOtherDevice){
         MessageRemoveStaticBodyFromOtherDevice *messageInit = ( MessageRemoveStaticBodyFromOtherDevice *)[data bytes];
        [DataManager.gameLayer.snakeManager removeStaticBodyFromOtherDevice:messageInit->staticbodyTag];
    }
    
    else if(message->messageType==kMessagPauseOtherDevice){
        [DataManager.gameLayer pauseOtherDevice];
    }
    
    else if(message->messageType==kMessagResumeOtherDevice){
        [DataManager.gameLayer resumeOtherDevice];
    }
    
    else if(message->messageType==KmessageYouLost){
        [DataManager.gameLayer gameOver];
    }
    else if(message->messageType==kMessageYouWin){
        [DataManager.gameLayer gameWin];
    }
    
    
}


#pragma mark - Match Start End
- (void)matchStarted
{
    didGotMultiplayerDetails = YES;
    
    //Sending random No
    playerRandomNo = arc4random() %1000;
    NSLog(@" player random number=%d",playerRandomNo);
    
    //Got player Details Process Random No which it recived !
    if([self.randomNoQueueArr count]>0)
    {
        for (NSNumber *aRandomNo in self.randomNoQueueArr) 
        {
            int aRandomNoInt = [aRandomNo unsignedIntValue];
            NSLog(@"Processing Random no for Arr %d",aRandomNoInt);
            [self proccessRandomNo:aRandomNoInt];
        }
    }
    
    MessageRandomNumber message;
    message.message.messageType = kMessageTypeRandomNumber;
    message.randomNumber = playerRandomNo;
    
    NSData *data = [NSData dataWithBytes:&message length:sizeof(MessageRandomNumber)];    
    [self sendData:data];
}


- (void)matchEnded
{
    
}

- (void)inviteReceived
{
    
}

-(void)setUpForGame{
    DataManager.gameMode=KARCADEMODE ;
    DataManager.noOfLifeAvailable=5;
}




#pragma mark - Snake
-(void)createSnakeWithPosition:(CGPoint )inSnakePosition withAngle:(float)rotation withTag:(int)snakeTag
{
    MessageCreateOtherDeviceSnake message;
    message.snakePosition=inSnakePosition;
    message.snakeAngle = rotation;
    message.tag = snakeTag;
    message.message.messageType = kMessageCreateSnakeFromOtherDevice;
    
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageCreateOtherDeviceSnake)];
    [self sendData:data];
}

-(void)createSnakeBody:(int)tag{
    
    MessageCreateOtherDeviceSnakeBody message;
    message.tag=tag;
    message.message.messageType=kMessageCreateSnakeBodyFromOtherDevice;
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageCreateOtherDeviceSnakeBody)];
    [self sendData:data];
}


-(void)createSnakeStativBody:(CGPoint)position{
    MessageCreateSnakeStaticBody message;
    message.staticBodyPosition=position;
    message.message.messageType=kMessageCreateSnakeStaticBody;
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageCreateSnakeStaticBody)];
    [self sendData:data];
}

-(void)createBonusWithPosition:(CGPoint)position withImageName:(NSString *)name type:(int)bonusType withGlowImage:(NSString *)glowImage
{
    
    MessageCreateSnakeBonus message;
    message.bonusPosition=position;
    message.type=bonusType;
    //message.glowImageName=glowImage;
    //message.name=name;
    //     [name getCString:message.bonusName maxLength:kMaxBonusNameLength encoding:NSUTF8StringEncoding];
    //    [glowImage getCString:message.bonusGlowName maxLength:kMaxBonusNameLength encoding:NSUTF8StringEncoding];
    
    NSLog(@"bonus name=%@",name);
    message.message.messageType=kMessageCreateSnakeBonus;
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageCreateSnakeBonus)];
    [self sendData:data];
    
    
}

-(void)sendSnakePosition:(CGPoint )inSnakePosition withSnakeHeadRotation:(float)rotation withTag:(int)snakeTag{
    
    // NSLog(@" sending snake tag=%d",snakeTag);
    
    MessageSnakeMove message;
    message.message.messageType = kMessageSnakePosition;
    message.snakePosition = inSnakePosition;
    message.snakeTag = snakeTag;
    message.angle=rotation;
    
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageSnakeMove)];
    [self sendData:data];
}



#pragma mark- set hit effect
-(void)setHitEffectToOtherD3eviceSnake:(int)tag{
    MessageSetHitEffect message;
    message.message.messageType=kMessageSnakeSetHitEffect;
    message.snakeTag=tag;
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageSetHitEffect)];
    [self sendData:data];
}

-(void)setShieldEffectToOtherDeviceSnake:(int)tag{
    MessageSetShieldEffect message;
    message.message.messageType=kMessageSetShieldEffect;
    message.snakeTag=tag;
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageSetShieldEffect)];
    [self sendData:data];
}

#pragma -mark remove 
-(void)DeleteBonusFromOtherDeivce{
    MessageRemoveBonus message;
    message.message.messageType=kMessageRemoveBonus;
    
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageRemoveBonus)];
    [self sendData:data];
    
}

-(void)removeStaticBodyFromOtherDevice:(int)staticBodytag{
    MessageRemoveStaticBodyFromOtherDevice message;
    message.staticbodyTag=staticBodytag;
    message.message.messageType=kMessageRemoveStaticBodyFromOtherDevice;
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageRemoveStaticBodyFromOtherDevice)];
    [self sendData:data];
}

-(void)removeShielsFromotherDevice:(int)snakeTag{
    
    NSLog(@" sending  snake tag=%d",snakeTag);
    MessageRemoveShield message;
    message.message.messageType=kMessageRemoveShield;
    message.tag=snakeTag;
     NSLog(@" sending messgae snake tag=%d",message.tag);
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageRemoveShield)];
    [self sendData:data]; 
    


}

#pragma mark pause 
-(void)pauseOtherDeviceSnake{
    MessagPauseOtherDevice message;
    message.message.messageType=kMessagPauseOtherDevice;
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessagPauseOtherDevice)];
    [self sendData:data];
}

-(void)resumeOtherDeviceSnake{
    MessagResumeOtherDevice message;
    message.message.messageType=kMessagResumeOtherDevice;
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessagResumeOtherDevice)];
    [self sendData:data];

}

#pragma mark -game over 
-(void)sendYouLostMessage{
    MessageYouLost message;
    message.message.messageType=KmessageYouLost;
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageYouLost)];
    [self sendData:data];
}
-(void)sendYouWinMessage{
    MessageYouWin message;
    message.message.messageType=kMessageYouWin;
    NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageYouWin)];
    [self sendData:data];
}
  
#pragma mark - Random level 

-(void)getRandomLevel
{
    int random=arc4random()%28+1;
    DataManager.currentLevel=random;
    DataManager.currentLevel=1;
    [self setUpForGame];
}

-(void)proccessRandomNo:(int)inRandomNo
{
    NSLog(@"Got random No from Other device %d",inRandomNo);
    if(playerRandomNo>inRandomNo)
    {
        NSLog(@"I am The BOSS");
        self.isBoss=YES;
    }
    
    if (self.isBoss) {
        [self getRandomLevel];
        
        NSLog(@" Boss choosed level  & sending= %d",DataManager.currentLevel);
        
        int level=DataManager.currentLevel;
        MessageInitialiseGame message;
        message.message.messageType = kMessageInitialiseGame;
        message.levelNo = level;
        
        //Get the random snake position 
        message.snakePosition = CGPointMake(200, 200);
        
        NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageInitialiseGame)];
        [self sendData:data];
        
        [DataManager.gameLayer startGame];
    }
}


-(void)gotRandomLevelFromBoss:(int)inLevel
{
    DataManager.currentLevel = inLevel;
    [self setUpForGame];
    [DataManager.gameLayer startGame];
    
    //[self sendMsgToBossAftewrRecieveRandomLevel];
}

-(void)sendMsgToBossAftewrRecieveRandomLevel{
    if(!isBoss){
        MessageRandomNumber message;
        message.message.messageType = kMessageAckFromNonBossToBoss;
        NSData *data=[NSData dataWithBytes:&message length:sizeof(MessageRandomNumber)];
        [self sendData:data];
    }
}




- (void)dealloc
{
    self.randomNoQueueArr = nil;
    [super dealloc];
}

@end
