//
//  moreAppsViewcontroller.m
//  DrawingApp
//
//  Created by i-CRG Labs on 5/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "moreAppsViewcontroller.h"


@implementation moreAppsViewcontroller

@synthesize backButton;
@synthesize creativeButton;
@synthesize clockButton;
@synthesize clock2Button;
@synthesize loveButton;
@synthesize love2Button;
@synthesize fallsButton;
@synthesize falls2Button;
@synthesize scrollview;
@synthesize mistPromoScrollView;


#pragma mark -
#pragma mark   ------apps actions
// actions for apps buttons

-(IBAction)select_creativeapp:(id)sender{
    NSString *storeAdd = nil;
    storeAdd = @"http://itunes.apple.com/app/id413990429?mt=8"; //creative pad
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:storeAdd]];
}

-(IBAction)select_clockapp_iphone:(id)sender{
    NSString *storeAdd = nil;
    storeAdd = @"http://itunes.apple.com/app/id458191967?mt=8"; //clocks iphone
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:storeAdd]];
}

-(IBAction)select_clockapp_ipad:(id)sender{
    NSString *storeAdd = nil;
    storeAdd = @"http://itunes.apple.com/app/id458188819?mt=8"; //clocks iPad
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:storeAdd]];
}

-(IBAction)select_loveapp_iphone:(id)sender{
    NSString *storeAdd = nil;
    //love forever 416981516
    storeAdd = @"http://itunes.apple.com/app/id416981516?mt=8";
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:storeAdd]];
    
}

-(IBAction)select_loveapp_ipad:(id)sender{
    NSString *storeAdd = nil;
    //love forever HD 416952665
    storeAdd = @"http://itunes.apple.com/app/id416952665?mt=8"; 
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:storeAdd]];
}

-(IBAction)select_fallsapp_iphone:(id)sender{
    NSString *storeAdd = nil;
    storeAdd = @"http://itunes.apple.com/app/id458627344?mt=8"; //waterfalls iPad
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:storeAdd]];
}

-(IBAction)select_fallsapp_ipad:(id)sender{
    NSString *storeAdd = nil;
    storeAdd = @"http://itunes.apple.com/app/id458629667?mt=8"; //waterfalls iPad
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:storeAdd]];
}

- (IBAction)mistybaby:(id)sender {
    NSString *storeAdd = nil;
    storeAdd = @"http://itunes.apple.com/app/id466257998?mt=8"; //misty baby

    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:storeAdd]];

}



#pragma mark -
#pragma mark   ------

-(IBAction)goBack{
    
    [self.navigationController popViewControllerAnimated:YES];
}

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
    [mistPromoScrollView release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.scrollview. contentSize=CGSizeMake(480,700);
    self.mistPromoScrollView.contentSize=CGSizeMake(1772,CGRectGetHeight(self.mistPromoScrollView.frame));
    self.navigationController.navigationBar.hidden=YES;
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [self setMistPromoScrollView:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	if (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight) {
		return YES;
	}
	return NO;
}

@end
