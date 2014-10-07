/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CoreAnimation-private.h>

@implementation CABackingStore

#pragma mark - Life cycle

- (id)init
{
    self = [super init];
    if (self) {
        _texture = [[EAGLTexture alloc] init];
    }
    return self;
}

- (void)dealloc
{
    [_texture release];
    [super dealloc];
}

@end

#pragma mark - Shared functions

void _CABackingStoreLoad(CABackingStore *backingStore, NSArray *images)
{
    //DLog();
    _EAGLTextureLoad(backingStore->_texture, images);
    //DLog(@"backingStore->_texture: %@", backingStore->_texture);
}

void _CABackingStoreUnload(CABackingStore *backingStore)
{
    //DLog();
    _EAGLTextureUnload(backingStore->_texture);
}

BOOL _CABackingStoreUnloaded(CABackingStore *backingStore)
{
    return _EAGLTextureUnloaded(backingStore->_texture);
}
