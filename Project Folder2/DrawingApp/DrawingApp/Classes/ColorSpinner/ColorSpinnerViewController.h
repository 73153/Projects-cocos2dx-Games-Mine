//
//  ColorSpinnerViewController.h
//  DrawingApp
//
//  Created by ICRG LABS on 23/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "Menu_CocosCreator.h"
#import "Menu_CocosScene.h"
#import "Singleton.h"
#import "ColorSpeedView.h"

@interface ColorSpinnerViewController : UIViewController<ColorWheelSpeedDelegate> {
    
    UIView *colorPalette;

    UIButton *selectedColorBtn;
    UIButton *colorListBtn;
    UIButton *randomColorBtn;
    UIImageView *colorTransView;
    UISlider *speedSlider;
    UIButton *startStopBtn;
    UIView *patternPaletterView;
    UIButton *patternsBtn;
    	
	IBOutlet UIButton *clearBtn;
	IBOutlet UIButton *backBtn;

	Menu_CocosCreator *Menu_cocosView;
    ColorSpeedView *colorSpeedView;
    
    UIButton *selectedPatternBtn;

	IBOutlet UIButton *secPattern;
	IBOutlet UILabel *speedLbl;

}
@property (nonatomic, retain) IBOutlet UIView *colorPalette;
@property (nonatomic, retain) UIButton *selectedColorBtn, *selectedPatternBtn;
@property (nonatomic, retain) IBOutlet UIButton *colorListBtn;
@property (nonatomic, retain) IBOutlet UIButton *randomColorBtn;
@property (nonatomic, retain) IBOutlet UIImageView *colorTransView;
@property (nonatomic, retain) IBOutlet UISlider *speedSlider;
@property (nonatomic, retain) IBOutlet UIButton *startStopBtn;
@property (nonatomic, retain) IBOutlet UIView *patternPaletterView;
@property (nonatomic, retain) IBOutlet UIButton *patternsBtn;

- (IBAction)wheelSpeed:(id)sender;
- (IBAction)pickPattern:(id)sender;
- (IBAction)choosePattern:(id)sender;

- (IBAction)back:(id)sender;
- (IBAction)clearScreen:(id)sender;
- (IBAction)randomColor:(id)sender;
- (IBAction)selectColor:(id)sender;

- (IBAction)pickColor:(id)sender;
- (IBAction)startAndStop:(id)sender;

-(UIColor*)selectedColor;

@property (nonatomic, retain) IBOutlet ColorSpeedView *colorSpeedView;

@end
