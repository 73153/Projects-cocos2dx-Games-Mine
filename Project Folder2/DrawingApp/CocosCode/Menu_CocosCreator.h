//
//  Menu_CocosCreator.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Menu_CocosScene.h"

@interface Menu_CocosCreator : UIView 
{
    Menu_CocosScene* mCurrentLayerl;
}

@property(nonatomic,retain)Menu_CocosScene *mCurrentLayerl;

@end
