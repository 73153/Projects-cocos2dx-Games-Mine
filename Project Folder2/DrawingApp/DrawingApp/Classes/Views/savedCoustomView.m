//
//  savedCoustomView.m
//  DrawingApp
//
//  Created by i-CRG Labs on 5/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "savedCoustomView.h"


@implementation savedCoustomView


@synthesize savedImageView;
@synthesize delegate;



- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
    }
    return self;
    
    
    
}
-(void)releaseMemory{
    savedImageView=nil;
	delegate=nil;
    
    
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    
    
    
    
    
}
-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
    
    //NSLog(@"touch");
    
    
    
}

-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event{
    
    
    
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
