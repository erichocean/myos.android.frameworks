/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import "AppDelegate.h"
#import "AnimationGradientsView.h"

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
    AnimationGradientsView *gradients = [[[AnimationGradientsView alloc] initWithFrame:CGRectMake(x,y,width,height)] autorelease];
    [window addSubview:gradients];

    [UIView beginAnimations:@"move1" context:nil];
    [UIView setAnimationDuration:4.0];
    //[UIView setAnimationCurve:UIViewAnimationCurveLinear];
    [UIView setAnimationRepeatCount:2.0];
    [UIView setAnimationRepeatAutoreverses:YES];
    gradients.center = CGPointMake(160,160);
    [UIView commitAnimations];
    
    AnimationGradientsView *gradients2;

    gradients2 = [[[AnimationGradientsView alloc] initWithFrame:CGRectMake(x+10,y-47,width-20,100)] autorelease];
    [window addSubview:gradients2];

    [UIView beginAnimations:@"move2" context:nil];
    [UIView setAnimationDuration:3.0];
    [UIView setAnimationCurve:UIViewAnimationCurveLinear];
    [UIView setAnimationRepeatCount:2];
    [UIView setAnimationRepeatAutoreverses:YES];
    gradients2.center = CGPointMake(160,500);
    [UIView commitAnimations];
    
    gradients2 = [[[AnimationGradientsView alloc] initWithFrame:CGRectMake(x+63,y+height-120,width-113,33)] autorelease];
    [window addSubview:gradients2];
    
    [UIView beginAnimations:@"move3" context:nil];
    [UIView setAnimationDuration:3.0];
    [UIView setAnimationCurve:UIViewAnimationCurveLinear];
    [UIView setAnimationRepeatCount:4];
    [UIView setAnimationRepeatAutoreverses:YES];
    gradients2.center = CGPointMake(160,430);
    [UIView commitAnimations];
    
    gradients2 = [[[AnimationGradientsView alloc] initWithFrame:CGRectMake(17,33,width-33,67)] autorelease];
    [gradients addSubview:gradients2];
    [window makeKeyAndVisible];

    [UIView beginAnimations:@"move4" context:nil];
    [UIView setAnimationDuration:3.0];
    //[UIView setAnimationCurve:UIViewAnimationCurveLinear];
    [UIView setAnimationRepeatCount:2];
    [UIView setAnimationRepeatAutoreverses:YES];
    gradients2.center = CGPointMake(160,0);
    [UIView commitAnimations];
    return YES;
}

- (void)dealloc
{
    [window release];
    [super dealloc];
}

@end

