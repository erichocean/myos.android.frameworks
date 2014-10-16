/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>

typedef enum {
    UIApplicationIconModeNormal,
    UIApplicationIconModeClose,
    UIApplicationIconModeDelete
} UIApplicationIconMode;

@class UIMAApplication; 
@class UIIconControl;

@interface UIApplicationIcon : UIView {
@package
    UIImageView *_iconImage;
    UIMAApplication *_application;
    UILabel *_iconLabel;
    //UIIconControl *_closeControl;
    //UIIconControl *_deleteControl;
    //UIIconControl *_menuControl;
    //UIIconControl *_anchorControl;
    UIApplicationIconMode _mode;
    UIScrollView *_parentScrollView;
    UITapGestureRecognizer *_singleTap;
    UILongPressGestureRecognizer *_longPress;
}

@property (nonatomic, assign) UIScrollView *parentScrollView;

- (id)initWithApplication:(UIMAApplication *)application;

@end
