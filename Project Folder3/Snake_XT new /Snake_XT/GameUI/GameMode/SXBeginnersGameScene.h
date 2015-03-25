//
//  BeginnersGameScene.h
//  Snake-XT
//
//  Created by i-CRG dinesh on 6/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
@interface SXBeginnersGameScene : CCLayer
{
    CCLabelTTF *scoreLabel;
    BOOL isGamePaused;
    CCSprite *Scorebg;
    NSMutableArray *lifefullArray;
    CCMenuItemImage *pauseButton;
    CCMenuItemImage *playButton;
    CCMenu *playMenu;
    UITextField *levelDisplay;
    CCLabelTTF *mBodyPartCounter;
    CCLayer *optionLayer;
    CCSprite *gameOptionBG;
}
+(id)scene;
@end
