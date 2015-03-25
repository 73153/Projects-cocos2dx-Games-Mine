//
//  DCRLevelManager.h
//  DarkCityRider
//
//  Created by Krithik B on 02/11/11.
//  Copyright 2011 i-CRG Labs. All rights reserved.
//

#import "SXGameManager.h"



//This Class will Handle the each level objects in the game 
//ie how many humans zombies , vehicles etc in each level

@interface SXLevelManager : SXGameManager
{
    int MaxNoBodies;
    NSString *backGroundImage;
    NSString *schieldimage;
}


@property(nonatomic,assign)int MaxNoBodies;
@property(nonatomic,retain)NSString *backGroundImage;
@property(nonatomic,assign) NSString *schieldimage;
@property(nonatomic,assign) NSString *snakeBodyImage;


-(void)setUpLevelForTheGame:(SXMainController *)game WithLevel:(NSString *)gameLevel;
-(void)setUpLevelForTheGame:(SXMainController *)game  WithGameMode:(int)gameMode;


@end
