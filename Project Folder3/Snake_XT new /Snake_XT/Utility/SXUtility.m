//
//  SXUtility.m
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "SXUtility.h"
#define SJ_PI 3.14159265359f
#define SJ_PI_X_2 6.28318530718f
#define SJ_RAD2DEG 180.0f/SJ_PI
#define SJ_DEG2RAD SJ_PI/180.0f


@implementation SXUtility
- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}


+(NSString *)getTheBasePathForPlist:(NSString *)plistName
{
    NSString *basePath = [[NSBundle mainBundle] pathForResource:plistName ofType:@"plist"];
    return basePath;
}
//+(NSString *)getDocumentsDirectoryPathForPlist:(NSString *)plistName
//{	
//    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString *basePath = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
//    NSString *plistPath =[NSString stringWithFormat:@"%@.plist",plistName];
//	basePath = [basePath stringByAppendingPathComponent:plistPath];
//	return basePath;
//}
+(float) getAngleFromCurrentPoint:(CGPoint )inCurrentPoint toPoint:(CGPoint)inToPoint
{
    CGPoint difference = ccpSub(inToPoint,inCurrentPoint);
    double angle = -1 * (atan2(difference.y, difference.x) * 180 / M_PI + 90) + 180;
    
    if (angle < 0) {
        
        angle = 360 + angle;
    }
    return abs(angle);
    // return angle;
}



+(float) getCocosAngleFromCurrentPoint:(CGPoint )p1 toPoint:(CGPoint)p2
{
    CGPoint difference = ccpSub(p1,p2);
    double angle = -1 * (atan2(difference.y, difference.x) * 180 / M_PI + 90);
    return angle;
}


+ (CGPoint)getRandomPoint
{
	CGPoint _point;
	
    int high = 280;  int low = 30;
	
	int xVal = rand() % (high - low + 1) + low;
	
	high = 440;  low = 20;
	
	int yVal = rand() % (high - low + 1) + low;
	
	_point = CGPointMake((float)yVal, (float)xVal);
    
	return _point;
    
}

+(CGPoint)getStraightPointWithRadius:(float )radius withAngle:(float)inAngle withStartPoint:(CGPoint)startPoint {
    
    float X = (startPoint.x) - sin(CC_DEGREES_TO_RADIANS(inAngle+180))*radius;
    float Y = (startPoint.y) - cos(CC_DEGREES_TO_RADIANS(inAngle+180))*radius;
    return ccp(X, Y);
}

+ (NSMutableArray *)getSavedProfiles
{
	
	NSMutableArray * profileDataArray;
	
	if([[NSUserDefaults standardUserDefaults] objectForKey:kProfileDataKey])
	{	
		profileDataArray = [NSKeyedUnarchiver unarchiveObjectWithData:[[NSUserDefaults standardUserDefaults] objectForKey:kProfileDataKey]];
		
		return profileDataArray;
	}
	
	return nil;
	
}

+(float)checkTheAngleLimitAngle:(float)currentAngle
{
    float finalAngle;
    float angleNew= currentAngle+90;
    if (angleNew<0) {
        angleNew = 360 + angleNew;
    }
    angleNew = (int)angleNew % 360;
    
    finalAngle =360 - ((int)angleNew + 180);
    
    
    return finalAngle;
    
    
    
}
+(CGPoint)getRotatedPointForPoint:(CGPoint)inPoint forAngle:(float)inAngle withContentSize:(CGSize)inContentSize forRectCornet:(RectCorner)inCorner
{
    double rad = inAngle*M_PI/180;
    
    if (inCorner == kTopLeft) {
        float tX = -(inContentSize.width * cosf(rad) + inContentSize.height * sinf(rad) ) + inPoint.x;
        float tY = -(inContentSize.width * sinf(rad) - inContentSize.height * cosf(rad) ) + inPoint.y;
        return ccp(tX, tY);
    }
    else if (inCorner == kTopRight) {
        float tX = (inContentSize.width * cosf(rad) - inContentSize.height * sinf(rad) ) + inPoint.x;
        float tY = (inContentSize.width * sinf(rad) + inContentSize.height * cosf(rad) ) + inPoint.y;
        return ccp(tX, tY);
    }
    else if (inCorner == kBottomLeft) {
        float tX = -(inContentSize.width * cosf(rad) - inContentSize.height * sinf(rad) ) + inPoint.x;
        float tY = -(inContentSize.width * sinf(rad) + inContentSize.height * cosf(rad) ) + inPoint.y;
        return ccp(tX, tY);
    }
    else if (inCorner == kBottomRight) {
        float tX = (inContentSize.width * cosf(rad) + inContentSize.height * sinf(rad) ) + inPoint.x;
        float tY = (inContentSize.width * sinf(rad) - inContentSize.height * cosf(rad) ) + inPoint.y;
        return ccp(tX, tY);
    }
    return CGPointZero;
}
+(float)getCurrentJoystickAngleForDegree:(float)inAngle
{
    float angleDegrees = inAngle-90;
    float cocosAngle = -1 * angleDegrees;
    return cocosAngle;
}

+(float)getAngleFromVelocity:(CGPoint)velocity{
    
	float dx = velocity.x;
	float dy =velocity.y;
	
	float angle = atan2f(dy, dx); // in radians
	if(angle < 0)
	{
		angle+= SJ_PI_X_2;
	}
	float degrees = angle * SJ_RAD2DEG;
	float angleDegrees = degrees-90;
	float cocosAngle = -1 * angleDegrees;
    return cocosAngle;
    //snakeHead.rotation=cocosAngle;
    
    
}

@end
