//
//  ArcadeScene.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXArcadeScene.h"
#import "SXMainMenu.h"
#import "SXGameScene.h"
#import "SXMainController.h"
#import "SXGameConstants.h"
@implementation SXArcadeScene
+(id)scene{
    CCScene *scene=[CCScene node];
    SXArcadeScene *layer=[SXArcadeScene node];
    [scene addChild:layer];
    return scene;
}
#pragma mark-init
-(id)init{
    
    if((self=[super init]))
    {
        
        layer1=[CCLayer node];
        layer2=[CCLayer node];
        
        CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt.png"];
        CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt_hvr.png"];
        
        
        CCMenuItemSprite *backMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goBackAction)];
        backMenuItem.position=ccp(60, 278);
    
        
        
        
        //adding bg 
        firstLevelSelectionBGsprite=[CCSprite spriteWithFile:@"level_bg.png"];
        firstLevelSelectionBGsprite.position=ccp(240,160);
        [self addChild:firstLevelSelectionBGsprite z:1];
        NSUserDefaults *userdefault=[NSUserDefaults standardUserDefaults];
       DataManager.totalLevelsCompletd=[userdefault integerForKey:KTotalLevelsCompleted];
       DataManager.scores=[userdefault integerForKey:kSavePointScore];
        
        
        if(DataManager.totalLevelsCompletd!=0 ){
            
            DataManager.isLevelCompleted=NO;
            [self updateLevelButtons];
            DataManager.noOfLifeAvailable=[userdefault integerForKey:kLifeAvailable];
        }
        
        else
        {
            [self addLevelButtons];
            DataManager.noOfLifeAvailable=5;
            DataManager.totalLevelsCompletd=1;
            DataManager.scores=0;
        }

        NSArray *layerArray=[[NSArray alloc]initWithObjects:layer1,layer2, nil];
        
        scrollLayer =[CCScrollLayer nodeWithLayers:layerArray widthOffset:0];
        [self addChild:scrollLayer z:2];
        
       
        normalSprite =[CCSprite spriteWithSpriteFrameName:@"reset_game.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"reset_game.png"];
        CCMenuItemSprite *lockLevelItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(UnlockAllLevels)];
        
        lockLevelItem.position=ccp(60, 30);
        
        CCMenu *Menu=[CCMenu menuWithItems:backMenuItem,lockLevelItem, nil];
        Menu.position=CGPointZero;
        [self addChild:Menu z:2];
    }
    return self;
}

-(void)UnlockAllLevels{
    DataManager.totalLevelsCompletd=28;
    DataManager.noOfLifeAvailable=5;

    NSUserDefaults *userdefault=[NSUserDefaults standardUserDefaults];
    [userdefault  setValue:[NSString stringWithFormat:@"%d",DataManager.totalLevelsCompletd] forKey:KTotalLevelsCompleted];
    [userdefault  setValue:[NSString stringWithFormat:@"%d",DataManager.noOfLifeAvailable] forKey:kLifeAvailable];

    [[CCDirector sharedDirector]replaceScene:[SXGameModeMenuScene scene]];

}

-(void)goBackAction{
    [[CCDirector sharedDirector] replaceScene: [CCTransitionMoveInL transitionWithDuration:.5 scene:[ SXGameModeMenuScene scene]]] ;
}


#pragma mark- level buttons 
-(void)addLevelButtons
{  
    float x=170;
    float y=210;
    float lockXPos=185;
    float LockYPos=195;
    
    
    CCSprite *levelsBG=[CCSprite spriteWithSpriteFrameName:@"level_sele_bg.png"];
    levelsBG.position=ccp(100, 210);
    [layer1 addChild:levelsBG];
    
    CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"level_1.png"];
    CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"level_1.png"];
    
    
    
    
    CCMenuItemSprite *level1MenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(startGameWithLevel:)];
    level1MenuItem.tag=1;
    level1MenuItem.position=ccp(100, 210);
    
    
    
    CCMenu *levelMenu=[CCMenu menuWithItems:level1MenuItem, nil];
    [layer1 addChild:levelMenu];
    levelMenu.position=CGPointZero;
    
    
    //adding level buttons
    for(int i=2;i<=28;i++)
    {
        //adding lock 
        CCSprite *lockSprite=[CCSprite spriteWithSpriteFrameName:@"lock.png"];
        lockSprite.position=ccp(lockXPos, LockYPos);
        
        //adding leevl bg 
        CCSprite *levelsBG=[CCSprite spriteWithSpriteFrameName:@"level_sele_bg.png"];
        levelsBG.position=ccp(x, y);
        
        // adding level umber sprite 
        NSString *normalSpriteImageName=[NSString stringWithFormat:@"level_%d_hvr.png",i];
        
        normalSprite=[CCSprite spriteWithSpriteFrameName:normalSpriteImageName];
        normalSprite.position=ccp(x, y);
        
         
        
        
        if(i<16)
        {
            if(i%5==0){
                x=100;
                y=y-65;
                lockXPos=120;
                LockYPos=LockYPos-65;
                
            }
            else{
                x=x+70;
                lockXPos=lockXPos+70;
                
            }
            [layer1 addChild:lockSprite];
            [layer1 addChild:normalSprite];
            [layer1 addChild:levelsBG];
        }
        
        else{
            if(i%5==0){
                x=100;
                y=y-65;
                lockXPos=120;
                LockYPos=LockYPos-65;
                
            }
            else{
                x=x+70;
                lockXPos=lockXPos+70;
                
            }
            [layer2 addChild:lockSprite];
            [layer2 addChild:normalSprite];
            [layer2 addChild:levelsBG];
        }
        
        if(i==15)
        {
            x=100;
            y=210;
            lockXPos=120;
            LockYPos=195;
        }
        
    }
}     


- (void)updateLevelButtons // updating level buttons
{
    
    float x=100;
    float y=210;
    float lockXPos=118;
    float LockYPos=193;
    
    CCSprite *normalSprite;
    CCSprite *selectedSprite;
    CCSprite *levelNumber;
    
    int i;
    
    
    normalSprite=[CCSprite spriteWithSpriteFrameName:@"level_1.png"];
    selectedSprite=[CCSprite spriteWithSpriteFrameName:@"level_1.png"];
    CCMenuItemSprite *level1MenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(startGameWithLevel:)];
    level1MenuItem.tag=1;
    level1MenuItem.position=ccp(100, 210);
    
    
    
    CCMenu *levelMenu=[CCMenu menuWithItems:level1MenuItem, nil];
    levelMenu.position=CGPointZero;  
    [layer1 addChild:levelMenu];

    
    normalSprite=[CCSprite spriteWithSpriteFrameName:@"level_16.png"];
    selectedSprite=[CCSprite spriteWithSpriteFrameName:@"level_16.png"];
    CCMenuItemSprite *level16MenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(startGameWithLevel:)];
    level16MenuItem.tag=16;
    level16MenuItem.position=ccp(100, 210);
    CCMenu *levelMenu1=[CCMenu menuWithItems:level16MenuItem, nil];
    levelMenu1.position=CGPointZero;  
    [layer2 addChild:levelMenu1];

    
    for (i = 1; i <= 28; i ++)   // for all 28 lebels
    {
       CCSprite *levelsBG=[CCSprite spriteWithSpriteFrameName:@"level_sele_bg.png"];
        levelsBG.position=ccp(x, y);
        if(i <=DataManager.totalLevelsCompletd)  // updating button till noumber of level completed
        {
            NSString *normalSpriteImageName=[NSString stringWithFormat:@"level_%d.png",i];
            NSString *selectedSpriteImageName=[NSString stringWithFormat:@"level_%d_hvr.png",i];
            
            normalSprite=[CCSprite spriteWithSpriteFrameName:normalSpriteImageName];
            selectedSprite=[CCSprite spriteWithSpriteFrameName:selectedSpriteImageName];
            CCMenuItemSprite *levelMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(startGameWithLevel:)];
            levelMenuItem.tag=i;
            levelMenuItem.position=CGPointMake(x, y);
            
            if(i>=16){
                [levelMenu1 addChild:levelMenuItem];

            }
            else{
                [levelMenu addChild:levelMenuItem];

            }
        }
        
        
        else   //adding normal sprite
        {
            
            // adding level umber sprite 
            NSString *normalSpriteImageName=[NSString stringWithFormat:@"level_%d_hvr.png",i];
            
           levelNumber=[CCSprite spriteWithSpriteFrameName:normalSpriteImageName];
            levelNumber.position=ccp(x, y);
          

            
            CCSprite *lockSprite=[CCSprite spriteWithSpriteFrameName:@"lock.png"];
            lockSprite.position=ccp(lockXPos, LockYPos);
            if(i<16){
                [layer1 addChild:levelNumber];
                [layer1 addChild:lockSprite];
                
            }
            else{
                [layer2 addChild:levelNumber];
                [layer2 addChild:lockSprite];
                
            }
        }
        
        if(i%5==0){
            x=100;
            y=y-65;
            lockXPos=x+15;
            LockYPos=y-16;
            
        }
        else{
            x=x+70;
            lockXPos=lockXPos+70;
            
        }
        if(i<16){
            [layer1 addChild:levelsBG];
        }
        
        else{
          
            [layer2 addChild:levelsBG];

        }
        
        if(i==15)
        {
            x=100;
            y=210;
            lockXPos=117;
            LockYPos=195;
        }
        
    }

}




#pragma mark-level button action
-(void)startGameWithLevel:(id)sender{ 
    DataManager.LevelFailedCount=0;
   // DataManager.noOfLifeAvailable=[DataManager.lifeFullArray count];
    
    DataManager.currentLevel=[sender tag];
    CCSprite *loadingsprite=[CCSprite spriteWithFile:@"loading.png"]; // adding loading sprite 
    [self addChild:loadingsprite z:3];
    
    loadingsprite.position=ccp(240, 350);
    id action=[CCMoveTo actionWithDuration:0.5 position:ccp(240, 160)]; 
    
    [loadingsprite runAction:[CCSpawn actions:action,nil]];
    [self runAction:[CCDelayTime actionWithDuration:2]]; // giving action for loading sprite to make it move to center before starting game
        [[CCDirector sharedDirector ]replaceScene:[CCTransitionFade transitionWithDuration:1 scene:[SXMainController scene]]];// 

}


#pragma  mark- deallocResources
-(void)dealloc{
    
    [layer1 removeAllChildrenWithCleanup:YES];
    [layer2 removeAllChildrenWithCleanup:YES];
    [scrollLayer removeAllChildrenWithCleanup:YES];
    [self removeChild:scrollLayer cleanup:YES];
    [super dealloc];
}
@end
