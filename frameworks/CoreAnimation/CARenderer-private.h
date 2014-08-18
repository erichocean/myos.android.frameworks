/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CARenderer.h>

extern CFMutableSetRef _needsDisplayLayers;
extern CFMutableSetRef _needsDisplayPresentationLayers;

void _CARendererInitialize();
void _CARendererDisplayLayers(BOOL isModelLayer);
void _CARendererLoadRenderLayers();
