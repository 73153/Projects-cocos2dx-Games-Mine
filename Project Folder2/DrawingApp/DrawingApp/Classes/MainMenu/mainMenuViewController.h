//
//  mainMenuViewController.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
//#import "CocosCreator.h"
//#import "CocosScene.h"

@class DrawingAppViewController;
@class moreAppsViewcontroller;


@interface mainMenuViewController : UIViewController {
    
    DrawingAppViewController *viewController;
    moreAppsViewcontroller *appController;
    IBOutlet UIButton *drawingButton;
    IBOutlet UIButton *moreApps;
    
    IBOutlet UIButton *closebutton;
    IBOutlet UIScrollView *helpscrollview;
    IBOutlet UIView *helpview;
    IBOutlet UIView *buttonsView;  
    IBOutlet UIImageView *ScrollViewBackGround;
    IBOutlet UIImageView *helpImage;
    
    ///color pallets splashing
    
    IBOutlet UIButton *lemonyellow;
    IBOutlet UIButton *crm_yellow;
    IBOutlet UIButton *yellow_orch;
    IBOutlet UIButton *orange;
    IBOutlet UIButton *red;
    IBOutlet UIButton *brown;
    IBOutlet UIButton *voilet;
    IBOutlet UIButton *lightgreen;
    IBOutlet UIButton *purple;
    IBOutlet UIButton *blue;
    IBOutlet UIButton *navy_blue;
    IBOutlet UIButton *black;
    IBOutlet UIButton *white;
    IBOutlet UIButton *yellow;
    IBOutlet UIButton *saffron;
    IBOutlet UIButton *pink;
    IBOutlet UIButton *scr_red;
    
//    Menu_CocosCreator *cocosViewe;
//    CocosScene *cocosvie;
}

@property (nonatomic, retain)  DrawingAppViewController *viewController;
@property(nonatomic,retain) moreAppsViewcontroller *appController;
@property(nonatomic,retain)UIButton *drawingButton;
@property(nonatomic,retain)UIButton *moreApps;
@property(nonatomic,retain)UIView *helpview;
@property(nonatomic,retain)UIButton *closebutton;
@property(nonatomic,retain)UIScrollView *helpscrollview;
@property(nonatomic,retain)UIImageView *ScrollViewBackGround;
@property(nonatomic,retain)UIView *buttonsView;
@property(nonatomic,retain)UIImageView *helpImage;


///splashing buttons
@property(nonatomic,retain)UIButton *lemonyellow;
@property(nonatomic,retain)UIButton *crm_yellow;
@property(nonatomic,retain)UIButton *yellow_orch;
@property(nonatomic,retain)UIButton *orange;
@property(nonatomic,retain)UIButton *red;
@property(nonatomic,retain)UIButton *brown;
@property(nonatomic,retain)UIButton *voilet;
@property(nonatomic,retain)UIButton *lightgreen;
@property(nonatomic,retain)UIButton *purple;
@property(nonatomic,retain)UIButton *blue;
@property(nonatomic,retain)UIButton *navy_blue;
@property(nonatomic,retain)UIButton *black;
@property(nonatomic,retain)UIButton *white;
@property(nonatomic,retain)UIButton *yellow;
@property(nonatomic,retain)UIButton *saffron;
@property(nonatomic,retain)UIButton *pink;
@property(nonatomic,retain)UIButton *scr_red;





-(IBAction)colorSpinner:(id)inSender;

-(IBAction)goToDraw;
-(IBAction)showHelp;
-(IBAction)showMoreApps;
-(IBAction)closeHelp;
///action for buttons 

-(IBAction)Select_lemonyellow;
-(IBAction)Select_crm_yellow;
-(IBAction)Select_yellow_orch;
-(IBAction)Select_orange;
-(IBAction)Select_red;
-(IBAction)Select_brown;
-(IBAction)Select_voilet;
-(IBAction)Select_lightgreen;
-(IBAction)Select_purple;
-(IBAction)Select_blue;
-(IBAction)Select_navy_blue;
-(IBAction)Select_black;
-(IBAction)Select_white;
-(IBAction)Select_yellow;
-(IBAction)Select_saffron;
-(IBAction)Select_pink;
-(IBAction)Select_scr_red;





@end
