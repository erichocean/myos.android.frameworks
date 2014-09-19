#
# Copyright 2014 myOS Group. All rights reserved.
#

CFLAGS=-DDEBUG
LDLIBS=-lCoreFoundation -lFoundation

ifeq ($(TARGET),NativeActivity)
    LIB_NAME=NACoreAnimation
    CFLAGS+=-DNA
    LDLIBS+=-lEGL -lGLESv1_CM -lNAIOKit -lNAOpenGLES -lNACoreGraphics -lNACoreText
else
    LIB_NAME=CoreAnimation
    LDLIBS+=-lIOKit -lOpenGLES -lCoreGraphics -lCoreText
endif

OBJECTS = \
    CAAnimation.o \
    CAGradientLayer.o \
    CAReplicatorLayer.o \
    CATiledLayer.o \
    CAValueFunction.o \
    CALayer.o \
    CALayer-CFunctions.o \
    CALayer+PresentationLayer.o \
    CARenderLayer.o \
    CALayerObserver.o \
    CAScrollLayer.o \
    CATransaction.o \
    CARenderer.o \
    CADisplayLink.o \
    CAMediaTiming.o \
    CAShapeLayer.o \
    CATransform3D.o \
    CAEAGLLayer.o \
    CAMediaTimingFunction.o \
    CATextLayer.o \
    CATransformLayer.o \
    CABackingStore.o \
    CAAnimator.o \
    CATransactionGroup.o \
    CACompositor.o \

include ${MYOS_PATH}/android/sdk/resources/makefile-shared
