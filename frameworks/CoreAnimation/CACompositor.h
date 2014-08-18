/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CABase.h>

// Composite means show Render Layer content to the window
@interface CACompositor : NSObject

@end

void _CACompositorInitialize();
void _CACompositorPrepareComposite();
void _CACompositorComposite();
