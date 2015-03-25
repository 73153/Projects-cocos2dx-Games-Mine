//
//  DrawingAppViewController.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "drawpadCustomView.h"
#import "samplesCustomView.h"
#import "savedCoustomView.h"
#import "sampleLargeCustomView.h"
#import "CocosCreator.h"
#import "CocosScene.h"
#import "DrawAddOnViewController.h"

@class DrawAddOnViewController;


@interface DrawingAppViewController : UIViewController<drawpadCoustomViewDelegate,samplesCustomViewDelegate,savedCoustomViewDelegate,sampleLargeCustomViewDelegate,UIAlertViewDelegate,UIGestureRecognizerDelegate,EditArtWorkDelegate> 
{    
	IBOutlet UIButton  *brushSecectionButton;

    IBOutlet UIView *mainView;
    IBOutlet UIView *applyingView;
    
    IBOutlet UIButton  *menuButton;
    IBOutlet UIScrollView *padsSrollview;
    IBOutlet UIScrollView *savedScrollview;
    IBOutlet UIScrollView *sampleScrollview;
    UIImageView *padsScrollviewbackground;
    UIImageView *samplesScrollviewbackground;
    UIImageView *savedScrollviewbackground;
    IBOutlet  UIImageView *FullImage;
    IBOutlet UIImageView *sampleFullImage;
    int padSelectedTag;
    int sampleSelectedTag;
    
    //menu buttons 
    IBOutlet UIButton *drawpadButton;
    IBOutlet UIButton *sampleButton;
    IBOutlet UIButton *myWorkButton;
    IBOutlet UIButton *newButton;
    IBOutlet UIButton *saveButton;
    IBOutlet UIView  *buttonsView;
    
    //tools buttons 
    IBOutlet UIButton *brushbutton;
    IBOutlet UIButton *chalkbutton;
    IBOutlet UIButton *slatepencilbutton;
    IBOutlet UIButton *crayonbutton;
    IBOutlet UIButton *eraserbutton;
    IBOutlet  UIButton *homebutton;
    IBOutlet  UIButton *clearbutton;
    IBOutlet  UIButton *pencilbutton;
    IBOutlet  UIButton *redobutton;
    IBOutlet UIView *allButtonsView;
    
    CGRect  AllButtonViewFrame;
    CGRect  chalkViewFrame;
    CGRect  brushesViewFrame;
    CGRect  colorpencilViewFrame;
    CGRect  crayonsViewFrame;
    CGRect  slatepencilViewFrame;
    
    BOOL isMovedToCenter;
    BOOL  isFadeinfadeout;
    
    //----// chalk buttons------------
    
    IBOutlet UIButton *ch_yellow;
    IBOutlet UIButton *ch_orange;
    IBOutlet UIButton *ch_green;
    IBOutlet UIButton *ch_blue;
    IBOutlet UIButton *ch_white;
    IBOutlet UIView *chalkView;
    
    
    //-----//brushes buttons-------
    
    IBOutlet UIButton *brush_white;
    IBOutlet UIButton *brush_blue;
    IBOutlet UIButton *brush_green;
    IBOutlet UIButton *brush_yellow;
    IBOutlet UIButton *brush_red;
    IBOutlet UIButton *brush_black;
    IBOutlet UIView *brushesView;
    IBOutlet UIImageView *pallet_1;
    IBOutlet UIImageView *pallet_2;
    
    IBOutlet UIView  *brush_sizeView;
    IBOutlet UIButton *Size1button;
    IBOutlet UIButton *Size2button;
    IBOutlet UIButton *Size3button;
    IBOutlet UIButton *Size4button;
    IBOutlet UIButton *Size5button;
    IBOutlet UIButton *Size6button;
    
    // color pencils buttons---
    IBOutlet UIButton *pencil_yellow;
    IBOutlet UIButton *pencil_chr_yellow;
    IBOutlet UIButton *pencil_orange;
    IBOutlet UIButton *pencil_scr_red;
    IBOutlet UIButton *pencil_red;
    IBOutlet UIButton *pencil_brown;
    IBOutlet UIButton *pencil_green;
    IBOutlet UIButton *pencil_lig_green;
    IBOutlet UIButton *pencil_sky_blue;
    IBOutlet UIButton *pencil_blue;
    IBOutlet UIButton *pencil_black;
    IBOutlet UIButton *pencil_white;
    IBOutlet UIView *colorpencilView;
    /// crayons......
    IBOutlet UIButton *cry_lemonyellow;
    IBOutlet UIButton *cry_crm_yellow;
    IBOutlet UIButton *cry_yellow_orch;
    IBOutlet UIButton *cry_orange;
    IBOutlet UIButton *cry_red;
    IBOutlet UIButton *cry_brown;
    IBOutlet UIButton *cry_darkgreen;
    IBOutlet UIButton *cry_green;
    IBOutlet UIButton *cry_skyblue;
    IBOutlet UIButton *cry_blue;
    IBOutlet UIButton *cry_black;
    IBOutlet UIButton *cry_white;
    IBOutlet UIView *crayonsView;
    
    ///slate pencil
    IBOutlet UIButton *slate_pencil_grey;
    IBOutlet UIButton *slate_pencil_white;
    IBOutlet UIButton *slate_pencil_orange;
    IBOutlet UIButton *slate_pencil_blue;
    IBOutlet UIButton *slate_pencil_green;
    IBOutlet UIView *slatepencilView;
    
    //pop up 
    
    IBOutlet UIButton *filpButton;
    IBOutlet UIButton *lockButton;
    IBOutlet UIButton *deleteButton;
    IBOutlet UIView *popView;
    sampleLargeCustomView *popUpinfo;
    
    
    
    NSArray  *savedArray;
    NSArray  *padsArray,*pads_hvr_Array;
    NSArray   *samplesArray;
    NSArray  *bigdrawingsArray;
    NSArray  *bigpadsArray;
    int noOfSamplesToFly;
    int padsArrayTag;
	
    CocosCreator *cocosView;
    
    sampleLargeCustomView *sampleLargeView;
    
    NSString *savedFileName;
    UILabel *updatedMsg;
    
    int _currentChalkColor;
    int _currentSlatePencilColor;
    int _currentCrayonColor;
    int _currentPencilColor;
	
	int lastPadType;
    int cImgTag;
    // BOOL ComingfromDrawpad;
    
    DrawAddOnViewController *showSavedMyWorks;
    
}

@property(nonatomic,retain) DrawAddOnViewController *showSavedMyWorks;

@property(assign)BOOL isChageMadeToEditedDrawing,isComingFromNewpad;

@property(nonatomic,copy) NSString *savedFileName;
//@property(assign) BOOL ComingfromDrawpad;
@property(assign)BOOL isMovedToCenter;
@property(nonatomic,retain) UIView *mainView;
@property(nonatomic,retain)UIView *applyingView;
@property(nonatomic,retain)UIButton  *menuButton;
@property(nonatomic,retain)UIScrollView *padsSrollview;
@property(nonatomic,retain)UIScrollView *savedScrollview;
@property(nonatomic,retain)UIScrollView *sampleScrollview;
@property(nonatomic,retain)UIImageView *padsScrollviewbackground;
@property(nonatomic,retain)UIImageView *samplesScrollviewbackground;
@property(nonatomic,retain)UIImageView *savedScrollviewbackground;
@property(nonatomic,retain)UIImageView *FullImage;@property(nonatomic,retain)UIImageView *sampleFullImage;
@property(assign)int padSelectedTag;
@property(assign)int sampleSelectedTag;
@property(nonatomic,retain)NSArray *padsArray,*pads_hvr_Array;
@property(nonatomic,retain)NSArray *samplesArray;
@property(nonatomic,retain)NSArray  *bigdrawingsArray;
@property(nonatomic,retain)NSArray   *bigpadsArray;

@property(nonatomic,assign) int noOfSamplesToFly;
@property(nonatomic,retain)sampleLargeCustomView *popUpinfo;


@property(nonatomic,retain)UIButton *drawpadButton;
@property(nonatomic,retain)UIButton *sampleButton;
@property(nonatomic,retain)UIButton *myWorkButton;
@property(nonatomic,retain)UIButton *newButton;
@property(nonatomic,retain)UIButton *saveButton;
@property(nonatomic,retain)UIView *buttonsView;
@property(nonatomic,retain)UIView *allButtonsView;

@property(assign)CGRect  AllButtonViewFrame;
@property(assign)CGRect  chalkViewFrame;
@property(assign)CGRect  brushesViewFrame;
@property(assign)CGRect  colorpencilViewFrame;
@property(assign)CGRect  crayonsViewFrame;
@property(assign)CGRect  slatepencilViewFrame;


@property(nonatomic,retain)UIButton *brushbutton;
@property(nonatomic,retain)UIButton *brushSecectionButton;
@property(nonatomic,retain)UIButton *chalkbutton;
@property(nonatomic,retain)UIButton *slatepencilbutton;
@property(nonatomic,retain)UIButton *crayonbutton;
@property(nonatomic,retain)UIButton *eraserbutton;
@property(nonatomic,retain)UIButton *homebutton;
@property(nonatomic,retain)UIButton *clearbutton;
@property(nonatomic,retain)UIButton *pencilbutton;
@property(nonatomic,retain)UIButton *redobutton;
@property(nonatomic,retain)UIImageView *pallet_1;
@property(nonatomic,retain)UIImageView *pallet_2;

@property(nonatomic,retain)UIView  *brush_sizeView;
@property(nonatomic,retain)UIButton *Size1button;
@property(nonatomic,retain)UIButton *Size2button;
@property(nonatomic,retain)UIButton *Size3button;
@property(nonatomic,retain)UIButton *Size4button;
@property(nonatomic,retain)UIButton *Size5button;
@property(nonatomic,retain)UIButton *Size6button;

///chalk buttons property--
@property(nonatomic,retain)UIButton *ch_yellow;
@property(nonatomic,retain)UIButton *ch_orange;
@property(nonatomic,retain)UIButton *ch_green;
@property(nonatomic,retain)UIButton *ch_blue;
@property(nonatomic,retain)UIButton *ch_white;
@property(nonatomic,retain)UIView *chalkView;

// brushes button property---
@property(nonatomic,retain)UIButton *brush_white;
@property(nonatomic,retain)UIButton *brush_blue;
@property(nonatomic,retain)UIButton *brush_green;
@property(nonatomic,retain)UIButton *brush_yellow;
@property(nonatomic,retain)UIButton *brush_red;
@property(nonatomic,retain)UIButton *brush_black;
@property(nonatomic,retain)UIView *brushesView;

//// color pencils property----
@property(nonatomic,retain)UIButton *pencil_yellow;
@property(nonatomic,retain)UIButton *pencil_chr_yellow;
@property(nonatomic,retain)UIButton *pencil_orange;
@property(nonatomic,retain)UIButton *pencil_scr_red;
@property(nonatomic,retain)UIButton *pencil_red;
@property(nonatomic,retain)UIButton *pencil_brown;
@property(nonatomic,retain)UIButton *pencil_green;
@property(nonatomic,retain)UIButton *pencil_lig_green;
@property(nonatomic,retain)UIButton *pencil_sky_blue;
@property(nonatomic,retain)UIButton *pencil_blue;
@property(nonatomic,retain)UIButton *pencil_black;
@property(nonatomic,retain)UIButton *pencil_white;
@property(nonatomic,retain)UIView *colorpencilView;

///crayons property
@property(nonatomic,retain)UIButton *cry_lemonyellow;
@property(nonatomic,retain)UIButton *cry_crm_yellow;
@property(nonatomic,retain)UIButton *cry_yellow_orch;
@property(nonatomic,retain)UIButton *cry_orange;
@property(nonatomic,retain)UIButton *cry_red;
@property(nonatomic,retain)UIButton *cry_brown;
@property(nonatomic,retain)UIButton *cry_darkgreen;
@property(nonatomic,retain)UIButton *cry_green;
@property(nonatomic,retain)UIButton *cry_skyblue;
@property(nonatomic,retain)UIButton *cry_blue;
@property(nonatomic,retain)UIButton *cry_black;
@property(nonatomic,retain)UIButton *cry_white;
@property(nonatomic,retain)UIView *crayonsView;

//slate property
@property(nonatomic,retain)UIButton *slate_pencil_grey;
@property(nonatomic,retain)UIButton *slate_pencil_white;
@property(nonatomic,retain)UIButton *slate_pencil_orange;
@property(nonatomic,retain)UIButton *slate_pencil_blue;
@property(nonatomic,retain)UIButton *slate_pencil_green;
@property(nonatomic,retain)UIView *slatepencilView;


//popup property
@property(nonatomic,retain)UIButton *filpButton;
@property(nonatomic,retain)UIButton *lockButton;
@property(nonatomic,retain)UIButton *deleteButton;
@property(nonatomic,retain)UIView *popView;

-(IBAction)menuControlls:(id)sender;
-(IBAction)showDrawingPad:(id)sender;
-(IBAction)showSamples:(id)sender;
-(IBAction)showMyworks:(id)sender;
-(IBAction)saveDrawing:(id)sender;
-(IBAction)newDrawing:(id)sender;

//actions for tools buttons

-(IBAction)selectBrushes:(id)sender;
-(IBAction)selectChalks:(id)sender;
-(IBAction)selectSlatePencils:(id)sender;
-(IBAction)selectcolorpencils:(id)sender;
-(IBAction)selectCrayons:(id)sender;
-(IBAction)selectToErase:(id)sender;
-(IBAction)backToHome:(id)sender;
-(IBAction)select_to_clear:(id)sender;
-(IBAction)select_undo:(id)sender;
-(IBAction)select_redo:(id)sender;


-(IBAction)flipSample:(id)sender;
-(IBAction)deleteSample:(id)sender;
-(IBAction)lockSample:(id)sender;



/////////////////////////////////////
// actions for brushes buttons//
-(IBAction)select_brush_white:(id)sender;
-(IBAction)select_brush_blue:(id)sender;
-(IBAction)select_brush_green:(id)sender;
-(IBAction)select_brush_yellow:(id)sender;
-(IBAction)select_brush_red:(id)sender;
-(IBAction)select_brush_black:(id)sender;

-(IBAction)select_Size1button:(id)sender;
-(IBAction)select_Size2button:(id)sender;
-(IBAction)select_Size3button:(id)sender;
-(IBAction)select_Size4button:(id)sender;
-(IBAction)select_Size5button:(id)sender;
-(IBAction)select_Size6button:(id)sender;

///actions for chalks...
-(IBAction)select_ch_yellow:(id)sender;
-(IBAction)select_ch_orange:(id)sender;
-(IBAction)select_ch_green:(id)sender;
-(IBAction)select_ch_blue:(id)sender;
-(IBAction)select_ch_white:(id)sender;

// actions for color pencils
-(IBAction)select_pencil_yellow:(id)sender;
-(IBAction)select_pencil_chr_yellow:(id)sender;
-(IBAction)select_pencil_orange:(id)sender;
-(IBAction)select_pencil_scr_red:(id)sender;
-(IBAction)select_pencil_red:(id)sender;
-(IBAction)select_pencil_brown:(id)sender;
-(IBAction)select_pencil_green:(id)sender;
-(IBAction)select_pencil_lig_green:(id)sender;
-(IBAction)select_pencil_sky_blue:(id)sender;
-(IBAction)select_pencil_blue:(id)sender;
-(IBAction)select_pencil_black:(id)sender;
-(IBAction)select_pencil_white:(id)sender;


//actions for crayons...///
-(IBAction)select_cry_lemonyellow:(id)sender;
-(IBAction)select_cry_crm_yellow:(id)sender;
-(IBAction)select_cry_yellow_orch:(id)sender;
-(IBAction)select_cry_orange:(id)sender;
-(IBAction)select_cry_red:(id)sender;
-(IBAction)select_cry_brown:(id)sender;
-(IBAction)select_cry_darkgreen:(id)sender;
-(IBAction)select_cry_green:(id)sender;
-(IBAction)select_cry_skyblue:(id)sender;
-(IBAction)select_cry_blue:(id)sender;
-(IBAction)select_cry_black:(id)sender;
-(IBAction)select_cry_white:(id)sender;


/// actions for slate pencil
-(IBAction)select_slate_pencil_grey:(id)sender;
-(IBAction)select_slate_pencil_white:(id)sender;
-(IBAction)select_slate_pencil_orange:(id)sender;
-(IBAction)select_slate_pencil_blue:(id)sender;
-(IBAction)select_slate_pencil_green:(id)sender;


-(void)setHighletedToolsImage:(UIButton *)inButton ;
-(void)setbuttonsizeHighletedImage:(UIButton *)inButton ;

-(void)setHighletedImage:(UIButton *)inButton ;

-(void)setmoveImage:(UIButton *)inButton ;
-(void)setmovecrayonsButton:(UIButton *)inButton;

-(void)setmovechalksButton:(UIButton *)inButton ;
-(void)setmovecolorpencilsButton:(UIButton *)inButton;


-(void)showImagessidesamples:images scrollView:(UIScrollView *)scrView;
-(void)showImagessidepads:images scrollView:(UIScrollView *)scrView;
-(void)setsample:(samplesCustomView *)inSamplesView  locatin:(CGPoint ) inLocation;

-(void)saveImage:(NSString *)inFilename;

-(IBAction)selectBrush:(id)sender;

@end


