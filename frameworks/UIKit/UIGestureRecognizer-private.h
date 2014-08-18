/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <UIKit/UIGestureRecognizer.h>

void _UIGestureRecognizerSetView(UIGestureRecognizer *gr, UIView *v);
void _UIGestureRecognizerRecognizeTouches(UIGestureRecognizer *recognizer, NSSet *touches, UIEvent *event);
void _UIGestureRecognizerPerformActions(UIGestureRecognizer *recognizer);

@interface UIGestureRecognizer()

@property (nonatomic,readwrite) UIGestureRecognizerState state;

- (void)_changeStatus;
- (void)ignoreTouch:(UITouch *)touch forEvent:(UIEvent *)event;		// don't override

// override, but be sure to call super
- (void)reset;
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

@end