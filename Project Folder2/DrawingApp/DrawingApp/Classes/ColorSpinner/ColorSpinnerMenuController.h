//
//  ColorSpinnerMenuController.h
//  DrawingApp
//
//  Created by ICRG LABS on 23/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface ColorSpinnerMenuController : UIViewController {
    
    UIButton *type1Btn;
    UIButton *type2Btn;
}
@property (nonatomic, retain) IBOutlet UIButton *type2Btn;
@property (nonatomic, retain) IBOutlet UIButton *type1Btn;
- (IBAction)back:(id)sender;
- (IBAction)colorSpinnerType1:(id)sender;
- (IBAction)colorSpinnerType2:(id)sender;
-(void)rotateButton:(UIButton*)inButton speed:(float)inDuration;
@end
