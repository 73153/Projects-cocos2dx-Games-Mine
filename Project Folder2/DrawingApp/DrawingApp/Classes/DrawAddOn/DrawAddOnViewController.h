//
//  DrawAddOnViewController.h
//  DrawAddOn
//
//  Created by Sandeep Reddy Dega on 27/05/11.
//  Copyright 2011 Nunc Systems. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>

#import "DrawedImage.h"

@class DrawedImage;

@protocol EditArtWorkDelegate <NSObject>

-(void)fileDidSelectForEditing:(NSString*)inFileName;

@end


@interface DrawAddOnViewController : UIViewController <UIGestureRecognizerDelegate,ThumbArtWorkDelegate,MFMailComposeViewControllerDelegate>{
    NSMutableArray *imageNames;
    IBOutlet UIImageView *savedImageView;
    IBOutlet UIScrollView *drawedScrollview;
    int pageIndex;
    IBOutlet UIButton *mainView;
    IBOutlet UIButton *editbutton;
    
    DrawedImage *selectedThumbArt;
    
    id <EditArtWorkDelegate> delegate;
}

@property(nonatomic,assign) id <EditArtWorkDelegate> delegate;

@property(nonatomic,retain)     NSMutableArray *imageNames;
@property(nonatomic,retain)     UIScrollView *drawedScrollview;
@property(nonatomic,retain)     UIImageView *savedImageView;

@property(nonatomic,retain) UIButton *mainView;
@property(nonatomic,retain) UIButton *editbutton;
@property(assign)int pageIndex;

@property(nonatomic,retain)  DrawedImage *selectedThumbArt;

-(void)setBackgroundImage:(int)tag;
-(IBAction)removeSavedImageView:(id)sender;
-(void)showDrawedScrollView ;
-(void)deletealertview;
-(void)deleteSaveddrawing:(int)inTag;
-(IBAction)editDrawing:(id)sender;
-(void)performTapGesture:(UITapGestureRecognizer *)recognizer;
-(void)setArtWorkWithFileName:(NSString*)inFileName;

-(IBAction)share:(id)sender;


@end

