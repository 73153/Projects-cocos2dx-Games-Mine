//
//  SXGameConstants.h
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//


#define DataManager [SXDataManager sharedManager]

#define SXMainLayer self.gameLayer
typedef enum{
    kTopLeft = 1,
    kTopRight = 2,
    kBottomLeft = 3,
    kBottomRight =4
}RectCorner;

//enum GameModes 
//{
//    kBEGINNERMODE,
//    KLEGENDARYMODE,
//    KARCADEMODE,
//    
//    KLevelCompletedSpriteTag,
//}
//GameMode;

enum
{
	kBonus1 = 1,//shield
	
	kBonus2,            //speed up bonus	
	kBonus3,            //speed down bonus
    
	
	kBonus4,            // butterfly
	
	kBonus5,           // green tree
	
	
	kBonus6,            //life bonus 
    
    kBonus7,          // skull

    
};

#define KBossSnakeTag   100
#define KNonBossSnakeTag 200
#define KStaticbodyTag 1000



#define  kPLAYMODE     @"PlayMode"  // challenge beginner mode
#define KJoystickPos   @"joystickPos"
#define KTotalLevelsCompleted @"total level completed "

#define  kBEGINNERMODE   0  // challenge beginner mode

 #define KLEGENDARYMODE  1  // challenge legendary mode

#define KARCADEMODE      2       //arcade  mode

#define kMenuButtonTag        100
#define kPlayButtonTag         200
#define kRestartButtonTag      300
#define kNextLeveButtonTag     400
#define kSubmitScoreButtonTag   500

#define karcadeProfileDict     @"arcadeProfileDict"
#define kBeginnerProfileDict   @" challengeProfileDict"
#define kLegendaryProfileDict  @"legendaryProfileDict"
#define kLifeAvailable		@"lifesavailable"




#define kProfilesKey			@"profiles"

#define kProfileNameKey			@"profilename"

#define kProfileGameModeKey		@"profilegamemodekey"

#define kProfileDictKey			@"profiledict"

#define kProfileDataKey			@"profilenames"


#define kSaveLevelnumber		@"levelnumer"

#define kSaveNumberOfLifeLost   @"lifeLost"
#define kSaveIsGamePaused       @ "isGamePaused"

#define kSaveBonusScore			@"bonusscore"
#define kSaveNoOfBonusCollected  @"bonusCollected"

#define kSavePointScore			@"pointscore"

#define kSaveRemainingBodyParts	@"remainingbodyparts"
#define kSaveMaxBodiesInLevel   @"maxbodiesInLevel"

#define kSaveBodyPartPositions	@"bodypartpositions"

#define KSaveMovablePartPosiiton @"movablePartPOsiiton" 

#define kSavepathArray			@"patharray"
#define kSaveObstaclesArray     @" obstaclesArray"
#define kSaveLifeArray          @"lifeArray"

#define kSaveHeadPosition		@"headposition"

#define kSaveHeadRotateAngle	@"headrotateangle"

#define kSaveHeadRotateFactor	@"headrotatefactor"

#define kSaveLevelFinished		@"levelfinished"

#define kSaveLevelFailed		@"levelfailed"

#define kSaveSFXVolume			@"sfxvolume"

#define kSaveBGSoundVolume		@"bgsoundvolume"

#define kGameMode				@"gamemode"

#define kSaveGameProperties		@"gameproperties"

#define kSaveChallengeGamePlay	@"challengegameplay"

#define kSnakebodyImage         @"sankeBodyImage"
#define KSnakeHeadIamge         @"snakeHeadImage"
#define kSnakeDullImage         @"snakeDullImage"
#define kSnakeShieldImage       @"snakeShieldImage"
#define kBackgroundImage        @"backgroundImage"

#define KPointsArray           @"pointsArray"
#define KCGPathCoordinates     @"CGPathCoordinates"
#define KMovableObjects        @"movableObjects"
#define KStaticObjects         @"staticObjects"
#define KObstacles             @"obstacles"


#define kLevelStartedLifes		@"levelstartedlifes"

#define kWorldStartedLifes		@"worldstartedlifes"

#define kLevelStartedBonus		@"levelstartedbonus"

#define kLevelStartedPoints		@"levelstartedpoints"

#define kCompletedLevels		@"completedlevels"

#define KBGObstacleOne          CGRectMake(400, 190, 23, 24)

#define KBGObstacleTwo          CGRectMake(170, 211, 60, 60)

#define KBGObstacleThree         CGRectMake(230, 65, 30, 30)

#define KLevelCompletedSprite   100

