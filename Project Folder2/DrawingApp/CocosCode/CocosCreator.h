//
//  CocosCreator.h
//  testEraseCocos
//
//  Created by i-CRG Labs on 5/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CocosScene.h" 

@interface CocosCreator : UIView {

    CocosScene *mCurrentLayer;
}
@property(nonatomic,retain)CocosScene *mCurrentLayer;

@end
