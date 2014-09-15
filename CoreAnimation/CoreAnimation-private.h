/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CoreAnimation.h>

#import <CoreAnimation/CAGradientLayer-private.h>
#import <CoreAnimation/CALayer-CFunctions.h>
#import <CoreAnimation/CALayer-private.h>
#import <CoreAnimation/CALayer+PresentationLayer.h>
#import <CoreAnimation/CALayerObserver.h>
#import <CoreAnimation/CARenderLayer.h>
#import <CoreAnimation/CATransaction-private.h>
#import <CoreAnimation/CARenderer-private.h>
#import <CoreAnimation/CACompositor.h>
#import <CoreAnimation/CAAnimator.h>
#import <CoreAnimation/CAAnimation-private.h>
#import <CoreAnimation/CATransactionGroup.h>
#import <CoreAnimation/CAMediaTimingFunction-private.h>
#import <CoreAnimation/CABackingStore.h>
#import <CoreAnimation/CADisplayLink-private.h>

#define _kSmallValue    0.0001
