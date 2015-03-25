//
//  Menu_CocosScene.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "Menu_CocosScene.h"
#import "Singleton.h"

@interface Menu_CocosScene : CCLayer
{
	CCRenderTexture* target;

	CCSprite* brush;
	
	CCLabelTTF* tutorialLabel;
	
    int touchesCount;
    int oldTouchesCount;
    
    float radius;
	float prevXX;
	float prevYY;
    float spinner1MinValue;
    float spinner2MinValue;
    
	BOOL isTouched;
	BOOL isScheduleRunning;
	BOOL isFirstTouch;
    
	CGPoint sPoint;
	CGPoint center; 
}

+(id) scene;

-(void) clearScreen;
-(void) selectRandomColor : (int)value;
-(void) setColorFromColor : (UIColor*)inColor;
-(void) setRotaionSpeed : (int)value;
-(void)setPatternWithFileName:(NSString*)inPatternName;
@end
