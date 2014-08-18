
LIB_NAME=MAGLESv1_enc
CFLAGS=-DDEBUG -I$(ANDROID_SOURCE_PATH)/development/tools/emulator/opengl/host/include/libOpenglRender -I${MY_FRAMEWORKS_PATH}/libraries/MAOpenglCodecCommon

# -I${MY_FRAMEWORKS_PATH}/libraries/MARenderControl_enc -I$(ANDROID_SOURCE_PATH)/device/generic/goldfish/opengl/system

OBJECTS = \
    GLEncoder.o \
    gl_entry.o \
    GLEncoderUtils.o \
    gl_enc.o \

include ${MY_FRAMEWORKS_PATH}/resources/makefile-static
