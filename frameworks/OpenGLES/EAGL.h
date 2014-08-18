/*
 * Copyright 2014 myOS Group. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <EGL/egl.h>

#define EAGL_MAJOR_VERSION      1
#define EAGL_MINOR_VERSION      0

typedef enum {
    kEAGLRenderingAPIOpenGLES1 = 1,
    kEAGLRenderingAPIOpenGLES2,
} EAGLRenderingAPI;

extern void EAGLGetVersion(unsigned int *major, unsigned int *minor);

@interface EAGLSharegroup : NSObject

@end

@class IOWindow;

@interface EAGLContext : NSObject
{
@public
    EAGLRenderingAPI API;
    EAGLSharegroup *_sharegroup;
    //Display *_display;
    IOWindow *_window;
    EGLDisplay _eglDisplay;
    EGLConfig _eglFBConfig[1];
    EGLSurface _eglSurface;
    EGLContext _eglContext;
    int _width;
    int _height;
    BOOL _vSyncEnabled;
}

@property (readonly) EAGLRenderingAPI API;
@property (readonly) EAGLSharegroup *sharegroup;

- (id)initWithAPI:(EAGLRenderingAPI)api;
- (id)initWithAPI:(EAGLRenderingAPI)api sharegroup:(EAGLSharegroup *)aSharegroup;

+ (BOOL)setCurrentContext:(EAGLContext *)context;
+ (EAGLContext *)currentContext;

@end
