/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CABase.h>

extern NSString *const kCATransactionAnimationDuration;
extern NSString *const kCATransactionAnimationTimingFunction;
extern NSString *const kCATransactionDisableActions;
extern NSString *const kCATransactionCompletionBlock;

@class CAMediaTimingFunction;

@interface CATransaction : NSObject 

+ (CFTimeInterval)animationDuration;
+ (void)setAnimationDuration:(CFTimeInterval)dur;
+ (CAMediaTimingFunction *)animationTimingFunction;
+ (void)setAnimationTimingFunction:(CAMediaTimingFunction *)function;
+ (BOOL)disableActions;
+ (void)setDisableActions:(BOOL)flag;
+ (id)valueForKey:(NSString *)key;
+ (void)setValue:(id)value forKey:(NSString *)key;

+ (void)begin;
+ (void)commit;
+ (void)flush;
+ (void)lock;
+ (void)unlock;

@end

