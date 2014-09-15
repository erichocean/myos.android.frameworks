/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreGraphics/CoreGraphics.h>
#import <GLES/gl.h>

@interface EAGLTexture : NSObject
{
@public
    int _numberOfTextures;
    GLuint *_textureIDs;
}

@end

void _EAGLTextureLoad(EAGLTexture *texture, NSArray *images);
void _EAGLTextureUnload(EAGLTexture *texture);
BOOL _EAGLTextureUnloaded(EAGLTexture *texture);
