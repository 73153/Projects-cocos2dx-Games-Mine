//
//  SXCustomSprite.h
//  Snake_XT
//
//  Created by i-CRG Labs Virupaksh on 6/6/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "SXGameConstants.h"

@class SXMainController;

@interface SXCustomSprite : CCSprite{

    SXMainController *gameLayer;
}
@property(nonatomic,assign)SXMainController *gameLayer;
@end
