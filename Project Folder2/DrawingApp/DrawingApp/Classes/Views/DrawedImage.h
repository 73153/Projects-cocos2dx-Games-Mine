//
//  DrawedImage.h
//  DrawAddOn
//
//  Created by Sandeep Reddy Dega on 27/05/11.
//  Copyright 2011 Nunc Systems. All rights reserved.
//

#import <UIKit/UIKit.h>
@class DrawedImage;
@protocol ThumbArtWorkDelegate <NSObject>

-(void)thumbArtWorkSelected:(DrawedImage*)inThumbArtView;

@end


@interface DrawedImage : UIView <UIGestureRecognizerDelegate>{
    UIImageView *imageView;
    int tag;
    id <ThumbArtWorkDelegate> delegate;
    
    UIButton *deleteButton;
}
@property(nonatomic,retain)    UIImageView *imageView;
@property(nonatomic,assign) id <ThumbArtWorkDelegate> delegate;
@property(nonatomic, retain) UIButton *deleteButton;

- (id)initWithFrame:(CGRect)frame withImageName:(NSString *)imgName;

@end
