/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <GLES/gl.h>

typedef enum {
    EAGLMAMessageEndOfMessage,
    EAGLMAMessageGenTexture,
} EAGLMAMessage;

#define _kEAGLMAPipeRead   110
#define _kEAGLMAPipeWrite  121

#ifdef __cplusplus
extern "C" {
#endif
    //void EAGLMAHandleMessages();
    //void EAGLMASetPipes(int pipeRead, int pipeWrite);
    int EAGLMAGenTexture();
    void EAGLMALoadImage(int textureID, int width, int height, const GLvoid *pixels);
    void EAGLMADraw(int textureID, const GLvoid *texCoords, const GLvoid *vertices, GLfloat opacity);
    void EAGLMASwapBuffers();
    void EAGLMADeleteTexture();
#ifdef __cplusplus
}
#endif
