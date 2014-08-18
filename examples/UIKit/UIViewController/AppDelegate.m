/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import "AppDelegate.h"
#import "RedRectangleVC.h"

@implementation AppDelegate

@synthesize window;

#pragma mark - Life cycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [super application:application didFinishLaunchingWithOptions:launchOptions];
    //DLog();
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    //DLog(@"window: %@", window);
    //self.window.backgroundColor = [UIColor brownColor];

    //RRSolidView *solidView = [[[RRSolidView alloc] initWithFrame:CGRectMake(0, 40, 170, 150)] autorelease];
    
    RedRectangleVC *rootVC = [[RedRectangleVC alloc] init];
    [window addSubview:rootVC.view];
    [window makeKeyAndVisible];
    return YES;
}

- (void)dealloc
{
    [window release];
    [super dealloc];
}

#pragma mark - Delegates

@end

