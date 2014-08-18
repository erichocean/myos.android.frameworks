/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <UIKit/UIApplication-private.h>

void android_main(struct android_app *state)
{
    app_dummy();
    _UIApplicationMain(state, @"AnimationGradients", @"AppDelegate");
}
