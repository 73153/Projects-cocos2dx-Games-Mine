//
//  SXBonus.h
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/12/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SXCustomSprite.h"
#import "SXSnakeManager.h"
@interface SXBonus : SXCustomSprite 
{
    SXSnakeManager *snManager; 
    int type;
    NSString *glowImage;
}
@property(nonatomic,assign)SXSnakeManager *snManager;
@property(nonatomic,assign)int type;
@property(nonatomic,retain)NSString *glowImage;

//-(void)addingBonus:(CGPoint)position withLayer:(SXMainController*)layer withManager:(SXSnakeManager*)manager type:(BOOL)isShield;
-(void)addingBonus:(CGPoint)position withLayer:(SXMainController*)layer withManager:(SXSnakeManager*)manager type:(int)bonusType;

-(void)setShieldGlowEffect;

@end
