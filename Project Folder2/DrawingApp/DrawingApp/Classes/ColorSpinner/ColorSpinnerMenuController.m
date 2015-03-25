//
//  ColorSpinnerMenuController.m
//  DrawingApp
//
//  Created by ICRG LABS on 23/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ColorSpinnerMenuController.h"
#import "ColorSpinnerViewController.h"
#import "Singleton.h"

@implementation ColorSpinnerMenuController
@synthesize type2Btn;
@synthesize type1Btn;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)dealloc
{
    [type1Btn release];
    [type2Btn release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle
-(void)viewWillAppear:(BOOL)animated{
    [self rotateButton:self.type1Btn speed:20.0];
    [self rotateButton:self.type2Btn speed:6.0];
    
    [super viewWillAppear:animated];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    [self rotateButton:self.type1Btn speed:20.0];
    [self rotateButton:self.type2Btn speed:6.0];
}

-(void)rotateButton:(UIButton*)inButton speed:(float)inDuration;{
    CALayer *layer = [inButton layer];
	layer.anchorPoint = CGPointMake(0.50f , 0.5f);
	
	CABasicAnimation *rotateAnimation = [CABasicAnimation animation];
	rotateAnimation.keyPath = @"transform.rotation.z";
	////(@"Variation from hour and minute %f",DegreesToRadians(variation));
	rotateAnimation.fromValue = [NSNumber numberWithFloat:(1* M_PI / 180)];
	rotateAnimation.toValue = [NSNumber numberWithFloat:((1 + 360)* M_PI / 180)];
	rotateAnimation.duration = inDuration;
	// leaves presentation layer in final state; preventing snap-back to original state
	rotateAnimation.fillMode = kCAFillModeBoth; 
	rotateAnimation.repeatCount = HUGE_VAL;
	rotateAnimation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear];
	
	// add the animation to the selection layer. This causes it to begin animating. 
	[layer addAnimation:rotateAnimation forKey:@"rotateAnimation"];

}

- (void)viewDidUnload
{
    [self setType1Btn:nil];
    [self setType2Btn:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight) {
		return YES;
	}
	return NO;
}

- (IBAction)back:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)colorSpinnerType1:(UIButton*)sender {
    [Singleton sharedMySingleton].isType1Spinner = TRUE;
    ColorSpinnerViewController *cntr = [[ColorSpinnerViewController alloc] initWithNibName:@"ColorSpinnerViewController" bundle:nil];
    [self.navigationController pushViewController:cntr animated:YES];
	
    [cntr release];
}

- (IBAction)colorSpinnerType2:(UIButton*)sender {
    [Singleton sharedMySingleton].isType1Spinner = FALSE;
    ColorSpinnerViewController *cntr = [[ColorSpinnerViewController alloc] initWithNibName:@"ColorSpinnerViewController" bundle:nil];
    [self.navigationController pushViewController:cntr animated:YES];
    [cntr release];
}

@end
