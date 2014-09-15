/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <OpenGLES/EAGL-private.h>
#import <IOKit/IOKit.h>
#import <CoreAnimation/CoreAnimation.h>

#define _kTimeoutLimit 5.0

#pragma mark - Shared functions

int EAGLMAGenTexture()
{
    //DLog();
    IOPipeWriteMessageWithPipe(EAGLMLMessageGenTexture, YES, _kEAGLMAPipeWrite);
    NSTimeInterval startTime = EAGLCurrentTime();
    int message;
    while (YES) {
        usleep(1000);
        message = IOPipeReadMessageWithPipe(_kEAGLMAPipeRead);
        switch (message) {
            case EAGLMAMessageEndOfMessage: {
                //DLog(@"MAPipeMessageEndOfMessage");
                break;
            }
            case EAGLMAMessageGenTexture:
                //DLog(@"EAGLMAMessageGenTexture");
                return IOPipeReadIntWithPipe(_kEAGLMAPipeRead);
            default:
                DLog(@"message: %d", message);
                break;
                //return -1;
        }
        if (EAGLCurrentTime() - startTime > _kTimeoutLimit) {
            DLog(@"EAGLCurrentTime() - startTime > _kTimeoutLimit");
            return 0;
        }
    }
}

void EAGLMALoadImage(int textureID, int width, int height, const GLvoid *pixels)
{
    //DLog(@"pixels: %p", pixels);
    IOPipeWriteMessageWithPipe(EAGLMLMessageLoadImage, NO, _kEAGLMAPipeWrite);
    IOPipeWriteIntWithPipe(textureID, _kEAGLMAPipeWrite);
    IOPipeWriteIntWithPipe(width, _kEAGLMAPipeWrite);
    IOPipeWriteIntWithPipe(height, _kEAGLMAPipeWrite);
    IOPipeWriteDataWithPipe(pixels, width*height*4, _kEAGLMAPipeWrite);
}

void EAGLMADraw(int textureID, const GLvoid *texCoords, const GLvoid *vertices, GLfloat opacity)
{
    //DLog();
    IOPipeWriteMessageWithPipe(EAGLMLMessageDraw, NO, _kEAGLMAPipeWrite);
    IOPipeWriteIntWithPipe(textureID, _kEAGLMAPipeWrite);
    IOPipeWriteDataWithPipe(texCoords, sizeof(GLfloat)*8, _kEAGLMAPipeWrite);
    IOPipeWriteDataWithPipe(vertices, sizeof(GLfloat)*8, _kEAGLMAPipeWrite);
    IOPipeWriteFloatWithPipe(opacity, _kEAGLMAPipeWrite);
    //DLog(@"opacity: %f", opacity);
}

void EAGLMASwapBuffers()
{
    //DLog();
    IOPipeWriteMessageWithPipe(EAGLMLMessageSwapBuffers, YES, _kEAGLMAPipeWrite);
}

void EAGLMADeleteTexture()
{
    DLog();
}
