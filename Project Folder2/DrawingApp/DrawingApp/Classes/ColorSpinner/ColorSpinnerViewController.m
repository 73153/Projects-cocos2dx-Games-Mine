//
//  ColorSpinnerViewController.m
//  DrawingApp
//
//  Created by ICRG LABS on 23/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ColorSpinnerViewController.h"


@implementation ColorSpinnerViewController
@synthesize colorSpeedView;
@synthesize colorPalette;
@synthesize selectedColorBtn,selectedPatternBtn;
@synthesize colorListBtn;
@synthesize randomColorBtn;
@synthesize colorTransView;
@synthesize speedSlider;
@synthesize startStopBtn;
@synthesize patternPaletterView;
@synthesize patternsBtn;

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
    self.selectedColorBtn = nil;
    self.selectedPatternBtn = nil;
    [colorPalette release];
    [colorListBtn release];
    [randomColorBtn release];
    [colorTransView release];
    [speedSlider release];
    [colorSpeedView release];
    [startStopBtn release];
    [patternPaletterView release];
    [patternsBtn release];
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
    self.startStopBtn.selected = YES;
    self.randomColorBtn.selected = YES;
    self.colorSpeedView.delegate = self;
    [self.colorSpeedView loadSliderView];
    
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
	
	// Creating the Cocos2d View 
	Menu_cocosView = [[Menu_CocosCreator alloc] initWithFrame:CGRectMake(0,0,768,1024)];
    [self.view addSubview:Menu_cocosView];
    [Menu_cocosView release];
	
	// Default Values
	[Singleton sharedMySingleton].isRandomColor = TRUE;
    [Singleton sharedMySingleton].isStopRotation = FALSE;
	
	[self.view insertSubview:self.colorListBtn aboveSubview:Menu_cocosView];
	[self.view insertSubview:self.randomColorBtn aboveSubview:Menu_cocosView];
	[self.view insertSubview:clearBtn aboveSubview:Menu_cocosView];
    [self.view insertSubview:self.patternsBtn aboveSubview:Menu_cocosView];
	[self.view insertSubview:backBtn aboveSubview:Menu_cocosView];
    [self.view insertSubview:self.speedSlider aboveSubview:Menu_cocosView];
	[self.view insertSubview:speedLbl aboveSubview:Menu_cocosView];
    [self.view insertSubview:self.startStopBtn aboveSubview:Menu_cocosView];
    [self.view insertSubview:self.colorSpeedView aboveSubview:Menu_cocosView];
    [self.view insertSubview:self.colorTransView aboveSubview:Menu_cocosView];
	
	[self pickPattern:self.patternsBtn];
	
	self.selectedPatternBtn = secPattern;
	
	self.selectedPatternBtn.layer.borderWidth = 2.0f;
	self.selectedPatternBtn.layer.borderColor = [UIColor whiteColor].CGColor;
}

- (void)viewDidUnload
{
    self.selectedColorBtn = nil;
    [self setColorPalette:nil];
    [self setColorListBtn:nil];
    [self setRandomColorBtn:nil];
    [self setColorTransView:nil];
    [self setSpeedSlider:nil];
    [self setColorSpeedView:nil];
    [self setStartStopBtn:nil];
    [self setPatternPaletterView:nil];
    [self setPatternsBtn:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	if (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight) {
		return YES;
	}
	return NO;
}

#pragma mark - Actions
- (IBAction)wheelSpeed:(UISlider*)sender {
    
    //NSLog(@"Speed is %f",[sender value]);
    
    [Menu_cocosView.mCurrentLayerl setRotaionSpeed:(int)[sender value]];

}

- (IBAction)pickPattern:(UIButton*)sender {
    sender.selected = !sender.selected;
    float alpha = (sender.selected)?1.0:0.0;
    
    if(nil == self.patternPaletterView.superview){
        CGRect rect = self.patternPaletterView.frame;
        rect.origin = CGPointMake(CGRectGetMinX(sender.frame)-CGRectGetWidth(rect)-10, CGRectGetMinY(sender.frame));
        self.patternPaletterView.frame = rect;
        self.patternPaletterView.alpha = 0.0;
        [self.view addSubview:self.patternPaletterView];
    }
    
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
    self.patternPaletterView.alpha = alpha;
    [UIView commitAnimations];

}

- (IBAction)choosePattern:(UIButton*)sender {
    
    if(self.selectedPatternBtn != sender || sender.tag == 9){
        self.selectedPatternBtn.layer.borderWidth = 0.0f;
        self.selectedPatternBtn.layer.borderColor = [UIColor clearColor].CGColor;
        
        self.selectedPatternBtn = sender;
        
        self.selectedPatternBtn.layer.borderWidth = 2.0f;
        self.selectedPatternBtn.layer.borderColor = [UIColor whiteColor].CGColor;
        
        NSString *patternName= @"ball_3.png";
        
        if(sender.tag >=1 && sender.tag <=8){
            patternName = [NSString stringWithFormat:@"%d.png",sender.tag];
        }
        else if(0 == sender.tag){
            patternName = @"ball_3.png";
        }
        else{
            NSInteger index = arc4random()%6;
            index +=9;
            if(index<9 || index>15)index=9;
            patternName = [NSString stringWithFormat:@"%d.png",index];
        }
        //Update the selected pattern
        [Menu_cocosView.mCurrentLayerl setPatternWithFileName:patternName];
    }
    
}

- (IBAction)back:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)clearScreen:(id)sender {
	[Menu_cocosView.mCurrentLayerl clearScreen];
}

- (IBAction)randomColor:(id)sender {
	    
    if(self.colorListBtn.selected){
        [self selectColor:self.colorListBtn];
    }
	
	[Singleton sharedMySingleton].isRandomColor = TRUE;

    self.randomColorBtn.selected = !self.randomColorBtn.selected;
	
	//set random color mode 
}

- (IBAction)selectColor:(UIButton*)sender {
    
    if(self.randomColorBtn.selected){
        [self randomColor:self.randomColorBtn];
    }
    
    [Singleton sharedMySingleton].isRandomColor = FALSE;

    sender.selected = !sender.selected;
    float alpha = (sender.selected)?1.0:0.0;
    
    if(nil == self.colorPalette.superview){
        CGRect rect = self.colorPalette.frame;
        rect.origin = CGPointMake(25+CGRectGetMinX(sender.frame), CGRectGetMaxY(sender.frame));
        self.colorPalette.frame = rect;
        self.colorPalette.alpha = 0.0;
        [self.view addSubview:self.colorPalette];
    }
    
    [UIView beginAnimations:nil context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
    self.colorPalette.alpha = alpha;
    [UIView commitAnimations];
	
	//set the new color
//	[Menu_cocosView.mCurrentLayerl setColorFromColor:[self selectedColor]]; 

}

- (IBAction)pickColor:(UIButton*)sender {
	if(self.selectedColorBtn != sender){
        self.selectedColorBtn.layer.borderWidth = 0.0f;
        self.selectedColorBtn.layer.borderColor = [UIColor clearColor].CGColor;
        
        self.selectedColorBtn = sender;
        
        self.selectedColorBtn.layer.borderWidth = 2.0f;
        self.selectedColorBtn.layer.borderColor = [UIColor whiteColor].CGColor;
        
        //Update the selected color
        if(sender.tag == 50){  //Original color
            [Menu_cocosView.mCurrentLayerl setColorFromColor:[UIColor clearColor]];
        }
        else{
            [Menu_cocosView.mCurrentLayerl setColorFromColor:[self selectedColor]];
        }
    }
}

- (IBAction)startAndStop:(id)sender {
    self.startStopBtn.selected = !self.startStopBtn.selected;
    if(self.startStopBtn.selected){
        // Start the wheel
        [Singleton sharedMySingleton].isStopRotation = FALSE;
    }
    else{
        // Stop the wheel
        [Singleton sharedMySingleton].isStopRotation = TRUE;
    }
}

#pragma mark - Utility
-(UIColor*)selectedColor;{ 
    UIColor *color = [UIColor yellowColor];
    
    if(self.selectedColorBtn){
        color = self.selectedColorBtn.backgroundColor;
    }
    
    return color;
}

#pragma mark - 
-(void)speedSelected:(int)inSpeed;{
    [Menu_cocosView.mCurrentLayerl setRotaionSpeed:inSpeed];
}

@end
