
CFLAGS=-DDEBUG -DRD
LDLIBS=-landroid -lCoreFoundation -lFoundation -lcairo -lpng -llcms -lpixman -lz -lfontconfig -lexpat -lfreetype -llog

ifeq ($(TARGET),NativeActivity)
    LIB_NAME=NACoreGraphics
    CFLAGS+=-DNA
else
    LIB_NAME=CoreGraphics
endif

OBJECTS = \
    CGAffineTransform.o \
    CGBitmapContext.o \
    CGColor.o \
    CGColorSpace.o \
    CGContext.o \
    CGDataConsumer.o \
    CGDataProvider.o \
    CGEvent.o \
    CGFont.o \
    CGFunction.o \
    CGGeometry.o \
    CGGradient.o \
    CGImage.o \
    CGImageDestination.o \
    CGImageSource.o \
    CGLayer.o \
    CGPDFArray.o \
    CGPDFContentStream.o \
    CGPDFContext.o \
    CGPDFDictionary.o \
    CGPDFDocument.o \
    CGPDFObject.o \
    CGPDFOperatorTable.o \
    CGPDFPage.o \
    CGPDFScanner.o \
    CGPDFStream.o \
    CGPDFString.o \
    CGPSConverter.o \
    CGPath.o \
    CGPattern.o \
    CGShading.o \
    CairoFont.o \
    OPColorSpaceIndexed.o \
    OPColorSpaceLCMS.o \
    OPColorTransformLCMS.o \
    OPImageConversion.o \
    OPPath.o \
    OPPostScriptContext.o \
    OPPremultiplyAlpha.o \
    OPSVGContext.o \
    StandardGlyphNames.o \
    CairoFontX11.o \
    CoreGraphics.o \

include ${MYOS_PATH}/android/sdk/resources/makefile-shared
