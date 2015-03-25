//
//  drawpadCustomView.m
//  DrawingApp
//
//  Created by i-CRG Labs on 5/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "drawpadCustomView.h"


@implementation drawpadCustomView

@synthesize padsImageView;
@synthesize delegate;



- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
    }
    return self;
    
    
    
}
-(void)releaseMemory{
    padsImageView=nil;
	delegate=nil;
    
    
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    
    
    
    
    
}
-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
 
    //NSLog(@"touch");
    
    [delegate setpad:self ];
    
    
    
}

-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event{

    
    
}

- (void)dealloc
{
    [self releaseMemory];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
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

- (void)viewDidUnload
{    
    
    [super viewDidUnload];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	return YES;
}

@end
