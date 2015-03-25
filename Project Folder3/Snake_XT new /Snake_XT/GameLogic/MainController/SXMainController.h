//
//  HelloWorldLayer.h
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//


// When you import this file, you import all the cocos2d classes

#import "SXUtility.h"
#import "SXGameConstants.h"
//#import "SXArcadeScene.h"
@class SXLevelManager;
@class SXSnakeManager;
@class SXMultiplayerManager;

@interface SXMainController : CCLayer
{
    
    
    SXLevelManager *leveDetails;
    SXSnakeManager *snakeManager;
    SXMultiplayerManager *multiplayerManager;
    
    
    // SXArcadeScene *acrcadeScene;
    CCLabelTTF *scoreLabel;
    CCLabelTTF *levelLabel;
    CCLabelTTF *partsLabel;
    CCSprite *Scorebg;
    
    CCMenuItemImage *pauseButton;
    CCMenuItemImage *playButton;
    CCMenu *playMenu;
    UITextField *levelDisplay;
    CCLabelTTF *mBodyPartCounter;
    CCSprite *optionsprite;
   // CCSprite *levelCompletedSprite;
    int gameMode;
    int count;
    BOOL isJoystickMode;
    CCSprite *pauseSprite;
    CCSprite *backGround;
    CCSprite *gameOptionmodeBG;
}



@property(nonatomic,retain)SXLevelManager *leveDetails;
@property(nonatomic,retain)SXSnakeManager *snakeManager;
@property(nonatomic,retain)SXMultiplayerManager *multiplayerManager;

@property(nonatomic,assign) CCSprite *backGround;


+(id)scene;  

-(void)update:(ccTime)dt;
-(void)addUI;
-(void) updateLifeArray;
-(void)addBonusLife;
-(void)addlifes;
-(void)startGame;
-(void)pauseOtherDevice;
-(void)resumeOtherDevice;
-(void)gameOver;
-(void)gameWin;


@end
