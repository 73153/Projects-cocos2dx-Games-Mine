//
//  mainMenuViewController.m
//  DrawingApp
//
//  Created by i-CRG Labs on 5/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "mainMenuViewController.h"
#import "DrawingAppViewController.h"
#import "moreAppsViewcontroller.h"
#import "ColorSpinnerMenuController.h"


@implementation mainMenuViewController

@synthesize viewController;
@synthesize  drawingButton; 
@synthesize  moreApps;
@synthesize  appController;
@synthesize   closebutton;
@synthesize  helpscrollview;
@synthesize  helpview;
@synthesize buttonsView;
@synthesize ScrollViewBackGround;
@synthesize helpImage;



////splashing buttons
@synthesize lemonyellow;
@synthesize crm_yellow;
@synthesize yellow_orch;
@synthesize orange;
@synthesize red;
@synthesize brown;
@synthesize voilet;
@synthesize lightgreen;
@synthesize purple;
@synthesize blue;
@synthesize navy_blue;
@synthesize black;
@synthesize white;
@synthesize yellow;
@synthesize saffron;
@synthesize pink;
@synthesize scr_red;


///actions for splashing buttons

-(IBAction)Select_lemonyellow{
    
}
-(IBAction)Select_crm_yellow{
    
}
-(IBAction)Select_yellow_orch{
    
}
-(IBAction)Select_orange{
    
}
-(IBAction)Select_red{
    
}
-(IBAction)Select_brown{
    
}
-(IBAction)Select_voilet{
    
}
-(IBAction)Select_lightgreen{
    
}
-(IBAction)Select_purple{
    
}
-(IBAction)Select_blue{
    
}
-(IBAction)Select_navy_blue{
    
}
-(IBAction)Select_black{
    
}
-(IBAction)Select_white{
    
}
-(IBAction)Select_yellow{
    
}
-(IBAction)Select_saffron{
    
}
-(IBAction)Select_pink{
    
}
-(IBAction)Select_scr_red{
    
}

-(IBAction)colorSpinner:(id)inSender;{
    ColorSpinnerMenuController *cntr = [[ColorSpinnerMenuController alloc] initWithNibName:@"ColorSpinnerMenuController" bundle:nil];
    [self.navigationController pushViewController:cntr animated:YES];
    [cntr release];
}

-(IBAction)goToDraw 
{
    if(self.viewController){
        [self.navigationController pushViewController:self.viewController animated:YES];
    }
    else{
        DrawingAppViewController *_viewController=[[DrawingAppViewController alloc]init];
        self.viewController = _viewController;
        self.viewController.title=@"DrawingPad";
        [self.navigationController pushViewController:self.viewController animated:YES];
        [_viewController release];
    }
}

-(IBAction)showHelp{
    
    [UIView beginAnimations:@"open" context:nil];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.helpview.alpha=1;
    self.ScrollViewBackGround.alpha=1;
    [UIView commitAnimations];
    
    CGRect frame=CGRectMake( 0,0,1004, 768);
	helpview.frame=frame;
	[self.view addSubview:helpview];
    //[self.view bringSubviewToFront:menuButton];
     self.helpscrollview. contentSize=CGSizeMake(468,1350);
}

-(IBAction)closeHelp{
    
    [UIView beginAnimations:@"hide" context:nil];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.helpview.alpha=0;
    self.ScrollViewBackGround.alpha=0;
    [UIView commitAnimations];

}

-(IBAction)showMoreApps{
    appController=[[moreAppsViewcontroller alloc]init];
    appController.title=@"moreApps";
    [self.navigationController pushViewController:appController animated:YES];
    [appController release];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

-(void)releaseMemory
{
    self.viewController=nil;
    drawingButton=nil; 
    moreApps=nil;
    appController=nil;
    closebutton=nil;
    helpscrollview=nil;
    helpview=nil;
}

- (void)dealloc
{   [self releaseMemory];
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
    
//    UIImageView *img = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"water-colour_palette_2.png"]];
//    [self.view addSubview:img];
//    [img setBackgroundColor:[UIColor redColor
//                             ]]; 
	
//	cocosViewe = [[Menu_CocosCreator alloc] initWithFrame:CGRectMake(0,0,1024,768)];
//    [self.view addSubview:cocosViewe];
//    [cocosViewe release];
	
    [super viewDidLoad];
	self.navigationController.navigationBar.hidden=YES;
    
    CGRect frame=CGRectMake( 40,300 , 731, 495);
	buttonsView.frame=frame;
	[self.view addSubview:buttonsView];
    [self.view bringSubviewToFront:buttonsView];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
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
