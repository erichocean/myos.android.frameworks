
#import <string.h>
#import <stdio.h>
#import <utils/Log.h>
//#include "renderControl_opcodes.h"
#import <MARenderControl_enc/MARenderControl_enc.h>

static void enc_unsupported()
{
	LOGE("Function is unsupported\n");
}

GLint rcGetRendererVersion_enc(void *self )
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	 unsigned char *ptr;
	 const size_t packetSize = 8;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcGetRendererVersion;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;


	GLint retval;
	stream->readback(&retval, 4);
	return retval;
}

EGLint rcGetEGLVersion_enc(void *self , EGLint* major, EGLint* minor)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	const unsigned int __size_major =  sizeof(EGLint);
	const unsigned int __size_minor =  sizeof(EGLint);
	 unsigned char *ptr;
	 const size_t packetSize = 8 + __size_major + __size_minor + 2*4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcGetEGLVersion;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

	*(unsigned int *)(ptr) = __size_major; ptr += 4;
	*(unsigned int *)(ptr) = __size_minor; ptr += 4;
	stream->readback(major, __size_major);
	stream->readback(minor, __size_minor);

	EGLint retval;
	stream->readback(&retval, 4);
	return retval;
}

EGLint rcQueryEGLString_enc(void *self , EGLenum name, void* buffer, EGLint bufferSize)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	const unsigned int __size_buffer =  bufferSize;
	 unsigned char *ptr;
	 const size_t packetSize = 8 + 4 + __size_buffer + 4 + 1*4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcQueryEGLString;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

		memcpy(ptr, &name, 4); ptr += 4;
	*(unsigned int *)(ptr) = __size_buffer; ptr += 4;
		memcpy(ptr, &bufferSize, 4); ptr += 4;
	stream->readback(buffer, __size_buffer);

	EGLint retval;
	stream->readback(&retval, 4);
	return retval;
}

EGLint rcGetGLString_enc(void *self , EGLenum name, void* buffer, EGLint bufferSize)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	const unsigned int __size_buffer =  bufferSize;
	 unsigned char *ptr;
	 const size_t packetSize = 8 + 4 + __size_buffer + 4 + 1*4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcGetGLString;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

		memcpy(ptr, &name, 4); ptr += 4;
	*(unsigned int *)(ptr) = __size_buffer; ptr += 4;
		memcpy(ptr, &bufferSize, 4); ptr += 4;
	stream->readback(buffer, __size_buffer);

	EGLint retval;
	stream->readback(&retval, 4);
	return retval;
}

EGLint rcGetNumConfigs_enc(void *self , uint32_t* numAttribs)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	const unsigned int __size_numAttribs =  sizeof(uint32_t);
	 unsigned char *ptr;
	 const size_t packetSize = 8 + __size_numAttribs + 1*4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcGetNumConfigs;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

	*(unsigned int *)(ptr) = __size_numAttribs; ptr += 4;
	stream->readback(numAttribs, __size_numAttribs);

	EGLint retval;
	stream->readback(&retval, 4);
	return retval;
}

EGLint rcGetConfigs_enc(void *self , uint32_t bufSize, GLuint* buffer)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	const unsigned int __size_buffer =  bufSize;
	 unsigned char *ptr;
	 const size_t packetSize = 8 + 4 + __size_buffer + 1*4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcGetConfigs;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

		memcpy(ptr, &bufSize, 4); ptr += 4;
	*(unsigned int *)(ptr) = __size_buffer; ptr += 4;
	stream->readback(buffer, __size_buffer);

	EGLint retval;
	stream->readback(&retval, 4);
	return retval;
}

EGLint rcChooseConfig_enc(void *self , EGLint* attribs, uint32_t attribs_size, uint32_t* configs, uint32_t configs_size)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	const unsigned int __size_attribs =  attribs_size;
	const unsigned int __size_configs = ((configs != NULL) ?  configs_size*sizeof(uint32_t) : 0);
	 unsigned char *ptr;
	 const size_t packetSize = 8 + __size_attribs + 4 + __size_configs + 4 + 2*4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcChooseConfig;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

	*(unsigned int *)(ptr) = __size_attribs; ptr += 4;
	memcpy(ptr, attribs, __size_attribs);ptr += __size_attribs;
		memcpy(ptr, &attribs_size, 4); ptr += 4;
	*(unsigned int *)(ptr) = __size_configs; ptr += 4;
		memcpy(ptr, &configs_size, 4); ptr += 4;
	if (configs != NULL) stream->readback(configs, __size_configs);

	EGLint retval;
	stream->readback(&retval, 4);
	return retval;
}

EGLint rcGetFBParam_enc(void *self , EGLint param)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	 unsigned char *ptr;
	 const size_t packetSize = 8 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcGetFBParam;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

		memcpy(ptr, &param, 4); ptr += 4;

	EGLint retval;
	stream->readback(&retval, 4);
	return retval;
}

uint32_t rcCreateContext_enc(void *self , uint32_t config, uint32_t share, uint32_t glVersion)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	 unsigned char *ptr;
	 const size_t packetSize = 8 + 4 + 4 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcCreateContext;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

		memcpy(ptr, &config, 4); ptr += 4;
		memcpy(ptr, &share, 4); ptr += 4;
		memcpy(ptr, &glVersion, 4); ptr += 4;

	uint32_t retval;
	stream->readback(&retval, 4);
	return retval;
}

void rcDestroyContext_enc(void *self , uint32_t context)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	 unsigned char *ptr;
	 const size_t packetSize = 8 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcDestroyContext;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

		memcpy(ptr, &context, 4); ptr += 4;
}

uint32_t rcCreateWindowSurface_enc(void *self , uint32_t config, uint32_t width, uint32_t height)
{
    //LOGD("rcCreateWindowSurface_enc");
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    //LOGD("rcCreateWindowSurface_enc 2");
    unsigned char *ptr;
    const size_t packetSize = 8 + 4 + 4 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcCreateWindowSurface;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    //LOGD("rcCreateWindowSurface_enc 3");
    memcpy(ptr, &config, 4); ptr += 4;
    memcpy(ptr, &width, 4); ptr += 4;
    memcpy(ptr, &height, 4); ptr += 4;
    
	uint32_t retval;
	stream->readback(&retval, 4);
    LOGD("rcCreateWindowSurface_enc retval: %d", retval);
	return retval;
}

void rcDestroyWindowSurface_enc(void *self , uint32_t windowSurface)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	 unsigned char *ptr;
	 const size_t packetSize = 8 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcDestroyWindowSurface;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

		memcpy(ptr, &windowSurface, 4); ptr += 4;
}

uint32_t rcCreateColorBuffer_enc(void *self , uint32_t width, uint32_t height, GLenum internalFormat)
{
    
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    
    unsigned char *ptr;
    const size_t packetSize = 8 + 4 + 4 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcCreateColorBuffer;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    
    memcpy(ptr, &width, 4); ptr += 4;
    memcpy(ptr, &height, 4); ptr += 4;
    memcpy(ptr, &internalFormat, 4); ptr += 4;
    
	uint32_t retval;
	stream->readback(&retval, 4);
	return retval;
}

void rcOpenColorBuffer_enc(void *self , uint32_t colorbuffer)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	 unsigned char *ptr;
	 const size_t packetSize = 8 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcOpenColorBuffer;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

		memcpy(ptr, &colorbuffer, 4); ptr += 4;
}

void rcCloseColorBuffer_enc(void *self , uint32_t colorbuffer)
{

	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;

	 unsigned char *ptr;
	 const size_t packetSize = 8 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcCloseColorBuffer;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;

		memcpy(ptr, &colorbuffer, 4); ptr += 4;

	stream->flush();
}

void rcSetWindowColorBuffer_enc(void *self , uint32_t windowSurface, uint32_t colorBuffer)
{
    LOGD("rcSetWindowColorBuffer_enc 1");
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    LOGD("rcSetWindowColorBuffer_enc 2");
    unsigned char *ptr;
    const size_t packetSize = 8 + 4 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcSetWindowColorBuffer;memcpy(ptr, &tmp, 4); ptr += 4;
    LOGD("rcSetWindowColorBuffer_enc 3");
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    memcpy(ptr, &windowSurface, 4); ptr += 4;
    memcpy(ptr, &colorBuffer, 4); ptr += 4;
    LOGD("rcSetWindowColorBuffer_enc 4");
}

int rcFlushWindowColorBuffer_enc(void *self , uint32_t windowSurface)
{
    LOGD("rcFlushWindowColorBuffer_enc 1");
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    LOGE("rcFlushWindowColorBuffer_enc 2");
    unsigned char *ptr;
    const size_t packetSize = 8 + 4;
	ptr = stream->alloc(packetSize);
    LOGE("rcFlushWindowColorBuffer_enc 3");
	int tmp = OP_rcFlushWindowColorBuffer;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    memcpy(ptr, &windowSurface, 4); ptr += 4;
    LOGD("rcFlushWindowColorBuffer_enc windowSurface: %d", windowSurface);
	int retval;
	stream->readback(&retval, 4);
    LOGD("rcFlushWindowColorBuffer_enc retval: %d", retval);
	return retval;
}

EGLint rcMakeCurrent_enc(void *self , uint32_t context, uint32_t drawSurf, uint32_t readSurf)
{
    LOGD("rcMakeCurrent_enc");
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    
    unsigned char *ptr;
    const size_t packetSize = 8 + 4 + 4 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcMakeCurrent;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    memcpy(ptr, &context, 4); ptr += 4;
    memcpy(ptr, &drawSurf, 4); ptr += 4;
    memcpy(ptr, &readSurf, 4); ptr += 4;
    
	EGLint retval;
	stream->readback(&retval, 4);
	return retval;
}

void rcFBPost_enc(void *self , uint32_t colorBuffer)
{
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    
    unsigned char *ptr;
    const size_t packetSize = 8 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcFBPost;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    memcpy(ptr, &colorBuffer, 4); ptr += 4;
}

void rcFBSetSwapInterval_enc(void *self , EGLint interval)
{
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    
    unsigned char *ptr;
    const size_t packetSize = 8 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcFBSetSwapInterval;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    memcpy(ptr, &interval, 4); ptr += 4;
}

void rcBindTexture_enc(void *self , uint32_t colorBuffer)
{
    
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    
    unsigned char *ptr;
    const size_t packetSize = 8 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcBindTexture;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    memcpy(ptr, &colorBuffer, 4); ptr += 4;
}

void rcBindRenderbuffer_enc(void *self , uint32_t colorBuffer)
{
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    unsigned char *ptr;
    const size_t packetSize = 8 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcBindRenderbuffer;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    memcpy(ptr, &colorBuffer, 4); ptr += 4;
}

EGLint rcColorBufferCacheFlush_enc(void *self , uint32_t colorbuffer, EGLint postCount, int forRead)
{
    
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    
    unsigned char *ptr;
    const size_t packetSize = 8 + 4 + 4 + 4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcColorBufferCacheFlush;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    memcpy(ptr, &colorbuffer, 4); ptr += 4;
    memcpy(ptr, &postCount, 4); ptr += 4;
    memcpy(ptr, &forRead, 4); ptr += 4;
    
	EGLint retval;
	stream->readback(&retval, 4);
	return retval;
}

void rcReadColorBuffer_enc(void *self , uint32_t colorbuffer, GLint x, GLint y, GLint width, GLint height, GLenum format, GLenum type, void* pixels)
{
    
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
	const unsigned int __size_pixels =  (((glUtilsPixelBitSize(format, type) * width) >> 3) * height);
    unsigned char *ptr;
    const size_t packetSize = 8 + 4 + 4 + 4 + 4 + 4 + 4 + 4 + __size_pixels + 1*4;
	ptr = stream->alloc(packetSize);
	int tmp = OP_rcReadColorBuffer;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    memcpy(ptr, &colorbuffer, 4); ptr += 4;
    memcpy(ptr, &x, 4); ptr += 4;
    memcpy(ptr, &y, 4); ptr += 4;
    memcpy(ptr, &width, 4); ptr += 4;
    memcpy(ptr, &height, 4); ptr += 4;
    memcpy(ptr, &format, 4); ptr += 4;
    memcpy(ptr, &type, 4); ptr += 4;
	*(unsigned int *)(ptr) = __size_pixels; ptr += 4;
	stream->readback(pixels, __size_pixels);
}

int rcUpdateColorBuffer_enc(void *self , uint32_t colorbuffer, GLint x, GLint y, GLint width, GLint height, GLenum format, GLenum type, void* pixels)
{
	renderControl_encoder_context_t *ctx = (renderControl_encoder_context_t *)self;
	IOStream *stream = ctx->m_stream;
    
	const unsigned int __size_pixels =  (((glUtilsPixelBitSize(format, type) * width) >> 3) * height);
    unsigned char *ptr;
    const size_t packetSize = 8 + 4 + 4 + 4 + 4 + 4 + 4 + 4 + __size_pixels + 1*4;
	ptr = stream->alloc(8 + 4 + 4 + 4 + 4 + 4 + 4 + 4);
	int tmp = OP_rcUpdateColorBuffer;memcpy(ptr, &tmp, 4); ptr += 4;
	memcpy(ptr, &packetSize, 4);  ptr += 4;
    memcpy(ptr, &colorbuffer, 4); ptr += 4;
    memcpy(ptr, &x, 4); ptr += 4;
    memcpy(ptr, &y, 4); ptr += 4;
    memcpy(ptr, &width, 4); ptr += 4;
    memcpy(ptr, &height, 4); ptr += 4;
    memcpy(ptr, &format, 4); ptr += 4;
    memcpy(ptr, &type, 4); ptr += 4;
	stream->flush();
	stream->writeFully(&__size_pixels,4);
	stream->writeFully(pixels, __size_pixels);
    
	int retval;
	stream->readback(&retval, 4);
	return retval;
}

renderControl_encoder_context_t::renderControl_encoder_context_t(IOStream *stream)
{
	m_stream = stream;

	set_rcGetRendererVersion(rcGetRendererVersion_enc);
	set_rcGetEGLVersion(rcGetEGLVersion_enc);
	set_rcQueryEGLString(rcQueryEGLString_enc);
	set_rcGetGLString(rcGetGLString_enc);
	set_rcGetNumConfigs(rcGetNumConfigs_enc);
	set_rcGetConfigs(rcGetConfigs_enc);
	set_rcChooseConfig(rcChooseConfig_enc);
	set_rcGetFBParam(rcGetFBParam_enc);
	set_rcCreateContext(rcCreateContext_enc);
	set_rcDestroyContext(rcDestroyContext_enc);
	set_rcCreateWindowSurface(rcCreateWindowSurface_enc);
	set_rcDestroyWindowSurface(rcDestroyWindowSurface_enc);
	set_rcCreateColorBuffer(rcCreateColorBuffer_enc);
	set_rcOpenColorBuffer(rcOpenColorBuffer_enc);
	set_rcCloseColorBuffer(rcCloseColorBuffer_enc);
	set_rcSetWindowColorBuffer(rcSetWindowColorBuffer_enc);
	set_rcFlushWindowColorBuffer(rcFlushWindowColorBuffer_enc);
	set_rcMakeCurrent(rcMakeCurrent_enc);
	set_rcFBPost(rcFBPost_enc);
	set_rcFBSetSwapInterval(rcFBSetSwapInterval_enc);
	set_rcBindTexture(rcBindTexture_enc);
	set_rcBindRenderbuffer(rcBindRenderbuffer_enc);
	set_rcColorBufferCacheFlush(rcColorBufferCacheFlush_enc);
	set_rcReadColorBuffer(rcReadColorBuffer_enc);
	set_rcUpdateColorBuffer(rcUpdateColorBuffer_enc);
}
