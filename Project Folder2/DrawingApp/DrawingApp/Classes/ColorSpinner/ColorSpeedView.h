//
//  ColorSpeedView.h
//  DrawingApp
//
//  Created by ICRG LABS on 24/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol ColorWheelSpeedDelegate <NSObject>

-(void)speedSelected:(int)inSpeed;

@end

@interface ColorSpeedView : UIView {
    CGPoint mTouchStartPoint;
	UIImageView *sliderView;
    
    id <ColorWheelSpeedDelegate> delegate;
}
@property(nonatomic,retain) UIImageView *sliderView;
@property(nonatomic,assign) id <ColorWheelSpeedDelegate> delegate;

-(void)loadSliderView;
-(void)updateSpeed;
@end
