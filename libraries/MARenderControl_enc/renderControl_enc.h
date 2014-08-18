

#ifndef GUARD_renderControl_encoder_context_t
#define GUARD_renderControl_encoder_context_t

#include "IOStream.h"
#include "renderControl_client_context.h"


#include <stdint.h>
#include <EGL/egl.h>
#include "glUtils.h"

struct renderControl_encoder_context_t : public renderControl_client_context_t {

	IOStream *m_stream;

	renderControl_encoder_context_t(IOStream *stream);


};

extern "C" {
	GLint rcGetRendererVersion_enc(void *self );
	EGLint rcGetEGLVersion_enc(void *self , EGLint* major, EGLint* minor);
	EGLint rcQueryEGLString_enc(void *self , EGLenum name, void* buffer, EGLint bufferSize);
	EGLint rcGetGLString_enc(void *self , EGLenum name, void* buffer, EGLint bufferSize);
	EGLint rcGetNumConfigs_enc(void *self , uint32_t* numAttribs);
	EGLint rcGetConfigs_enc(void *self , uint32_t bufSize, GLuint* buffer);
	EGLint rcChooseConfig_enc(void *self , EGLint* attribs, uint32_t attribs_size, uint32_t* configs, uint32_t configs_size);
	EGLint rcGetFBParam_enc(void *self , EGLint param);
	uint32_t rcCreateContext_enc(void *self , uint32_t config, uint32_t share, uint32_t glVersion);
	void rcDestroyContext_enc(void *self , uint32_t context);
	uint32_t rcCreateWindowSurface_enc(void *self , uint32_t config, uint32_t width, uint32_t height);
	void rcDestroyWindowSurface_enc(void *self , uint32_t windowSurface);
	uint32_t rcCreateColorBuffer_enc(void *self , uint32_t width, uint32_t height, GLenum internalFormat);
	void rcOpenColorBuffer_enc(void *self , uint32_t colorbuffer);
	void rcCloseColorBuffer_enc(void *self , uint32_t colorbuffer);
	void rcSetWindowColorBuffer_enc(void *self , uint32_t windowSurface, uint32_t colorBuffer);
	int rcFlushWindowColorBuffer_enc(void *self , uint32_t windowSurface);
	EGLint rcMakeCurrent_enc(void *self , uint32_t context, uint32_t drawSurf, uint32_t readSurf);
	void rcFBPost_enc(void *self , uint32_t colorBuffer);
	void rcFBSetSwapInterval_enc(void *self , EGLint interval);
	void rcBindTexture_enc(void *self , uint32_t colorBuffer);
	void rcBindRenderbuffer_enc(void *self , uint32_t colorBuffer);
	EGLint rcColorBufferCacheFlush_enc(void *self , uint32_t colorbuffer, EGLint postCount, int forRead);
	void rcReadColorBuffer_enc(void *self , uint32_t colorbuffer, GLint x, GLint y, GLint width, GLint height, GLenum format, GLenum type, void* pixels);
	int rcUpdateColorBuffer_enc(void *self , uint32_t colorbuffer, GLint x, GLint y, GLint width, GLint height, GLenum format, GLenum type, void* pixels);
};
#endif