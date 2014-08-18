/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CABase.h>

void _CALayerObserverInitialize();

@interface CALayerObserver : NSObject

@end

CALayerObserver *_CALayerObserverGetSharedObserver();

