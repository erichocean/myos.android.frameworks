/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <UIKit/UIControl.h>

//void _UIControlStateDidChange(UIControl* control);

@interface UIControl ()

- (void)_sendActionsForControlEvents:(UIControlEvents)controlEvents withEvent:(UIEvent *)event;

@end
