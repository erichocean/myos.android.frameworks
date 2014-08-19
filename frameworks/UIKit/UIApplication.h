/*
 * Copyright (c) 2011, The Iconfactory. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of The Iconfactory nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE ICONFACTORY BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIDevice.h>
#import <UIKit/UIImageView.h>

extern NSString *const UIApplicationWillChangeStatusBarOrientationNotification;
extern NSString *const UIApplicationDidChangeStatusBarOrientationNotification;
extern NSString *const UIApplicationWillEnterForegroundNotification;
extern NSString *const UIApplicationWillTerminateNotification;
extern NSString *const UIApplicationWillResignActiveNotification;
extern NSString *const UIApplicationDidEnterBackgroundNotification;
extern NSString *const UIApplicationDidBecomeActiveNotification;
extern NSString *const UIApplicationDidFinishLaunchingNotification;

extern NSString *const UIApplicationLaunchOptionsURLKey;
extern NSString *const UIApplicationLaunchOptionsSourceApplicationKey;
extern NSString *const UIApplicationLaunchOptionsRemoteNotificationKey;
extern NSString *const UIApplicationLaunchOptionsAnnotationKey;
extern NSString *const UIApplicationLaunchOptionsLocalNotificationKey;
extern NSString *const UIApplicationLaunchOptionsLocationKey;

extern NSString *const UIApplicationDidReceiveMemoryWarningNotification;

extern NSString *const UITrackingRunLoopMode;

typedef enum {
  UIStatusBarStyleDefault,
  UIStatusBarStyleBlackTranslucent,
  UIStatusBarStyleBlackOpaque
} UIStatusBarStyle;

typedef enum {
    UIInterfaceOrientationPortrait           = UIDeviceOrientationPortrait,
    UIInterfaceOrientationPortraitUpsideDown = UIDeviceOrientationPortraitUpsideDown,
    UIInterfaceOrientationLandscapeLeft      = UIDeviceOrientationLandscapeRight,
    UIInterfaceOrientationLandscapeRight     = UIDeviceOrientationLandscapeLeft
} UIInterfaceOrientation;

#define UIInterfaceOrientationIsPortrait(orientation) \
((orientation) == UIInterfaceOrientationPortrait || \
(orientation) == UIInterfaceOrientationPortraitUpsideDown)

#define UIInterfaceOrientationIsLandscape(orientation) \
((orientation) == UIInterfaceOrientationLandscapeLeft || \
(orientation) == UIInterfaceOrientationLandscapeRight)

// push is not gonna work in mac os, unless you are apple (facetime)
typedef enum {
  UIRemoteNotificationTypeNone    = 0,
  UIRemoteNotificationTypeBadge   = 1 << 0,
  UIRemoteNotificationTypeSound   = 1 << 1,
  UIRemoteNotificationTypeAlert   = 1 << 2
} UIRemoteNotificationType;

typedef enum { 
  UIApplicationStateActive,
  UIApplicationStateInactive, 
  UIApplicationStateBackground
} UIApplicationState;

typedef NSUInteger UIBackgroundTaskIdentifier;

const UIBackgroundTaskIdentifier UIBackgroundTaskInvalid;
const NSTimeInterval UIMinimumKeepAliveTimeout;

@class UIWindow, UIApplication, UILocalNotification;
@protocol UIApplicationDelegate;

@interface UIApplication : UIResponder {
    @package
    UIEvent *_currentEvent;
    UIWindow *_keyWindow;
    NSMutableSet *_visibleWindows;
    UIApplicationState _applicationState;
    id<UIApplicationDelegate> _delegate;
    BOOL _idleTimerDisabled;
    BOOL _networkActivityIndicatorVisible;
    BOOL _applicationSupportsShakeToEdit;
    NSUInteger _ignoringInteractionEvents;
    NSInteger _applicationIconBadgeNumber;
    NSDate *_backgroundTasksExpirationDate;
    NSMutableArray *_backgroundTasks;
    UIView *_blackScreen;
    NSTimeInterval _lastActivityTime;
    int _screenMode;
    UIImageView *_appImage;
}

@property (nonatomic, readonly) UIWindow *keyWindow;
@property (nonatomic, readonly) NSArray *windows;
@property (nonatomic, getter=isStatusBarHidden, readonly) BOOL statusBarHidden;
@property (nonatomic, readonly) CGRect statusBarFrame;
@property (nonatomic, getter=isNetworkActivityIndicatorVisible) BOOL networkActivityIndicatorVisible; // does nothing, always returns NO
@property (nonatomic) UIInterfaceOrientation statusBarOrientation;
@property (nonatomic, readonly) NSTimeInterval statusBarOrientationAnimationDuration;
@property (nonatomic, assign) id<UIApplicationDelegate> delegate;
@property (nonatomic, getter=isIdleTimerDisabled) BOOL idleTimerDisabled;	// has no actual affect
@property (nonatomic) BOOL applicationSupportsShakeToEdit;					// no effect
@property (nonatomic) UIStatusBarStyle statusBarStyle;                      // always returns UIStatusBarStyleDefault
@property (nonatomic, readonly) UIApplicationState applicationState;        // see notes near UIApplicationState struct for details!
@property (nonatomic, readonly) NSTimeInterval backgroundTimeRemaining;     // always 0
@property (nonatomic) NSInteger applicationIconBadgeNumber;                 // no effect, but does set/get the number correctly
@property (nonatomic, copy) NSArray *scheduledLocalNotifications;           // no effect, returns nil
@property (nonatomic, retain) UIImageView *appImage;

+ (UIApplication *)sharedApplication;

- (BOOL)sendAction:(SEL)action to:(id)target from:(id)sender forEvent:(UIEvent *)event;
- (void)sendEvent:(UIEvent *)event;

- (void)setStatusBarStyle:(UIStatusBarStyle)statusBarStyle animated:(BOOL)animated;  // no effect

- (void)beginIgnoringInteractionEvents;
- (void)endIgnoringInteractionEvents;
- (BOOL)isIgnoringInteractionEvents;

- (void)cancelAllLocalNotifications;

//- (UIBackgroundTaskIdentifier)beginBackgroundTaskWithExpirationHandler:(void(^)(void))handler;
- (void)endBackgroundTask:(UIBackgroundTaskIdentifier)identifier;

@end

@interface UIApplication(UIApplicationDeprecated)
- (void)setStatusBarHidden:(BOOL)hidden animated:(BOOL)animated __attribute__((deprecated)); // use -setStatusBarHidden:withAnimation:
@end

@protocol UIApplicationDelegate <NSObject>
@optional
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
- (void)applicationDidFinishLaunching:(UIApplication *)application;
- (void)applicationDidBecomeActive:(UIApplication *)application;
- (void)applicationWillResignActive:(UIApplication *)application;
- (void)applicationWillTerminate:(UIApplication *)application;
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;
- (void)applicationDidEnterBackground:(UIApplication *)application;
- (void)applicationWillEnterForeground:(UIApplication *)application;
@end

int UIApplicationMain(int argc, char *argv[], NSString *principalClassName, NSString *delegateClassName);