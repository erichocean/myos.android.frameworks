/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <UIKit/UIControl.h>

typedef enum {
    UIIconControlTypeClose,
    UIIconControlTypeDelete,
    UIIconControlTypeMenu,
    UIIconControlTypeAnchor,
} UIIconControlType;

#define _kIconControlSize       17

@interface UIIconControl : UIControl {
@package
    UIIconControlType _type;
    UIApplicationIcon *_applicationIcon;
} 

- (id)initWithFrame:(CGRect)frame andType:(UIIconControlType)type;

@end
