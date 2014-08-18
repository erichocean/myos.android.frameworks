/*
 * Copyright (c) 2012. All rights reserved.
 *
 */

#import "AppDelegate.h"
#import "MyImageView.h"

@implementation AppDelegate

@synthesize window;

#pragma mark - Life cycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    CGRect frame = [[UIScreen mainScreen] bounds];
    self.window = [[[UIWindow alloc] initWithFrame:frame] autorelease];
    window.backgroundColor = [UIColor brownColor];
    float width = kParentFrameSize;
    float height = kParentFrameSize; 
    float x = (frame.size.width - width) / 2.0;
    float y = (frame.size.height - height) / 2.0;
    MyImageView *imageView = [[[MyImageView alloc] initWithFrame:CGRectMake(x,y,width,height)] autorelease];
    [window addSubview:imageView];
    [window makeKeyAndVisible];
    //DLog();
    return YES;
}

- (void)dealloc
{
    [window release];
    [super dealloc];
}

@end

