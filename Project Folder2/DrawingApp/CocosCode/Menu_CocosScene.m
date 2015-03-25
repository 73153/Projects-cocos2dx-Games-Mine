//
//  Menu_CocosScene.m
//  DrawingApp
//
//  Created by i-CRG Labs on 5/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Menu_CocosScene.h"


@implementation Menu_CocosScene

+(id) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	Menu_CocosScene *layer = [Menu_CocosScene node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

-(id) init
{
	// always call "super" init
	// Apple recommends to re-assign "self" with the "super" return value
	if( (self=[super init] )) 
	{
		//NSLog(@"init in menu cocos2d layer");
		self.isTouchEnabled = YES;
		
		isFirstTouch = FALSE; 
		spinner1MinValue = 1.0;
        spinner2MinValue = 25.0;
        
		CGSize screenSize = [[CCDirector sharedDirector] winSize];	
		center = ccp(screenSize.width/2,screenSize.height/2);
		
		// Create the Target for CCRender
		//target = [[CCRenderTexture renderTextureWithWidth:screenSize.width height:screenSize.height] retain] ;
	
	target=[[CCRenderTexture renderTextureWithWidth:screenSize.width height:screenSize.height pixelFormat:kTexture2DPixelFormat_RGBA8888] retain];
		[target setPosition:ccp(screenSize.width/2, screenSize.height/2)];
		[self addChild:target z:1]; 
		
		// Tutorial Label
		tutorialLabel = [CCLabelTTF labelWithString:[NSString stringWithFormat:@"Touch Me!"] dimensions:CGSizeMake(380,100) alignment:UITextAlignmentLeft fontName:@"Marker Felt" fontSize:60];
		tutorialLabel.position = ccp(350,540); 
		tutorialLabel.rotation = 270;
	    [tutorialLabel setColor:ccc3(0,255,255)];
		[self addChild:tutorialLabel z:50];
    
		// Creating the Brush According to the selection of Spinner 
        
		if([Singleton sharedMySingleton].isType1Spinner == TRUE)
		{
            //NSLog(@"type1");
			brush = [CCSprite spriteWithFile:@"1.png"]; //rjasmine rflower  
			//brush.color = ccc3(150, 100, 200);
			[brush setOpacity:255];
			[self addChild:brush];
		}
		else 
		{
            //NSLog(@"type2");
			brush = [CCSprite spriteWithFile:@"1.png"]; 
			//brush.color = ccc3(150, 100, 200);
            brush.scale = 1;
			[brush setOpacity:255];
			[self addChild:brush]; 
		}
	}
    
	return self;
}

#pragma mark - Main Schedule 
-(void) tick: (ccTime) dt
{	    
    if(![Singleton sharedMySingleton].isStopRotation)
    {
        if([Singleton sharedMySingleton].isType1Spinner == TRUE)
        {
            target.rotation += spinner1MinValue;
            
            if(isTouched)
            { 
                float X = (center.x) - sin(target.rotation)*radius;
                float Y = (center.y) - cos(target.rotation)*radius;
                
                [target begin]; 
                
                [brush setPosition:ccp(X, Y)];
                [brush visit]; 
                
                // finish drawing and return context back to the screen 
                [target end];
                
            //    angle += 0.5;
            }
        }
        else 
        {
            self.rotation += spinner2MinValue; 
            target.rotation += 0.20;
            
            if(isTouched)
            { 
                if(!isScheduleRunning)
                    [self schedule:@selector(drawCurve:)];
            }
            else 
            {
                [self unschedule:@selector(drawCurve:)];
                isScheduleRunning = FALSE;
            }
        }
    }
    else
    {
        if([Singleton sharedMySingleton].isType1Spinner)
        {
            ////NSLog(@"target rotation is %f",target.rotation);
            target.rotation = 0;
        }
        else
        {
            target.rotation = 0;
            self.rotation = 0;
        }
    }
}

// Spinner Type 2 Method
-(void) drawCurve : (ccTime*)dt
{
	isScheduleRunning = TRUE;
	
	float X = (center.x) - sin(target.rotation)*radius;
	float Y = (center.y) - cos(target.rotation)*radius;
		
	CGPoint start = ccp(X,Y);
	CGPoint end = ccp(prevXX,prevYY);
	
	[target begin]; 
	
	float distance = ccpDistance(start, end);
	if (distance > 1)
	{
		int d = (int)distance;
		for (int i = 0; i < d; i++)
		{ 
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / distance;
			[brush setPosition:ccp((start.x) + (difx * delta), (start.y) + (dify * delta))];
			[brush setRotation:rand()%360];
			// Call visit to draw the brush, don't call draw... 
			[brush visit]; 
        //    i = i + 15;
        }
	} 
	
	// finish drawing and return context back to the screen 
	[target end];
	
	prevXX = X;
	prevYY = Y; 
	
//	angle += 0.1;
}

#pragma mark - Touch Delegates
-(void) ccTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    //touchesCount++;
    oldTouchesCount = [touches count];
    
    NSArray *touchArray = [touches allObjects];
    
    UITouch *touchOne = [touchArray objectAtIndex:0];
    CGPoint locationOne = [touchOne locationInView:[touchOne view]];
    locationOne = [[CCDirector sharedDirector] convertToGL: locationOne];
    
    //NSLog(@"LocationOne is %@",NSStringFromCGPoint(locationOne));
    
//    UITouch *touchTwo = [touchArray objectAtIndex:1];
//    CGPoint locationTwo = [touchTwo locationInView:[touchTwo view]];
//    //NSLog(@"LocationTwo is %@",NSStringFromCGPoint(locationTwo));
    
    
    if(oldTouchesCount > 1)
    {
        touchesCount = touchesCount + oldTouchesCount;
    }
    else
    {
        touchesCount++;
        
    }

    //NSLog(@"touch begins after return %d",touchesCount);
    
	if(!isFirstTouch)
	{
        [self removeChild:tutorialLabel cleanup:YES];
        isFirstTouch = TRUE;
		[self schedule:@selector(tick:)];
	}
		
	UITouch *touch = [touches anyObject];
	CGPoint start = [touch locationInView: [touch view]];	
	start = [[CCDirector sharedDirector] convertToGL: start];
	
	brush.position = ccp(start.x,start.y);
	isTouched = TRUE;
	sPoint = start;
	
	radius = ccpDistance(center, start);
	
	// Setting random color for brush
	if([Singleton sharedMySingleton].isRandomColor)
	{
		int random = arc4random()%20;
		[self selectRandomColor:random];
	}
	
	if(![Singleton sharedMySingleton].isType1Spinner)
	{
		float X = (center.x) - sin(target.rotation)*radius;
		float Y = (center.y) - cos(target.rotation)*radius;
		
		prevXX = X;
		prevYY = Y; 
	}
}
 
-(void)ccTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *myTouch = [touches anyObject];
    CGPoint start = [myTouch locationInView:[myTouch view]];
    start = [[CCDirector sharedDirector] convertToGL:start];
	CGPoint end = [myTouch previousLocationInView:[myTouch view]];
	end = [[CCDirector sharedDirector] convertToGL:end];
	
	sPoint = start;
	
	radius = ccpDistance(center, start);
    
    if([Singleton sharedMySingleton].isStopRotation)
    {
        if([Singleton sharedMySingleton].isType1Spinner)
        {
            [target begin]; 
            
            [brush setPosition:ccp(start.x, start.y)];
            [brush visit]; 
            
            // finish drawing and return context back to the screen 
            [target end];
        }
        else
        {
            // Begin drawing to the render texture
            [target begin]; 
            
            // for extra points, we'll draw this smoothly from the last position and vary the sprite's
            // scale/rotation/offset
            float distance = ccpDistance(start, end);
            if (distance > 1)
            {
                int d = (int)distance;
                for (int i = 0; i < d; i++)
                { 
                    float difx = end.x - start.x;
                    float dify = end.y - start.y;
                    float delta = (float)i / distance;
                    [brush setPosition:ccp(start.x + (difx * delta), start.y + (dify * delta))];
                    //brush.color = ccc3(arc4random()%(255 - 40) + 40, arc4random()%(255 - 40) + 40, arc4random()%(255 - 40) + 40);
                    //[brush setRotation:rand()%360];
                    //float r = ((float)(rand()%50)/50.f) + 0.25f;
                    //[brush setScale:r];
                    // Call visit to draw the brush, don't call draw... 
                    [brush visit];
                }
            } 
            // finish drawing and return context back to the screen 
            [target end];
        }
	}
}

- (void)ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    oldTouchesCount = [touches count];
    if(oldTouchesCount > 1)
    {
        touchesCount = touchesCount - oldTouchesCount;
    }
    else
    {
        touchesCount--;
    }
        //NSLog(@"touch count %d",touchesCount);
	isTouched = FALSE;
	brush.position = ccp(2000,2000);
}

#pragma mark - Utilities
-(void)setPatternWithFileName:(NSString*)inPatternName;{
    
    //NSLog(@"String==%@",inPatternName);
    if(brush){
        [self removeChild:brush cleanup:YES];
    }
    brush = [CCSprite spriteWithFile:inPatternName]; //rjasmine rflower 
    //brush.color = ccc3(150, 100, 200);
    [brush setOpacity:255];
    [self addChild:brush];
}

-(void)setColorFromColor:(UIColor*)inColor;{
	
	CGColorRef _color = [inColor CGColor];
	ccColor3B colorInCC3;
	
	int numComponents = CGColorGetNumberOfComponents(_color);
	CGFloat red = 0, green = 0, blue =0;
	if (numComponents >=3)
	{
		const CGFloat *components = CGColorGetComponents(_color);
		red = components[0]*255;
		green = components[1]*255;
		blue = components[2]*255;
		colorInCC3 = ccc3(red, green, blue);
		brush.color = colorInCC3;
	}
}

-(void) clearScreen
{
	[target clear:0 g:0 b:0 a:0];
	brush.position = ccp(2000,2000);
}

-(void) selectRandomColor : (int) value
{
	Byte pixelColor[3];
	pixelColor[0] = 0;
	pixelColor[1] = 0;
	pixelColor[2] = 0;
	
	switch (value) {
		case 0:
			pixelColor[0] = 255;
			pixelColor[1] = 31;
			pixelColor[2] = 255;
			break;
		case 1:
			pixelColor[0] = 255;
			pixelColor[1] = 0;
			pixelColor[2] = 255;
			break;
		case 2:
			pixelColor[0] = 0;
			pixelColor[1] = 255;
			pixelColor[2] = 255;
			break;
		case 3:
			pixelColor[0] = 255;
			pixelColor[1] = 204;
			pixelColor[2] = 230;
			break;
		case 4:
			pixelColor[0] = 255;
			pixelColor[1] = 143;
			pixelColor[2] = 255;
			break;
		case 5:
			pixelColor[0] = 255;
			pixelColor[1] = 0;
			pixelColor[2] = 128;
			break;
		case 6:
			pixelColor[0] = 159;
			pixelColor[1] = 237;
			pixelColor[2] = 81;
			break;
		case 7:
			pixelColor[0] = 255;
			pixelColor[1] = 90;
			pixelColor[2] = 80;
			break;
		case 8:
			pixelColor[0] = 245;
			pixelColor[1] = 0;
			pixelColor[2] = 245;
			break;
		case 9:
			pixelColor[0] = 179;
			pixelColor[1] = 255;
			pixelColor[2] = 0;
			break;
		case 10:
			pixelColor[0] = 0;
			pixelColor[1] = 255;
			pixelColor[2] = 204;
			break;
		case 11:
			pixelColor[0] = 204;
			pixelColor[1] = 0;
			pixelColor[2] = 255;
			break;
		case 12:
			pixelColor[0] = 255;
			pixelColor[1] = 255;
			pixelColor[2] = 204;
			break;
		case 13:
			pixelColor[0] = 255;
			pixelColor[1] = 102;
			pixelColor[2] = 51;
			break;
		case 14:
			pixelColor[0] = 255;
			pixelColor[1] = 102;
			pixelColor[2] = 230;
			break;
		case 15:
			pixelColor[0] = 128;
			pixelColor[1] = 0;
			pixelColor[2] = 255;
			break;
		case 16:
			pixelColor[0] = 254;
			pixelColor[1] = 71;
			pixelColor[2] = 4;
			break;
		case 17:
			pixelColor[0] = 244;
			pixelColor[1] = 11;
			pixelColor[2] = 166;
			break;
		case 18:
			pixelColor[0] = 120;
			pixelColor[1] = 239;
			pixelColor[2] = 94;
			break;
		case 19:
			pixelColor[0] = 179;
			pixelColor[1] = 0;
			pixelColor[2] = 255;
			break;
		case 20:
			pixelColor[0] = 255;
			pixelColor[1] = 0;
			pixelColor[2] = 204;
			break;
		default:
			break;
	}
	brush.color = ccc3(pixelColor[0], pixelColor[1], pixelColor[2]);
}

//{
//	
//	Byte pixelColor[3];
//	pixelColor[0] = 0;
//	pixelColor[1] = 0;
//	pixelColor[2] = 0;
//	
//	switch (value) {
//		case 0:
//			pixelColor[0] = 72;
//			pixelColor[1] = 247;
//			pixelColor[2] = 53;
//			break;
//		case 1:
//			pixelColor[0] = 247;
//			pixelColor[1] = 9;
//			pixelColor[2] = 249;
//			break;
//		case 2:
//			pixelColor[0] = 15;
//			pixelColor[1] = 199;
//			pixelColor[2] = 53;
//			break;
//		case 3:
//			pixelColor[0] = 36;
//			pixelColor[1] = 61;
//			pixelColor[2] = 246;
//			break;
//		case 4:
//			pixelColor[0] = 28;
//			pixelColor[1] = 4;
//			pixelColor[2] = 132;
//			break;
//		case 5:
//			pixelColor[0] = 188;
//			pixelColor[1] = 247;
//			pixelColor[2] = 78;
//			break;
//		case 6:
//			pixelColor[0] = 248;
//			pixelColor[1] = 1;
//			pixelColor[2] = 174;
//			break;
//		case 7:
//			pixelColor[0] = 237;
//			pixelColor[1] = 39;
//			pixelColor[2] = 53;
//			break;
//		case 8:
//			pixelColor[0] = 174;
//			pixelColor[1] = 13;
//			pixelColor[2] = 227;
//			break;
//		case 9:
//			pixelColor[0] = 252;
//			pixelColor[1] = 240;
//			pixelColor[2] = 22;
//			break;
//		case 10:
//			pixelColor[0] = 175;
//			pixelColor[1] = 249;
//			pixelColor[2] = 16;
//			break;
//		case 11:
//			pixelColor[0] = 11;
//			pixelColor[1] = 230;
//			pixelColor[2] = 155;
//			break;
//		case 12:
//			pixelColor[0] = 214;
//			pixelColor[1] = 246;
//			pixelColor[2] = 220;
//			break;
//		case 13:
//			pixelColor[0] = 125;
//			pixelColor[1] = 239;
//			pixelColor[2] = 241;
//			break;
//		case 14:
//			pixelColor[0] = 250;
//			pixelColor[1] = 237;
//			pixelColor[2] = 132;
//			break;
//		case 15:
//			pixelColor[0] = 149;
//			pixelColor[1] = 21;
//			pixelColor[2] = 248;
//			break;
//		case 16:
//			pixelColor[0] = 254;
//			pixelColor[1] = 71;
//			pixelColor[2] = 4;
//			break;
//		case 17:
//			pixelColor[0] = 13;
//			pixelColor[1] = 243;
//			pixelColor[2] = 205;
//			break;
//		case 18:
//			pixelColor[0] = 120;
//			pixelColor[1] = 239;
//			pixelColor[2] = 94;
//			break;
//		case 19:
//			pixelColor[0] = 228;
//			pixelColor[1] = 28;
//			pixelColor[2] = 202;
//			break;
//		case 20:
//			pixelColor[0] = 2;
//			pixelColor[1] = 189;
//			pixelColor[2] = 115;
//			break;
//		default:
//			break;
//	}
//	brush.color = ccc3(pixelColor[0], pixelColor[1], pixelColor[2]);
//}

-(void) setRotaionSpeed : (int)value;
{
    if([Singleton sharedMySingleton].isType1Spinner)
    {
        switch (value) {
            case 1:
                spinner1MinValue = 1.4;
                break;
            case 2:
                spinner1MinValue = 1.8;
                break;
            case 3:
                spinner1MinValue = 2.2;
                break;
            case 4:
                spinner1MinValue = 2.6;
                break;
            case 5:
                spinner1MinValue = 3.0;
                break;
            case 6:
                spinner1MinValue = 3.4;
                break;
            case 7:
                spinner1MinValue = 3.8;
                break;
            case 8:
                spinner1MinValue = 4.2;
                break;
            case 9:
                spinner1MinValue = 4.6;
                break;
            case 10:
                spinner1MinValue = 5.0;
                break;
            default:
                break;
        }
        spinner1MinValue -= 3.0;
    }
    else
    {
        switch (value) {
            case 1:
                spinner2MinValue = -15.0;
                break;
            case 2:
                spinner2MinValue = -14.0;
                break;
            case 3:
                spinner2MinValue = -13.0;
                break;
            case 4:
                spinner2MinValue = -12.0;
                break;
            case 5:
                spinner2MinValue = 21.0;
                break;
            case 6:
                spinner2MinValue = 22.0;
                break;
            case 7:
                spinner2MinValue = 23.0;
                break;
            case 8:
                spinner2MinValue = 24.0;
                break;
            case 9:
                spinner2MinValue = 25.0;
                break;
            case 10:
                spinner2MinValue = 26.0;
                break;
            default:
                break;
        }
        spinner2MinValue -= 10.0;
    }
}

#pragma mark - Deallocation
-(void) dealloc
{
    [super dealloc];
} 

@end
