/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import "CATransaction.h"
#import "CATransactionGroup.h"

extern BOOL _layersNeedLayout;

void _CATransactionInitialize();
void _CATransactionAddToRemoveLayers(CALayer *layer);
void _CATransactionCreateImplicitTransactionIfNeeded();
