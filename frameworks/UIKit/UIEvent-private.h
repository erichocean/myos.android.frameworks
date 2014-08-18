/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <UIKit/UIEvent.h>

#define _kUIEventTimeDiffMax	0.27

@interface UIEvent (private)
- (id)initWithEventType:(UIEventType)type;
@end

void _UIEventSetTouch(UIEvent* event, UITouch* touch);
void _UIEventSetTimestamp(UIEvent* event, NSTimeInterval timestamp);
//void _UIEventSetUnhandledKeyPressEvent(UIEvent* event);
//BOOL _UIEventIsUnhandledKeyPressEvent(UIEvent* event);
