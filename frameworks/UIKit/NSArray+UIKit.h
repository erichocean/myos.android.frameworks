//
// Copyright 2014 myOS Group. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSMutableArray (UIKit)

- (void)moveObjectToTop:(id)anObject;
- (void)moveObject:(id)firstObject afterObject:(id)secondObject;
- (void)moveObject:(id)firstObject beforeObject:(id)secondObject;
- (void)moveObject:(id)anObject toIndex:(int)index;

@end
