//
//  samplesCustomView.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>




    @class samplesCustomView;
    @protocol samplesCustomViewDelegate
   
    -(void)setsample:(samplesCustomView *)inSamplesView;

    
    @end
    
    
    @interface samplesCustomView : UIView {
        
        UIImageView *samplesImageView;
        NSString  *samplesImageId;
        id<samplesCustomViewDelegate> delegate;
        
    }
@property(nonatomic,retain)	UIImageView *samplesImageView;
@property(nonatomic,retain) NSString  *samplesImageId;
@property(nonatomic,assign)id<samplesCustomViewDelegate> delegate;
    
    @end

    

