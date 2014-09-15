/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

//#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>
#import <CoreGraphics/CGContext-private.h>
#import <rd_app_glue.h>

//@class IOWindow;

@interface IOWindow : NSObject
{
@public
    ANativeWindow *_nWindow;
    CGContextRef _context;
    CGRect _rect;
}
@end

CGContextRef IOWindowCreateContext();
void *IOWindowCreateNativeWindow(int pipeRead);
void IOWindowDestroyNativeWindow(void *nWindow);
void IOWindowSetNativeWindow(void* nWindow);
//void IOWindowInitWithRdApp(struct android_app* app);
IOWindow *IOWindowCreateSharedWindow();
IOWindow *IOWindowGetSharedWindow();
void IOWindowDestroySharedWindow();

CGContextRef IOWindowCreateContextWithRect(CGRect aRect);
CGContextRef IOWindowContext();

/*void IOWindowSetContextSize(CGSize size);
void IOWindowFlush();
void IOWindowClear();
*/
