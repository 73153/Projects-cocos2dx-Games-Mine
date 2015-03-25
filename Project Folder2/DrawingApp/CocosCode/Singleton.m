//
//  Singleton.m
//  DrawingApp
//
//  Created by i-CRG Labs on 5/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Singleton.h"


@implementation Singleton

static Singleton* _sharedMySingleton = nil;

@synthesize _colour1;
@synthesize _colour2;

@synthesize _chalkColor;
@synthesize _slatePencilColor;
@synthesize _crayonColor;
@synthesize _pencilColor;

@synthesize _pageUpdated;
@synthesize isType1Spinner;
@synthesize isRandomColor;
@synthesize isStopRotation;

@synthesize _pointsArray1;

+(Singleton*)sharedMySingleton
{
	@synchronized([Singleton class])
	{
		if (!_sharedMySingleton){
			[[self alloc] init];
            _sharedMySingleton._chalkColor = 6;//yellow chalk
        }
        
        
		return _sharedMySingleton;
	}
    
	return nil;
}

+(id)alloc
{
	@synchronized([Singleton class])
	{
		NSAssert(_sharedMySingleton == nil, @"Attempted to allocate a second instance of a singleton.");
		_sharedMySingleton = [super alloc];
		return _sharedMySingleton;
	}
    
	return nil;
}

-(id)init 
{
	self = [super init];
	if (self != nil)
    {
		// initialize stuff here
	}
    
	return self;
}

-(void)sayHello
{
	//NSLog(@"Hello World!");
}

-(void)dealloc
{
    [_pointsArray1 release];
    _pointsArray1 = nil;
    
    [super dealloc];
}

@end
