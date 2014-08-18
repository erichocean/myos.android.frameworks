/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <IOKit/IOKit.h>
#import <OpenGLES/EAGL-private.h>

NSLock *_EAGLMLLock = nil;
BOOL _EAGLMLCanDraw = YES;

static int _pipeRead;
static int _pipeWrite;
static BOOL _childAppRunning = NO;

#pragma mark - Shared functions

void EAGLMLSetChildAppIsRunning(BOOL isRunning)
{
    //DLog();
    //_startTime = CACurrentMediaTime();
    //DLog(@"_startTime: %f", _startTime);
    _childAppRunning = isRunning;
}

void EAGLMLSetPipes(int pipeRead, int pipeWrite)
{
    //DLog(@"pipeRead: %d, pipeWrite: %d", pipeRead, pipeWrite);
    _pipeRead = pipeRead;
    _pipeWrite = pipeWrite;
}

void EAGLMLHandleMessages()
{
    //DLog();
    if (!_childAppRunning) {
        return;
    }
    //DLog();
#ifdef NA
    int message = IOPipeReadMessageWithPipe(_pipeRead);
    switch (message) {
        case EAGLMLMessageEndOfMessage:
            //DLog(@"EAGLMLMessageEndOfMessage");
            break;
        case EAGLMLMessageChildIsReady:
            DLog(@"EAGLMLMessageChildIsReady");
            break;
        case EAGLMLMessageGenTexture:
            //DLog(@"EAGLMLMessageGenTexture");
            EAGLMLGenTexture();
            break;
        case EAGLMLMessageLoadImage:
            //DLog(@"EAGLMLMessageLoadImage");
            EAGLMLLoadImage();
            break;
        case EAGLMLMessageDraw:
            //DLog(@"EAGLMLMessageDraw");
            EAGLMLDraw();
            break;
        case EAGLMLMessageSwapBuffers:
            //DLog(@"EAGLMLMessageSwapBuffers");
            _EAGLSwapBuffers();
            break;
        default:
            break;
    }
#endif
}

void EAGLMLGenTexture()
{
    //DLog();
    GLuint textureID;
    glGenTextures(1, &textureID);
    //DLog(@"textureID: %d", textureID);
    IOPipeWriteMessageWithPipe(EAGLMAMessageGenTexture, NO, _pipeWrite);
    IOPipeWriteIntWithPipe(textureID, _pipeWrite);
    IOPipeWriteMessageWithPipe(EAGLMAMessageEndOfMessage, NO, _pipeWrite);
}

void EAGLMLLoadImage()
{
    //DLog();
    //CATransactionGroup *group = [[CATransactionGroup alloc] init];
    //CFArrayAppendValue(_transactions, group);
    int textureID = IOPipeReadIntWithPipe(_pipeRead);
    glBindTexture(GL_TEXTURE_2D, textureID);
    int width = IOPipeReadIntWithPipe(_pipeRead);
    int height = IOPipeReadIntWithPipe(_pipeRead);
    int size = width*height*4;
    //DLog(@"width: %d, height: %d", width, height);
    void *pixels = malloc(size);
    IOPipeReadDataWithPipe(pixels, size, _pipeRead);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid *)pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //DLog(@"glGetError: %d", glGetError());
    free(pixels);
}

void EAGLMLDraw()
{
    //DLog();
    //[_EAGLMLLock lock];
    //DLog(@"_EAGLMLLock: %@", _EAGLMLLock);
    //if (!_EAGLMLCanDraw) {
        //return;
    //}

    int i;
    int textureID = IOPipeReadIntWithPipe(_pipeRead);
    glBindTexture(GL_TEXTURE_2D, textureID);
    //DLog(@"_width: %d, _height: %d", _width, _height);
    
    EAGLContext *context = _EAGLGetCurrentContext();
    //DLog(@"context->_width: %d, context->_height: %d", context->_width, context->_height);
    glViewport(0, 0, context->_width, context->_height);
    
    //glViewport(0, 0, _width, _height);
    int size = sizeof(GLfloat)*8;
    //DLog(@"size: %d", size);

    GLfloat texCoords[] = {
        0, 1,
        1, 1,
        0, 0,
        1, 0
    };
    IOPipeReadDataWithPipe(texCoords, size, _pipeRead);
    GLfloat vertices[] = {
        -1, 1,
        1, 1,
        -1, -1,
        1, -1
    };
    IOPipeReadDataWithPipe(vertices, size, _pipeRead);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    //DLog(@"vertices: %p", vertices);
    glVertexPointer(2, GL_FLOAT, 0, vertices);
    float opacity = IOPipeReadFloatWithPipe(_pipeRead);
    //DLog(@"opacity: %0.1f", opacity);
    glColor4f(opacity, opacity, opacity, opacity);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //DLog();
    //[_EAGLMLLock unlock];
}

void EAGLMLDeleteTexture()
{
    DLog();
}
