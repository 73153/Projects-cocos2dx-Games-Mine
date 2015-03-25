//
//  HelloWorldLayer.h
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/28/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//


// When you import this file, you import all the cocos2d classes
#import <UIKit/UIKit.h>
#import "cocos2d.h"
#import "SXDataManager.h"
#import "GCHelper.h"

typedef enum {
    kMessageTypeRandomNumber = 0,
    kMessageTypeGameBegin,
    kMessageTypeMove,
    kMessageTypeGameOver
} MessageType;

typedef struct {
    MessageType messageType;
} Message;

typedef struct {
    Message message;
    uint32_t randomNumber;
} MessageRandomNumber;

typedef struct {
    Message message;
} MessageGameBegin;

typedef struct {
    Message message;
} MessageMove;

typedef struct {
    Message message;
    BOOL player1Won;
} MessageGameOver;

typedef enum {
    kEndReasonWin,
    kEndReasonLose,
    kEndReasonDisconnect
} EndReason;

typedef enum {
    kGameStateWaitingForMatch = 0,
    kGameStateWaitingForRandomNumber,
    kGameStateWaitingForStart,
    kGameStateActive,
    kGameStateDone
} GameState;


// HelloWorldLayer
@interface SXMainMenu : CCLayer
{
    GameState gameState;
    CCLabelTTF *debugLabel;
    uint32_t ourRandom;   
    NSString *otherPlayerID;



}
// returns a CCScene that contains the HelloWorldLayer as the only child
+(CCScene *) scene;

@end
