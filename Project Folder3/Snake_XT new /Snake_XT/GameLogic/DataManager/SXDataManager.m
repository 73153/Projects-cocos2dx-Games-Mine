//
//  ELDataManager.m
//  Elevator
//
//  Created by ICRG LABS on 18/04/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SXDataManager.h"
#import "SXUtility.h"
#import "SXGameConstants.h"

@implementation SXDataManager
@synthesize gameLayer,lifeFullArray,highScoreArray,profileArray,mProfile_Arcade,mProfile_Challenge,mProfile_Legendary;


@synthesize isLeftSlide,isAppInsidesideGameScene,isOptionInsideGame,isMainmenuInsideMode,isNewGame,isGamePaused,isLevelCompleted,isLevelFailed,needToSave,isRestartMode,isLevelButtonClicked,mSkullShowed,IsLoadingGame,firstTap,isResumeMode,isSwitchModeInsideGame,isNewArcadeGame,isNewBeginnerGame,isNewLegendaryGame,isPlayAgain,isMultiplayer;

@synthesize totalLevelsCompletd,currentLevel,scores,bonus,noOfParts,numOfLifeLost,noOfLifeAvailable,gameMode,maxNoOfBodiesInLevel,nOOfBonusCollected,LevelFailedCount,noOfLifeBonusCollected;

@synthesize playerName,StaticBodyPosiitons,movableBodyPosiitons,bonusBodyPosiitons;
@synthesize snakeSpeed;

static  SXDataManager *sSharedInstance = nil;


+(SXDataManager *)sharedManager {
    
    @synchronized([SXDataManager class])
	{
		if (!sSharedInstance)
			[[self alloc] init];
        
		return sSharedInstance;
	}
	return nil; 
}

+(id)alloc
{
	@synchronized([SXDataManager class])
	{
		NSAssert(sSharedInstance == nil, @"Attempted to allocate a second instance of a singleton.");
		sSharedInstance = [super alloc];
		return sSharedInstance;
	}
    
	return nil;
}

- (id)init
{
    self = [super init];
    if (self) {
        NSMutableArray *temp=[[NSMutableArray alloc] init];
        self.lifeFullArray=temp;
        [temp release];
        self.highScoreArray=[[NSMutableArray alloc] init];
        self.lifeFullArray=[[NSMutableArray alloc]init];

        self.profileArray=[[NSMutableArray alloc]init];
    
        self.snakeSpeed=2;        
        // Initialization code here.
    }
    
    return self;
}
-(void)saveData:(int)score :(int)part :(int)level{
    scores=score;
    noOfParts=part;
    
    totalLevelsCompletd=level;
    
    
}
-(void) dealloc {
    
    StaticBodyPosiitons=nil;
    movableBodyPosiitons=nil;
    bonusBodyPosiitons=nil;
    self.playerName=nil;
    self.mProfile_Arcade=nil;
    self.mProfile_Challenge=nil;
    self.mProfile_Legendary=nil;
    self.lifeFullArray=nil;
    self.highScoreArray=nil;
    self.profileArray=nil;
    [super dealloc];
}

@end
