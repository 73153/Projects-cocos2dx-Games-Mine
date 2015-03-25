//
//  Drawing_Subclasses.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

@interface DR_Curve : NSObject 
{
    
    NSMutableArray *arrCurvePoints;    
    int brushType;
    int brushColor;
    
}
@property(nonatomic,retain)NSMutableArray *arrCurvePoints;
@property(nonatomic,assign)int brushType;
@property(nonatomic,assign)int brushColor;

@end


@interface DR_Point : NSObject
{
    CGPoint startPoint;
    CGPoint endPoint;
}
@property(nonatomic,assign)CGPoint startPoint;
@property(nonatomic,assign)CGPoint endPoint;

@end

@interface Brush_Color : NSObject
{
    ccColor3B color;
}
@property(nonatomic,assign)ccColor3B color;
@end