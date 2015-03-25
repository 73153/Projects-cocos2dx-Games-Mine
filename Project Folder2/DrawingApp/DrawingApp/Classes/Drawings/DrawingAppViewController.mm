//
//  DrawingAppViewController.m
//  DrawingApp
//
//  Created by i-CRG Labs on 5/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DrawingAppViewController.h"
#import "Globals.c"
#import "Singleton.h"

#import "Menu_CocosScene.h"

@implementation DrawingAppViewController

@synthesize mainView;
@synthesize applyingView;

@synthesize savedScrollview;
@synthesize padsSrollview;
@synthesize sampleScrollview;
@synthesize padsScrollviewbackground;
@synthesize samplesScrollviewbackground;
@synthesize savedScrollviewbackground;
@synthesize FullImage;
@synthesize sampleFullImage;
@synthesize padSelectedTag;
@synthesize sampleSelectedTag;

@synthesize padsArray,pads_hvr_Array;
@synthesize samplesArray;
@synthesize bigdrawingsArray;
@synthesize bigpadsArray;
@synthesize menuButton;

@synthesize drawpadButton;
@synthesize sampleButton;
@synthesize myWorkButton;
@synthesize newButton;
@synthesize saveButton;

@synthesize buttonsView;
@synthesize brushbutton,brushSecectionButton;
@synthesize chalkbutton;
@synthesize slatepencilbutton;
@synthesize crayonbutton;
@synthesize eraserbutton;
@synthesize homebutton;
@synthesize clearbutton;
@synthesize pencilbutton;
@synthesize redobutton;
@synthesize allButtonsView;

@synthesize AllButtonViewFrame;
@synthesize chalkViewFrame;
@synthesize brushesViewFrame;
@synthesize colorpencilViewFrame;
@synthesize crayonsViewFrame;
@synthesize slatepencilViewFrame;

@synthesize  isMovedToCenter;
// chalks buttons
@synthesize ch_yellow;
@synthesize ch_orange;
@synthesize ch_green;
@synthesize ch_blue;
@synthesize ch_white;
@synthesize chalkView;
// brush buttons
@synthesize brush_white;
@synthesize brush_blue;
@synthesize brush_green;
@synthesize brush_yellow;
@synthesize brush_red;
@synthesize brush_black;
@synthesize brushesView;
@synthesize pallet_1;
@synthesize pallet_2;

@synthesize brush_sizeView;
@synthesize Size1button;
@synthesize Size2button;
@synthesize Size3button;
@synthesize Size4button;
@synthesize Size5button;
@synthesize Size6button;

// color pencils
@synthesize pencil_yellow;
@synthesize pencil_chr_yellow;
@synthesize pencil_orange;
@synthesize pencil_scr_red;
@synthesize pencil_red;
@synthesize pencil_brown;
@synthesize pencil_green;
@synthesize pencil_lig_green;
@synthesize pencil_sky_blue;
@synthesize pencil_blue;
@synthesize pencil_black;
@synthesize pencil_white;
@synthesize colorpencilView;

// crayons...
@synthesize cry_lemonyellow;
@synthesize cry_crm_yellow;
@synthesize cry_yellow_orch;
@synthesize cry_orange;
@synthesize cry_red;
@synthesize cry_brown;
@synthesize cry_darkgreen;
@synthesize cry_green;
@synthesize cry_skyblue;
@synthesize cry_blue;
@synthesize cry_black;
@synthesize cry_white;
@synthesize crayonsView;

// slate pencil
@synthesize slate_pencil_grey;
@synthesize slate_pencil_white;
@synthesize slate_pencil_orange;
@synthesize slate_pencil_blue;
@synthesize slate_pencil_green;
@synthesize slatepencilView;
@synthesize noOfSamplesToFly;

// popup 
@synthesize filpButton;
@synthesize lockButton;
@synthesize deleteButton;
@synthesize popView;
@synthesize popUpinfo;

@synthesize savedFileName;
@synthesize isChageMadeToEditedDrawing,isComingFromNewpad;
//@synthesize ComingfromDrawpad;
@synthesize showSavedMyWorks;


//
#pragma mark -
#pragma mark actions for brushes buttons and sizes

-(IBAction)select_Size1button:(id)sender{
    [self setbuttonsizeHighletedImage:(UIButton *)sender ];
    [cocosView.mCurrentLayer selectBrushSize:1];
	
	[UIView beginAnimations:@"showCrayons" context:nil];
	[UIView setAnimationDuration:0.5];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
	self.brush_sizeView.alpha=0;
	[UIView commitAnimations];
    
}
-(IBAction)select_Size2button:(id)sender{
    [self setbuttonsizeHighletedImage:(UIButton *)sender ];
    [cocosView.mCurrentLayer selectBrushSize:2];
	
	[UIView beginAnimations:@"showCrayons" context:nil];
	[UIView setAnimationDuration:0.5];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
	self.brush_sizeView.alpha=0;
	[UIView commitAnimations];
}
-(IBAction)select_Size3button:(id)sender{
    [self setbuttonsizeHighletedImage:(UIButton *)sender ];
    [cocosView.mCurrentLayer selectBrushSize:3];
	
	[UIView beginAnimations:@"showCrayons" context:nil];
	[UIView setAnimationDuration:0.5];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
	self.brush_sizeView.alpha=0;
	[UIView commitAnimations];
}
-(IBAction)select_Size4button:(id)sender{
    [self setbuttonsizeHighletedImage:(UIButton *)sender ];
    [cocosView.mCurrentLayer selectBrushSize:4];
	
	[UIView beginAnimations:@"showCrayons" context:nil];
	[UIView setAnimationDuration:0.5];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
	self.brush_sizeView.alpha=0;
	[UIView commitAnimations];
}
-(IBAction)select_Size5button:(id)sender{
    [self setbuttonsizeHighletedImage:(UIButton *)sender ];
    [cocosView.mCurrentLayer selectBrushSize:5];
	
	[UIView beginAnimations:@"showCrayons" context:nil];
	[UIView setAnimationDuration:0.5];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
	self.brush_sizeView.alpha=0;
	[UIView commitAnimations];
}
-(IBAction)select_Size6button:(id)sender{
    [self setbuttonsizeHighletedImage:(UIButton *)sender ];
    [cocosView.mCurrentLayer selectBrushSize:6];
	
	[UIView beginAnimations:@"showCrayons" context:nil];
	[UIView setAnimationDuration:0.5];
	[UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
	self.brush_sizeView.alpha=0;
	[UIView commitAnimations];
}

#pragma mark - select brush button -
-(IBAction)selectBrush:(id)sender;{
	if(self.brush_sizeView.alpha==1){
		[UIView beginAnimations:@"showChalks" context:nil];
		[UIView setAnimationDuration:0.5];
		[UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
		self.brush_sizeView.alpha=0;
		[UIView commitAnimations];
	}
	else 
	{
		[UIView beginAnimations:@"showChalks" context:nil];
		[UIView setAnimationDuration:0.5];
		[UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
		self.brush_sizeView.alpha=1;
		[UIView commitAnimations];
	}
}

#pragma mark -
#pragma mark actions for brushes buttons

-(IBAction)select_brush_white:(id)sender{
    
    [Singleton sharedMySingleton]._colour1 = 2;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._colour1];
}

-(IBAction)select_brush_blue:(id)sender{
    
    [Singleton sharedMySingleton]._colour1 = 3;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._colour1];
}

-(IBAction)select_brush_green:(id)sender{
    
    [Singleton sharedMySingleton]._colour1 = 4;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._colour1]; 
}

-(IBAction)select_brush_yellow:(id)sender{
    
    [Singleton sharedMySingleton]._colour1 = 6;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._colour1];
}

-(IBAction)select_brush_red:(id)sender{
    
    [Singleton sharedMySingleton]._colour1 = 5;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._colour1];
}

-(IBAction)select_brush_black:(id)sender{
    
    [Singleton sharedMySingleton]._colour1 = 1;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._colour1];
}

#pragma mark -
#pragma mark actions for clalks  buttons
///actions for chalks...

-(IBAction)select_ch_yellow:(id)sender{
    [self setmovechalksButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._chalkColor = 6;
    _currentChalkColor = [Singleton sharedMySingleton]._chalkColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._chalkColor];
    
    [UIView beginAnimations:@"showChalks" context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.chalkView.alpha=0;
    [UIView commitAnimations];
}

-(IBAction)select_ch_orange:(id)sender{
    [self setmovechalksButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._chalkColor = 7;
    _currentChalkColor = [Singleton sharedMySingleton]._chalkColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._chalkColor];
    
    [UIView beginAnimations:@"showChalks" context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.chalkView.alpha=0;
    [UIView commitAnimations];
}

-(IBAction)select_ch_green:(id)sender{
    [self setmovechalksButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._chalkColor = 4;
    _currentChalkColor = [Singleton sharedMySingleton]._chalkColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._chalkColor];
    
    [UIView beginAnimations:@"showChalks" context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.chalkView.alpha=0;
    [UIView commitAnimations];
}

-(IBAction)select_ch_blue:(id)sender{
    [self setmovechalksButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._chalkColor = 3;
    _currentChalkColor = [Singleton sharedMySingleton]._chalkColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._chalkColor];
    
    [UIView beginAnimations:@"showChalks" context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.chalkView.alpha=0;
    [UIView commitAnimations];
}

-(IBAction)select_ch_white:(id)sender{
    [self setmovechalksButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._chalkColor = 2;
    _currentChalkColor = [Singleton sharedMySingleton]._chalkColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._chalkColor];
    
    [UIView beginAnimations:@"showChalks" context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.chalkView.alpha=0;
    [UIView commitAnimations];
}

#pragma mark -
#pragma mark actions for color pencils  buttons
// actions for color pencils
-(IBAction)select_pencil_yellow:(id)sender{
    
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    
    [Singleton sharedMySingleton]._pencilColor = 6;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
    
}
-(IBAction)select_pencil_chr_yellow:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 8;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}
-(IBAction)select_pencil_orange:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 7;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}
-(IBAction)select_pencil_scr_red:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 14;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}
-(IBAction)select_pencil_red:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 5;  
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}
-(IBAction)select_pencil_brown:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 15;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}
-(IBAction)select_pencil_green:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 11;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}
-(IBAction)select_pencil_lig_green:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 4;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}
-(IBAction)select_pencil_sky_blue:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 16;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}
-(IBAction)select_pencil_blue:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 3;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}
-(IBAction)select_pencil_black:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 1;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}
-(IBAction)select_pencil_white:(id)sender{
    [self setmovecolorpencilsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._pencilColor = 2;
    _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
}

#pragma mark -
#pragma mark actions for crayons  buttons
//actions for crayons.../// 
-(IBAction)select_cry_lemonyellow:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._crayonColor = 12;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}
-(IBAction)select_cry_crm_yellow:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._crayonColor = 8;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}
-(IBAction)select_cry_yellow_orch:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._crayonColor = 17;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}
-(IBAction)select_cry_orange:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._crayonColor = 7;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}
-(IBAction)select_cry_red:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._crayonColor = 5;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}
-(IBAction)select_cry_brown:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._crayonColor = 15;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}
-(IBAction)select_cry_darkgreen:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._colour1 = 11;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._colour1];
}
-(IBAction)select_cry_green:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._crayonColor = 4;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}
-(IBAction)select_cry_skyblue:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._crayonColor = 16;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}
-(IBAction)select_cry_blue:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._crayonColor = 3;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}
-(IBAction)select_cry_black:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    [Singleton sharedMySingleton]._crayonColor = 1;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}
-(IBAction)select_cry_white:(id)sender{
    [self setmovecrayonsButton:(UIButton *)sender ];
    
    [Singleton sharedMySingleton]._crayonColor = 2;
    _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
}

#pragma mark -
#pragma mark actions for slatepencils  buttons
-(IBAction)select_slate_pencil_grey:(id)sender{
    [self setmoveImage:(UIButton *)sender ];
    [Singleton sharedMySingleton]._slatePencilColor = 1;
    _currentSlatePencilColor = [Singleton sharedMySingleton]._slatePencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._slatePencilColor]; 
	
	[UIView beginAnimations:@"showChalks" context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.slatepencilView.alpha=0;
    [UIView commitAnimations];
}

-(IBAction)select_slate_pencil_white:(id)sender{
    [self setmoveImage:(UIButton *)sender ];
    [Singleton sharedMySingleton]._slatePencilColor = 2;
    _currentSlatePencilColor = [Singleton sharedMySingleton]._slatePencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._slatePencilColor];
	
	[UIView beginAnimations:@"showChalks" context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.slatepencilView.alpha=0;
    [UIView commitAnimations];
}

-(IBAction)select_slate_pencil_orange:(id)sender{
    [self setmoveImage:(UIButton *)sender ];
    [Singleton sharedMySingleton]._slatePencilColor = 7;
    _currentSlatePencilColor = [Singleton sharedMySingleton]._slatePencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._slatePencilColor];
	
	[UIView beginAnimations:@"showChalks" context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.slatepencilView.alpha=0;
    [UIView commitAnimations];
}

-(IBAction)select_slate_pencil_blue:(id)sender{
    [self setmoveImage:(UIButton *)sender ];
    [Singleton sharedMySingleton]._slatePencilColor = 3;
    _currentSlatePencilColor = [Singleton sharedMySingleton]._slatePencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._slatePencilColor];
	
	[UIView beginAnimations:@"showChalks" context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.slatepencilView.alpha=0;
    [UIView commitAnimations];
}

-(IBAction)select_slate_pencil_green:(id)sender{
    [self setmoveImage:(UIButton *)sender ];
    [Singleton sharedMySingleton]._slatePencilColor = 4;
    _currentSlatePencilColor = [Singleton sharedMySingleton]._slatePencilColor;
    [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._slatePencilColor];
	
	[UIView beginAnimations:@"showChalks" context:nil];
    [UIView setAnimationDuration:0.5];
    [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    self.slatepencilView.alpha=0;
    [UIView commitAnimations];
}


#pragma mark -
#pragma mark  tools actions ------

-(IBAction)selectBrushes:(id)sender
{  
    [self setHighletedToolsImage:(UIButton *)sender ];
    if(padsArrayTag<4){
        [Singleton sharedMySingleton]._colour2 = 1;
        
        self.crayonsView.alpha=0;
        self.colorpencilView.alpha=0;
        self.chalkView.alpha=0;
        self.slatepencilView.alpha=0;
        
        
        //    CGRect frame=CGRectMake( 200,20 , 260, 348);
        //	brushesView.frame=frame;
        //	[self.view addSubview:brushesView];
        
        
        if(self.brushesView.alpha==1){
            
            [UIView beginAnimations:@"showChalks" context:nil];
            [UIView setAnimationDuration:0.5];
            [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
            self.brushesView.alpha=0;
            self.brush_sizeView.alpha=0;
            [UIView commitAnimations];
            
            [cocosView.mCurrentLayer CPallete];
        }
        else 
        {
            [UIView beginAnimations:@"showChalks" context:nil];
            [UIView setAnimationDuration:0.5];
            [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
            self.brushesView.alpha=1;
            self.brush_sizeView.alpha=1;
            [UIView commitAnimations];
			self.brushSecectionButton.hidden = NO;

            
            [cocosView.mCurrentLayer createPallete];
        }
        UIPanGestureRecognizer *dragBrushes=[[UIPanGestureRecognizer alloc]initWithTarget:self action:@selector(dragBrushes:)];
        [brushesView addGestureRecognizer:dragBrushes];
        [dragBrushes release];
        brushesViewFrame=brushesView.frame;
        
    }
}

-(IBAction)selectChalks:(id)sender
{  
	self.brushSecectionButton.hidden = YES;

    [self setHighletedToolsImage:(UIButton *)sender ];
    if(padsArrayTag>=4){
        [Singleton sharedMySingleton]._colour2 = 2;
        [cocosView.mCurrentLayer CPallete];
        
        //    if([Singleton sharedMySingleton]._chalkColor != 6 || [Singleton sharedMySingleton]._chalkColor != 7 || [Singleton sharedMySingleton]._chalkColor != 4 || [Singleton sharedMySingleton]._chalkColor != 3 || [Singleton sharedMySingleton]._chalkColor != 2)
//        if(_currentChalkColor == 0)
//        {
//            //  //NSLog(@"inside condition");
//            [Singleton sharedMySingleton]._chalkColor = 6;
//            _currentChalkColor = [Singleton sharedMySingleton]._chalkColor;
//            [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._chalkColor];
//        }
        
//        [Singleton sharedMySingleton]._chalkColor = _currentChalkColor;
        [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._chalkColor];
        
        self.brushesView.alpha=0;
        self.colorpencilView.alpha=0;
        self.crayonsView.alpha=0;
        self.slatepencilView.alpha=0;
        self.brush_sizeView.alpha=0;
        //   self.chalkView.alpha=0;
        
        CGRect frame=CGRectMake( 100,100 , 135, 199);
        chalkView.frame=frame;
        [self.view addSubview:chalkView];
        
        
        if(self.chalkView.alpha==1){
            
            [UIView beginAnimations:@"showChalks" context:nil];
            [UIView setAnimationDuration:0.5];
            [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
            self.chalkView.alpha=0;
            [UIView commitAnimations];
        }
        else 
        {
            [UIView beginAnimations:@"showChalks" context:nil];
            [UIView setAnimationDuration:0.3];
            [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
            self.chalkView.alpha=1;
            [UIView commitAnimations];
            
        }
        UIPanGestureRecognizer *dragchalks=[[UIPanGestureRecognizer alloc]initWithTarget:self action:@selector(dragchalks:)];
        [chalkView addGestureRecognizer:dragchalks];
        [dragchalks release];
        chalkViewFrame=chalkView.frame;    
    }
}

-(IBAction)selectcolorpencils:(id)sender
{   [brushbutton setHighlighted:FALSE];
	self.brushSecectionButton.hidden = YES;
	
    [self setHighletedToolsImage:(UIButton *)sender ];
    if(padsArrayTag<4){
        [Singleton sharedMySingleton]._colour2 = 3;
        [cocosView.mCurrentLayer CPallete];
        
        self.brushesView.alpha=0;
        self.crayonsView.alpha=0;
        self.chalkView.alpha=0;
        self.slatepencilView.alpha=0;
        self.brush_sizeView.alpha=0;
        
        //    if([Singleton sharedMySingleton]._pencilColor != 1 || [Singleton sharedMySingleton]._pencilColor != 2 || [Singleton sharedMySingleton]._pencilColor != 3 || [Singleton sharedMySingleton]._pencilColor != 4 || [Singleton sharedMySingleton]._pencilColor != 5 || [Singleton sharedMySingleton]._pencilColor != 6 || [Singleton sharedMySingleton]._pencilColor != 7 || [Singleton sharedMySingleton]._pencilColor != 8 || [Singleton sharedMySingleton]._pencilColor != 11 || [Singleton sharedMySingleton]._pencilColor != 14 || [Singleton sharedMySingleton]._pencilColor != 15 || [Singleton sharedMySingleton]._pencilColor != 16)
        if(_currentPencilColor == 0)
        {
            [Singleton sharedMySingleton]._pencilColor = 6;
            _currentPencilColor = [Singleton sharedMySingleton]._pencilColor;
            [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
        }
        
        [Singleton sharedMySingleton]._pencilColor = _currentPencilColor;
        [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._pencilColor];
        
        CGRect frame=CGRectMake( 200,200 , 297, 463);
        colorpencilView.frame=frame;
        [self.view addSubview:colorpencilView];
        
        
        if(self.colorpencilView.alpha==1){
            
            [UIView beginAnimations:@"showChalks" context:nil];
            [UIView setAnimationDuration:0.5];
            [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
            self.colorpencilView.alpha=0;
            [UIView commitAnimations];
        }
        else 
        {
            [UIView beginAnimations:@"showChalks" context:nil];
            [UIView setAnimationDuration:0.3];
            [UIView setAnimationCurve:UIViewAnimationCurveEaseIn]; 
            self.colorpencilView.alpha=1;
            [UIView commitAnimations];
            
        }
        UIPanGestureRecognizer *dragcolorpencil=[[UIPanGestureRecognizer alloc]initWithTarget:self action:@selector(dragcolorpencil:)];
        [colorpencilView addGestureRecognizer:dragcolorpencil];
        [dragcolorpencil release];
        colorpencilViewFrame=colorpencilView.frame;  
        
    }
}
-(IBAction)selectSlatePencils:(id)sender
{  
	self.brushSecectionButton.hidden = YES;

    [chalkbutton setHighlighted:FALSE];
    [self setHighletedToolsImage:(UIButton *)sender ];
    if(padsArrayTag>=4){
        [Singleton sharedMySingleton]._colour2 = 4;
        [cocosView.mCurrentLayer CPallete];
        
        self.brushesView.alpha=0;
        self.crayonsView.alpha=0;
        self.chalkView.alpha=0;
        self.colorpencilView.alpha=0;
        self.brush_sizeView.alpha=0;
        
        //    if([Singleton sharedMySingleton]._slatePencilColor != 1 || [Singleton sharedMySingleton]._slatePencilColor != 2 || [Singleton sharedMySingleton]._slatePencilColor != 3 || [Singleton sharedMySingleton]._slatePencilColor != 4 || [Singleton sharedMySingleton]._slatePencilColor != 7)
        if(_currentSlatePencilColor == 0)
        {
            [Singleton sharedMySingleton]._slatePencilColor = 2;
            _currentSlatePencilColor = [Singleton sharedMySingleton]._slatePencilColor;
            [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._slatePencilColor];
        }
        
        [Singleton sharedMySingleton]._slatePencilColor = _currentSlatePencilColor;
        [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._slatePencilColor];
        
        CGRect frame=CGRectMake( 150,100 , 297, 241);
        slatepencilView.frame=frame;
        [self.view addSubview:slatepencilView];
        
        if(self.slatepencilView.alpha==1){
            
            [UIView beginAnimations:@"showChalks" context:nil];
            [UIView setAnimationDuration:0.5];
            [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
            self.slatepencilView.alpha=0;
            [UIView commitAnimations];
        }
        else 
        {
            [UIView beginAnimations:@"showChalks" context:nil];
            [UIView setAnimationDuration:0.3];
            [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
            self.slatepencilView.alpha=1;
            [UIView commitAnimations];
        }
        UIPanGestureRecognizer *dragslates=[[UIPanGestureRecognizer alloc]initWithTarget:self action:@selector(dragslates:)];
        [slatepencilView addGestureRecognizer:dragslates];
        [dragslates release];
        slatepencilViewFrame=slatepencilView.frame;   
        
    }
}

-(IBAction)selectCrayons:(id)sender
{   [brushbutton setHighlighted:FALSE];
	self.brushSecectionButton.hidden = NO;

    [self setHighletedToolsImage:(UIButton *)sender ];
    if(padsArrayTag<4){
        
        [Singleton sharedMySingleton]._colour2 = 5;
        [cocosView.mCurrentLayer CPallete];
        
        self.brushesView.alpha=0;
        self.colorpencilView.alpha=0;
        self.chalkView.alpha=0;
        self.slatepencilView.alpha=0;
        
        //        if([Singleton sharedMySingleton]._crayonColor != 1 || [Singleton sharedMySingleton]._crayonColor != 2 || [Singleton sharedMySingleton]._crayonColor != 3 || [Singleton sharedMySingleton]._crayonColor != 4 || [Singleton sharedMySingleton]._crayonColor != 5 || [Singleton sharedMySingleton]._crayonColor != 6 || [Singleton sharedMySingleton]._crayonColor != 7 || [Singleton sharedMySingleton]._crayonColor != 8 || [Singleton sharedMySingleton]._crayonColor != 11 || [Singleton sharedMySingleton]._crayonColor != 14 || [Singleton sharedMySingleton]._crayonColor != 15 || [Singleton sharedMySingleton]._crayonColor != 16)
        if(_currentCrayonColor == 0)
        {
            [Singleton sharedMySingleton]._crayonColor = 6;
            _currentCrayonColor = [Singleton sharedMySingleton]._crayonColor;
            [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
        }
        
        [Singleton sharedMySingleton]._crayonColor = _currentCrayonColor;
        [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._crayonColor];
        
        
        CGRect frame=CGRectMake( 200,36, 241, 472);
        crayonsView.frame=frame;
        [self.view addSubview:crayonsView];
        //    
        //    CGRect frame2=CGRectMake( 50,600 , 322, 103);
        //	brush_sizeView.frame=frame2;
        //	[self.view addSubview:brush_sizeView];
        
        if(self.crayonsView.alpha==1){
            
            [UIView beginAnimations:@"showCrayons" context:nil];
            [UIView setAnimationDuration:0.5];
            [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
            self.crayonsView.alpha=0;
            self.brush_sizeView.alpha=0;
            [UIView commitAnimations];
        }
        else 
        {
            [UIView beginAnimations:@"showCrayons" context:nil];
            [UIView setAnimationDuration:0.5];
            [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
            self.crayonsView.alpha=1;
            self.brush_sizeView.alpha=1;
            [UIView commitAnimations];
            
        }
        UIPanGestureRecognizer *dragcrayons=[[UIPanGestureRecognizer alloc]initWithTarget:self action:@selector(dragcrayons:)];
        [crayonsView addGestureRecognizer:dragcrayons];
        [dragcrayons release];
        crayonsViewFrame=crayonsView.frame;
    }
    
}
-(IBAction)selectToErase:(id)sender
{ 
    [brushbutton setHighlighted:FALSE];
    [chalkbutton setHighlighted:FALSE];
	self.brushSecectionButton.hidden = NO;
    [self setHighletedToolsImage:(UIButton *)sender ];
    //    int k = [[Singleton sharedMySingleton]._redoPointsArray count];
    //    //NSLog(@"%d",k);
    //    
    //    if(k > 0)
    //    {
    //        [[Singleton sharedMySingleton]._pointsArray1 addObject:[[Singleton sharedMySingleton]._redoPointsArray objectAtIndex:k-1]];
    //        [[Singleton sharedMySingleton]._redoPointsArray removeObjectAtIndex:k-1];
    //    }
    //    
    //    [cocosView.mCurrentLayer redraw];
    
    [Singleton sharedMySingleton]._colour2 = 6;
    [cocosView.mCurrentLayer CPallete];
    
    self.chalkView.alpha=0;
    self.colorpencilView.alpha=0;
    self.brushesView.alpha=0;
    self.crayonsView.alpha=0;
    self.slatepencilView.alpha=0;
    
    //    if(self.brush_sizeView.alpha==1){
    //        
    //        [UIView beginAnimations:@"showCrayons" context:nil];
    //        [UIView setAnimationDuration:0.5];
    //        [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
    //        
    //        self.brush_sizeView.alpha=0;
    //        [UIView commitAnimations];
    //    }
    //    else 
    {
        [UIView beginAnimations:@"showCrayons" context:nil];
        [UIView setAnimationDuration:0.5];
        [UIView setAnimationCurve:UIViewAnimationCurveEaseIn];
        
        self.brush_sizeView.alpha=1;
        [UIView commitAnimations];}
}


-(IBAction)select_to_clear:(id)sender
{
    UIAlertView *myAlertView = [[UIAlertView alloc] initWithTitle:@"Alert!!" message:@"Do you want to clear the page?" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"OK", nil];
    myAlertView.tag = 99;
    [myAlertView show];
    [myAlertView release];
    
}




-(IBAction)select_undo:(id)sender{
    
}

-(IBAction)select_redo:(id)sender{
    
}

#pragma mark -
#pragma mark  drag buttons ------

-(void)dragAllButtonView:(UIPanGestureRecognizer *)sender {
	////NSLog(@"frame %@", sender.view);
    
	CGPoint translate = [sender translationInView:self.allButtonsView];
	CGRect newFrame = AllButtonViewFrame; 
	newFrame.origin.x += translate.x; 
	if(newFrame.origin.x <0){
        newFrame.origin.x=0;
	}
	if(newFrame.origin.x >900){
		newFrame.origin.x=900;
	}
	
	if(newFrame.origin.y <10){
		newFrame.origin.y=10;
	}
	if(newFrame.origin.y >580){
		newFrame.origin.y=580;
	}
	newFrame.origin.y += translate.y; sender.view.frame = newFrame;
   	[self.view bringSubviewToFront:sender.view];
	
	
    
	if (sender.state == UIGestureRecognizerStateEnded) {
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		
		AllButtonViewFrame = newFrame;
        [UIView commitAnimations];
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		[sender.view setFrame:AllButtonViewFrame];
        [UIView commitAnimations];
		
	}
	[self.view bringSubviewToFront:allButtonsView];	
	
}
-(void)dragBrushes:(UIPanGestureRecognizer *)sender {
	////NSLog(@"frame %@", sender.view);
    
	CGPoint translate = [sender translationInView:self.brushesView];
	CGRect newFrame = brushesViewFrame; 
	newFrame.origin.x += translate.x; 
	if(newFrame.origin.x <0){
        newFrame.origin.x=0;
	}
	if(newFrame.origin.x >900){
		newFrame.origin.x=900;
	}
	
	if(newFrame.origin.y <10){
		newFrame.origin.y=10;
	}
	if(newFrame.origin.y >580){
		newFrame.origin.y=580;
	}
    newFrame.origin.y += translate.y; sender.view.frame = newFrame;
   	[self.view bringSubviewToFront:sender.view];
	
	
    
	if (sender.state == UIGestureRecognizerStateEnded) {
		
		
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		
		brushesViewFrame = newFrame;
        [UIView commitAnimations];
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		[sender.view setFrame:brushesViewFrame];
        [UIView commitAnimations];
		
	}
	[self.view bringSubviewToFront:brushesView];	
	
}
-(void)dragchalks:(UIPanGestureRecognizer *)sender {
	////NSLog(@"frame %@", sender.view);
    
	CGPoint translate = [sender translationInView:self.chalkView];
	CGRect newFrame = chalkViewFrame; 
	newFrame.origin.x += translate.x; 
	if(newFrame.origin.x <0){
        newFrame.origin.x=0;
	}
	if(newFrame.origin.x >900){
		newFrame.origin.x=900;
	}
	
	if(newFrame.origin.y <10){
		newFrame.origin.y=10;
	}
	if(newFrame.origin.y >580){
		newFrame.origin.y=580;
	}
    newFrame.origin.y += translate.y; sender.view.frame = newFrame;
   	[self.view bringSubviewToFront:sender.view];
	
	
    
	if (sender.state == UIGestureRecognizerStateEnded) {
		
		
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		
		chalkViewFrame = newFrame;
        [UIView commitAnimations];
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		[sender.view setFrame:chalkViewFrame];
        [UIView commitAnimations];
		
	}
	[self.view bringSubviewToFront:chalkView];	
	
}
-(void)dragcrayons:(UIPanGestureRecognizer *)sender {
	////NSLog(@"frame %@", sender.view);
    
	CGPoint translate = [sender translationInView:self.crayonsView];
	CGRect newFrame = crayonsViewFrame; 
	newFrame.origin.x += translate.x; 
	if(newFrame.origin.x <0){
        newFrame.origin.x=0;
	}
	if(newFrame.origin.x >900){
		newFrame.origin.x=900;
	}
	
	if(newFrame.origin.y <10){
		newFrame.origin.y=10;
	}
	if(newFrame.origin.y >580){
		newFrame.origin.y=580;
	}
    newFrame.origin.y += translate.y; sender.view.frame = newFrame;
   	[self.view bringSubviewToFront:sender.view];
	
	
    
	if (sender.state == UIGestureRecognizerStateEnded) {
		
		
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		
		crayonsViewFrame = newFrame;
        [UIView commitAnimations];
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		[sender.view setFrame:crayonsViewFrame];
        [UIView commitAnimations];
		
	}
	[self.view bringSubviewToFront:crayonsView];	
	
}
-(void)dragcolorpencil:(UIPanGestureRecognizer *)sender {
	////NSLog(@"frame %@", sender.view);
    
	CGPoint translate = [sender translationInView:self.colorpencilView];
	CGRect newFrame = colorpencilViewFrame; 
	newFrame.origin.x += translate.x; 
	if(newFrame.origin.x <0){
        newFrame.origin.x=0;
	}
	if(newFrame.origin.x >900){
		newFrame.origin.x=900;
	}
	
	if(newFrame.origin.y <10){
		newFrame.origin.y=10;
	}
	if(newFrame.origin.y >580){
		newFrame.origin.y=580;
	}
    newFrame.origin.y += translate.y; sender.view.frame = newFrame;
   	[self.view bringSubviewToFront:sender.view];
	
	
    
	if (sender.state == UIGestureRecognizerStateEnded) {
		
		
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		
		colorpencilViewFrame = newFrame;
        [UIView commitAnimations];
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		[sender.view setFrame:colorpencilViewFrame];
        [UIView commitAnimations];
		
	}
	[self.view bringSubviewToFront:colorpencilView];	
	
}
-(void)dragslates:(UIPanGestureRecognizer *)sender {
	////NSLog(@"frame %@", sender.view);
    
	CGPoint translate = [sender translationInView:self.slatepencilView];
	CGRect newFrame = slatepencilViewFrame; 
	newFrame.origin.x += translate.x; 
	if(newFrame.origin.x <0){
        newFrame.origin.x=0;
	}
	if(newFrame.origin.x >900){
		newFrame.origin.x=900;
	}
	
	if(newFrame.origin.y <10){
		newFrame.origin.y=10;
	}
	if(newFrame.origin.y >580){
		newFrame.origin.y=580;
	}
    newFrame.origin.y += translate.y; sender.view.frame = newFrame;
   	[self.view bringSubviewToFront:sender.view];
	
	
    
	if (sender.state == UIGestureRecognizerStateEnded) {
		
		
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		
		slatepencilViewFrame = newFrame;
        [UIView commitAnimations];
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationDuration:1.5];
		[sender.view setFrame:slatepencilViewFrame];
        [UIView commitAnimations];
		
	}
	[self.view bringSubviewToFront:slatepencilView];	
	
}

#pragma mark -
#pragma mark  menu actions ------


-(IBAction)showMyworks:(id)sender{
    [drawpadButton setHighlighted:FALSE];
    [sampleButton  setHighlighted:FALSE];
    [newButton  setHighlighted:FALSE];
    [saveButton  setHighlighted:FALSE];
    
    self.padsSrollview.hidden=YES;
    self.sampleScrollview.hidden=YES;
    padsScrollviewbackground.hidden=YES;
    samplesScrollviewbackground.hidden=YES;
    
    DrawAddOnViewController *_showSavedMyWorks=[[DrawAddOnViewController alloc]init];
    self.showSavedMyWorks = _showSavedMyWorks;
    self.showSavedMyWorks.delegate = self;
    [_showSavedMyWorks release];
    
    [self.view addSubview:self.showSavedMyWorks.view];
}

-(IBAction)showSamples:(id)sender{
    [self setHighletedImage:(UIButton *)sender ];
    self.padsSrollview.hidden=YES;
    //self.padsSrollview.alpha=0;
    self.savedScrollview.hidden=YES;
    padsScrollviewbackground.hidden=YES;
    savedScrollviewbackground.hidden=YES;
    
    if(self.sampleScrollview.hidden==NO)
    { 
        [UIView beginAnimations:@"showpads" context:nil];
        [UIView setAnimationDuration:0.5];
        self.sampleScrollview.alpha=0;
		self.sampleScrollview.hidden=YES;
        samplesScrollviewbackground.hidden=YES;
        
        [UIView commitAnimations];
    }
	else {
        
		[UIView beginAnimations:@"showpads" context:nil];
		[UIView setAnimationDuration:0.5];
        self.sampleScrollview.hidden=NO;
        samplesScrollviewbackground.hidden=NO;
        self.sampleScrollview.alpha=1;
		
        [UIView commitAnimations];
	}
    
    if(nil == samplesArray){
        samplesArray=[[NSArray alloc] initWithObjects:[UIImage imageNamed:@"baby_thumb.png"],[UIImage imageNamed:@"bird_thumb.png"],[UIImage imageNamed:@"car_thumb.png"],[UIImage imageNamed:@"duck_thumb.png"],[UIImage imageNamed:@"elaphant_thumb.png"],[UIImage imageNamed:@"flower_thumb.png"],[UIImage imageNamed:@"fish_thumb.png"],[UIImage imageNamed:@"home_thumb.png"],[UIImage imageNamed:@"rabbit_thumb.png"],[UIImage imageNamed:@"tree_thumb.png"],nil];
        int height1 =[samplesArray count]*60;
        sampleScrollview.contentSize=CGSizeMake(height1, CGRectGetHeight(sampleScrollview.frame));
        
        ////  big samples array   
        
        bigdrawingsArray=[[NSArray alloc] initWithObjects:[UIImage imageNamed:@"baby.png"],[UIImage imageNamed:@"bird.png"],[UIImage imageNamed:@"car.png"],[UIImage imageNamed:@"duck.png"],[UIImage imageNamed:@"elaphant.png"],[UIImage imageNamed:@"flower.png"],[UIImage imageNamed:@"fish.png"],[UIImage imageNamed:@"home.png"],[UIImage imageNamed:@"rabiit.png"],[UIImage imageNamed:@"tree.png"],nil];
        
        [self showImagessidesamples:samplesArray scrollView:sampleScrollview];
        
        NSString *imagePath;
        NSBundle *bundle = [NSBundle mainBundle]; 
        NSString *path = [bundle bundlePath];
        imagePath = [NSBundle pathForResource:@"top_bt_bg_1" ofType:@"png" inDirectory:path];
        
        
        samplesScrollviewbackground.frame=CGRectMake(440,75, 512, 80);
        samplesScrollviewbackground.image=[UIImage imageWithContentsOfFile:imagePath];
        [self.view addSubview:samplesScrollviewbackground];
    }
    [self.view insertSubview:sampleScrollview aboveSubview:self.samplesScrollviewbackground];
    
    //	[self.view insertSubview:samplesScrollviewbackground belowSubview:self.sampleScrollview];
    
    
}

-(IBAction)showDrawingPad:(id)sender{
    [self setHighletedImage:(UIButton *)sender ];
    
    self.sampleScrollview.hidden=YES;
    self.savedScrollview.hidden=YES;
    samplesScrollviewbackground.hidden=YES;
    savedScrollviewbackground.hidden=YES;
    
    if(self.padsSrollview.hidden==NO)
    { 
        [UIView beginAnimations:@"showpads" context:nil];
        [UIView setAnimationDuration:0.5];
        self.padsSrollview.alpha=0;
		self.padsSrollview.hidden=YES;
        padsScrollviewbackground.hidden=YES;
        [UIView commitAnimations];
    }
	else {
        
		[UIView beginAnimations:@"showpads" context:nil];
		[UIView setAnimationDuration:0.5];
        self.padsSrollview.hidden=NO;
        padsScrollviewbackground.hidden=NO;
        self.padsSrollview.alpha=1;
		
        [UIView commitAnimations];
	}
    
    if(nil == padsArray){
        padsArray=[[NSArray alloc] initWithObjects:[UIImage imageNamed:@"handmade_paper.png"],[UIImage imageNamed:@"handmade_paper_2.png"],[UIImage imageNamed:@"canvas_board_thumb.png"],[UIImage imageNamed:@"normal_paper.png"],[UIImage imageNamed:@"slate_1_thumb.png"],[UIImage imageNamed:@"slate_2_thumb.png"],[UIImage imageNamed:@"slate_3_thumb.png"],[UIImage imageNamed:@"slate_4_thumb.png"],nil];
        
        pads_hvr_Array=[[NSArray alloc] initWithObjects:[UIImage imageNamed:@"handmade_paper_hvr.png"],[UIImage imageNamed:@"handmade_paper_2_hvr.png"],[UIImage imageNamed:@"canvas_board_thumb_hvr.png"],[UIImage imageNamed:@"normal_paper_hvr.png"],[UIImage imageNamed:@"slate_1_thumb_hvr.png"],[UIImage imageNamed:@"slate_2_thumb_hvr.png"],[UIImage imageNamed:@"slate_3_thumb_hvr.png"],[UIImage imageNamed:@"slate_4_thumb_hvr.png"],nil];
        
        int height1 =[padsArray count]*130;
        padsSrollview.contentSize=CGSizeMake(height1, CGRectGetHeight(padsSrollview.frame));
        
        [self showImagessidepads:padsArray scrollView:padsSrollview];
        
        bigpadsArray=[[NSArray alloc] initWithObjects:[UIImage imageNamed:@"handmade_1.png"],[UIImage imageNamed:@"handmade_2.png"],[UIImage imageNamed:@"canvas.png"],[UIImage imageNamed:@"normalpaper.png"],[UIImage imageNamed:@"slate1.png"],[UIImage imageNamed:@"slate2.png"],[UIImage imageNamed:@"slate3.png"],[UIImage imageNamed:@"slate4.png"],nil];
        
        NSString *imagePath;
        NSBundle *bundle = [NSBundle mainBundle]; 
        NSString *path = [bundle bundlePath];
        imagePath = [NSBundle pathForResource:@"top_bt_bg_1" ofType:@"png" inDirectory:path];
        
        UIImageView *image = [[UIImageView alloc] init];
        image.frame = CGRectMake(448, 5, 2, 60);
        
        [image setImage:[UIImage imageNamed:@"line.png"]];
        [padsSrollview addSubview: image];
        [image release];
        
        
        padsScrollviewbackground.frame=CGRectMake(440,75, 512, 80);
        padsScrollviewbackground.image=[UIImage imageWithContentsOfFile:imagePath];
        [self.view addSubview:padsScrollviewbackground];
    }
    
	[self.view insertSubview:padsSrollview aboveSubview:self.padsScrollviewbackground];
}  


-(IBAction)saveDrawing:(id)sender{
    
    [drawpadButton setHighlighted:FALSE];
    [drawpadButton setImage:[UIImage imageNamed:@"drawing_pad.png"] forState:UIControlStateNormal];
    [sampleButton setImage:[UIImage imageNamed:@"samples.png"] forState:UIControlStateNormal];
    [sampleButton  setHighlighted:FALSE];
    [myWorkButton  setHighlighted:FALSE];
    [newButton  setHighlighted:FALSE];
    
    self.padsSrollview.hidden=YES;
    self.padsScrollviewbackground.hidden=YES;
    self.sampleScrollview.hidden=YES;
    self.samplesScrollviewbackground.hidden=YES;
    if(savedFileName==nil){
        UIAlertView *myAlertView = [[UIAlertView alloc]initWithTitle:@"Enter the file name" message:@"" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"OK", nil];
        myAlertView.tag=100;
        UITextField *myTextField = [[UITextField alloc] initWithFrame:CGRectMake(12.0, 45.0, 260.0, 23.0)];
        myAlertView.frame = CGRectMake(0, 0, 260.0, 500.0); 
        myTextField.tag = 10;
        [myTextField setBackgroundColor:[UIColor whiteColor]];
        [myAlertView addSubview:myTextField];
        [myTextField becomeFirstResponder];
        CGAffineTransform myTransform = CGAffineTransformMakeTranslation(0.0, 10.0);
        [myAlertView setTransform:myTransform];
        [myAlertView show];
        [myAlertView release];
        [myTextField release];
    }
    else{
        [self saveImage:savedFileName];
        [ Singleton sharedMySingleton]._pageUpdated=NO;
        isChageMadeToEditedDrawing=NO;
        //        updatedMsg=[[UILabel alloc]initWithFrame:CGRectMake(500, 300, 300, 30)];
        //        updatedMsg.text=[NSString stringWithFormat: @"Drawing Saved as %@",savedFileName];
        //        updatedMsg.font=[UIFont systemFontOfSize:20];
        //        updatedMsg.backgroundColor=[UIColor whiteColor];
        //        updatedMsg.textColor=[UIColor blueColor];
        //        [self.view addSubview:updatedMsg];
        //        [self performSelector:@selector(removeUpadatedMsgLabel) withObject:nil afterDelay:3.0];
    }
    
}

-(void)removeUpadatedMsgLabel{
    [updatedMsg  removeFromSuperview];
}


- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex 
{ 
    if(alertView.tag==100||alertView.tag==101)
    {
        if(buttonIndex==1)
        {
            BOOL fileexits=NO;
            UITextField *filename=(UITextField *)[alertView viewWithTag:10];
            
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
            NSString *basePath = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
            basePath = [basePath stringByAppendingPathComponent:@"DrawApp"];
            BOOL isDir;
            
            
            NSArray *tempimageNames=[[NSArray alloc]init];
            NSFileManager *fileManager=[NSFileManager defaultManager];
            if ([fileManager fileExistsAtPath:basePath isDirectory:&isDir] && isDir) {
                
                tempimageNames=    [fileManager contentsOfDirectoryAtPath:basePath error:nil];
                if([tempimageNames count]>0){
                    for(NSString *checkfileName in tempimageNames){
                        if([[checkfileName lowercaseString] isEqualToString:[[NSString stringWithFormat:@"%@.png", filename.text]lowercaseString] ]){
                            fileexits=YES;
                            break;
                        }
                    }
                }
                //[cocosView.mCurrentLayer saveImage];
            }
            
            if(fileexits){
                UIAlertView *myAlertView = [[UIAlertView alloc]initWithTitle:@"File Already Exists! Give Another Name" message:@"" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"OK", nil];
                myAlertView.tag=100;
                UITextField *myTextField = [[UITextField alloc] initWithFrame:CGRectMake(12.0, 45.0, 260.0, 23.0)];
                myAlertView.frame = CGRectMake(0, 0, 380.0, 800.0); 
                myTextField.tag = 10;
                [myTextField setBackgroundColor:[UIColor whiteColor]];
                [myAlertView addSubview:myTextField];
                [myTextField becomeFirstResponder];
                CGAffineTransform myTransform = CGAffineTransformMakeTranslation(0.0, 10.0);
                [myAlertView setTransform:myTransform];
                [myAlertView show];
                [myAlertView release];
                [myTextField release];
            }
            else{
                [self saveImage:filename.text];
            }
        }
    }
    else if(99 == alertView.tag){
        if(buttonIndex != [alertView cancelButtonIndex]){
            [cocosView.mCurrentLayer CPallete];
            [brushbutton setHighlighted:FALSE];
            [chalkbutton setHighlighted:FALSE];
            [crayonbutton setHighlighted:FALSE];
            [pencilbutton setHighlighted:FALSE];
            [slatepencilbutton setHighlighted:FALSE];
            [eraserbutton setHighlighted:FALSE];
            [self setHighletedToolsImage:nil];
            [cocosView.mCurrentLayer clearDraw];
        }
    }
    
    if(alertView.tag==101){
        if(buttonIndex==1){
            UITextField *filename=(UITextField *)[alertView viewWithTag:11];
            [self saveImage:filename.text];
        }
        
    }
    
    if(alertView.tag==102){
        if(buttonIndex==1){
            [self saveDrawing:nil];
        }
        else{
            [Singleton sharedMySingleton]._pageUpdated=NO;
        }
    }
}


-(void)saveImage:(NSString *)inFilename
{    
    if(savedFileName==nil){
        savedFileName=[[NSString alloc]init];
    }
    if(isComingFromNewpad){
        savedFileName=nil;
        isComingFromNewpad=NO;
    }
    
    savedFileName=[inFilename copy];    
    self.mainView.hidden=YES;
    self.buttonsView.hidden=YES;
    self.allButtonsView.hidden=YES;
    self.chalkView.hidden=YES;
    self.colorpencilView.hidden=YES;
    self.brushesView.hidden=YES;
    self.crayonsView.hidden=YES;
    self.slatepencilView.hidden=YES;
    self.popView.hidden=YES;
    self.brush_sizeView.hidden=YES;
    
    [cocosView.mCurrentLayer CPallete];
    
    // Save the UI Part alone
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *basePath = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
    basePath= [basePath stringByAppendingPathComponent:@"DrawApp"];
    
    NSFileManager *fileManager=[NSFileManager defaultManager];
    BOOL isDir;
    if ([fileManager fileExistsAtPath:basePath isDirectory:&isDir] && isDir) {
        
    }
    else {
        NSError *error;
        BOOL   success = [fileManager createDirectoryAtPath:basePath withIntermediateDirectories:NO attributes:nil error:&error];
        if (!success) NSLog(@"ERROR:%@", error);
        
    }
    
    basePath= [basePath stringByAppendingPathComponent:[NSString stringWithFormat: @"%@_UI",inFilename]];
    
    UIView *src = [self.view retain];
	
	UIGraphicsBeginImageContext(src.bounds.size);
	[src.layer renderInContext:UIGraphicsGetCurrentContext()];
	UIImage *resultingImage = UIGraphicsGetImageFromCurrentImageContext();
	UIGraphicsEndImageContext();
	[src release];
	
	NSData *pdfData = UIImagePNGRepresentation(resultingImage);    
    // NSData *imageData = [NSData dataWithData:UIImagePNGRepresentation(mCurrentScreenshotImage)]; 
	[pdfData writeToFile:basePath atomically:YES];
    
    [self performSelector:@selector(saveImageAfterDelay:) withObject:inFilename afterDelay:0.5];
}


-(void )saveImageAfterDelay:(NSString *)inFilename
{
    UIImage *openglImage = [cocosView.mCurrentLayer saveImage:inFilename];
    //   //NSLog(@"openglImage os %@",openglImage);
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *basePath = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
    basePath= [basePath stringByAppendingPathComponent:@"DrawApp"];
    
    NSFileManager *fileManager=[NSFileManager defaultManager];
    BOOL isDir;
    if ([fileManager fileExistsAtPath:basePath isDirectory:&isDir] && isDir) {
        
    }
    else {
        NSError *error;
        BOOL   success = [fileManager createDirectoryAtPath:basePath withIntermediateDirectories:NO attributes:nil error:&error];
        if (!success) NSLog(@"ERROR:%@", error);
        
    }
    
    basePath= [basePath stringByAppendingPathComponent:[NSString stringWithFormat: @"%@",inFilename]];
    //NSLog(@"basePath os and date%@,,,%@",basePath,[NSDate date]); 
    
    //add UImageview of Saved open gl view
    UIImageView *openglImageView = [[UIImageView alloc] initWithImage:openglImage];
    [self.view addSubview:openglImageView];
    [openglImageView release];
    
    UIView *src = [self.view retain];
	
	UIGraphicsBeginImageContext(src.bounds.size);
	[src.layer renderInContext:UIGraphicsGetCurrentContext()];
	UIImage *resultingImage = UIGraphicsGetImageFromCurrentImageContext();
	UIGraphicsEndImageContext();
	[src release];
	
	NSData *pdfData = UIImagePNGRepresentation(resultingImage);    
    // NSData *imageData = [NSData dataWithData:UIImagePNGRepresentation(mCurrentScreenshotImage)]; 
	[pdfData writeToFile:basePath atomically:YES];
    
    self.allButtonsView.hidden=NO;
    self.mainView.hidden=NO;
    
    [openglImageView removeFromSuperview];
    
    //Save the image into the photoalbum
    //UIImageWriteToSavedPhotosAlbum(mCurrentScreenshotImage, nil, nil, nil);
    
    //    //NSLog(@"mCurrentScreenshotImage is %@",mCurrentScreenshotImage);
	//[mCurrentScreenshotImage release];
    self.mainView.hidden=NO;
    self.allButtonsView.hidden=NO;
    self.buttonsView.hidden=NO;
    self.chalkView.hidden=NO;
    self.colorpencilView.hidden=NO;
    self.brushesView.hidden=NO;
    self.crayonsView.hidden=NO;
    self.slatepencilView.hidden=NO;
    self.popView.hidden=NO;
    self.brush_sizeView.hidden=NO;
    [cocosView.mCurrentLayer createPallete];
}

-(IBAction)newDrawing:(id)sender
{
    [brushbutton setImage:[UIImage imageNamed:@"brushes_bt.png"] forState:UIControlStateNormal];
    [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt_grey.png"] forState:UIControlStateNormal];
    [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt_grey.png"] forState:UIControlStateNormal];
    [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt.png"] forState:UIControlStateNormal];
    [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt.png"] forState:UIControlStateNormal];
    [drawpadButton setImage:[UIImage imageNamed:@"drawing_pad.png"] forState:UIControlStateNormal];
    [sampleButton setImage:[UIImage imageNamed:@"samples.png"] forState:UIControlStateNormal];
    [chalkbutton setEnabled:FALSE];
    [slatepencilbutton setEnabled:FALSE];
    [drawpadButton setHighlighted:FALSE];
    [sampleButton  setHighlighted:FALSE];
    [myWorkButton  setHighlighted:FALSE];
    [saveButton  setHighlighted:FALSE];
    [brushbutton setEnabled:TRUE];
    [crayonbutton setEnabled:TRUE];
    [pencilbutton setEnabled:TRUE];
    self.chalkView.alpha=0;
    self.brushesView.alpha=0;
    self.crayonsView.alpha=0;
    self.slatepencilView.alpha=0;
    self.colorpencilView.alpha=0;
    self.brush_sizeView.alpha=0;
    [cocosView.mCurrentLayer CPallete];
    [Singleton sharedMySingleton]._colour2 = 1;
    
    if(cImgTag == 6)
    {
        [cocosView.mCurrentLayer disableBalls];
    } 
    
    [brushbutton setHighlighted:TRUE];
	self.brushSecectionButton.hidden = NO;
    if([Singleton sharedMySingleton]._pageUpdated && self.savedFileName)
    {
        UIAlertView *myAlertView = [[UIAlertView alloc] initWithTitle:@"" message:@"Do you want to save the changes?" delegate:self cancelButtonTitle:@"NO" otherButtonTitles:@"YES", nil];
        myAlertView.tag=102;
        myAlertView.frame = CGRectMake(0, 0, 260.0, 500.0); 
        CGAffineTransform myTransform = CGAffineTransformMakeTranslation(0.0, 10.0);
        [myAlertView setTransform:myTransform];
        [myAlertView show];
        [myAlertView release];
        isComingFromNewpad=YES;     
    }
    
    if(isComingFromNewpad)
    {
        
    }
    else{
        self.savedFileName=nil;
        [Singleton sharedMySingleton]._pageUpdated=NO;
    }
    
    
    savedScrollview.alpha=0;
    padsSrollview.hidden=YES;
    sampleScrollview.hidden=YES;
    savedScrollviewbackground.hidden=YES;
    samplesScrollviewbackground.hidden=YES;
    padsScrollviewbackground.hidden=YES;
    buttonsView.hidden=NO;
    
    NSArray *subviews=	[self.view subviews];
	for(sampleLargeCustomView *deleteView in subviews){
		if([deleteView isKindOfClass:[sampleLargeCustomView class]]){
            
            [deleteView removeFromSuperview];
        }
	}
   	
    [FullImage setImage:[UIImage imageNamed:@"handmade_2.png"]];
    
    [cocosView.mCurrentLayer selectFrame:8];
    [cocosView.mCurrentLayer clearDraw];
}


-(IBAction)menuControlls:(id)sender{
    [drawpadButton setImage:[UIImage imageNamed:@"drawing_pad.png"] forState:UIControlStateNormal];
    [sampleButton setImage:[UIImage imageNamed:@"samples.png"] forState:UIControlStateNormal];
    [myWorkButton setImage:[UIImage imageNamed:@"myworks.png"] forState:UIControlStateNormal];
    [newButton setImage:[UIImage imageNamed:@"new.png"] forState:UIControlStateNormal];
    [saveButton setImage:[UIImage imageNamed:@"save.png"] forState:UIControlStateNormal];
    CGRect frame;
    if(self.buttonsView.hidden==NO)
    { 
        [UIView setAnimationDuration:0.5];
        //self.savedScrollview.alpha=0;
		self.savedScrollview.hidden=YES;
        self.sampleScrollview.hidden=YES;
        self.padsSrollview.hidden=YES;
        self.buttonsView.hidden=YES;
        self.padsScrollviewbackground.hidden=YES;
        self.savedScrollviewbackground.hidden=YES;
        self.samplesScrollviewbackground.hidden=YES;
        buttonsView.userInteractionEnabled=NO;
        sampleScrollview.userInteractionEnabled=NO;
        savedScrollview.userInteractionEnabled=NO;
        padsSrollview.userInteractionEnabled=NO;
        padsScrollviewbackground.userInteractionEnabled=NO;
        samplesScrollviewbackground.userInteractionEnabled=NO;
        savedScrollviewbackground.userInteractionEnabled=NO;
        
        [UIView commitAnimations];
    }
	else 
    {
    	[UIView setAnimationDuration:0.5];
	    self.savedScrollview.hidden=NO;
        self.sampleScrollview.hidden=NO;
        self.padsSrollview.hidden=NO;
        self.buttonsView.hidden=NO;
        self.padsScrollviewbackground.hidden=NO;
        self.savedScrollviewbackground.hidden=NO;
        self.samplesScrollviewbackground.hidden=NO;
        
        buttonsView.userInteractionEnabled=YES;
        sampleScrollview.userInteractionEnabled=YES;
        savedScrollview.userInteractionEnabled=YES;
        padsSrollview.userInteractionEnabled=YES;
        padsScrollviewbackground.userInteractionEnabled=YES;
        samplesScrollviewbackground.userInteractionEnabled=YES;
        savedScrollviewbackground.userInteractionEnabled=YES;
        
        [UIView commitAnimations];
	}
    self.savedScrollview.hidden=YES;
    self.sampleScrollview.hidden=YES;
    self.padsSrollview.hidden=YES;
    self.padsScrollviewbackground.hidden=YES;
    self.savedScrollviewbackground.hidden=YES;
    self.samplesScrollviewbackground.hidden=YES;
    
    frame=CGRectMake(445,8 , 512, 80);
	buttonsView.frame=frame;
	[self.view addSubview:buttonsView];
    [self.view bringSubviewToFront:menuButton];
    [self.view bringSubviewToFront:savedScrollviewbackground];
    [self.view bringSubviewToFront:samplesScrollviewbackground];
    [self.view bringSubviewToFront:padsScrollviewbackground];
    [self.view bringSubviewToFront:sampleScrollview];
    [self.view bringSubviewToFront:padsSrollview];
    [self.view bringSubviewToFront:savedScrollview];
    
}

#pragma mark -
#pragma mark  touches  ------


-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{    
    /*[UIView beginAnimations:@"hide" context:nil];
     [UIView setAnimationCurve:0.7];
     self.chalkView.alpha=0;
     self.colorpencilView.alpha=0;
     self.brushesView.alpha=0;
     self.crayonsView.alpha=0;
     self.slatepencilView.alpha=0;
     [UIView commitAnimations];
     */
}

#pragma mark -
#pragma mark   ------

-(void)showImagessidepads:images scrollView:(UIScrollView *)scrView
{  
    NSArray *subview=[padsSrollview subviews];
    for(UIView *remove in subview){
        [remove removeFromSuperview];
    }
    float x=0;
    float y=0;
    int i=0;
    int s=0;
    for (UIImage *uiimg in padsArray)
    {
        drawpadCustomView *cImgView=[[drawpadCustomView alloc]init];
        
        cImgView.userInteractionEnabled=YES;
        cImgView.delegate=self;
        cImgView.tag=i;
        CGRect frame;
        if(s<=1){
            
            [cImgView setFrame:CGRectMake(x,y,135,53)];
            frame=CGRectMake(3,3,135,48);
            cImgView.padsImageView=[[UIImageView alloc]init];
            [ cImgView.padsImageView setFrame:frame];
            [cImgView.padsImageView setContentMode:UIViewContentModeCenter];
            s++;
            x=x+135;
        }
        else {
            if(s==2){
                
                [cImgView setFrame:CGRectMake(260,y,90,53)];
                frame =CGRectMake(3,3,90,48);
                cImgView.padsImageView=[[UIImageView alloc]init];
                [ cImgView.padsImageView setFrame:frame];
                [cImgView.padsImageView setContentMode:UIViewContentModeCenter];
                x=x+90;
                s++;
                
            }
            else
            {
                [cImgView setFrame:CGRectMake(x,y,80,53)];
                frame =CGRectMake(3,3,80,48);
                cImgView.padsImageView=[[UIImageView alloc]init];
                [ cImgView.padsImageView setFrame:frame];
                [cImgView.padsImageView setContentMode:UIViewContentModeCenter];
                x=x+80;
                s++;
            }
        }
        [cImgView setUserInteractionEnabled:YES];
        
        cImgView. padsImageView.image=uiimg;
        [cImgView addSubview: cImgView.padsImageView];
        [scrView addSubview:cImgView];
        
        [ cImgView.padsImageView release];
        [cImgView release];
        i++;
        self.padsSrollview. contentSize=CGSizeMake( x, 50);
    }
}

-(void)showImagessidesamples:images scrollView:(UIScrollView *)scrView{
    float x=0;
    float y=0;
    int i=0;
    NSArray *subview=[sampleScrollview subviews];
    
    for(UIView *remove in subview){
        [remove removeFromSuperview];
    }
    
    for (UIImage *uiimg in samplesArray)
    {
        samplesCustomView *cImgView=[[samplesCustomView alloc]init];
        cImgView.userInteractionEnabled=YES;
        cImgView.delegate=self;
        cImgView.tag=i;
        //cImgView.highlighted=NO;
        [cImgView setFrame:CGRectMake(x,y,83,48)];
        [cImgView setUserInteractionEnabled:YES];
        cImgView.samplesImageView=[[UIImageView alloc]init];
        CGRect frame=CGRectMake(3,3,77,48);
        [ cImgView.samplesImageView setFrame:frame];
        cImgView. samplesImageView.image=uiimg;
        [cImgView addSubview: cImgView.samplesImageView];
        [scrView addSubview:cImgView];
        x=x+50;
        [cImgView.samplesImageView release];
        [cImgView release];
        i++;
    }
}

-(void)setpad:(drawpadCustomView *)inPadsView
{   
    int i=0;
    NSArray *resetview=[padsSrollview subviews];
    
    for(drawpadCustomView *v in resetview)
    {
        if([v isKindOfClass:[drawpadCustomView class]]){
            
            v.padsImageView.image=[padsArray objectAtIndex:i];
            i++;
        }
    }
    
    inPadsView.padsImageView.image=[pads_hvr_Array 	objectAtIndex:inPadsView.tag];
    
    lastPadType = padsArrayTag;
    cImgTag=inPadsView.tag;
    padsArrayTag=inPadsView.tag;
    
    // Clearing the drawings and the UIImages 
    [cocosView.mCurrentLayer clearDraw];
    
    NSArray *subviews=	[self.view subviews];
	for(sampleLargeCustomView *deleteView in subviews){
		if([deleteView isKindOfClass:[sampleLargeCustomView class]]){
            
            [deleteView removeFromSuperview];
        }
	}
    
    if(cImgTag == 6)
    {
        [cocosView.mCurrentLayer createBalls];
        // [self performSelector:@selector(enableBallsFunc) withObject:self afterDelay:0.1f];
        
    }
    
    if(lastPadType == 6)
    {
        [cocosView.mCurrentLayer disableBalls];
        // [self performSelector:@selector(disableBallsFunc) withObject:self afterDelay:0.1f];
    }   
    
    if(padsArrayTag>=4)  //For Slate
    {
        [Singleton sharedMySingleton]._colour2 = 2;
        [cocosView.mCurrentLayer selectBrushColor:[Singleton sharedMySingleton]._chalkColor];

        [brushbutton setImage:[UIImage imageNamed:@"brushes_bt_grey.png"] forState:UIControlStateNormal];
        [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt.png"] forState:UIControlStateNormal];
        [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt.png"] forState:UIControlStateNormal];
        [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt_grey.png"] forState:UIControlStateNormal];
        [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt_grey.png"] forState:UIControlStateNormal];
        [chalkbutton setEnabled:TRUE];
        [slatepencilbutton setEnabled:TRUE];
        [brushbutton setEnabled:FALSE];
		self.brushSecectionButton.hidden = YES;
        [crayonbutton setEnabled:FALSE];
        [pencilbutton setEnabled:FALSE];
        [chalkbutton setHighlighted:TRUE];
        [brushbutton setHighlighted:FALSE];
    }
    else
    {
        [brushbutton setImage:[UIImage imageNamed:@"brushes_bt.png"] forState:UIControlStateNormal];
        [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt_grey.png"] forState:UIControlStateNormal];
        [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt_grey.png"] forState:UIControlStateNormal];
        [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt.png"] forState:UIControlStateNormal];
        [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt.png"] forState:UIControlStateNormal];
        [chalkbutton setEnabled:FALSE];
        [slatepencilbutton setEnabled:FALSE];
        [brushbutton setEnabled:TRUE];
        [crayonbutton setEnabled:TRUE];
        [pencilbutton setEnabled:TRUE];
        [chalkbutton setHighlighted:FALSE];
        [brushbutton setHighlighted:TRUE];
		self.brushSecectionButton.hidden = NO;
    }
	
    if(cImgTag >= 4)
    {
        self.brushesView.alpha=0;
        self.colorpencilView.alpha=0;
        self.crayonsView.alpha=0;
        self.brush_sizeView.alpha=0;
        [cocosView.mCurrentLayer CPallete];
        
        if([Singleton sharedMySingleton]._colour2 == 1 || [Singleton sharedMySingleton]._colour2 == 3 || [Singleton sharedMySingleton]._colour2 == 5)
        {
            [Singleton sharedMySingleton]._colour2 = 2;
        }
    }
    else
    {
        self.slatepencilView.alpha=0;
        self.chalkView.alpha=0;
        
        if([Singleton sharedMySingleton]._colour2 == 2 || [Singleton sharedMySingleton]._colour2 == 4)
        {
            [Singleton sharedMySingleton]._colour2 = 1;
        }
    }
    
    [cocosView.mCurrentLayer selectFrame:cImgTag];
    
    if(padSelectedTag!=-1)
    {
        if(padSelectedTag!=cImgTag)
        {
            [UIView beginAnimations:@"hideImage" context:nil];
            [UIView setAnimationDuration:0.2];
            self.FullImage.alpha=0.5;
            [UIView commitAnimations];
            [UIView beginAnimations:@"showImage" context:nil];
            [UIView setAnimationDuration:0.3];
            self.FullImage.image=[self.bigpadsArray objectAtIndex:cImgTag]; 
            self.FullImage.alpha=1;
            [UIView commitAnimations];
            padSelectedTag=cImgTag;
        }
    }
    else{
        [UIView beginAnimations:@"hideImage" context:nil];
        [UIView setAnimationDuration:0.2];
        self.FullImage.alpha=0.5;
        [UIView commitAnimations];
        [UIView beginAnimations:@"showImage" context:nil];
        [UIView setAnimationDuration:0.3];
		self.FullImage.image=[self.bigpadsArray objectAtIndex:cImgTag]; 
        self.FullImage.alpha=1;
		[UIView commitAnimations];
		padSelectedTag=cImgTag;
        
    }
}

-(void)enableBallsFunc
{
    [cocosView.mCurrentLayer enableBalls];
}

-(void)disableBallsFunc
{
    [cocosView.mCurrentLayer disableBalls];
}

-(void)setsample:(samplesCustomView *)inSamplesView  locatin:(CGPoint ) inLocation
{
    float xOffSet,yOffSet;
    xOffSet=random()%500 ;
    yOffSet=random()%600 ;
    sampleLargeView=[[sampleLargeCustomView alloc]initWithFrame:CGRectMake(inLocation.x ,inLocation.y, 250,200)];
    UIImageView *image=[[UIImageView alloc]initWithImage:[bigdrawingsArray objectAtIndex:inSamplesView.tag]];
    image.frame=CGRectMake(0, 0, 250, 200);
    
    UIPinchGestureRecognizer *zoomGesture = [[UIPinchGestureRecognizer alloc] initWithTarget:sampleLargeView action:@selector(zoomsample:)];
    [sampleLargeView addGestureRecognizer:zoomGesture];
    [zoomGesture release];	
    
    UIPanGestureRecognizer *panGesture = [[UIPanGestureRecognizer alloc] initWithTarget:sampleLargeView action:@selector(panPiece:)];
    [panGesture setMaximumNumberOfTouches:2];
    [panGesture setDelegate:self];
    [sampleLargeView addGestureRecognizer:panGesture];
    [panGesture release];
    
    UIRotationGestureRecognizer *rotationGesture = [[UIRotationGestureRecognizer alloc] initWithTarget:sampleLargeView action:@selector(rotatePiece:)];
    
    [sampleLargeView addGestureRecognizer:rotationGesture];
    [rotationGesture release];
    
    UITapGestureRecognizer *TapGesture = [[UITapGestureRecognizer alloc] initWithTarget:sampleLargeView action:@selector(TapPiece:)];
    [sampleLargeView addGestureRecognizer:TapGesture];
    [TapGesture release];
    
    UITapGestureRecognizer* doubleTap = [[UITapGestureRecognizer alloc]initWithTarget:sampleLargeView action:@selector(handleDoubleTap:)];
    
    [TapGesture requireGestureRecognizerToFail : doubleTap];
    
    [doubleTap setDelaysTouchesBegan : YES];
    [TapGesture setDelaysTouchesBegan : YES];
    
    [doubleTap setNumberOfTapsRequired : 2];
    [TapGesture setNumberOfTapsRequired : 1];
    
    [sampleLargeView  addGestureRecognizer : doubleTap];
    [doubleTap release];
    
    sampleLargeView.delegate=self;
    
    [sampleLargeCustomView beginAnimations:@"mocing" context:nil];
    [sampleLargeCustomView setAnimationDuration:2.0];
    [sampleLargeCustomView setAnimationDelegate:self];
    [sampleLargeView addSubview:image];
    [image release];
    [self.view addSubview:sampleLargeView];
    sampleLargeView.frame=CGRectMake(xOffSet, yOffSet, 200, 200);
    [sampleLargeCustomView commitAnimations];	
    [self.view bringSubviewToFront:savedScrollviewbackground];
    [self.view bringSubviewToFront:samplesScrollviewbackground];
    [self.view bringSubviewToFront:padsScrollviewbackground];
    [self.view bringSubviewToFront:sampleScrollview];
    [self.view bringSubviewToFront:padsSrollview];
    [self.view bringSubviewToFront:savedScrollview];
    [self.view bringSubviewToFront:mainView];
    [self.view bringSubviewToFront:allButtonsView];
    [self.view bringSubviewToFront:buttonsView];
}

-(void)showPopUp:(sampleLargeCustomView*)inSamplesView
{
    popUpinfo=inSamplesView;
    
    CGRect sampleframe= inSamplesView.frame;
    CGRect frame=CGRectMake( sampleframe.origin.x+50, sampleframe.origin.y+50, 165, 64);
	popView.frame=frame;
	[self.view addSubview:popView];
	popView.hidden=NO;
    
}
-(void)hidePopUp 
{
	popView.hidden=YES;
}

-(IBAction)flipSample:(id)sender
{
	popUpinfo.transform=CGAffineTransformConcat(popUpinfo.transform,CGAffineTransformMake(-1, 0, 0, 1, 0, 0));
	popView.hidden=YES;
	return;
}

-(IBAction)deleteSample:(id)sender
{
    [popUpinfo removeFromSuperview];
    popView.hidden=YES;
}

-(IBAction)lockSample:(id)sender
{
    NSArray *array = popUpinfo.gestureRecognizers;
    for (UIGestureRecognizer *gesture in array) {
        if ([gesture isMemberOfClass:[UIPinchGestureRecognizer class]]) {
            if(gesture.enabled){
                gesture.enabled = NO;
                popView.hidden=YES;
                [sampleLargeView setUserInteractionEnabled:NO];
                [lockButton setBackgroundImage:[UIImage imageNamed:@"lock_bt.png"] forState:UIControlStateNormal];
            }
            else { 
                gesture.enabled = YES;
                popView.hidden=YES;
                [sampleLargeView setUserInteractionEnabled:YES];
                [lockButton setBackgroundImage:[UIImage imageNamed:@"lock_bt.png"] forState:UIControlStateNormal];   
            }
        }
        if (([gesture isMemberOfClass:[UIPanGestureRecognizer class]])) {
            if(gesture.enabled){
                gesture.enabled = NO;
                popView.hidden=YES;
                [sampleLargeView setUserInteractionEnabled:NO];
                [lockButton setBackgroundImage:[UIImage imageNamed:@"lock_bt.png"] forState:UIControlStateNormal];
            }
            else { 
                gesture.enabled = YES;
                popView.hidden=YES;
                [sampleLargeView setUserInteractionEnabled:YES];
                [lockButton setBackgroundImage:[UIImage imageNamed:@"lock_bt.png"] forState:UIControlStateNormal];   
            }                
        }
        if (([gesture isMemberOfClass:[UIRotationGestureRecognizer class]])) {
            if(gesture.enabled){
                gesture.enabled = NO;
                popView.hidden=YES;
                [sampleLargeView setUserInteractionEnabled:NO];
                [lockButton setBackgroundImage:[UIImage imageNamed:@"lock_bt.png"] forState:UIControlStateNormal];
            }
            else { 
                gesture.enabled = YES;
                popView.hidden=YES;
                [sampleLargeView setUserInteractionEnabled:YES];
                [lockButton setBackgroundImage:[UIImage imageNamed:@"lock_bt.png"] forState:UIControlStateNormal];   
            }                
        }        
    }
}


-(void)releaseMemory{
    self.showSavedMyWorks=nil;
    savedFileName=nil;
    savedScrollview=nil;
    padsSrollview=nil;
    sampleScrollview=nil;
    menuButton=nil;
    drawpadButton=nil;
    sampleButton=nil;
    myWorkButton=nil;
    buttonsView=nil;
    padsScrollviewbackground=nil;
    samplesScrollviewbackground=nil;
    savedScrollviewbackground=nil;
    brushbutton=nil;
    chalkbutton=nil;
    slatepencilbutton=nil;
    crayonbutton=nil;
    eraserbutton=nil;
    homebutton=nil;
    ch_yellow=nil;
    ch_orange=nil;
    ch_green=nil;
    ch_blue=nil;
    ch_white=nil;
    chalkView=nil;
    pencil_yellow=nil;
    pencil_chr_yellow=nil;
    pencil_orange=nil;
    pencil_scr_red=nil;
    pencil_red=nil;
    pencil_brown=nil;
    pencil_green=nil;
    pencil_lig_green=nil;
    pencil_sky_blue=nil;
    pencil_blue=nil;
    pencil_black=nil;
    pencil_white=nil;
    colorpencilView=nil;
    brush_white=nil;
    brush_blue=nil;
    brush_green=nil;
    brush_yellow=nil;
    brush_red=nil;
    brush_black=nil;
    brushesView=nil;
    cry_lemonyellow=nil;
    cry_crm_yellow=nil;
    cry_yellow_orch=nil;
    cry_orange=nil;
    cry_red=nil;
    cry_brown=nil;
    cry_darkgreen=nil;
    cry_green=nil;
    cry_skyblue=nil;
    cry_blue=nil;
    cry_black=nil;
    cry_white=nil;
    crayonsView=nil;
    slate_pencil_grey=nil;
    slate_pencil_white=nil;
    slatepencilView=nil;
    filpButton=nil;
    deleteButton=nil;
    lockButton=nil;
    popView=nil;
    popUpinfo=nil;
    brush_sizeView=nil;
    Size1button=nil;
    Size2button=nil;
    Size3button=nil;
    Size4button=nil;
    Size5button=nil;
    Size6button=nil;
}

#pragma mark - # setheightleted Image
-(void)setHighletedToolsImage:(UIButton *)inButton 
{    
    if(!inButton){
        [brushbutton setImage:[UIImage imageNamed:@"brushes_bt.png"] forState:UIControlStateNormal];
        [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt.png"] forState:UIControlStateNormal];
        [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt.png"] forState:UIControlStateNormal];
        [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt.png"] forState:UIControlStateNormal];
        [eraserbutton setImage:[UIImage imageNamed:@"eraser_bt.png"] forState:UIControlStateNormal];
        [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt.png"] forState:UIControlStateNormal];
    }
    if(inButton==brushbutton){
        [inButton setImage:[UIImage imageNamed:@"brushes_bt_hvr.png"] forState:UIControlStateNormal];
        [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt.png"] forState:UIControlStateNormal];
        [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt.png"] forState:UIControlStateNormal];
        [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt.png"] forState:UIControlStateNormal];
        [eraserbutton setImage:[UIImage imageNamed:@"eraser_bt.png"] forState:UIControlStateNormal];
        [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt.png"] forState:UIControlStateNormal];
    }
    else if(inButton==chalkbutton){
        [brushbutton setImage:[UIImage imageNamed:@"brushes_bt.png"] forState:UIControlStateNormal];
        [inButton setImage:[UIImage imageNamed:@"chalk_bt_hvr.png"] forState:UIControlStateNormal];
        [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt.png"] forState:UIControlStateNormal];
        [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt.png"] forState:UIControlStateNormal];
        [eraserbutton setImage:[UIImage imageNamed:@"eraser_bt.png"] forState:UIControlStateNormal];
        [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt.png"] forState:UIControlStateNormal];
    }
    else if(inButton==slatepencilbutton){
        [brushbutton setImage:[UIImage imageNamed:@"brushes_bt.png"] forState:UIControlStateNormal];
        [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt.png"] forState:UIControlStateNormal];
        [inButton setImage:[UIImage imageNamed:@"slate_pencil_bt_hvr.png"] forState:UIControlStateNormal];
        [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt.png"] forState:UIControlStateNormal];
        [eraserbutton setImage:[UIImage imageNamed:@"eraser_bt.png"] forState:UIControlStateNormal];
        [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt.png"] forState:UIControlStateNormal];
    }
    else if(inButton==crayonbutton){
        [brushbutton setImage:[UIImage imageNamed:@"brushes_bt.png"] forState:UIControlStateNormal];
        [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt.png"] forState:UIControlStateNormal];
        [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt.png"] forState:UIControlStateNormal];
        [inButton setImage:[UIImage imageNamed:@"cryons_bt_hvr.png"] forState:UIControlStateNormal];
        [eraserbutton setImage:[UIImage imageNamed:@"eraser_bt.png"] forState:UIControlStateNormal];
        [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt.png"] forState:UIControlStateNormal];
    }
    else if(inButton==clearbutton){
        [brushbutton setImage:[UIImage imageNamed:@"brushes_bt.png"] forState:UIControlStateNormal];
        [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt.png"] forState:UIControlStateNormal];
        [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt.png"] forState:UIControlStateNormal];
        [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt.png"] forState:UIControlStateNormal];
        [eraserbutton setImage:[UIImage imageNamed:@"eraser_bt.png"] forState:UIControlStateNormal];
        [clearbutton setImage:[UIImage imageNamed:@"clear_bt.png"] forState:UIControlStateNormal];
        [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt.png"] forState:UIControlStateNormal];
    }
    else if(inButton==eraserbutton){
        [brushbutton setImage:[UIImage imageNamed:@"brushes_bt.png"] forState:UIControlStateNormal];
        [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt.png"] forState:UIControlStateNormal];
        [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt.png"] forState:UIControlStateNormal];
        [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt.png"] forState:UIControlStateNormal];
        [inButton setImage:[UIImage imageNamed:@"eraser_bt_hvr.png"] forState:UIControlStateNormal];
        [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt.png"] forState:UIControlStateNormal];
    }
    else if(inButton==pencilbutton){
        [brushbutton setImage:[UIImage imageNamed:@"brushes_bt.png"] forState:UIControlStateNormal];
        [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt.png"] forState:UIControlStateNormal];
        [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt.png"] forState:UIControlStateNormal];
        [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt.png"] forState:UIControlStateNormal];
        [eraserbutton setImage:[UIImage imageNamed:@"eraser_bt.png"] forState:UIControlStateNormal];
        [inButton setImage:[UIImage imageNamed:@"colour_pencil_bt_hvr.png"] forState:UIControlStateNormal];
    }
}

-(void)setHighletedImage:(UIButton *)inButton 
{
    if(!inButton){
        [drawpadButton setImage:[UIImage imageNamed:@"drawing_pad.png"] forState:UIControlStateNormal];
        [sampleButton setImage:[UIImage imageNamed:@"samples.png"] forState:UIControlStateNormal];
        [myWorkButton setImage:[UIImage imageNamed:@"myworks.png"] forState:UIControlStateNormal];
        [newButton setImage:[UIImage imageNamed:@"new.png"] forState:UIControlStateNormal];
        [saveButton setImage:[UIImage imageNamed:@"save.png"] forState:UIControlStateNormal];
    }
    if(inButton==drawpadButton){
        [inButton setImage:[UIImage imageNamed:@"drawing_pad_hvr.png"] forState:UIControlStateNormal];
        
        [sampleButton setImage:[UIImage imageNamed:@"samples.png"] forState:UIControlStateNormal];
        [myWorkButton setImage:[UIImage imageNamed:@"myworks.png"] forState:UIControlStateNormal];
        [newButton setImage:[UIImage imageNamed:@"new.png"] forState:UIControlStateNormal];
        [saveButton setImage:[UIImage imageNamed:@"save.png"] forState:UIControlStateNormal];        
    }
    else if(inButton==sampleButton){
        [inButton setImage:[UIImage imageNamed:@"samples_hvr.png"] forState:UIControlStateNormal];
        
        [drawpadButton setImage:[UIImage imageNamed:@"drawing_pad.png"] forState:UIControlStateNormal];
        [myWorkButton setImage:[UIImage imageNamed:@"myworks.png"] forState:UIControlStateNormal];
        [newButton setImage:[UIImage imageNamed:@"new.png"] forState:UIControlStateNormal];
        [saveButton setImage:[UIImage imageNamed:@"save.png"] forState:UIControlStateNormal];
    }
    else if(inButton==myWorkButton){
        [inButton setImage:[UIImage imageNamed:@"myworks_hvr.png"] forState:UIControlStateNormal];
        [drawpadButton setImage:[UIImage imageNamed:@"drawing_pad.png"] forState:UIControlStateNormal];
        [sampleButton setImage:[UIImage imageNamed:@"samples.png"] forState:UIControlStateNormal];
        [newButton setImage:[UIImage imageNamed:@"new.png"] forState:UIControlStateNormal];
        [saveButton setImage:[UIImage imageNamed:@"save.png"] forState:UIControlStateNormal];
    }
    else if(inButton==saveButton){
        [inButton setImage:[UIImage imageNamed:@"save_hvr.png"] forState:UIControlStateNormal];
        [drawpadButton setImage:[UIImage imageNamed:@"drawing_pad.png"] forState:UIControlStateNormal];
        [sampleButton setImage:[UIImage imageNamed:@"samples.png"] forState:UIControlStateNormal];
        [newButton setImage:[UIImage imageNamed:@"new.png"] forState:UIControlStateNormal];
        [myWorkButton setImage:[UIImage imageNamed:@"myworks.png"] forState:UIControlStateNormal];
        
    }
    else if(inButton==newButton){
        [inButton setImage:[UIImage imageNamed:@"new_hvr.png"] forState:UIControlStateNormal];
        [drawpadButton setImage:[UIImage imageNamed:@"drawing_pad.png"] forState:UIControlStateNormal];
        [sampleButton setImage:[UIImage imageNamed:@"samples.png"] forState:UIControlStateNormal];
        [saveButton setImage:[UIImage imageNamed:@"save.png"] forState:UIControlStateNormal];
        [myWorkButton setImage:[UIImage imageNamed:@"myworks.png"] forState:UIControlStateNormal];
    }    
}

-(void)setbuttonsizeHighletedImage:(UIButton *)inButton 
{
    if(!inButton){
        [Size1button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size2button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size3button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size4button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size5button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size6button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
    }
    
    if(inButton==Size1button){
        [inButton setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size2button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size3button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size4button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size5button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size6button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];        
    }
    else if(inButton==Size2button){
        [inButton setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size1button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size3button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size4button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size5button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size6button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
    }
    else if(inButton==Size3button){
        [inButton setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size2button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size1button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size4button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size5button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size6button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
    }
    else if(inButton==Size4button){
        [inButton setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size2button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size3button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size1button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size5button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
        [Size6button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
    }
    else if(inButton==Size5button){
        [inButton setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size2button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size3button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size4button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size1button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size6button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
    }
    else if(inButton==Size6button){
        [inButton setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size2button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size3button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size4button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size5button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
        [Size1button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
    }
}

-(void)setmoveImage:(UIButton *)inButton 
{    
    if(!inButton){
        [slate_pencil_grey setFrame:CGRectMake(40, 93, 265, 26)];        
        [slate_pencil_white setFrame:CGRectMake(20, 56, 265, 26)];
        [slate_pencil_orange setFrame:CGRectMake(20, 127, 265, 26)];
        [slate_pencil_blue setFrame:CGRectMake(20, 161, 265, 26)];
        [slate_pencil_green setFrame:CGRectMake(20, 195, 265, 26)];
    }
    if(inButton==slate_pencil_grey){
        [inButton setFrame:CGRectMake(40, 93, 265, 26)];        
        [slate_pencil_white setFrame:CGRectMake(20, 56, 265, 26)];
        [slate_pencil_orange setFrame:CGRectMake(20, 127, 265, 26)];
        [slate_pencil_blue setFrame:CGRectMake(20, 161, 265, 26)];
        [slate_pencil_green setFrame:CGRectMake(20, 195, 265, 26)];
    }
    else if(inButton==slate_pencil_white){
        [inButton setFrame:CGRectMake(40, 56, 265, 26)];        
        [slate_pencil_grey setFrame:CGRectMake(20, 93, 265, 26)];
        [slate_pencil_orange setFrame:CGRectMake(20, 127, 265, 26)];
        [slate_pencil_blue setFrame:CGRectMake(20, 161, 265, 26)];
        [slate_pencil_green setFrame:CGRectMake(20, 195, 265, 26)];        
    }
    else if(inButton==slate_pencil_orange){
        [inButton setFrame:CGRectMake(40, 127, 265, 26)];        
        [slate_pencil_grey setFrame:CGRectMake(20, 93, 265, 26)];
        [slate_pencil_white setFrame:CGRectMake(20, 56, 265, 26)];
        [slate_pencil_blue setFrame:CGRectMake(20, 161, 265, 26)];
        [slate_pencil_green setFrame:CGRectMake(20, 195, 265, 26)];        
    }
    else if(inButton==slate_pencil_blue){
        [inButton setFrame:CGRectMake(40, 161, 265, 26)];        
        [slate_pencil_grey setFrame:CGRectMake(20, 93, 265, 26)];
        [slate_pencil_orange setFrame:CGRectMake(20, 127, 265, 26)];
        [slate_pencil_white setFrame:CGRectMake(20, 56, 265, 26)];
        [slate_pencil_green setFrame:CGRectMake(20, 195, 265, 26)];        
    }
    else if(inButton==slate_pencil_green){
        [inButton setFrame:CGRectMake(40, 195, 265, 26)];        
        [slate_pencil_grey setFrame:CGRectMake(20, 93, 265, 26)];
        [slate_pencil_orange setFrame:CGRectMake(20, 127, 265, 26)];
        [slate_pencil_white setFrame:CGRectMake(20, 56, 265, 26)];
        [slate_pencil_blue setFrame:CGRectMake(20, 161, 265, 26)];        
    }
}

-(void)setmovecrayonsButton:(UIButton *)inButton 
{
    if(!inButton){
        [cry_lemonyellow setFrame:CGRectMake(43, 53, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    
    if(inButton==cry_lemonyellow){
        [inButton setFrame:CGRectMake(43, 53, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_crm_yellow){
        [inButton setFrame:CGRectMake(43, 88, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_yellow_orch){
        [inButton setFrame:CGRectMake(43, 122, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_orange){
        [inButton setFrame:CGRectMake(43, 155, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_red){
        [inButton setFrame:CGRectMake(43, 189, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_brown){
        [inButton setFrame:CGRectMake(43, 223, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_darkgreen){
        [inButton setFrame:CGRectMake(43, 257, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_green){
        [inButton setFrame:CGRectMake(43, 292, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_skyblue){
        [inButton setFrame:CGRectMake(43, 327, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_blue){
        [inButton setFrame:CGRectMake(43, 362, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_black){
        [inButton setFrame:CGRectMake(43, 392, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];
        [cry_white setFrame:CGRectMake(23, 426, 195, 26)];        
    }
    else if(inButton==cry_white){
        [inButton setFrame:CGRectMake(43, 426, 195, 26)];
        [cry_crm_yellow setFrame:CGRectMake(23, 88, 195, 26)];
        [cry_yellow_orch setFrame:CGRectMake(23, 122, 195, 26)];
        [cry_orange setFrame:CGRectMake(23, 155, 195, 26)];
        [cry_red setFrame:CGRectMake(23, 189, 195, 26)];
        [cry_brown setFrame:CGRectMake(23, 223, 195, 26)];
        [cry_darkgreen setFrame:CGRectMake(23, 257, 195, 26)];
        [cry_green setFrame:CGRectMake(23, 292, 195, 26)];
        [cry_skyblue setFrame:CGRectMake(23, 327, 195, 26)];
        [cry_blue setFrame:CGRectMake(23, 362, 195, 26)];
        [cry_black setFrame:CGRectMake(23, 392, 195, 26)];
        [cry_lemonyellow setFrame:CGRectMake(23, 53, 195, 26)];        
    }
}

-(void)setmovechalksButton:(UIButton *)inButton 
{
    if(!inButton){
        [ch_yellow setFrame:CGRectMake(0, 0, 100, 41)];
        [ch_orange setFrame:CGRectMake(0, 39, 135, 41)];
        [ch_green setFrame:CGRectMake(0, 77, 135, 41)];
        [ch_blue setFrame:CGRectMake(0, 117, 135, 41)];
        [ch_white setFrame:CGRectMake(0, 158, 135, 41)];
    }
    
    if(inButton==ch_yellow){
        [inButton setFrame:CGRectMake(0, 0, 100, 41)];
        [ch_orange setFrame:CGRectMake(0, 39, 135, 41)];
        [ch_green setFrame:CGRectMake(0, 77, 135, 41)];
        [ch_blue setFrame:CGRectMake(0, 117, 135, 41)];
        [ch_white setFrame:CGRectMake(0, 158, 135, 41)];
    }
    else if(inButton==ch_orange){
        [inButton setFrame:CGRectMake(0, 39, 100, 41)];
        [ch_yellow setFrame:CGRectMake(0, 0, 135, 41)];
        [ch_green setFrame:CGRectMake(0, 77, 135, 41)];
        [ch_blue setFrame:CGRectMake(0, 117, 135, 41)];
        [ch_white setFrame:CGRectMake(0, 158, 135, 41)];
    }
    else if(inButton==ch_green){
        [inButton setFrame:CGRectMake(0, 77, 100, 41)];
        [ch_orange setFrame:CGRectMake(0, 39, 135, 41)];
        [ch_yellow setFrame:CGRectMake(0, 0, 135, 41)];
        [ch_blue setFrame:CGRectMake(0, 117, 135, 41)];
        [ch_white setFrame:CGRectMake(0, 158, 135, 41)];
    }
    else if(inButton==ch_blue){
        [inButton setFrame:CGRectMake(0, 117, 100, 41)];
        [ch_orange setFrame:CGRectMake(0, 39, 135, 41)];
        [ch_green setFrame:CGRectMake(0, 77, 135, 41)];
        [ch_yellow setFrame:CGRectMake(0, 0, 135, 41)];
        [ch_white setFrame:CGRectMake(0, 158, 135, 41)];
    }
    else if(inButton==ch_white){
        [inButton setFrame:CGRectMake(0, 158, 100, 41)];
        [ch_orange setFrame:CGRectMake(0, 39, 135, 41)];
        [ch_green setFrame:CGRectMake(0, 77, 135, 41)];
        [ch_blue setFrame:CGRectMake(0, 117, 135, 41)];
        [ch_yellow setFrame:CGRectMake(0, 0, 135, 41)];
    }
}


-(void)setmovecolorpencilsButton:(UIButton *)inButton 
{
    if(!inButton){
        [pencil_yellow setFrame:CGRectMake(39, 61, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    
    if(inButton==pencil_yellow){
        [inButton setFrame:CGRectMake(39, 61, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_chr_yellow){
        [inButton setFrame:CGRectMake(39, 92, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_orange){
        [inButton setFrame:CGRectMake(39, 124, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_scr_red){
        [inButton setFrame:CGRectMake(39, 158, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_red){
        [inButton setFrame:CGRectMake(39, 189, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_brown){
        [inButton setFrame:CGRectMake(39, 221, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_green){
        [inButton setFrame:CGRectMake(39, 254, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_lig_green){
        [inButton setFrame:CGRectMake(39, 287, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_sky_blue){
        [inButton setFrame:CGRectMake(39, 322, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_blue){
        [inButton setFrame:CGRectMake(39, 354, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_black){
        [inButton setFrame:CGRectMake(39, 391, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
        [pencil_white setFrame:CGRectMake(19, 423, 260, 23)];
    }
    else if(inButton==pencil_white){
        [inButton setFrame:CGRectMake(39, 423, 260, 23)];
        [pencil_chr_yellow setFrame:CGRectMake(19, 92, 260, 23)];
        [pencil_orange setFrame:CGRectMake(19, 124, 260, 23)];
        [pencil_scr_red setFrame:CGRectMake(19, 158, 260, 23)];
        [pencil_red setFrame:CGRectMake(19, 189, 260, 23)];
        [pencil_brown setFrame:CGRectMake(19, 221, 260, 23)];
        [pencil_green setFrame:CGRectMake(19, 254, 260, 23)];
        [pencil_lig_green setFrame:CGRectMake(19, 287, 260, 23)];
        [pencil_sky_blue setFrame:CGRectMake(19, 322, 260, 23)];
        [pencil_blue setFrame:CGRectMake(19, 354, 260, 23)];
        [pencil_black setFrame:CGRectMake(19, 391, 260, 23)];
        [pencil_yellow setFrame:CGRectMake(19, 61, 260, 23)];
    }
}

-(void)deleteInSuperView:(NSSet *)touches withEvent:(UIEvent *)event view:(sampleLargeCustomView *)inSamplesView 
{
    CGPoint center=[inSamplesView center];
	
	if(center.x<-51 ||center.x>1024 ||center.y<-42 ||center.y>730)
	{
		[inSamplesView removeFromSuperview];
		inSamplesView=nil;						
	}
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

#pragma mark -  EditArtWork Delegate Methods -
-(void)fileDidSelectForEditing:(NSString*)inFileName;
{
    [cocosView.mCurrentLayer clearDraw];
    
    NSString *temp = [NSString stringWithFormat:@"%@.png",inFileName];
    
    inFileName = [NSString stringWithFormat:@"%@_UI",inFileName];
    //NSLog(@"view bg is %@",inFileName);
    
    [FullImage setImage:[UIImage imageWithContentsOfFile:inFileName]]; 
    
    [cocosView.mCurrentLayer setTopLayer:temp];
}


#pragma mark - View lifecycle

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    // remove below two lines 
    padSelectedTag=-1;
    self.redobutton.hidden=YES;
    
    cocosView=[[CocosCreator alloc] initWithFrame:CGRectMake(96,96,832,582)];
    [self.view addSubview:cocosView];
    [cocosView release];
    
    
    CGRect frame2=CGRectMake( 80,615 , 322, 103);
    brush_sizeView.frame=frame2;
    [self.view addSubview:brush_sizeView];
    self.brush_sizeView.alpha=0;
    
    // [cocosView.mCurrentLayer redraw];
    
    [super viewDidLoad];
        
    // ComingfromDrawpad=YES;
    self.navigationController.navigationBar.hidden=YES;
    
    padsScrollviewbackground=[[UIImageView alloc]init];
    samplesScrollviewbackground=[[UIImageView alloc]init];
    savedScrollviewbackground=[[UIImageView alloc]init];
    
    [Size1button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
    [Size2button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
    [Size3button setImage:[UIImage imageNamed:@"brush_nib_hvr.png"] forState:UIControlStateNormal];
    [Size4button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
    [Size5button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
    [Size6button setImage:[UIImage imageNamed:@"brush_nib.png"] forState:UIControlStateNormal];
    
    [brushbutton setImage:[UIImage imageNamed:@"brushes_bt.png"] forState:UIControlStateNormal];
    [chalkbutton setImage:[UIImage imageNamed:@"chalk_bt_grey.png"] forState:UIControlStateNormal];
    [slatepencilbutton setImage:[UIImage imageNamed:@"slate_pencil_bt_grey.png"] forState:UIControlStateNormal];
    [crayonbutton setImage:[UIImage imageNamed:@"cryons_bt.png"] forState:UIControlStateNormal];
    [pencilbutton setImage:[UIImage imageNamed:@"colour_pencil_bt.png"] forState:UIControlStateNormal];
    [chalkbutton setEnabled:FALSE];
    [slatepencilbutton setEnabled:FALSE];
    [brushbutton setEnabled:TRUE];
    [crayonbutton setEnabled:TRUE];
    [pencilbutton setEnabled:TRUE];
    
    [brushbutton setHighlighted:TRUE];
    
    
    [self.view bringSubviewToFront:mainView];
    //    [self.view bringSubviewToFront:padsSrollview]; 
    //    [self.view bringSubviewToFront:savedScrollview]; 
    [self.view bringSubviewToFront:menuButton];
    
    CGRect frame=CGRectMake( 935,6 , 83, 80);
	mainView.frame=frame;
	[self.view addSubview:mainView];
    
    //   CGRect frame1=CGRectMake( 96,96 , 832, 582);
    //	applyingView.frame=frame1;
    //	[self.view addSubview:applyingView];
    //    [self.view bringSubviewToFront:applyingView];
    
    
    [FullImage setImage:[UIImage imageNamed:@"handmade_2.png"]]; 
    
	isMovedToCenter=NO;
	UIPanGestureRecognizer *dragAllButtonView=[[UIPanGestureRecognizer alloc]initWithTarget:self action:@selector(dragAllButtonView:)];
	[allButtonsView addGestureRecognizer:dragAllButtonView];
	[dragAllButtonView release];
    AllButtonViewFrame=allButtonsView.frame;
    [self.view addSubview:allButtonsView];
    
    self.brushesView.alpha = 0;
    self.crayonsView.alpha=0;
    self.colorpencilView.alpha=0;
    self.chalkView.alpha=0;
    self.slatepencilView.alpha=0;
    self.buttonsView.hidden = YES;
    //buttonsView.userInteractionEnabled = NO;
    
    //[lockButton setBackgroundImage:[UIImage imageNamed:@"lock_bt.png"]];
    
    // [Singleton sharedMySingleton]._redoPointsArray = [[NSMutableArray alloc] init];
    
    CGRect rect = padsSrollview.frame;
    rect.origin.y -= 30;
    padsSrollview.frame = rect;
    
    rect = sampleScrollview.frame;
    rect.origin.y -= 30;
    sampleScrollview.frame = rect;
 }

-(IBAction)backToHome:(id)sender{
    //  [[CCDirector sharedDirector] replaceScene:[Menu_CocosScene scene]];	
	[self.navigationController popViewControllerAnimated:YES];
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
