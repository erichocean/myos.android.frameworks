/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CABase.h>

@class EAGLTexture;

@interface CABackingStore : NSObject {
@package
    EAGLTexture *_texture;
}

@end

void _CABackingStoreLoad(CABackingStore *backingStore, NSArray *images);
void _CABackingStoreUnload(CABackingStore *backingStore);
BOOL _CABackingStoreUnloaded(CABackingStore *backingStore);
