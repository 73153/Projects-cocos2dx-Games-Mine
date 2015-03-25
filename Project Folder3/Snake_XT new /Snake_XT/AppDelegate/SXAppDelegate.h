//
//  AppDelegate.h
//  Snake-XT
//
//  Created by i-CRG dinesh on 5/28/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#import <UIKit/UIKit.h>
//#import "Snake-XTViewContriller.h"

@class RootViewController;

@interface SXAppDelegate : NSObject <UIApplicationDelegate> {
	UIWindow			*window;
	RootViewController	*viewController;
    UINavigationController *navController;
	

}
@property (nonatomic, retain) RootViewController *viewController;

@property (nonatomic,retain)  UINavigationController *navController;

@property (nonatomic, retain) UIWindow *window;


@end
