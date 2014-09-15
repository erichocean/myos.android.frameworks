/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CABase.h>

@interface CADisplayLink : NSObject {
@package
    CFTimeInterval _timestamp;
    CFTimeInterval _duration;
    BOOL _paused;
    NSInteger _frameInterval;
    id _target;
    SEL _selector;
    NSTimer *_timer;
}

@property (nonatomic, readonly) CFTimeInterval timestamp;
@property (nonatomic, readonly) CFTimeInterval duration;
@property (nonatomic, getter=isPaused) BOOL paused;
@property (nonatomic) NSInteger frameInterval;

+ (CADisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)sel;

- (void)invalidate;

@end
