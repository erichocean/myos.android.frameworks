
#import "eglDisplay.h"
#import <MAOpenglCodecCommon/GLClientState.h>
#import <MAOpenglCodecCommon/GLSharedGroup.h>

struct EGLContext_t {
    
    enum {
        IS_CURRENT      =   0x00010000,
        NEVER_CURRENT   =   0x00020000
    };
    
    EGLContext_t(EGLDisplay dpy, EGLConfig config, EGLContext_t *shareCtx);
    ~EGLContext_t();
    uint32_t            flags;
    EGLDisplay          dpy;
    EGLConfig           config;
    EGLSurface          read;
    EGLSurface          draw;
    EGLContext_t       *shareCtx;
    EGLint              version;
    uint32_t            rcContext;
    const char*         versionString;
    const char*         vendorString;
    const char*         rendererString;
    const char*         extensionString;
    
    GLClientState * getClientState(){ return clientState; }
    GLSharedGroupPtr getSharedGroup(){ return sharedGroup; }
private:
    GLClientState    *    clientState;
    GLSharedGroupPtr      sharedGroup;
};
