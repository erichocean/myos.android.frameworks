/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CoreAnimation-private.h>

@implementation CATransactionGroup

#pragma mark - Life cycle

- (id)init
{
    self = [super init];
    if (self) {
        _values = CFDictionaryCreateMutable(kCFAllocatorDefault, 2, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
        CFDictionarySetValue(_values, kCATransactionAnimationDuration, [NSNumber numberWithFloat:0.25]);
        CFDictionarySetValue(_values, kCATransactionDisableActions, [NSNumber numberWithBool:NO]);
        //DLog(@"_values: %@", _values);
    }
    return self;
}

- (void)dealloc
{
    //DLog();
    CFRelease(_values);
    [super dealloc];
}

@end
