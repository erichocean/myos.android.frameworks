/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CoreAnimation.h>

extern NSString *const kCAScrollNone;
extern NSString *const kCAScrollVertically;
extern NSString *const kCAScrollHorizontally;
extern NSString *const kCAScrollBoth;

@interface CAScrollLayer : CALayer {
@package
	NSString *scrollMode;
}

@property (copy) NSString *scrollMode;

- (void)scrollToPoint:(CGPoint)point;
- (void)scrollToRect:(CGRect)rect;

@end

@interface CALayer (CALayerScrolling)

- (void)scrollPoint:(CGPoint)point;
- (void)scrollRectToVisible:(CGRect)rect;
- (CGRect)visibleRect;

@end
