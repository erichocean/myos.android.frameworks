#
# Copyright 2014 myOS Group. All rights reserved.
#

CFLAGS=-DDEBUG
LDLIBS=-llog -landroid -lCoreFoundation -lFoundation
OBJECTS=NSFileHandle+IOKit.o IOWindow.o IOPipe.o
ifeq ($(TARGET),NativeActivity)
    LIB_NAME=NAIOKit
    CFLAGS+=-DNA
    LDLIBS+=-lNACoreGraphics
else
    LIB_NAME=IOKit
    LDLIBS+=-lCoreGraphics
    SLIBS=MAKit
endif
include ${MYOS_PATH}/android/sdk/resources/makefile-shared
