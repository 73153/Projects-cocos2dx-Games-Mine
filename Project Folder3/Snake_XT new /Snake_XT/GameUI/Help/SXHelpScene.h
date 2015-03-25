//
//  HelpScene.h
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
@interface SXHelpScene : CCLayer<UIScrollViewDelegate,UIScrollViewDelegate>{
    UIScrollView *scrollview;
    UIImageView *textImageview;
    UIImageView *helpBgImageview;

    
    UIImageView *scrollButton;
    CGRect mScrollBallRect;
    CGRect mScrollViewRect;
    BOOL mControlTapped;

}
+(id)scene;
-(void)resetControlFrame;

@end
