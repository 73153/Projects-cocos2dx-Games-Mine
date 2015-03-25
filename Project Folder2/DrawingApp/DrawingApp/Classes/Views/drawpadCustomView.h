//
//  drawpadCustomView.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


//@interface drawpadCustomView : UIView { 
    @class drawpadCustomView;
    @protocol drawpadCoustomViewDelegate
    
-(void)setpad:(drawpadCustomView *)inPadsView;
    
    @end
    
    
    @interface drawpadCustomView : UIView {
        
        UIImageView *padsImageView;
        //NSString *themeImageName;
        id<drawpadCoustomViewDelegate> delegate;
        
    }
@property(nonatomic,retain)	UIImageView *padsImageView;
@property(nonatomic,assign)id<drawpadCoustomViewDelegate> delegate;
    
    @end
