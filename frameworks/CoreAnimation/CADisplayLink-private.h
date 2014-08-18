/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

@interface CADisplayLink(private)

- (id)initWithTarget:(id)target selector:(SEL)sel;
- (void)displayFrame;

@end

