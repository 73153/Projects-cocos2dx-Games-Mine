//
//  savedCoustomView.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@class savedCoustomView;
@protocol savedCoustomViewDelegate

-(void)setTool:(savedCoustomView *)inToolsView;

@end


@interface savedCoustomView : UIView {
    
    UIImageView *savedImageView;
	id<savedCoustomViewDelegate> delegate;
    
}
@property(nonatomic,retain)	UIImageView *savedImageView;
@property(nonatomic,assign)id<savedCoustomViewDelegate> delegate;

@end
