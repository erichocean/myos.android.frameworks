/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import "RoundButtonView.h"

@implementation RoundButtonView
 
@synthesize button;

#pragma mark - Life cycle

- (id)initWithFrame:(CGRect)theFrame
{
    self = [super initWithFrame:theFrame];
    if (self) {
        self.backgroundColor = [UIColor greenColor];
        self.button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        self.button.frame = CGRectMake(50,50,150,70);
        self.button.backgroundColor = [UIColor whiteColor];
        self.button.layer.borderColor = [[UIColor grayColor] CGColor];

        [self.button setTitle:@"Toto" forState:UIControlStateNormal];
        
//        [button addTarget:self action:@selector(clickedButton:) forControlEvents:UIControlEventTouchDown];
//        [button addTarget:self action:@selector(unClickButton:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:button];
    }
    return self;
}

- (void)dealloc
{
    [button release];
    [super dealloc];
}

#pragma mark - Actions
/*
- (void)clickedButton:(id)sender
{
    DLog(@"sender: %@", sender);
    self.button.highlighted = YES;
//    [NSTimer scheduledTimerWithTimeInterval:5.0 target:self selector:@selector(unClickButton) userInfo:nil repeats:NO];
}

- (void)unClickButton:(id)sender
{
    DLog(@"sender: %@", sender);
    self.button.highlighted = NO;
}
*/
@end

