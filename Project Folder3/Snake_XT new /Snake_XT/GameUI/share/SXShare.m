//
//  SXShare.m
//  Snake_XT
//
//  Created by Pavitra on 01/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXShare.h"
#import "SXMainMenu.h"

@implementation SXShare


+(id)scene{
    CCScene *scen=[CCScene node];
    
    SXShare *layer=[SXShare node];
    [scen addChild:layer];
    return  scen;
}

-(id)init{
    
    if(self=[super init]){
        //bg
        CCSprite *bg=[CCSprite spriteWithFile:@"bg.png"];
        bg.position=ccp(240, 160);
        [self addChild:bg];
        
        
        CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt.png"];
        CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt_hvr.png"];
        
        
        CCMenuItemSprite *backMenuItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goBackAction)];
        backMenuItem.position=ccp(60, 278);

        //share label 
        CCSprite *shareLabelSprite=[CCSprite spriteWithSpriteFrameName:@"label_share.png"];
        [self addChild:shareLabelSprite];
        shareLabelSprite.position=ccp(240, 278);

        
        //share message bg
        CCSprite *shareMessageBG=[CCSprite spriteWithSpriteFrameName:@"share_bg.png"];
        [self addChild:shareMessageBG];
         shareMessageBG.position=ccp(240, 160);
        
        
        
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"facebook.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"facebook_hvr.png"];
        CCMenuItemSprite *facebookMenuitem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToFacebook)];
        facebookMenuitem.position=ccp(310, 190);
        
        
        normalSprite=[CCSprite spriteWithSpriteFrameName:@"twitter.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"twitter_hvr.png"];
        CCMenuItemSprite *twitterMenuitem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToFacebook)];
        twitterMenuitem.position=ccp(350, 190);

        normalSprite=[CCSprite spriteWithSpriteFrameName:@"msg_icon.png"];
        selectedSprite=[CCSprite spriteWithSpriteFrameName:@"msg_icon_hvr.png"];
        CCMenuItemSprite *sendMessageMenuitem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goToFacebook)];
        sendMessageMenuitem.position=ccp(310, 135);
        
        CCMenu *backMenu=[CCMenu menuWithItems:backMenuItem,facebookMenuitem,twitterMenuitem,sendMessageMenuitem, nil];
        backMenu.position=CGPointZero;
        [self addChild:backMenu z:2];
        
    }
    return self;
}

-(void)goBackAction{
    [[CCDirector sharedDirector]replaceScene:[CCTransitionSlideInL transitionWithDuration:.5 scene:[SXMainMenu scene]]];
}

-(void)goToFacebook{
    
}

-(void)dealloc{
    [super dealloc];
}

@end
