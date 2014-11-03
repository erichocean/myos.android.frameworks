/*
 Copyright © 2014 myOS Group
 
 This file is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2 of the License, or (at your option) any later version.
 
 This file is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 Contributor(s):
 Amr Aboelela <amraboelela@gmail.com>
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
    UIApplicationIconMode _mode;
    UIScrollView *_parentScrollView;
    UITapGestureRecognizer *_singleTap;
    UILongPressGestureRecognizer *_longPress;
}

@property (nonatomic, assign) UIScrollView *parentScrollView;

- (id)initWithApplication:(UIMAApplication *)application;

@end
