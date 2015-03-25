//
//  ColorSpeedView.m
//  DrawingApp
//
//  Created by ICRG LABS on 24/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ColorSpeedView.h"

#define MAX_SPEED 10

@implementation ColorSpeedView

@synthesize sliderView,delegate;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

- (void)dealloc
{
    self.sliderView = nil;
    self.delegate = nil;
    [super dealloc];
}


-(void)loadSliderView;{
    if(nil == self.sliderView){
        UIImage *_srcColorImage = [UIImage imageNamed:@"sliderhand.png"];
		UIImageView *_bg = [[UIImageView alloc] initWithImage:_srcColorImage];
		self.sliderView = _bg;
		[self addSubview:_bg];
		CGRect viewFrame = self.sliderView.frame;
		//viewFrame.origin.x = CGRectGetMidX(self.bounds);
		viewFrame.origin.y = CGRectGetMidY(self.bounds);
		self.sliderView.frame = viewFrame;
		[_bg release];
    }
}
#pragma mark -

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{	
	mTouchStartPoint = [[touches anyObject] locationInView:self];
	
	CGRect newFrame = self.sliderView.frame;
	newFrame.origin.y = mTouchStartPoint.y;
	newFrame.origin.y -= 8;
	
	if(newFrame.origin.y < 0){
		newFrame.origin.y = 0;
	}
	else if(CGRectGetMaxY(newFrame) > CGRectGetHeight(self.bounds)){
		newFrame.origin.y = CGRectGetHeight(self.bounds)-CGRectGetHeight(newFrame);
	}
	
	self.sliderView.frame = newFrame;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
{
	CGPoint newPoint = [[touches anyObject] locationInView:self];
	
	CGRect newFrame = self.sliderView.frame;
	newFrame.origin.y += (newPoint.y-mTouchStartPoint.y);

	if(newFrame.origin.y < 0){
		newFrame.origin.y = 0;
	}
	else if(CGRectGetMaxY(newFrame) > CGRectGetHeight(self.bounds)){
		newFrame.origin.y = CGRectGetHeight(self.bounds)-CGRectGetHeight(newFrame);
	}
	self.sliderView.frame = newFrame;
	
	CGRect _frame = self.superview.frame;
	_frame.origin.y += (newPoint.y-mTouchStartPoint.y);
	//self.superview.frame = newFrame;
	
	mTouchStartPoint = newPoint;
    [self updateSpeed];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	CGPoint newPoint = [[touches anyObject] locationInView:self];
	
	CGRect newFrame = self.sliderView.frame;
	newFrame.origin.y = newPoint.y;
	newFrame.origin.y -= 8;
    
	if(newFrame.origin.y < 0){
		newFrame.origin.y = 0;
	}
	else if(CGRectGetMaxY(newFrame) > CGRectGetHeight(self.bounds)-5){
		newFrame.origin.y = CGRectGetHeight(self.bounds)-CGRectGetHeight(newFrame)-5;
	}
	
	self.sliderView.frame = newFrame;
    [self updateSpeed];
}

-(void)updateSpeed;
{
    int speed = 1;
    float height = CGRectGetHeight(self.frame);
    float originY =  CGRectGetMidY(self.sliderView.frame);
    speed = (int)(MAX_SPEED*originY)/height;
    if([self.delegate respondsToSelector:@selector(speedSelected:)]){
        [self.delegate speedSelected:MAX_SPEED-speed];
    }
}

@end
