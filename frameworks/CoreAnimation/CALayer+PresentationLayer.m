/*
 * Copyright 2014 myOS Group. All rights reserved.
 *
 */

#import <CoreAnimation/CoreAnimation-private.h>
#import <CoreFoundation/CFArray-private.h>
#import <CoreGraphics/CoreGraphics-private.h>

// Presentation Layer is a node in the Presentation Tree
@implementation CALayer (PresentationLayer)

#pragma mark - Life cycle

- (id)initWithModelLayer:(CALayer *)layer
{
    self = [self initWithLayer:layer];
    if (self) {
        _needsComposite = NO;
        _modelLayer = layer;
        //_modelLayer->_presentationLayer = self;
        //_renderLayer = nil;
        _CALayerCopyAnimations(self);
    }
    return self;
}

@end

#pragma mark - Shared functions

#pragma mark - CALayer

void _CALayerRemoveFromSuperlayer(CALayer *layer)
{
    if (layer->_superlayer) {
        _CFArrayRemoveValue(layer->_superlayer->_sublayers, layer);
        layer->_superlayer = nil;
    }
}

void _CALayerAddSublayer(CALayer *layer, CALayer *sublayer, CFIndex index)
{
    _CALayerRemoveFromSuperlayer(sublayer);

    if (index >= CFArrayGetCount(layer->_sublayers)) {
        CFArrayAppendValue(layer->_sublayers, sublayer);
    } else {
        CFArrayInsertValueAtIndex(layer->_sublayers, index, sublayer);
    }
    sublayer->_superlayer = layer;
}

void _CALayerCopyAnimations(CALayer *layer)
{
    //DLog();
    if ([layer->_modelLayer->_animations count]) {
        //DLog(@"");
        if (layer->_animations) {
            [layer->_animations release];
        }
        layer->_animations = [[NSMutableDictionary alloc] initWithDictionary:layer->_modelLayer->_animations];
        //CFArrayRef keys = [layer animationKeys];
        //DLog(@"layer->_animations: %@", layer->_animations);
        for (NSString *key in [layer animationKeys]) {
            //DLog(@"key: %@", key);
            CAAnimation *theAnimation = [layer animationForKey:key];
            if ([theAnimation isKindOfClass:[CABasicAnimation class]]) {
                CABasicAnimation *animation = (CABasicAnimation *)theAnimation;
                if (!animation->toValue) {
                    animation.toValue = [layer->_modelLayer valueForKeyPath:animation->keyPath];
                }
            } else if ([theAnimation isKindOfClass:[CAKeyframeAnimation class]]) {
                //DLog(@"[theAnimation isKindOfClass:[CAKeyframeAnimation class]]");
            }
        }
        //DLog(@"_animations: %@", layer->_animations);
    }
}

void _CALayerApplyAnimations(CALayer *layer)
{
    //DLog(@"layer: %@", layer);
    if ([layer->_animations count]) {
        CFTimeInterval time = [layer convertTime:CACurrentMediaTime() fromLayer:nil];
        //DLog(@"layer->_animations: %@", layer->_animations);
        CFArrayRef keys = [layer animationKeys];
        //DLog(@"keys: %@", keys);
        for (NSString *key in keys) {
            // Adjust animation begin time
            CAAnimation *animation = [layer animationForKey:key];
            _CAAnimationApplyAnimationForLayer(animation, layer, time);
        }
    }
}

