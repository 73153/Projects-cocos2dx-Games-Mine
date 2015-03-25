//
//  LMConfig.h
//  LostMonster
//
//  Created by Krithik B on 8/20/12.
//  Copyright (c) 2012 iCRG Labs. All rights reserved.
//

#ifndef LostMonster_LMConfig_h
#define LostMonster_LMConfig_h

#include "cocos2d.h"

using namespace cocos2d;

#define CC_IS_IPHONE() (CCDirector::sharedDirector()->getWinSize().width==480||CCDirector::sharedDirector()->getWinSize().height==480)
#define CC_IS_IPAD() (CCDirector::sharedDirector()->getWinSize().width==1024||CCDirector::sharedDirector()->getWinSize().height==1024)
#define CC_IS_IPAD3() (CC_IS_IPAD() && CC_CONTENT_SCALE_FACTOR()>1.0f)

#define PTM_RATIO 32

#define kRolloWalkingAnimXFactor 2.0
#define kRolloWalkingAnimYFactor 9.0

#define kRolloIdleAnimPosCorrectionFactor ccp(4.0,18.0)
#define kRolloRightQuesMarkAnimPosCorrectionFactor ccp(-12.0,30.0)
#define kRolloLeftQuesMarkAnimPosCorrectionFactor ccp(18.0,5.0)
#define kRolloExitPositionCorrectionFactor 0.5
#define kRolloWinAnimPosCorrectionFactor ccp(-5.0,25.0)

#define kWoodSliceMargin 0.03


#define kSpringMotorTorgue 750
#define kSpringMotorSpeed 200

#define kFountainMotorSpeed 15

#define kClockTime 12

#define ViewSize CGRectMake(0,0,1024, 768)

#define tutorialHeadingLblFrame CGRectMake(413, 160, 200, 50)
#define tutorialLabelFrame CGRectMake(270, 212, 500, 50)
#define continueBtnFrame CGRectMake(430, 600, 171, 43)
#define rScreenFrame CGRectMake(230,277, 590, 252)
#define bgMoviePlayerViewFrame CGRectMake(0, 0, 590, 252)
#define patchImageViewFrame CGRectMake(155,240, 127,287)

#define exitDoorInitialAdjustmentFactor 0.0
#define exitDoorAnimationPosAdjustmentFactor 0.4

#define kLifeRegenerationTime 1

//#define kLostMonsterDebug

enum StatusMessage
{
    kLoginSuccess = 1,
    kLoginFailed = 2,
    kRegistrationSuccess = 3,
    kRegistrationFailed = 4,
    kSyncSuccess = 5,
    kSyncFailed = 6,
};

#endif
 