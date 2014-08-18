
#import "MAEGL-private.h"
//#import <egl/egl_ftable.h>
#import <utils/Log.h>
#import <system/Window.h>
//#import "gralloc_cb.h"
#import "ClientAPIExts.h"
//#import <MAGLESv1_enc/MAGLESv1_enc.h>
//#import <MAOpenglSystemCommon/MAOpenglSystemCommon.h>
#import <OpenGLES/EAGLMA.h>

#define ST_LOGV(x, ...) LOGV("[%s] "x, mConsumerName.string(), ##__VA_ARGS__)
#define ST_LOGD(x, ...) LOGD("[%s] "x, mConsumerName.string(), ##__VA_ARGS__)
#define ST_LOGI(x, ...) LOGI("[%s] "x, mConsumerName.string(), ##__VA_ARGS__)
#define ST_LOGW(x, ...) LOGW("[%s] "x, mConsumerName.string(), ##__VA_ARGS__)
#define ST_LOGE(x, ...) LOGE("[%s] "x, mConsumerName.string(), ##__VA_ARGS__)

#define RETURN_ERROR(ret,err)           \
LOGE("tid %d: %s(%d): error 0x%x (%s)", gettid(), __FUNCTION__, __LINE__, err, eglStrError(err));    \
return ret;

//getEGLThreadInfo()->eglError = err;    \



#define VALIDATE_DISPLAY(dpy,ret) \
if ((dpy) != (EGLDisplay)&s_display) { \
RETURN_ERROR(ret, EGL_BAD_DISPLAY);    \
}

#define VALIDATE_DISPLAY_INIT(dpy,ret) \
VALIDATE_DISPLAY(dpy, ret)    \
if (!s_display.initialized()) {        \
RETURN_ERROR(ret, EGL_NOT_INITIALIZED);    \
}

#define setErrorReturn(error, retVal)     \
{                                                \
LOGE("tid %d: %s(%d): error 0x%x (%s)", gettid(), __FUNCTION__, __LINE__, error, eglStrError(error));     \
return setErrorFunc(error, retVal);            \
}

/*#define DEFINE_AND_VALIDATE_HOST_CONNECTION(ret) \
HostConnection *hostCon = HostConnection::get(); \
if (!hostCon) { \
LOGE("egl: Failed to get host connection\n"); \
return ret; \
} \
renderControl_encoder_context_t *rcEnc = hostCon->rcEncoder(); \
if (!rcEnc) { \
LOGE("egl: Failed to get renderControl encoder context\n"); \
return ret; \
}*/

/*#define DEFINE_HOST_CONNECTION \
HostConnection *hostCon = HostConnection::get(); \
renderControl_encoder_context_t *rcEnc = (hostCon ? hostCon->rcEncoder() : NULL)
*/
#define VALIDATE_SURFACE_RETURN(surface, ret)    \
    if (surface != EGL_NO_SURFACE) {    \
        egl_surface_t* s( static_cast<egl_surface_t*>(surface) );    \
        if (s->dpy != (EGLDisplay)&s_display)    \
            setErrorReturn(EGL_BAD_DISPLAY, EGL_FALSE);    \
    }

#define VALIDATE_CONFIG(cfg,ret) \
if(((int)cfg<0)||((int)cfg>s_display.getNumConfigs())) { \
RETURN_ERROR(ret,EGL_BAD_CONFIG); \
}

#define VALIDATE_CONTEXT_RETURN(context,ret)        \
if (!context) {                                    \
RETURN_ERROR(ret,EGL_BAD_CONTEXT);    \
}

#pragma mark - Static functions

template<typename T>
static T setErrorFunc(GLint error, T returnValue)
{
    //getEGLThreadInfo()->eglError = error;
    return 0;//returnValue;
}

static const char *eglStrError(EGLint err)
{
    switch (err){
        case EGL_SUCCESS:           return "EGL_SUCCESS";
        case EGL_NOT_INITIALIZED:   return "EGL_NOT_INITIALIZED";
        case EGL_BAD_ACCESS:        return "EGL_BAD_ACCESS";
        case EGL_BAD_ALLOC:         return "EGL_BAD_ALLOC";
        case EGL_BAD_ATTRIBUTE:     return "EGL_BAD_ATTRIBUTE";
        case EGL_BAD_CONFIG:        return "EGL_BAD_CONFIG";
        case EGL_BAD_CONTEXT:       return "EGL_BAD_CONTEXT";
        case EGL_BAD_CURRENT_SURFACE: return "EGL_BAD_CURRENT_SURFACE";
        case EGL_BAD_DISPLAY:       return "EGL_BAD_DISPLAY";
        case EGL_BAD_MATCH:         return "EGL_BAD_MATCH";
        case EGL_BAD_NATIVE_PIXMAP: return "EGL_BAD_NATIVE_PIXMAP";
        case EGL_BAD_NATIVE_WINDOW: return "EGL_BAD_NATIVE_WINDOW";
        case EGL_BAD_PARAMETER:     return "EGL_BAD_PARAMETER";
        case EGL_BAD_SURFACE:       return "EGL_BAD_SURFACE";
        case EGL_CONTEXT_LOST:      return "EGL_CONTEXT_LOST";
        default: return "UNKNOWN";
    }
}

#pragma mark egl_surface_t

//we don't need to handle depth since it's handled when window created on the host

struct egl_surface_t {
    
    EGLDisplay          dpy;
    EGLConfig           config;
    
    
    egl_surface_t(EGLDisplay dpy, EGLConfig config, EGLint surfaceType);
    virtual     ~egl_surface_t();
    
    virtual     void        setSwapInterval(int interval) = 0;
    virtual     EGLBoolean  swapBuffers() = 0;
    
    EGLint      getSwapBehavior() const;
    uint32_t    getRcSurface()   { return rcSurface; }
    EGLint      getSurfaceType() { return surfaceType; }
    
    EGLint      getWidth(){ return width; }
    EGLint      getHeight(){ return height; }
    void        setTextureFormat(EGLint _texFormat) { texFormat = _texFormat; }
    EGLint      getTextureFormat() { return texFormat; }
    void        setTextureTarget(EGLint _texTarget) { texTarget = _texTarget; }
    EGLint      getTextureTarget() { return texTarget; }
    
private:
    //
    //Surface attributes
    //
    EGLint      width;
    EGLint      height;
    EGLint      texFormat;
    EGLint      texTarget;
    
protected:
    void        setWidth(EGLint w)  { width = w;  }
    void        setHeight(EGLint h) { height = h; }
    
    EGLint      surfaceType;
    uint32_t    rcSurface; //handle to surface created via remote control
};

egl_surface_t::egl_surface_t(EGLDisplay dpy, EGLConfig config, EGLint surfaceType)
: dpy(dpy), config(config), surfaceType(surfaceType), rcSurface(0)
{
    width = 0;
    height = 0;
    texFormat = EGL_NO_TEXTURE;
    texTarget = EGL_NO_TEXTURE;
}

EGLint egl_surface_t::getSwapBehavior() const {
    return EGL_BUFFER_PRESERVED;
}

egl_surface_t::~egl_surface_t()
{
}

#pragma mark egl_window_surface_t

struct egl_window_surface_t : public egl_surface_t {
    static egl_window_surface_t* create(
                                        EGLDisplay dpy, EGLConfig config, EGLint surfType,
                                        ANativeWindow* window);
    
    virtual ~egl_window_surface_t();
    
    virtual void       setSwapInterval(int interval);
    virtual EGLBoolean swapBuffers();
    
private:
    egl_window_surface_t(
                         EGLDisplay dpy, EGLConfig config, EGLint surfType,
                         ANativeWindow* window);
    EGLBoolean init();
    
    ANativeWindow*              nativeWindow;
    android_native_buffer_t*    buffer;
};

egl_window_surface_t::egl_window_surface_t (
                                            EGLDisplay dpy, EGLConfig config, EGLint surfType,
                                            ANativeWindow* window)
:   egl_surface_t(dpy, config, surfType),
nativeWindow(window),
buffer(NULL)
{
    // keep a reference on the window
    nativeWindow->common.incRef(&nativeWindow->common);
    EGLint w,h;
    nativeWindow->query(nativeWindow, NATIVE_WINDOW_WIDTH, &w);
    setWidth(w);
    nativeWindow->query(nativeWindow, NATIVE_WINDOW_HEIGHT, &h);
    setHeight(h);
}

EGLBoolean egl_window_surface_t::init()
{
    //LOGD("egl_window_surface_t::init 1");
    /*if (nativeWindow->dequeueBuffer_DEPRECATED(nativeWindow, &buffer) != NO_ERROR) {
        setErrorReturn(EGL_BAD_ALLOC, EGL_FALSE);
    }
    DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_FALSE);
    //LOGD("egl_window_surface_t::init 2");
    rcSurface = rcEnc->rcCreateWindowSurface(rcEnc, (uint32_t)config, getWidth(), getHeight());
    if (!rcSurface) {
        LOGE("rcCreateWindowSurface returned 0");
        return EGL_FALSE;
    }
    rcEnc->rcSetWindowColorBuffer(rcEnc, rcSurface, ((cb_handle_t*)(buffer->handle))->hostHandle);*/
    
    return EGL_TRUE;
}

egl_window_surface_t* egl_window_surface_t::create(
                                                   EGLDisplay dpy, EGLConfig config, EGLint surfType,
                                                   ANativeWindow* window)
{
    egl_window_surface_t* wnd = new egl_window_surface_t(dpy, config, surfType, window);
    if (wnd && !wnd->init()) {
        delete wnd;
        wnd = NULL;
    }
    return wnd;
}

egl_window_surface_t::~egl_window_surface_t() {
    /*DEFINE_HOST_CONNECTION;
    if (rcSurface && rcEnc) {
        rcEnc->rcDestroyWindowSurface(rcEnc, rcSurface);
    }
    if (buffer) {
        nativeWindow->cancelBuffer_DEPRECATED(nativeWindow, buffer);
    }
    nativeWindow->common.decRef(&nativeWindow->common);*/
}

void egl_window_surface_t::setSwapInterval(int interval)
{
    nativeWindow->setSwapInterval(nativeWindow, interval);
}

EGLBoolean egl_window_surface_t::swapBuffers()
{
    LOGV("egl_window_surface_t::swapBuffers 1");
    /*DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_FALSE);
    //LOGE("egl_window_surface_t::swapBuffers 2");
    rcEnc->rcFlushWindowColorBuffer(rcEnc, rcSurface);
    //LOGE("egl_window_surface_t::swapBuffers nativeWindow: %p", nativeWindow);
    //LOGE("egl_window_surface_t::swapBuffers nativeWindow->queueBuffer_DEPRECATED: %p", nativeWindow->queueBuffer_DEPRECATED);
    nativeWindow->queueBuffer_DEPRECATED(nativeWindow, buffer);
    //LOGV("((cb_handle_t *)(buffer->handle))->hostHandle 1: %d", ((cb_handle_t *)(buffer->handle))->hostHandle);
    //rcEnc->rcFBPost(rcEnc, ((cb_handle_t *)(buffer->handle))->hostHandle);
    
    //LOGE("egl_window_surface_t::swapBuffers 3.1");
    if (nativeWindow->dequeueBuffer_DEPRECATED(nativeWindow, &buffer)) {
        //LOGE("egl_window_surface_t::swapBuffers 4");
        buffer = NULL;
        setErrorReturn(EGL_BAD_ALLOC, EGL_FALSE);
    }
    //LOGE("egl_window_surface_t::swapBuffers 5");
    rcEnc->rcSetWindowColorBuffer(rcEnc, rcSurface, ((cb_handle_t *)(buffer->handle))->hostHandle);
    //LOGV("((cb_handle_t *)(buffer->handle))->hostHandle 2: %d", ((cb_handle_t *)(buffer->handle))->hostHandle);
    //LOGE("egl_window_surface_t::swapBuffers 6");
    //rcEnc->rcFBPost(rcEnc, ((cb_handle_t *)(buffer->handle))->hostHandle);*/
    return EGL_TRUE;
}

static const char *getGLString(int glEnum)
{
    LOGE("getGLString 1");
    /*EGLThreadInfo *tInfo = getEGLThreadInfo();
    if (!tInfo || !tInfo->currentContext) {
        return NULL;
    }
    LOGE("getGLString 2");
    const char** strPtr = NULL;
    
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02
#define GL_EXTENSIONS                     0x1F03
    
    switch(glEnum) {
        case GL_VERSION:
            strPtr = &tInfo->currentContext->versionString;
            LOGE("getGLString GL_VERSION strPtr: %s", *strPtr);
            break;
        case GL_VENDOR:
            strPtr = &tInfo->currentContext->vendorString;
            LOGE("getGLString GL_VENDOR strPtr: %s", *strPtr);
            break;
        case GL_RENDERER:
            strPtr = &tInfo->currentContext->rendererString;
            LOGE("getGLString GL_RENDERER strPtr: %s", *strPtr);
            break;
        case GL_EXTENSIONS:
            strPtr = &tInfo->currentContext->extensionString;
            LOGE("getGLString GL_EXTENSIONS strPtr: %s", *strPtr);
            break;
    }
    if (!strPtr) {
        return NULL;
    }
    
    if (*strPtr != NULL) {
        //
        // string is already cached
        //
        return *strPtr;
    }
    LOGE("*strPtr == NULL");
    //
    // first query of that string - need to query host
    //
    DEFINE_AND_VALIDATE_HOST_CONNECTION(NULL);
    char *hostStr = NULL;
    int n = rcEnc->rcGetGLString(rcEnc, glEnum, NULL, 0);
    if (n < 0) {
        hostStr = new char[-n+1];
        n = rcEnc->rcGetGLString(rcEnc, glEnum, hostStr, -n);
        if (n <= 0) {
            delete [] hostStr;
            hostStr = NULL;
        }
    }
    LOGE("getGLString 5");
    //
    // keep the string in the context and return its value
    //
    *strPtr = hostStr;
    LOGE("getGLString *strPtr = hostStr: %s", *strPtr);
    return hostStr;*/
    return 0;
}

// The one and only supported display object.
static eglDisplay s_display;

/*static EGLClient_eglInterface s_eglIface = {
    getEGLThreadInfo,
    getGLString
};*/

#pragma mark - Public C functions

EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id)
{ 
    //LOGV("eglGetDisplay");
    //
    // we support only EGL_DEFAULT_DISPLAY.
    //
    if (display_id != EGL_DEFAULT_DISPLAY) {
        return EGL_NO_DISPLAY;
    }
    //LOGE("eglGetDisplay 2");
    return (EGLDisplay)&s_display;
}

EGLDisplay eglGetDisplayFromSurface(EGLSurface surface)
{
    //LOGE("eglGetDisplayFromSurface");
    egl_surface_t *s = static_cast<egl_surface_t*>(surface);
    //LOGE("eglGetDisplayFromSurface 2");
    return s->dpy;
}

EGLBoolean eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    //LOGV("eglInitialize dpy: %p", dpy);
    /*VALIDATE_DISPLAY(dpy,EGL_FALSE);
    if (!s_display.initialize(&s_eglIface)) {
        return EGL_FALSE;
    }
    if (major!=NULL) {
        *major = s_display.getVersionMajor();
    }
    if (minor!=NULL) {
        *minor = s_display.getVersionMinor();
    }*/
    return EGL_TRUE;
}

EGLBoolean eglTerminate(EGLDisplay dpy)
{
    VALIDATE_DISPLAY_INIT(dpy, EGL_FALSE);
    s_display.terminate();
    return EGL_TRUE;
}

EGLint eglGetError()
{
    //EGLint error = getEGLThreadInfo()->eglError;
    //getEGLThreadInfo()->eglError = EGL_SUCCESS;
    return 0;//error;
}

EGLBoolean eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    /*VALIDATE_DISPLAY_INIT(dpy, EGL_FALSE);
    //LOGV("eglChooseConfig, dpy: %p", dpy);
    int attribs_size = 0;
    if (attrib_list) {
        const EGLint * attrib_p = attrib_list;
        while (attrib_p[0] != EGL_NONE) {
            attribs_size += 2;
            attrib_p += 2;
        }
        attribs_size++; //for the terminating EGL_NONE
    }
    
    DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_FALSE);
    *num_config = rcEnc->rcChooseConfig(rcEnc, (EGLint*)attrib_list, attribs_size * sizeof(EGLint), (uint32_t*)configs, config_size);
    if (*num_config <= 0) {
        return EGL_FALSE;
    }*/
    return EGL_TRUE;
}

EGLBoolean eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
    //LOGV("eglGetConfigAttrib, config: %p, attribute: %d", config, attribute);
    /*VALIDATE_DISPLAY_INIT(dpy, NULL);
    VALIDATE_CONFIG(config, EGL_FALSE);
    
    if (s_display.getConfigAttrib(config, attribute, value)) {
        return EGL_TRUE;
    } else {
        RETURN_ERROR(EGL_FALSE, EGL_BAD_ATTRIBUTE);
    }*/
    return 0;
}

EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
    /*VALIDATE_DISPLAY_INIT(dpy, EGL_NO_CONTEXT);
    VALIDATE_CONFIG(config, EGL_NO_CONTEXT);
    //LOGV("eglCreateContext, share_context: %p", share_context);
    EGLint version = 1; //default
    while (attrib_list && attrib_list[0]) {
        if (attrib_list[0] == EGL_CONTEXT_CLIENT_VERSION) version = attrib_list[1];
        attrib_list+=2;
    }
    
    uint32_t rcShareCtx = 0;
    EGLContext_t * shareCtx = NULL;
    if (share_context) {
        shareCtx = static_cast<EGLContext_t*>(share_context);
        rcShareCtx = shareCtx->rcContext;
        if (shareCtx->dpy != dpy)
            setErrorReturn(EGL_BAD_MATCH, EGL_NO_CONTEXT);
    }
    
    DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_NO_CONTEXT);
    uint32_t rcContext = rcEnc->rcCreateContext(rcEnc, (uint32_t)config, rcShareCtx, version);
    if (!rcContext) {
        LOGE("rcCreateContext returned 0");
        setErrorReturn(EGL_BAD_ALLOC, EGL_NO_CONTEXT);
    }
    
    EGLContext_t * context = new EGLContext_t(dpy, config, shareCtx);
    if (!context)
        setErrorReturn(EGL_BAD_ALLOC, EGL_NO_CONTEXT);
    
    context->version = version;
    context->rcContext = rcContext;
    
    */
    return 0;//context;
}

EGLBoolean eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    VALIDATE_DISPLAY_INIT(dpy, EGL_FALSE);
    VALIDATE_CONTEXT_RETURN(ctx, EGL_FALSE);
    
    EGLContext_t * context = static_cast<EGLContext_t*>(ctx);
    /*if (getEGLThreadInfo()->currentContext == context) {
        eglMakeCurrent(dpy, EGL_NO_CONTEXT, EGL_NO_SURFACE, EGL_NO_SURFACE);
    }
    if (context->rcContext) {
        DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_FALSE);
        rcEnc->rcDestroyContext(rcEnc, context->rcContext);
        context->rcContext = 0;
    }
    
    delete context;*/
    return EGL_TRUE;
}

EGLSurface eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list)
{
    return 0;
    VALIDATE_DISPLAY_INIT(dpy, NULL);
    VALIDATE_CONFIG(config, EGL_FALSE);
    if (win == 0) {
        setErrorReturn(EGL_BAD_MATCH, EGL_NO_SURFACE);
    }
    //eglDisplay *s_display = (eglDisplay *)dpy;
    EGLint surfaceType = EGL_WINDOW_BIT;
    //LOGE("s_display->getConfigAttrib: %p", s_display->getConfigAttrib);
    //LOGE("s_display->m_attribs: %d", s_display->m_attribs);
    //LOGE("s_display->m_configs: %d", s_display->m_configs);
    //LOGE("s_display->m_numConfigAttribs: %d", s_display->m_numConfigAttribs);
    /*if (s_display->getConfigAttrib(config, EGL_SURFACE_TYPE, &surfaceType) == EGL_FALSE) {
     return EGL_FALSE;
     }*/
    if (!(surfaceType & EGL_WINDOW_BIT)) {
        setErrorReturn(EGL_BAD_MATCH, EGL_NO_SURFACE);
    }
    if (static_cast<ANativeWindow*>(win)->common.magic != ANDROID_NATIVE_WINDOW_MAGIC) {
        setErrorReturn(EGL_BAD_NATIVE_WINDOW, EGL_NO_SURFACE);
    }
    egl_surface_t* surface = egl_window_surface_t::create(dpy, config, surfaceType, static_cast<ANativeWindow*>(win));
    if (!surface) {
        setErrorReturn(EGL_BAD_ALLOC, EGL_NO_SURFACE);
    }
    return surface;
}

EGLBoolean eglQuerySurface(EGLDisplay dpy, EGLSurface eglSurface, EGLint attribute, EGLint *value)
{
    //LOGE("eglQuerySurface 1.2");
    //eglQuerySurface(dpy, eglSurface, attribute, value);
    
    /*VALIDATE_DISPLAY_INIT(dpy, EGL_FALSE);
    VALIDATE_SURFACE_RETURN(eglSurface, EGL_FALSE);
    
    egl_surface_t* surface( static_cast<egl_surface_t*>(eglSurface) );*/
    EGLBoolean ret = EGL_TRUE;
    switch (attribute) {
        case EGL_CONFIG_ID:
            //ret = s_display.getConfigAttrib(surface->config, EGL_CONFIG_ID, value);
            break;
        case EGL_WIDTH:
            *value = 480;//surface->getWidth();
            break;
        case EGL_HEIGHT:
            *value = 800;//surface->getHeight();
            break;
        case EGL_TEXTURE_FORMAT:
            *value = 0;//surface->getTextureFormat();
            break;
        case EGL_TEXTURE_TARGET:
            *value = 0;//surface->getTextureTarget();
            break;
        case EGL_SWAP_BEHAVIOR:
            *value = 0;//surface->getSwapBehavior();
            break;
        case EGL_LARGEST_PBUFFER:
            // not modified for a window or pixmap surface
            // and we ignore it when creating a PBuffer surface (default is EGL_FALSE)
            //if (surface->getSurfaceType() & EGL_PBUFFER_BIT) *value = EGL_FALSE;
            break;
            //TODO: complete other attributes
        default:
            LOGE("eglQuerySurface %x  EGL_BAD_ATTRIBUTE", attribute);
            ret = setErrorFunc(EGL_BAD_ATTRIBUTE, EGL_FALSE);
            break;
    }
    //LOGE("eglQuerySurface value: %d", *value);
    return ret;
}

EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
    /*VALIDATE_DISPLAY_INIT(dpy, EGL_FALSE);
    VALIDATE_SURFACE_RETURN(draw, EGL_FALSE);
    VALIDATE_SURFACE_RETURN(read, EGL_FALSE);
    //LOGD("eglMakeCurrent");
    if ((read == EGL_NO_SURFACE && draw == EGL_NO_SURFACE) && (ctx != EGL_NO_CONTEXT)) {
        setErrorReturn(EGL_BAD_MATCH, EGL_FALSE);
    }
    if ((read != EGL_NO_SURFACE || draw != EGL_NO_SURFACE) && (ctx == EGL_NO_CONTEXT)) {
        setErrorReturn(EGL_BAD_MATCH, EGL_FALSE);
    }
    EGLContext_t *context = (EGLContext_t *)ctx;
    uint32_t ctxHandle = (context) ? context->rcContext : 0;
    egl_surface_t * drawSurf = static_cast<egl_surface_t *>(draw);
    uint32_t drawHandle = (drawSurf) ? drawSurf->getRcSurface() : 0;
    egl_surface_t * readSurf = static_cast<egl_surface_t *>(read);
    uint32_t readHandle = (readSurf) ? readSurf->getRcSurface() : 0;
    
    //
    // Nothing to do if no binding change has made
    //
    EGLThreadInfo *tInfo = getEGLThreadInfo();
    if (tInfo->currentContext == context &&
        (context == NULL ||
         (context && context->draw == draw && context->read == read))) {
            return EGL_TRUE;
        }
    
    if (context && (context->flags & EGLContext_t::IS_CURRENT) && (context != tInfo->currentContext)) {
        //context is current to another thread
        setErrorReturn(EGL_BAD_ACCESS, EGL_FALSE);
    }
    
    DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_FALSE);
    if (rcEnc->rcMakeCurrent(rcEnc, ctxHandle, drawHandle, readHandle) == EGL_FALSE) {
        LOGE("rcMakeCurrent returned EGL_FALSE");
        setErrorReturn(EGL_BAD_CONTEXT, EGL_FALSE);
    }
    
    //Now make the local bind
    if (context) {
        //LOGD("eglMakeCurrent context: %p, hostCon: %p", context, hostCon);
        context->draw = draw;
        context->read = read;
        context->flags |= EGLContext_t::IS_CURRENT;
        //set the client state
        hostCon->glEncoder()->setClientState(context->getClientState());
        hostCon->glEncoder()->setSharedGroup(context->getSharedGroup());
        //LOGE("eglMakeCurrent 4");
        //}
    } else {
        LOGE("eglMakeCurrent context: NULL");
        //release ClientState & SharedGroup
        hostCon->glEncoder()->setClientState(NULL);
        hostCon->glEncoder()->setSharedGroup(GLSharedGroupPtr(NULL));
        //}
    }
    //LOGE("eglMakeCurrent 5");
    if (tInfo->currentContext) {
        tInfo->currentContext->flags &= ~EGLContext_t::IS_CURRENT;
    }
    //Now make current
    tInfo->currentContext = context;
    //LOGE("eglMakeCurrent 7");
    //Check maybe we need to init the encoder, if it's first eglMakeCurrent
    if (tInfo->currentContext) {
        if (!hostCon->glEncoder()->isInitialized()) {
            //LOGE("eglMakeCurrent 8");
            //s_display.gles_iface()->init();
            //LOGE("eglMakeCurrent 9");
            hostCon->glEncoder()->setInitialized();
            //LOGE("eglMakeCurrent 9.1");
            //ClientAPIExts::initClientFuncs(s_display.gles_iface(), 0);
        }
        //}
    }
    //LOGE("eglMakeCurrent 10");*/
    return EGL_TRUE;
}

EGLBoolean eglSwapBuffers(EGLDisplay dpy, EGLSurface eglSurface)
{
    //LOGD("eglSwapBuffers 1");
    EAGLMASwapBuffers();
    /*
    VALIDATE_DISPLAY_INIT(dpy, EGL_FALSE);
    if (eglSurface == EGL_NO_SURFACE) {
        setErrorReturn(EGL_BAD_SURFACE, EGL_FALSE);
    }
    //LOGE("eglSwapBuffers dpy: %p", dpy);
    DEFINE_AND_VALIDATE_HOST_CONNECTION(EGL_FALSE);
    //LOGE("eglSwapBuffers 3");
    egl_surface_t* s = static_cast<egl_surface_t*>(eglSurface);
    //LOGD("eglSwapBuffers s->dpy: %p", s->dpy);
    if (s->dpy != dpy) {
        setErrorReturn(EGL_BAD_DISPLAY, EGL_FALSE);
    }
    //LOGE("eglSwapBuffers 4");
    // post the surface
    s->swapBuffers();
    //LOGE("eglSwapBuffers 5");
    hostCon->flush();
    //LOGV("eglSwapBuffers 6");*/
    return EGL_TRUE;
}

EGLBoolean eglDestroySurface(EGLDisplay dpy, EGLSurface eglSurface)
{
    VALIDATE_DISPLAY_INIT(dpy, EGL_FALSE);
    VALIDATE_SURFACE_RETURN(eglSurface, EGL_FALSE);
    
    egl_surface_t* surface(static_cast<egl_surface_t*>(eglSurface));
    delete surface;
    
    return EGL_TRUE;
}
