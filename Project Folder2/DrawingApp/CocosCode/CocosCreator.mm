//
//  CocosCreator.m
//  testEraseCocos
//
//  Created by i-CRG Labs on 5/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CocosCreator.h"
#import "cocos2d.h"
#import "CocosScene.h"

@implementation CocosCreator
@synthesize mCurrentLayer;

- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:CGRectMake(0,0,1024,748)];
    if (self) 
    {		
		// Initialization code.
		[[CCDirector sharedDirector]end];
		
		// Setting up the director
		if( ! [CCDirector setDirectorType:CCDirectorTypeDisplayLink] )
			[CCDirector setDirectorType:CCDirectorTypeDefault];
		
		CCDirector *director = [CCDirector sharedDirector];
		
		EAGLView *glView = [EAGLView viewWithFrame:CGRectMake(0,0,1024,768)
							 pixelFormat:kEAGLColorFormatRGBA8
							 depthFormat:GL_DEPTH_COMPONENT24_OES
					  preserveBackbuffer:NO
							  sharegroup:nil
						   multiSampling:NO
						 numberOfSamples:4];
	
		glView.opaque = NO;
	
		[glView setMultipleTouchEnabled:YES];
		// attach the openglView to the director
		[director setOpenGLView:glView];
		
		[self addSubview:glView];
		
		// before creating any layer, set the landscape mode
		[director setAnimationInterval:1.0/60];
		[director setDisplayFPS:YES];
		[director setProjection:kCCDirectorProjection2D];
		
		
		[[CCDirector sharedDirector]setDeviceOrientation:CCDeviceOrientationLandscapeLeft];
		[CCTexture2D setDefaultAlphaPixelFormat:kCCTexture2DPixelFormat_RGBA4444];
		
		
		// 'scene' is an autorelease object.
		CCScene *scene = [CCScene node];
		
		// 'layer' is an autorelease object.
		mCurrentLayer = [CocosScene node];
        
		// add layer as a child to scene
		[scene addChild: mCurrentLayer];
		
		[[CCDirector sharedDirector] runWithScene:scene];
		//[[CCDirector sharedDirector] replaceScene:scene];
    }
    return self;
}




- (void)dealloc 
{
	
	//NSLog(@"Dealloc in Cocos Game Scene Creator");
    
    [super dealloc];
}



@end
