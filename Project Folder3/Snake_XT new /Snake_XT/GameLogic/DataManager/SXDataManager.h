//
//  ELDataManager.h
//  Elevator
//
//  Created by ICRG LABS on 18/04/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
//#import "SXGameScene.h"

@class SXMainController;

@interface SXDataManager : NSObject {
    
    SXMainController *gameLayer;
    
    NSMutableArray *lifeFullArray;
    NSMutableArray *highScoreArray;
    NSMutableDictionary *gameLevelDataDict;
    NSMutableArray *profileArray;
    NSMutableDictionary *mProfile_Challenge;
    NSMutableDictionary *mProfile_Legendary;

    
    NSMutableDictionary *mProfile_Arcade;
    
    int tototlScore;
    int bonus;
    int numberOfBodyParts;
    int scores;
    int challengeScore;
    int noOfParts;
    int totalLevelsCompletd;
    int numOfLifeLost;
    int currentLevel;
    int noOfLifeAvailable;
    int  maxNoOfBodiesInLevel;
    int gameMode;
    int nOOfBonusCollected;
    int noOfLifeBonusCollected;
    int LevelFailedCount;

    int snakeSpeed;
    
    BOOL isAppInsidesideGameScene;
    BOOL isOptionInsideGame;
    BOOL isMainmenuInsideMode;
    BOOL isLeftSlide;
    BOOL isGamePaused;
    BOOL isLevelCompleted;
    BOOL isLevelFailed;
    BOOL isNewGame;
    BOOL isNewArcadeGame;
    BOOL isNewBeginnerGame;
    BOOL isNewLegendaryGame;
    BOOL needToSave;
    BOOL isRestartMode;
    BOOL isLevelButtonClicked;
    BOOL isPlayAgain;
    BOOL isSwitchModeInsideGame;
    BOOL isMultiplayer;
        
    CGPoint *headPos;
    NSString *playerName;
    //NSString *backgroundImage;
    NSString *StaticBodyPosiitons;
    NSString *movableBodyPosiitons;
    NSString *bonusBodyPosiitons;


    

}

+(SXDataManager *)sharedManager;
//-(void)saveData;
//-(void)reloadGameWithProfileName:(NSString *)profileName;


@property(nonatomic,assign) SXMainController *gameLayer;

//@property(nonatomic,assign)NSMutableDictionary *gameLevelDataDict;
@property(nonatomic,retain)NSMutableArray *lifeFullArray;
@property(nonatomic,retain)    NSMutableArray *highScoreArray;
@property(nonatomic,retain)    NSMutableArray *profileArray;



@property(nonatomic)BOOL isLeftSlide;
@property(nonatomic)BOOL isAppInsidesideGameScene;
@property(nonatomic)BOOL isOptionInsideGame;
@property(nonatomic)BOOL isMainmenuInsideMode;
@property(nonatomic)BOOL isGamePaused;
@property(nonatomic)BOOL isLevelCompleted;
@property(nonatomic)BOOL isLevelFailed;
@property(nonatomic)BOOL isNewGame;
@property(nonatomic)BOOL isNewArcadeGame;
@property(nonatomic)BOOL isNewBeginnerGame;
@property(nonatomic)BOOL isNewLegendaryGame;
@property(nonatomic)BOOL isMultiplayer;



@property(nonatomic)BOOL needToSave;
@property(nonatomic)BOOL isRestartMode;
@property(nonatomic)BOOL isResumeMode;
@property(nonatomic)BOOL isLevelButtonClicked;
@property(nonatomic)BOOL mSkullShowed;
@property(nonatomic)BOOL IsLoadingGame;
@property(nonatomic)BOOL firstTap;
@property(nonatomic)BOOL isPlayAgain;


@property(nonatomic)BOOL isSwitchModeInsideGame;





@property(nonatomic,assign)int totalLevelsCompletd;
@property(nonatomic,assign)int currentLevel;
@property(nonatomic,assign)int scores;
@property(nonatomic,assign)int noOfParts;
@property(nonatomic,assign)int bonus;
@property(nonatomic,assign)int numOfLifeLost;
@property(nonatomic,assign)int noOfLifeAvailable;
@property(nonatomic,assign)int gameMode;
@property(nonatomic,assign)int maxNoOfBodiesInLevel;
@property(nonatomic,assign)int nOOfBonusCollected;
@property(nonatomic,assign)int noOfLifeBonusCollected;
@property(nonatomic,assign)int LevelFailedCount;
@property(nonatomic,assign)int snakeSpeed;

@property(nonatomic,retain)    NSString *playerName;
//@property(nonatomic,retain) NSString *backgroundImage;

@property(nonatomic,retain)    NSString *StaticBodyPosiitons;

@property(nonatomic,retain)    NSString *movableBodyPosiitons;

@property(nonatomic,retain)    NSString *bonusBodyPosiitons;
@property(nonatomic,retain)    NSMutableDictionary *mProfile_Arcade;
@property(nonatomic,retain)    NSMutableDictionary *mProfile_Challenge;
@property(nonatomic,retain)    NSMutableDictionary *mProfile_Legendary;





@end
