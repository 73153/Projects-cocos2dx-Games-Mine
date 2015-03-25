//
//  OptionScene.h
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "CCControlSlider.h"
#import "SXDataManager.h"
@interface SXOptionScene : CCLayer

{
    CCLabelTTF *SnakeSpeedLabel;
    CCSprite *optionBG;
    CCSprite *transparentBG;
    CCControlSlider *snakeSpeedSlider;
    BOOL isJoystickMode;
    CCSprite *touchSprite;
}
+(id)scene;
@end
