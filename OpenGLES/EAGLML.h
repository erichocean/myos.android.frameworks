/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

typedef enum {
    EAGLMLMessageEndOfMessage,
    EAGLMLMessageChildIsReady,
    EAGLMLMessageGenTexture,
    EAGLMLMessageLoadImage,
    EAGLMLMessageDraw,
    EAGLMLMessageSwapBuffers,
    EAGLMLMessageDeleteTexture,
} EAGLMLMessage;

//extern NSLock *_EAGLMLLock;
//extern BOOL _EAGLMLCanDraw;

void EAGLMLSetChildAppIsRunning(BOOL isRunning);
void EAGLMLHandleMessages();
void EAGLMLSetPipes(int pipeRead, int pipeWrite);
void EAGLMLGenTexture();
void EAGLMLLoadImage();
void EAGLMLDraw();
void EAGLMLDeleteTexture();
