/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import "RRSolidView.h"

@implementation RRSolidView

#pragma mark - Life cycle

- (id)initWithFrame:(CGRect)theFrame
{
    DLog();
    self = [super initWithFrame:theFrame];
    if (self) {
        //self.backgroundColor = [UIColor colorWithRed:0.0 green:0.0 blue:1.0 alpha:1.0];
        self.backgroundColor = [UIColor redColor];//[UIColor colorWithRed:1.0 green:0.0 blue:0.0 alpha:1.0];
    }
    return self;
}

#pragma mark - Overridden methods
/*
- (void)drawRect:(CGRect)rect
{
    [[UIColor redColor] set];
    [[UIColor redColor] setFill];
    NSRectFill(NSMakeRect(0,0,200,100));
}*/

@end
