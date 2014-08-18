/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

@interface CALayer (private)

- (void)moveLayerToTop:(CALayer *)layer;
- (CFIndex)indexOfLayer:(CALayer *)layer;

@end

