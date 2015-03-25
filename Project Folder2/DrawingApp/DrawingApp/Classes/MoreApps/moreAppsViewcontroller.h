//
//  moreAppsViewcontroller.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface moreAppsViewcontroller : UIViewController {
    IBOutlet  UIButton *backButton; 
    IBOutlet  UIButton *creativeButton;
    IBOutlet  UIButton *clockButton;
    IBOutlet  UIButton *clock2Button;
    IBOutlet  UIButton *loveButton;
    IBOutlet  UIButton *love2Button;
    IBOutlet  UIButton *fallsButton;
    IBOutlet  UIButton *falls2Button;
    IBOutlet UIScrollView *scrollview;
    UIScrollView *mistPromoScrollView;
}
@property(nonatomic,retain)UIButton *backButton;
@property(nonatomic,retain)UIButton *creativeButton;
@property(nonatomic,retain)UIButton *clockButton;
@property(nonatomic,retain)UIButton *clock2Button;
@property(nonatomic,retain)UIButton *loveButton;
@property(nonatomic,retain)UIButton *love2Button;
@property(nonatomic,retain)UIButton *fallsButton;
@property(nonatomic,retain)UIButton *falls2Button;
@property(nonatomic,retain)UIScrollView *scrollview;

@property (nonatomic, retain) IBOutlet UIScrollView *mistPromoScrollView;

-(IBAction)goBack;
-(IBAction)select_creativeapp:(id)sender;
-(IBAction)select_clockapp_iphone:(id)sender;
-(IBAction)select_clockapp_ipad:(id)sender;
-(IBAction)select_loveapp_iphone:(id)sender;
-(IBAction)select_loveapp_ipad:(id)sender;
-(IBAction)select_fallsapp_iphone:(id)sender;
-(IBAction)select_fallsapp_ipad:(id)sender;

- (IBAction)mistybaby:(id)sender;

@end


