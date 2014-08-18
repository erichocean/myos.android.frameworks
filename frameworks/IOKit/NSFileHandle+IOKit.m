/*
 * Copyright (c) 2012-2013. All rights reserved.
 *
 */

#import <IOKit/IOKit.h>

#pragma mark - Shared functions

NSString *_NSFileHandleReadLine(int file)
{
    NSMutableString *result = [[NSMutableString alloc] init];
    char aChar;
    DLog();
    while (read(file, &aChar , 1)) {
        //DLog(@"%c", aChar);
        if (aChar == '\n') {
            break;
        }
        [result appendFormat:@"%c", aChar];
    }
    return [result autorelease];
}