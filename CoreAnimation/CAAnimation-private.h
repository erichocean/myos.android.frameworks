/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CAAnimation.h>

// Life cycle

void _CAAnimationInitialize();

// Animation

void _CAAnimationApplyAnimationForLayer(CAAnimation *theAnimation, CALayer *layer, CFTimeInterval time);

// CAAnimationGroup

CAAnimationGroup *_CAAnimationGroupNew();
CAAnimationGroup *_CAAnimationGroupGetCurrent();
void _CAAnimationGroupAddAnimation(CAAnimationGroup *animationGroup, CAAnimation *animation);
void _CAAnimationGroupRemoveAnimation(CAAnimationGroup *animationGroup, CAAnimation *animation);
void _CAAnimationGroupCommit();

// Helpers

void _CAAnimationCopy(CAAnimation *toAnimation, CAAnimation *fromAnimation);
