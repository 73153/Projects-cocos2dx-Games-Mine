//
//  SXMessageType.h
//  Snake_XT
//
//  Created by Pavitra on 17/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Snake_XT_SXMessageType_h
#define Snake_XT_SXMessageType_h

#define kMaxBonusNameLength 10

typedef enum {
    kMessageTypeRandomNumber = 0,
    kMessageTypeGameBegin,
    kMessageTypeGameOver,
    kMessageInitialiseGame,
    kMessageAckFromNonBossToBoss,
    kMessageSnakePosition,
    kMessageBodyPosition,
    kMessageCreateSnakeFromOtherDevice,
    kMessageCreateSnakeBodyFromOtherDevice,
    kMessageSnakePathArray,
    kMessageSnakeSetHitEffect,
    kMessageSetShieldEffect,
    kMessageCreateSnakeStaticBody,
    kMessageCreateSnakeBonus,
    kMessageRemoveBonus,
    kMessageRemoveShield,
    kMessageRemoveStaticBodyFromOtherDevice,
    kMessagPauseOtherDevice,
    kMessagResumeOtherDevice,
    kMessageYouWin,
    KmessageYouLost
    
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
    uint32_t levelNo;
    CGPoint snakePosition;
} MessageInitialiseGame;



typedef struct {
    Message message;
    CGPoint snakePosition;
    float snakeAngle;
    int tag;
} MessageCreateOtherDeviceSnake;

typedef struct {
    Message message;
    CGPoint snakePosition;
    int tag;
} MessageCreateOtherDeviceSnakeBody;

typedef struct {
    Message message;
    CGPoint staticBodyPosition;
    int tag;
} MessageCreateSnakeStaticBody;

typedef struct {
    Message message;
    CGPoint bonusPosition;
    int type;
    
} MessageCreateSnakeBonus;

typedef struct {
    Message message;
    CGPoint snakePosition;
    float angle;
    int snakeTag;
} MessageSnakeMove;



typedef struct {
    Message message;
    int snakeTag;
} MessageSetHitEffect;

typedef struct {
    Message message;
    int snakeTag;
} MessageSetShieldEffect;



typedef struct {
    Message message;
    int tag;
    
} MessageRemoveShield;


typedef struct {
    Message message;
   
} MessageRemoveBonus;


typedef struct {
    Message message;
    int staticbodyTag;
    
} MessageRemoveStaticBodyFromOtherDevice;


typedef struct {
    Message message;
    int staticbodyTag;
    
} MessagPauseOtherDevice;


typedef struct {
    Message message;
    int staticbodyTag;
    
} MessagResumeOtherDevice;


typedef struct {
    Message message;
    
} MessageYouLost;

typedef struct {
    Message message;
} MessageYouWin;



typedef struct {
    Message message;
    BOOL player1Won;
} MessageGameOver;

typedef enum 
{
    kEndReasonWin,
    kEndReasonLose,
    kEndReasonDisconnect
} EndReason;

typedef enum 
{
    kGameStateWaitingForMatch = 0,
    kGameStateWaitingForRandomNumber,
    kGameStateWaitingForStart,
    kGameStateActive,
    kGameStateDone
} GameState;

#endif
