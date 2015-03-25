//
//  GameScene.h
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "SXGameOptionMenuScene.h"
#import "SXOptionScene.h"
#import "SXOtherAppScene.h"
#import "SXGameModeMenuScene.h"
#import "SXMainMenu.h"

@interface SXGameScene : CCLayer
{
    int count;
    CCLabelTTF *scoreLabel;
    CCLabelTTF *levelLabel;
    CCLabelTTF *partsLabel;
    CCSprite *Scorebg;

    BOOL isGamePaused;
    NSMutableArray *lifefullArray;
    CCMenuItemImage *pauseButton;
    CCMenuItemImage *playButton;
    CCMenu *playMenu;
    UITextField *levelDisplay;
    CCLabelTTF *mBodyPartCounter;
    CCLayer *optionLayer;
    CCSprite *optionsprite;
  
    
}
@property(nonatomic,retain)CCLayer *optionLayer;
+(id)scene;
-(void)addGameOptionLayer;

-(id)initWith:(int)score:(int)parts;

@end
