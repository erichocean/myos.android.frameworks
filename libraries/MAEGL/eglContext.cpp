
//#import "HostConnection.h"
#import "MAEGL-private.h"

EGLContext_t::EGLContext_t(EGLDisplay dpy, EGLConfig config, EGLContext_t *shareCtx) :
dpy(dpy),
config(config),
read(EGL_NO_SURFACE),
draw(EGL_NO_SURFACE),
shareCtx(shareCtx),
rcContext(0),
versionString(NULL),
vendorString(NULL),
rendererString(NULL),
extensionString(NULL)
{
    flags = 0;
    version = 1;
    clientState = new GLClientState();
    if (shareCtx) {
        sharedGroup = shareCtx->getSharedGroup();
    } else {
        sharedGroup = GLSharedGroupPtr(new GLSharedGroup());
    }
};

EGLContext_t::~EGLContext_t()
{
    delete clientState;
    delete [] versionString;
    delete [] vendorString;
    delete [] rendererString;
    delete [] extensionString;
}
