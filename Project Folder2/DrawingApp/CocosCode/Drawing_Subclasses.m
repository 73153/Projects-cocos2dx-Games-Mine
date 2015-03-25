//
//  Drawing_Subclasses.m
//  DrawingApp
//
//  Created by i-CRG Labs on 5/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Drawing_Subclasses.h"


@implementation DR_Curve
@synthesize arrCurvePoints;
@synthesize brushType;
@synthesize brushColor; 

-(void)dealloc
{
    self.arrCurvePoints = nil;
    [super dealloc];
}

@end


@implementation DR_Point
@synthesize startPoint;
@synthesize endPoint;

-(void)dealloc
{
    [super dealloc];
}

@end


@implementation Brush_Color

@synthesize color;


-(void)dealloc
{
    [super dealloc];
}

@end
