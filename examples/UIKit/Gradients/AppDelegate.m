/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import "AppDelegate.h"
#import "GradientsView.h"

@implementation AppDelegate

@synthesize window;

#pragma mark - Life cycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    CGRect frame = [[UIScreen mainScreen] bounds];
    self.window = [[[UIWindow alloc] initWithFrame:frame] autorelease];
    window.backgroundColor = [UIColor brownColor];
    float width = 313;
    float height = 200;
    float x = (frame.size.width - width) / 2.0;
    float y = (frame.size.height - height) / 2.0;
    GradientsView *gradients = [[[GradientsView alloc] initWithFrame:CGRectMake(x,y,width,height)] autorelease];
    [window addSubview:gradients];
    //DLog(@"gradients: %@", gradients);

    GradientsView *gradients2;

    gradients2 = [[[GradientsView alloc] initWithFrame:CGRectMake(x+10,y-47,width-20,100)] autorelease];
    [window addSubview:gradients2];
    gradients2 = [[[GradientsView alloc] initWithFrame:CGRectMake(x+63,y+height-120,width-113,33)] autorelease];
    [window addSubview:gradients2];

    gradients2 = [[[GradientsView alloc] initWithFrame:CGRectMake(17,33,width-33,67)] autorelease];
    [gradients addSubview:gradients2];

    [window makeKeyAndVisible];

    return YES;
}

- (void)dealloc
{
    [window release];
    [super dealloc];
}

@end

