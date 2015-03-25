//
//  Constants.h
//  Snake-XT
//
//  Created by i-CRG dinesh on 6/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


enum GameModes 
{
    kBEGINNERMODE,
    KLEGENDARYMODE,
    KARCADEMODE,
}
GameMode;

enum
{
	kBonus_Shield = 1,
	
	kBonus_LifeIncrease,
	
	kBonus_SpeedIncrease,
	
	kBonus_SpeedDecrease,
	
	kBonus_Leprechaun,
	
	kBonus_Skull,	
	
	kBonus_LifeDecrease,
	
	kBonus_LengthDecrease,
	
	
};

#define kProfilesKey			@"profiles"

#define kProfileNameKey			@"profilename"

#define kProfileGameModeKey		@"profilegamemodekey"

#define kProfileDictKey			@"profiledict"

#define kProfileDataKey			@"profilenames"


#define kSaveLevelnumber		@"levelnumer"

#define kSaveLifeAvailable		@"lifesavailable"

#define kSaveBonusScore			@"bonusscore"

#define kSavePointScore			@"pointscore"

#define kSaveRemainingBodyParts	@"remainingbodyparts"

#define kSaveBodyPartPositions	@"bodypartpositions"

#define kSavepathArray			@"patharray"

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




#define kLevelStartedLifes		@"levelstartedlifes"

#define kWorldStartedLifes		@"worldstartedlifes"

#define kLevelStartedBonus		@"levelstartedbonus"

#define kLevelStartedPoints		@"levelstartedpoints"

#define kCompletedLevels		@"completedlevels"


