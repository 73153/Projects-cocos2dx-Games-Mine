//
//  CocosScene.h
//  testEraseCocos
//
//  Created by i-CRG Labs on 5/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "Drawing_Subclasses.h"
#import "Box2D.h"
#import "GLES-Render.h"
#import "QueryCallback.h"

@interface CocosScene : CCLayer
{
	CCRenderTexture* target;

	CCSprite* brush;
	
    CCSprite* SF1;
    CCSprite* SF2;
	CCSprite* SF3;
	CCSprite* SF4;
    
    CCSprite *mPallete;
    CCSprite *mPalletTab1;
    CCSprite *mPalletTab2;
    CCSprite *mPalletTab1_h;
    CCSprite *mPalletTab2_h;
    
    CCSprite *selSprite;
    
    CCMenu * myMenu;
    
    NSMutableArray* _colorsArray;
    NSMutableArray* _colorsArray4;
    
    UIPanGestureRecognizer *gestureRecognizer;
    
    int mSelectedTab;
    
    int mBrushColor;
    int mBrushType;
    
    ccColor3B _brushColor;
    ccColor3B _chalkColor;
    ccColor3B _slatePencilColor;
    ccColor3B _crayonColor;
    ccColor3B _pencilColor;
    
    float mBrushSize;
    float mBrushOpacity;
    
    BOOL isTouchedOnPallete;
    
    CGRect mPalletRect;
    CGRect mPalletTabRect1;
    CGRect mPalletTabRect2;
    
    //temp
    DR_Curve *aCurve;
    
    ccColor3B bColorValue;
    ccColor3B currentColor;
    
    ccColor3B pallet1Color;
    ccColor3B pallet2Color; 
    
    int r, g, b;
    int selectColorCount;
    
    
    // Create box2d world
    b2World* world;
	GLESDebugDraw *m_debugDraw;
	
	b2MouseJoint *m_MouseJoint;
	
	b2Body* groundBody;
    
    CCSprite* _ball[55];
    
    BOOL _touchedOnObj;
    BOOL isOrientationLandscapeLeft;
    
    int cin;
}


+(id) scene;
-(void) redraw;
-(void) selectBrushColor : (int) value;
-(void) selectBrushType : (int) value;
-(void) selectFrame : (int) value;
-(void) staticBox :(CCSprite *) sprite; 
-(void)	addStone1Box:(CCSprite *)spri;
-(void) clearDraw;
-(void) createBalls;
-(void) createBoundary;
-(void) selectBrushSize : (int) value;
-(void) createPallete;
-(void) CPallete;
-(void) enableBalls;
-(void) disableBalls;
-(void) panForTranslation:(CGPoint)translation;
-(void) destroyBox;

-(UIImage *)saveImage:(NSString *)inFilename;
-(void) setTopLayer:(NSString*)fileName;

@end
