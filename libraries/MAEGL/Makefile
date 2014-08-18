#
# Copyright 2014 myOS Group. All rights reserved.
#

LIB_NAME=MAEGL
CFLAGS=-DDEBUG -I$(ANDROID_SOURCE_PATH)/device/generic/goldfish/opengl/system -I$(ANDROID_SOURCE_PATH)/development/tools/emulator/opengl/host/include/libOpenglRender -I${MY_FRAMEWORKS_PATH}/libraries/MAOpenglCodecCommon -I${MY_FRAMEWORKS_PATH}/libraries/MARenderControl_enc

#LDLIBS= -llog -lGLESv1_CM -lEGL_emulation -landroid -lOpenglSystemCommon -l_renderControl_enc
#LDFLAGS=-v -Wl,--no-undefined
OBJECTS = \
    ClientAPIExts.o \
    egl.o \
    eglDisplay.o \
    eglContext.o \

include ${MY_FRAMEWORKS_PATH}/resources/makefile-static
