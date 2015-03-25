//
//  toolsCoustomView.m
//  DrawingApp
//
//  Created by i-CRG Labs on 5/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "samplesCustomView.h"



@implementation samplesCustomView

@synthesize samplesImageView;
@synthesize delegate;
@synthesize samplesImageId;


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
    }
    return self;
    
    
    
}
-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    
    
    
    
    
}
-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
    NSSet *allTouches = [event allTouches];
	
    int len = [allTouches count]-1;
	
    UITouch *touch =[[allTouches allObjects] objectAtIndex:len];
    CGPoint inLocation = [touch locationInView:[[self superview] superview]];
    [delegate setsample:self locatin:inLocation];
}

-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event{
    
    
    
}


-(void)releaseMemory{
    samplesImageView=nil;
	delegate=nil;
    
    
}

- (void)dealloc
{
    [self releaseMemory];
    [super dealloc];
}


#pragma mark - View lifecycle

/*
 // Implement loadView to create a view hierarchy programmatically, without using a nib.
 - (void)loadView
 {
 }
 */

/*
 // Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
 - (void)viewDidLoad
 {
 [super viewDidLoad];
 }
 */


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}

@end
