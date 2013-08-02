//
//  segmentAppController.h
//  segment
//
//  Created by 이일재 on 13. 7. 10..
//  Copyright __MyCompanyName__ 2013년. All rights reserved.
//

#define APP_HANDLED_URL @"APP_HANDLED_URL"

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

