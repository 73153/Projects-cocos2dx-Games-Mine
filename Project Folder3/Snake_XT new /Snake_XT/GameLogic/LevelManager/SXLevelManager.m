//
//  DCRLevelManager.m
//  DarkCityRider
//
//  Created by Krithik B on 02/11/11.
//  Copyright 2011 i-CRG Labs. All rights reserved.
//

#import "SXLevelManager.h"
#import "SXUtility.h"
#import "SXSnakeManager.h"
#import "SXDataManager.h"
#import "SXObstacle.h"


@implementation SXLevelManager
@synthesize MaxNoBodies,backGroundImage,schieldimage,snakeBodyImage;


- (id)init
{
    self = [super init];
    if (self) {
        
        
    }
    
    return self;
}

-(void)setUpLevelForTheGame:(SXMainController *)game  WithGameMode:(int)gameMode
{
    
    self.gameLayer = game;
    
    NSString *basepath=[SXUtility getTheBasePathForPlist:@"SnakeXTLevelDetails"];
    
    if([[NSFileManager defaultManager]fileExistsAtPath:basepath])
    {
        NSDictionary  *gameDict=[NSDictionary dictionaryWithContentsOfFile:basepath];
        
        
        
        
        NSMutableArray *modeArray=[gameDict objectForKey:@"GameModeLevelDetails"];
        NSDictionary *modeDict;
        
        switch (gameMode) {
            case 0:
                modeDict= [modeArray objectAtIndex:0];
                DataManager.isNewBeginnerGame=NO;
                
                break;
                
                
            case 1:
                DataManager.isNewLegendaryGame=NO;
                modeDict= [modeArray objectAtIndex:1];
                
                break;
                
            default:
                break;
        }
        self. backGroundImage=[modeDict objectForKey:@"BackGroundImage"];
        //DataManager.backgroundImage=backGroundImage;
        
        NSDictionary *snakeHeadDict=[ modeDict objectForKey:@"SnakeHead"];
        SXMainLayer.snakeManager. snakeHeadImage=[snakeHeadDict objectForKey:@"SnakeHeadImage"];
        
        
        
        //getting head coordinates 
        
        NSString *headcoordinateString=[modeDict objectForKey:@"HeadCoordinates"];
        NSArray *headCoordinatArray=[headcoordinateString componentsSeparatedByString:@"|"];
        
        
        
        // getting cgPath  points for head 
        
        NSString * headCGPathPointsStrig=[modeDict objectForKey:@"HeadCgPathPoints"];
        
        NSArray *cgPathPointsArray=[headCGPathPointsStrig componentsSeparatedByString:@","];
        
        CGPoint snakePosition= CGPointFromString([snakeHeadDict objectForKey:@"Position"]);
        
        
        
        [SXMainLayer.snakeManager createSnakeHead:snakePosition withImageName:SXMainLayer.snakeManager.snakeHeadImage withHeadCoordinatesL:headCoordinatArray withCGPathPointsArray:cgPathPointsArray];
        
        
        
        
        //dull image 
        SXMainLayer.snakeManager.snakeDullImage=[modeDict objectForKey:@"dullImage"];
        
        //shield image
        SXMainLayer.snakeManager.shieldImage=[modeDict objectForKey:@"shield"];
        
        // obstacle array 
        NSArray *obstacleArray =[modeDict objectForKey:@"ObstacleRect"];
        
        for( int i=0;i<[obstacleArray count];i++)
        {
            [SXMainLayer.snakeManager.obstacleArray addObject:[obstacleArray objectAtIndex:i]];
        }
        
        
        //snake body image name  and position 
        NSArray *SnakeBodyArray =[modeDict objectForKey:@"SnakeBody"];
        for (NSDictionary *aBodyDictionary in SnakeBodyArray) 
        {
            SXMainLayer.snakeManager.snakeBodyImage=[aBodyDictionary objectForKey:@"SnakeBodyImage"];
            CGPoint snakeBodyPosition= CGPointFromString([aBodyDictionary objectForKey:@"Position"]);
            [SXMainLayer.snakeManager createSnakeParts:snakeBodyPosition withImageName:SXMainLayer.snakeManager.snakeBodyImage];
        }
        
        
        // getting obscatcle points
        
        NSMutableArray *obstacleArray1=[modeDict objectForKey:@"obstacles"];
        for (NSDictionary *obstacleDict in obstacleArray1)
        {
            NSString *obstacleImage=[obstacleDict objectForKey:@"obstacleImage"];
            CGPoint obstaclePosition=CGPointFromString([obstacleDict objectForKey:@"position"]);
            NSString *obstacleCoordinateString=[obstacleDict objectForKey:@"coordinates"];
            NSArray *cocordinateArray=[obstacleCoordinateString componentsSeparatedByString:@"|"];
            [SXMainLayer.snakeManager addingObstaclesWithPosition:obstaclePosition withImageName:obstacleImage withPointsArray:cocordinateArray];
        }
    }
}


// load level details for arcade mode 
-(void)setUpLevelForTheGame:(SXMainController *)game WithLevel:(NSString *)gameLevel
{
    self.gameLayer = game;
    
    NSString *basepath=[SXUtility getTheBasePathForPlist:@"SnakeXTLevelDetails"];
    
    if([[NSFileManager defaultManager]fileExistsAtPath:basepath])
    {
        NSDictionary  *gameDict=[NSDictionary dictionaryWithContentsOfFile:basepath];  // game dict 
        NSDictionary *levelDict=[gameDict objectForKey:gameLevel];                 // perticular level dict 
        
        
        //Snake Head
        NSDictionary *snakHeadDict=[levelDict objectForKey:@"SnakeHead"];
        SXMainLayer.snakeManager.snakeHeadImage=[snakHeadDict objectForKey:@"SnakeHeadImage"];
        
        
        //getting head coordinates 
        NSString *headcoordinateString=[levelDict objectForKey:@"HeadCoordinates"];
        NSArray *headCoordinatArray=[headcoordinateString componentsSeparatedByString:@"|"];
        
        
        
        // getting cgPath  points for head 
        
        NSString * headCGPathPointsStrig=[levelDict objectForKey:@"HeadCgPathPoints"];
        
        NSArray *cgPathPointsArray=[headCGPathPointsStrig componentsSeparatedByString:@","];
        
        CGPoint snakePosition= CGPointFromString([snakHeadDict objectForKey:@"Position"]);
        
        
        [SXMainLayer.snakeManager createSnakeHead:snakePosition withImageName:SXMainLayer.snakeManager.snakeHeadImage withHeadCoordinatesL:headCoordinatArray withCGPathPointsArray:cgPathPointsArray];
        
        
        //Snake Body
        NSArray *SnakeBodyArray =[levelDict objectForKey:@"SnakeBody"];
        for (NSDictionary *aBodyDictionary in SnakeBodyArray) 
        {
            SXMainLayer.snakeManager.snakeBodyImage=[aBodyDictionary objectForKey:@"SnakeBodyImage"];
            CGPoint snakeBodyPosition= CGPointFromString([aBodyDictionary objectForKey:@"Position"]);
            [SXMainLayer.snakeManager createSnakeParts:snakeBodyPosition withImageName:SXMainLayer.snakeManager.snakeBodyImage];
        }
        
        [SXDataManager sharedManager].maxNoOfBodiesInLevel=[[levelDict objectForKey:@"NumberOfBodies"]intValue];
        MaxNoBodies=[SXDataManager sharedManager].maxNoOfBodiesInLevel;
        self. backGroundImage=[levelDict objectForKey:@"BackGroundImage"];
        SXMainLayer.snakeManager.snakeDullImage=[levelDict objectForKey:@"dullImage"];
        
        
        // getting obscatcle points
        
        NSMutableArray *obstacleArray=[levelDict objectForKey:@"obstacles"];
        for (NSDictionary *obstacleDict in obstacleArray)
        {
            NSString *obstacleImage=[obstacleDict objectForKey:@"obstacleImage"];
            CGPoint obstaclePosition=CGPointFromString([obstacleDict objectForKey:@"position"]);
            NSString *obstacleCoordinateString=[obstacleDict objectForKey:@"coordinates"];
            NSArray *cocordinateArray=[obstacleCoordinateString componentsSeparatedByString:@"|"];
            [SXMainLayer.snakeManager addingObstaclesWithPosition:obstaclePosition withImageName:obstacleImage withPointsArray:cocordinateArray];
        }
        
        NSString *obstaclePointsString=[levelDict objectForKey:@"obstacleAttributePoints"];
        NSArray *tempObstaclePointsArray=[ obstaclePointsString componentsSeparatedByString:@"|"];
        
        for(int i=0;i<[tempObstaclePointsArray count];i++)
        {
            CGPoint tempPos=CGPointFromString([tempObstaclePointsArray objectAtIndex:i]);
            [SXMainLayer.snakeManager.obstacleAtributePointsArray addObject:[NSValue valueWithCGPoint:tempPos]];
        }
        
        //shield image 
        SXMainLayer.snakeManager.shieldImage=[levelDict objectForKey:@"Shield"];
    }
}

- (void)dealloc 
{
    self.backGroundImage=nil;
    [super dealloc];
}

@end
