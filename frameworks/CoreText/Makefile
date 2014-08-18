
LIB_NAME=CoreText
CFLAGS=-DDEBUG
LDLIBS= -lCoreFoundation -lFoundation

ifeq ($(TARGET),NativeActivity)
    LIB_NAME=NACoreText
    CFLAGS+=-DNA
    LDLIBS+=-lNACoreGraphics
else
    LIB_NAME=CoreText
    LDLIBS+=-lCoreGraphics
endif

OBJECTS = \
	CTFontCollection.o \
	CTFontDescriptor.o \
	CTFont.o \
	CTFontTraits.o \
	CTFrame.o \
	CTFramesetter.o \
	CTGlyphInfo.o \
	CTLine.o \
	CTNSFontconfigFontDescriptor.o \
	CTNSFontDescriptor.o \
	CTNSFont.o \
	CTParagraphStyle.o \
	CTRun.o \
	CTStringAttributes.o \
	CTTextTab.o \
	CTTypesetter.o \
	OPSimpleLayoutEngine.o \

include ${MY_FRAMEWORKS_PATH}/resources/makefile-shared
