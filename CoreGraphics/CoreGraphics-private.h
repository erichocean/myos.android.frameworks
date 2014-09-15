/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreGraphics/CoreGraphics.h>
#import <CoreGraphics/CairoFontX11-private.h>
#import <CoreGraphics/StandardGlyphNames.h>
#import <CoreGraphics/CGColorSpace-private.h>
#import <CoreGraphics/CGDataProvider-private.h>
#import <CoreGraphics/CGImageDestination-private.h>
#import <CoreGraphics/CGBitmapContext-private.h>
#import <CoreGraphics/CGContext-private.h>
#import <CoreGraphics/CGFont-private.h>
#import <CoreGraphics/CGImageSource-private.h>
#import <CoreGraphics/CGColor-private.h>
#import <CoreGraphics/CGDataConsumer-private.h>
#import <CoreGraphics/CGGradient-private.h>
#import <CoreGraphics/CGGeometry-private.h>
#import <CoreGraphics/CGImage-private.h>
#import <rd_app_glue.h>
#import <cairo/cairo.h>

void _CoreGraphicsInitialize(struct android_app *app);

extern struct android_app *_app;
