//
//  Singleton.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//  This class is used to store the variables as global 

#import <Foundation/Foundation.h>


@interface Singleton : NSObject 
{
    int _colour1;
    int _colour2;
       
    int _chalkColor;
    int _slatePencilColor;
    int _crayonColor;
    int _pencilColor;
    
    BOOL _pageUpdated;
	BOOL isType1Spinner;
    BOOL isRandomColor;
    BOOL isStopRotation;
	
    NSMutableArray* _pointsArray1;
}

@property(nonatomic,assign) int _colour1;
@property(nonatomic,assign) int _colour2;

@property(nonatomic,assign) int _chalkColor;
@property(nonatomic,assign) int _slatePencilColor;
@property(nonatomic,assign) int _crayonColor;
@property(nonatomic,assign) int _pencilColor;

@property(nonatomic,assign) BOOL _pageUpdated;
@property(nonatomic,assign) BOOL isType1Spinner;
@property(nonatomic,assign) BOOL isRandomColor;
@property(nonatomic,assign) BOOL isStopRotation;

@property(nonatomic,retain) NSMutableArray* _pointsArray1;

+(Singleton*)sharedMySingleton;
-(void)sayHello;

@end
