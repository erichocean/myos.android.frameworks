/*
 * Copyright 2014 myOS Group. All rights reserved.
 */

#import <OpenGLES/EAGL.h>
#import <GLES/gl.h>
#import <OpenGLES/EAGLTexture.h>
//#ifdef NA
    #import <OpenGLES/EAGLML.h>
//#else
    #import <OpenGLES/EAGLMA.h>
//#endif

extern BOOL _EAGLSwappingBuffers;

EAGLContext *_EAGLGetCurrentContext();
void _EAGLSetup();
void _EAGLSetSwapInterval(int interval);
void _EAGLClear();
void _EAGLFlush();
void _EAGLSwapBuffers();
NSTimeInterval EAGLCurrentTime();
