//
//  DrawedImage.m
//  DrawAddOn
//
//  Created by Sandeep Reddy Dega on 27/05/11.
//  Copyright 2011 Nunc Systems. All rights reserved.
//

#import "DrawedImage.h"


@implementation DrawedImage
@synthesize imageView;
@synthesize delegate;
@synthesize deleteButton;

- (id)initWithFrame:(CGRect)frame withImageName:(NSString *)imgName;
{
    self = [super initWithFrame:frame];
    if (self) {
        self.imageView=[[UIImageView alloc]initWithFrame:self.bounds];
        self.imageView.image=[UIImage imageWithContentsOfFile:imgName ];
        [self addSubview:self.imageView];
        [self.imageView release];
    }
    return self;
}

- (void)dealloc
{
    self.imageView=nil;
    self.delegate = nil;
    self.deleteButton = nil;
    [super dealloc];
}


-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
       
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
    if([self.delegate respondsToSelector:@selector(thumbArtWorkSelected:)]){
        [self.delegate thumbArtWorkSelected:self];
    }
}

@end
