/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CABase.h>

typedef enum {
    _CAAnimatorConditionLockStartup,
    _CAAnimatorConditionLockHasNoWork,
    _CAAnimatorConditionLockHasWork
} _CAAnimatorConditionLockTypes;

extern NSConditionLock *_CAAnimatorConditionLock;
#ifdef NA
extern NSConditionLock *_CAAnimatorNAConditionLock;
#endif
extern BOOL _CAAnimatorCaptureScreen;
extern CGImageRef _CAAnimatorScreenCapture;

@interface CAAnimator : NSObject

+ (void)run;
+ (void)display;

@end

void _CAAnimatorInitialize();
