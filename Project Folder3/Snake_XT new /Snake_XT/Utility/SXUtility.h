//
//  SXUtility.h
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "SXMainController.h"
#import "SXGameConstants.h"


@interface SXUtility : NSObject {
    
}
+(NSString *)getTheBasePathForPlist:(NSString *)plistName;
//+(NSString *)getDocumentsDirectoryPathForPlist:(NSString *)plistName;
+(float) getAngleFromCurrentPoint:(CGPoint )inCurrentPoint toPoint:(CGPoint)inToPoint;
+(float) getCocosAngleFromCurrentPoint:(CGPoint )p1 toPoint:(CGPoint)p2;
+ (CGPoint)getRandomPoint;
+(CGPoint)getStraightPointWithRadius:(float )radius withAngle:(float)inAngle withStartPoint:(CGPoint)startPoint;
+(CGPoint)getRotatedPointForPoint:(CGPoint)inPoint forAngle:(float)inAngle withContentSize:(CGSize)inContentSize forRectCornet:(RectCorner)inCorner;

+(float)checkTheAngleLimitAngle:(float)currentAngle;
+(float)getCurrentJoystickAngleForDegree:(float)inAngle;

+(float)getAngleFromVelocity:(CGPoint)velocity;

+ (NSMutableArray *)getSavedProfiles;


@end
