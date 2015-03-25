//
//  sampleLargeCustomView.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>



//@interface sampleLargeCustomView : UIView {
    @class sampleLargeCustomView;
@class DrawingAppViewController;
    @protocol sampleLargeCustomViewDelegate

 -(void)showPopUp:(sampleLargeCustomView*)inSamplesView; 
-(void)deleteInSuperView:(NSSet *)touches withEvent:(UIEvent *)event view:(sampleLargeCustomView *)inSamplesView ;
-(void)hidePopUp;
    
    
    @end
    
    
    @interface sampleLargeCustomView : UIView {
        
        UIImageView *sampleLargeImageView;
         NSString  *samplesName;
        id<sampleLargeCustomViewDelegate> delegate;
        float lastScale;
        
    }
    @property(nonatomic,retain)	UIImageView *sampleLargeImageView;
   @property(nonatomic,retain) NSString *samplesName;
  @property(nonatomic,assign)float lastScale;
   @property(nonatomic,assign)id<sampleLargeCustomViewDelegate> delegate;
    
    @end
