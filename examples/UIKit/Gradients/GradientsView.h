/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>

@interface GradientsView : UIView
{
    CAGradientLayer *gradientLayer;
    NSTimer *timer;
}

@property (nonatomic, retain) CAGradientLayer *gradientLayer;
@property (nonatomic, assign) NSTimer *timer;

@end

