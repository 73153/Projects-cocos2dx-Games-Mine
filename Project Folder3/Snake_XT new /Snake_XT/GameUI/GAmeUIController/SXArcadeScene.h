//
//  ArcadeScene.h
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "CCScrollLayer.h"
#import "SXDataManager.h"
@interface SXArcadeScene : CCLayer
{
    CCSprite *firstLevelSelectionBGsprite;
    CCLayer *layer1;
    CCLayer *layer2;

    CCScrollLayer *scrollLayer;
    UIView *view;
}


+(id)scene;

-(void)addLevelButtons;
-(void)updateLevelButtons;

@end;