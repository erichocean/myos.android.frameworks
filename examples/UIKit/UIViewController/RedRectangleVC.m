/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import "RedRectangleVC.h"
#import "RRSolidView.h"

@implementation RedRectangleVC

#pragma mark - Life cycle

- (void)viewDidLoad
{
    DLog();
    [super viewDidLoad];
    
    RRSolidView *solidView = [[[RRSolidView alloc] initWithFrame:CGRectMake(0, 40, 170, 150)] autorelease];
    self.view.backgroundColor = [UIColor greenColor];
    [self.view addSubview:solidView];
}

- (void)dealloc
{
    [super dealloc];
}

#pragma mark - Overridden methods

@end
