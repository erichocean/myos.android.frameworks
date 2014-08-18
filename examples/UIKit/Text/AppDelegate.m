/*
 * Copyright (c) 2012. All rights reserved.
 *
 */

#import "AppDelegate.h"

@implementation AppDelegate

@synthesize window;

#pragma mark - Life cycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    CGRect frame = [[UIScreen mainScreen] bounds];
    self.window = [[[UIWindow alloc] initWithFrame:frame] autorelease];
    window.backgroundColor = [UIColor yellowColor];
    UILabel *label = [[[UILabel alloc] initWithFrame:CGRectMake(10,40,160,30)] autorelease];
    //label.contentScaleFactor = [[UIScreen mainScreen] scale];
    label.text = @"Test text drawing 12";
    label.textColor = [UIColor redColor];
    label.backgroundColor = [UIColor whiteColor];
    label.textAlignment = UITextAlignmentCenter;
    label.font = [UIFont boldSystemFontOfSize:12];
    [window addSubview:label];

    label = [[[UILabel alloc] initWithFrame:CGRectMake(10,80,160,30)] autorelease];
    label.text = @"Test text drawing 20";
    label.textColor = [UIColor blueColor];
    label.backgroundColor = [UIColor redColor];
    label.textAlignment = UITextAlignmentRight;
    label.font = [UIFont boldSystemFontOfSize:18];
    [window addSubview:label];

    label = [[[UILabel alloc] initWithFrame:CGRectMake(10,120,160,30)] autorelease];
    //label.contentScaleFactor = [[UIScreen mainScreen] scale];
    label.text = @"Test text drawing 20";
    label.textAlignment = UITextAlignmentLeft;
    label.font = [UIFont systemFontOfSize:16];
    [window addSubview:label];
/*
    label = [[[UILabel alloc] initWithFrame:CGRectMake(10,160,160,30)] autorelease];
    //label.contentScaleFactor = [[UIScreen mainScreen] scale];
    label.text = @"Test text drawing 20";
    label.textAlignment = UITextAlignmentLeft;
    label.font = [UIFont systemFontOfSize:16];
    [window addSubview:label];*/
    
    label = [[[UILabel alloc] initWithFrame:CGRectMake(180,40,130,30)] autorelease];
    label.text = @"Test text drawing 12";
    label.backgroundColor = [UIColor greenColor];
    label.textColor = [UIColor redColor];
    label.lineBreakMode = UILineBreakModeMiddleTruncation;
    [window addSubview:label];

    label = [[[UILabel alloc] initWithFrame:CGRectMake(180,80,130,30)] autorelease];
    //label.contentScaleFactor = [[UIScreen mainScreen] scale];
    label.text = @"Test text drawing 20";
    label.textColor = [UIColor blueColor];
    label.backgroundColor = [UIColor grayColor];
    label.lineBreakMode = UILineBreakModeHeadTruncation;
    label.font = [UIFont systemFontOfSize:18];
    [window addSubview:label];

    label = [[[UILabel alloc] initWithFrame:CGRectMake(180,120,130,30)] autorelease];
    label.text = @"Test text drawing 20";
    label.backgroundColor = [UIColor brownColor];
    label.lineBreakMode = UILineBreakModeTailTruncation;
    label.font = [UIFont fontWithName:@"DejaVu Serif-Bold" size:18];
    [window addSubview:label];

    [window makeKeyAndVisible];

    return YES;
}

- (void)dealloc
{
    [window release];
    [super dealloc];
}

@end

