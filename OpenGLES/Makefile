#
# Copyright 2014 myOS Group. All rights reserved.
#

CFLAGS=-DDEBUG -I$(ANDROID_SOURCE_PATH)/development/tools/emulator/opengl/host/include/libOpenglRender
LDLIBS=-llog -landroid -lCoreFoundation -lFoundation
OBJECTS=EAGL.o EAGLTexture.o
ifeq ($(TARGET),NativeActivity)
    LIB_NAME=NAOpenGLES
    CFLAGS+=-DNA
    LDLIBS+=-lEGL -lGLESv1_CM -lGLESv1_enc -lNAIOKit -lNACoreGraphics
    OBJECTS+=EAGLML.o
else
    LIB_NAME=OpenGLES
    LDLIBS+=-lIOKit -lCoreGraphics
    #-lcutils -lutils
    OBJECTS+=EAGLMA.o
    SLIBS=MAEGL MAGLESv1_enc
    
    #MAEGL MAOpenglSystemCommon MARenderControl_enc MAGLESv1_enc MAOpenglCodecCommon
endif
include ${MYOS_PATH}/android/sdk/resources/makefile-shared
