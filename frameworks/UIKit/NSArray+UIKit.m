//
// Copyright 2014 myOS Group. All rights reserved.
//

#import <UIKit/NSArray+UIKit.h>

@implementation NSMutableArray (UIKit)

- (void)moveObjectToTop:(id)anObject
{
    //DLog(@"anObject: %@", anObject);
    [anObject retain];
    [self removeObject:anObject];
    [self addObject:anObject];
    [anObject release];
}

- (void)moveObject:(id)firstObject afterObject:(id)secondObject
{
    [firstObject retain];
    [self removeObject:firstObject];
    if ([self lastObject] == secondObject) {
        [self addObject:firstObject];
    } else {
        [self insertObject:firstObject atIndex:[self indexOfObject:secondObject]+1];
    }
    [firstObject release];
}

- (void)moveObject:(id)firstObject beforeObject:(id)secondObject
{
    [firstObject retain];
    [self removeObject:firstObject];
    [self insertObject:firstObject atIndex:[self indexOfObject:secondObject]];
    [firstObject release];
}

- (void)moveObject:(id)anObject toIndex:(int)index
{
    [anObject retain];
    [self removeObject:anObject];
    [self insertObject:anObject atIndex:index];
    [anObject release];
}

@end
