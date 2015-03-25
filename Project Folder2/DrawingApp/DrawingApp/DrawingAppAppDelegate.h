//
//  DrawingAppAppDelegate.h
//  DrawingApp
//
//  Created by i-CRG Labs on 5/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DrawingAppViewController;

@interface DrawingAppAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
	DrawingAppViewController *menuViewController;
	UINavigationController *navigationController;

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet DrawingAppViewController *viewController;

@end
