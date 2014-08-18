
LIB_NAME=MAOpenglSystemCommon
CFLAGS=-DDEBUG -DHAVE_PTHREADS -I$(ANDROID_SOURCE_PATH)/development/tools/emulator/opengl/host/include/libOpenglRender -I${MY_FRAMEWORKS_PATH}/libraries/MAOpenglCodecCommon -I${MY_FRAMEWORKS_PATH}/libraries/MAEGL -I${MY_FRAMEWORKS_PATH}/libraries/MARenderControl_enc

#-I$(ANDROID_SOURCE_PATH)/device/generic/goldfish/opengl/system/renderControl_enc

OBJECTS = \
    HostConnection.o \
    QemuPipeStream.o \
    ThreadInfo.o \

include ${MY_FRAMEWORKS_PATH}/resources/makefile-static
