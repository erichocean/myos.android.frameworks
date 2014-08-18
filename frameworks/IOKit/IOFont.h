/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreGraphics/CGFont-private.h>
#import <cairo/cairo.h>

@class CGFont;

@interface IOFont : CGFont
{
@public
    cairo_scaled_font_t *cairofont;
}
@end
