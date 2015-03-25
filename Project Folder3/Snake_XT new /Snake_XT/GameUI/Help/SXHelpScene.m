//
//  HelpScene.m
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SXHelpScene.h"
#import "SXMainMenu.h"
#import "CocosDenshion.h"
//#import "CCScrollLayer.h"

@implementation SXHelpScene
#pragma mark-scene

+(id)scene{
    CCScene *scene=[CCScene node];
    SXHelpScene *layer=[SXHelpScene node];
    [scene addChild:layer];
    return scene;
} 
#pragma mark-init

-(id)init{
    if((self=[super init])){
    self.isTouchEnabled=YES;
        CCSprite *sprite=[CCSprite spriteWithFile:@"help_bg.png"];
        
        [self addChild:sprite z:2];
        sprite.position=ccp(240, 160);
//        helpBgImageview=[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"help_bg"]] ;
//        helpBgImageview.frame=CGRectMake(0, 0, 480,320);
//        [[[CCDirector sharedDirector] openGLView] addSubview:helpBgImageview];

        
        CCSprite *normalSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt.png"];
        CCSprite *selectedSprite=[CCSprite spriteWithSpriteFrameName:@"back_bt_hvr.png"];
        
        /// new  game menu item 
        CCMenuItemSprite *backItem=[CCMenuItemSprite itemFromNormalSprite:normalSprite selectedSprite:selectedSprite target:self selector:@selector(goBack)];
        backItem.position=ccp(65, 278); 
        CCMenu *menu=[CCMenu menuWithItems:backItem, nil];
        [self addChild:menu z:2];
        menu.position=CGPointZero;
        
        
        //creating  scroll view
        scrollview = [[UIScrollView alloc] init];
		
		mScrollViewRect=CGRectMake(597
                                   ,57, 408, 230);
		
		[scrollview setFrame:mScrollViewRect];
		
		[scrollview setBackgroundColor:[UIColor clearColor ]];
		
		[scrollview setCanCancelContentTouches:NO];
		
		[scrollview setClipsToBounds:YES];
		
		[scrollview setContentSize:CGSizeMake(408, 934)];
		
		[scrollview setScrollEnabled:YES];
		
		[scrollview setDelegate:self];
		
		scrollview.showsVerticalScrollIndicator=NO;
		
        [[[CCDirector sharedDirector] openGLView] addSubview:scrollview];
        
        
        [UIView beginAnimations:nil context:nil];
        [UIView setAnimationDuration:.5];
        [scrollview setFrame:CGRectMake(25,57, 408, 230)];

        [UIView commitAnimations];

        

        
        //addimg image view to scroll view
        textImageview=[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"help_text"]] ;
       	[textImageview setFrame:CGRectMake(10, 8, 390,924)];
		
		textImageview.autoresizesSubviews = YES;
		
		[scrollview  addSubview:textImageview];
		
		[textImageview release];
		
        //adding scroll bar image 
        	
		        [[CCTouchDispatcher sharedDispatcher]addTargetedDelegate:self priority:1 swallowsTouches:YES];
        

        
    }
    return  self;
}-(void)onEnterTransitionDidFinish{
    
    scrollButton= [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"help_scroll_ball.png"]];
    
    mScrollBallRect=CGRectMake(439,59 , 8,28);
    
    [scrollButton setFrame:mScrollBallRect];
    
    scrollButton.autoresizesSubviews = YES;
    
    
    
    
    [[[CCDirector sharedDirector] openGLView] addSubview:scrollButton];
    
    
    
    [scrollButton release];

}
-(void)goBack{
    
    [scrollview removeFromSuperview];
    [scrollButton removeFromSuperview];
    [helpBgImageview removeFromSuperview];
    
	[[CCDirector sharedDirector] replaceScene: [CCTransitionMoveInL transitionWithDuration:.5 scene:[SXMainMenu scene]]];
    
    
}
#pragma mark-touches

-(BOOL)ccTouchBegan:(UITouch *)touch withEvent:(UIEvent *)event
{
    CGPoint	location = [touch locationInView:[touch view]];
	
	CGRect touchRect=CGRectMake( mScrollBallRect.origin.x ,mScrollBallRect.origin.y,mScrollBallRect.size.width+ 10,mScrollBallRect.size.height);
	
	if(CGRectContainsPoint(touchRect, location))
    
    mControlTapped = YES;
    
    return YES;   
}
    



-(void)ccTouchMoved:(UITouch *)touch withEvent:(UIEvent *)event{
    CGPoint	location = [touch locationInView:[touch view] ];
    
    if(mControlTapped)
    {
        mScrollBallRect.origin.y = location.y - 14;
        
        if(mScrollBallRect.origin.y > 259)
            mScrollBallRect.origin.y =258;
        if(mScrollBallRect.origin.y < 59)
            mScrollBallRect.origin.y =59;
    }
    [self resetControlFrame];
    
    [[[CCDirector sharedDirector] openGLView]setNeedsDisplay];
    
}


-(void)resetControlFrame

{
    [scrollButton setFrame:mScrollBallRect];
    
	float offset = (mScrollBallRect.origin.y - 59) * 3.55;
    
	[scrollview setContentOffset:CGPointMake(0,offset) animated:NO];
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
	mScrollBallRect.origin.y = (scrollView.contentOffset.y/3.55) + 59;
	
	if(mScrollBallRect.origin.y > 259)
		mScrollBallRect.origin.y =258;
	if(mScrollBallRect.origin.y < 59)
		mScrollBallRect.origin.y =59;
	
    [scrollButton setFrame:mScrollBallRect];
	
}

- (void) touchesEnded:(NSSet*)touches withEvent:(UIEvent*)event
{
	
	mControlTapped=NO;
}
#pragma  mark- dealloc
-(void)dealloc{
    [self removeAllChildrenWithCleanup:YES];
    [scrollview release];
    [super dealloc];
}
@end
