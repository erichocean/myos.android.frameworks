/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <UIKit/UIApplication.h>
#import <rd_app_glue.h>

typedef enum {
    _UIApplicationScreenModeActive,
    _UIApplicationScreenModeSleeping,
    _UIApplicationScreenModeOff
} _UIApplicationScreenMode;

@class UIWindow, UIScreen;

void _UIApplicationMain(struct android_app *app, NSString *appName, NSString *delegateClassName);
void _UIApplicationSetKeyWindow(UIApplication *app, UIWindow *newKeyWindow);
void _UIApplicationWindowDidBecomeVisible(UIApplication *app, UIWindow *theWindow);
void _UIApplicationWindowDidBecomeHidden(UIApplication *app, UIWindow *theWindow);
void _UIApplicationCancelTouchesInView(UIApplication *app, UIView *aView);
UIResponder *_UIApplicationFirstResponderForScreen(UIApplication *app, UIScreen *screen);
BOOL _UIApplicationFirstResponderCanPerformAction(UIApplication *app, SEL action, id sender, UIScreen *theScreen);
BOOL _UIApplicationSendActionToFirstResponder(UIApplication *app, SEL action, id sender, UIScreen *theScreen);
void _UIApplicationRemoveViewFromTouches(UIApplication* application, UIView *aView);
void _UIApplicationSetCurrentEventTouchedView();
void _UIApplicationSendEvent(UIEvent *event);
void _UIApplicationEnterForeground();
BOOL _UIApplicationEnterBackground();