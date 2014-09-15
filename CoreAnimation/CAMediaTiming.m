/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CAMediaTiming.h>

NSString *const kCAFillModeForwards = @"CAFillModeForwards";
NSString *const kCAFillModeBackwards = @"CAFillModeBackwards";
NSString *const kCAFillModeBoth = @"CAFillModeBoth";
NSString *const kCAFillModeRemoved = @"CAFillModeRemoved";
NSString *const kCAFillModeFrozen = @"CAFillModeFrozen";

CFTimeInterval CACurrentMediaTime() 
{
    CFTimeInterval result = (CFTimeInterval)[NSDate timeIntervalSinceReferenceDate];
    //DLog(@"result: %f", result);
    return result;
}

