
#import <utils/Errors.h>
#import "MAWindow.h"
#import <EGL/egl.h>
#import <GLES/gl.h>
//#import <MAOpenglSystemCommon/MAOpenglSystemCommon.h>

namespace android
{
    static MAWindow *_window = NULL;
    //Surface *nativeWindow;
    //sp<Surface> gSurface;
    //sp<SurfaceComposerClient> gComposerClient;
    //sp<SurfaceControl> gControl;
    
    static void incRef(android_native_base_t* base)
    {
        //ANativeObjectBase* self = getSelf(base);
        //self->incStrong(self);
    }
    static void decRef(android_native_base_t* base)
    {
        printfWithProcess("MAKit","decRef");
        //ANativeObjectBase* self = getSelf(base);
        //self->decStrong(self);
    }
    
    MAWindow::MAWindow(int pipeRead)//(const sp<IGraphicBufferProducer>& bufferProducer)
    { 
        //mBufferProducer = new MABufferQueue(true);
        // Initialize the ANativeWindow function pointers.
        nativeWindow = (ANativeWindow *)malloc(sizeof(ANativeWindow));
        memset(nativeWindow, 0, sizeof(ANativeWindow));
        
        nativeWindow->common.magic = ANDROID_NATIVE_WINDOW_MAGIC;
        nativeWindow->common.version = sizeof(ANativeWindow);
        memset(nativeWindow->common.reserved, 0, sizeof(nativeWindow->common.reserved));
        nativeWindow->common.incRef = incRef;
        nativeWindow->common.decRef = decRef;
        
        nativeWindow->perform          = hook_perform;
        nativeWindow->setSwapInterval  = hook_setSwapInterval;
        nativeWindow->dequeueBuffer    = hook_dequeueBuffer;
        nativeWindow->cancelBuffer     = hook_cancelBuffer;
        nativeWindow->queueBuffer      = hook_queueBuffer;
        nativeWindow->query            = hook_query;
        
        //nativeWindow->dequeueBuffer_DEPRECATED = hook_dequeueBuffer_DEPRECATED;
        //nativeWindow->cancelBuffer_DEPRECATED  = hook_cancelBuffer_DEPRECATED;
        //nativeWindow->lockBuffer_DEPRECATED    = hook_lockBuffer_DEPRECATED;
        //nativeWindow->queueBuffer_DEPRECATED   = hook_queueBuffer_DEPRECATED;
        
        const_cast<int&>(nativeWindow->minSwapInterval) = 0;
        const_cast<int&>(nativeWindow->maxSwapInterval) = 1;
        
        mReqWidth = 480;
        mReqHeight = 800;
        mReqFormat = PIXEL_FORMAT_RGBA_8888;
        mReqUsage = 0;
        mTimestamp = NATIVE_WINDOW_TIMESTAMP_AUTO;
        //mCrop.clear();
        mScalingMode = NATIVE_WINDOW_SCALING_MODE_FREEZE;
        mTransform = 0;
        mDefaultWidth = 0;
        mDefaultHeight = 0;
        mUserWidth = 0;
        mUserHeight = 0;
        mTransformHint = 0;
        mConsumerRunningBehind = false;
        mConnectedToCpu = false;
        _window = this;
    }
    
    MAWindow::~MAWindow()
    {
    }
    
#pragma mark - Concrete functions
    
    int MAWindow::setBuffersFormat(int format)
    {
        if (format<0) {
            return BAD_VALUE;
        }
        //Mutex::Autolock lock(mMutex);
        mReqFormat = format;
        return NO_ERROR;
    }
    
    int MAWindow::dispatchSetBuffersFormat(va_list args)
    {
        int f = va_arg(args, int);
        return setBuffersFormat(f);
    }
    
    int MAWindow::setBuffersUserDimensions(int w, int h)
    {
        if (w<0 || h<0) {
            return BAD_VALUE;
        }
        if ((w && !h) || (!w && h)) {
            return BAD_VALUE;
        }
        //Mutex::Autolock lock(mMutex);
        mUserWidth = w;
        mUserHeight = h;
        return NO_ERROR;
    }
    
    int MAWindow::dispatchSetBuffersUserDimensions(va_list args)
    {
        int w = va_arg(args, int);
        int h = va_arg(args, int);
        return setBuffersUserDimensions(w, h);
    }
    
    int MAWindow::setScalingMode(int mode)
    {
        //ATRACE_CALL();
        //ALOGV("Surface::setScalingMode(%d)", mode);
        /*switch (mode) {
            case NATIVE_WINDOW_SCALING_MODE_FREEZE:
            case NATIVE_WINDOW_SCALING_MODE_SCALE_TO_WINDOW:
            case NATIVE_WINDOW_SCALING_MODE_SCALE_CROP:
                break;
            default:
                printfWithProcess("MAKit","unknown scaling mode: %d", mode);
                //ALOGE("unknown scaling mode: %d", mode);
                return BAD_VALUE;
        }
        //Mutex::Autolock lock(mMutex);
        mScalingMode = mode;*/
        return NO_ERROR;
    }
    
    int MAWindow::dispatchSetScalingMode(va_list args)
    {
        int m = va_arg(args, int);
        return setScalingMode(m);
    }
    
    int MAWindow::connect(int api)
    {
        //ATRACE_CALL();
        //ALOGV("Surface::connect");
        /*printfWithProcess("MAKit","connect api: %d", api);
        //Mutex::Autolock lock(mMutex);
        MABufferProducer::QueueBufferOutput output;
        int err = mBufferProducer->connect(api, &output);
        if (err == NO_ERROR) {
            uint32_t numPendingBuffers = 0;
            //output.deflate(&mDefaultWidth, &mDefaultHeight, &mTransformHint,
            //               &numPendingBuffers);
            mConsumerRunningBehind = (numPendingBuffers >= 2);
        }
        if (!err && api == NATIVE_WINDOW_API_CPU) {
            mConnectedToCpu = true;
        }*/
        return 0;//err;
    }
    
    int MAWindow::dispatchConnect(va_list args)
    {
        int api = va_arg(args, int);
        return connect(api);
    }
    
    int MAWindow::perform(int operation, va_list args)
    {
        int res = NO_ERROR;
        switch (operation) {
            case NATIVE_WINDOW_CONNECT:
                printfWithProcess("MAKit","NATIVE_WINDOW_CONNECT");
                // deprecated. must return NO_ERROR.
                break;
            case NATIVE_WINDOW_DISCONNECT:
                printfWithProcess("MAKit","NATIVE_WINDOW_DISCONNECT");
                // deprecated. must return NO_ERROR.
                break;
            case NATIVE_WINDOW_SET_USAGE:
                printfWithProcess("MAKit","NATIVE_WINDOW_SET_USAGE");
                //res = dispatchSetUsage(args);
                break;
            case NATIVE_WINDOW_SET_CROP:
                printfWithProcess("MAKit","NATIVE_WINDOW_SET_CROP");
                //res = dispatchSetCrop(args);
                break;
            case NATIVE_WINDOW_SET_BUFFER_COUNT:
                printfWithProcess("MAKit","NATIVE_WINDOW_SET_BUFFER_COUNT");
                //res = dispatchSetBufferCount(args);
                break;
            case NATIVE_WINDOW_SET_BUFFERS_GEOMETRY:
                printfWithProcess("MAKit","NATIVE_WINDOW_SET_BUFFERS_GEOMETRY");
                //res = dispatchSetBuffersGeometry(args);
                break;
            case NATIVE_WINDOW_SET_BUFFERS_TRANSFORM:
                printfWithProcess("MAKit","NATIVE_WINDOW_SET_BUFFERS_TRANSFORM");
                //res = dispatchSetBuffersTransform(args);
                break;
            case NATIVE_WINDOW_SET_BUFFERS_TIMESTAMP:
                printfWithProcess("MAKit","NATIVE_WINDOW_SET_BUFFERS_TIMESTAMP");
                //res = dispatchSetBuffersTimestamp(args);
                break;
            case NATIVE_WINDOW_SET_BUFFERS_DIMENSIONS:
                printfWithProcess("MAKit","NATIVE_WINDOW_SET_BUFFERS_DIMENSIONS");
                //res = dispatchSetBuffersDimensions(args);
                break;
            /*case NATIVE_WINDOW_SET_BUFFERS_USER_DIMENSIONS:
                res = dispatchSetBuffersUserDimensions(args);
                break;*/
            case NATIVE_WINDOW_SET_BUFFERS_FORMAT:
                res = dispatchSetBuffersFormat(args);
                break;
            case NATIVE_WINDOW_LOCK:
                printfWithProcess("MAKit","NATIVE_WINDOW_LOCK");
                //res = dispatchLock(args);
                break;
            case NATIVE_WINDOW_UNLOCK_AND_POST:
                printfWithProcess("MAKit","NATIVE_WINDOW_UNLOCK_AND_POST");
                //res = dispatchUnlockAndPost(args);
                break;
            case NATIVE_WINDOW_SET_SCALING_MODE:
                res = dispatchSetScalingMode(args);
                break;
            case NATIVE_WINDOW_API_CONNECT:
                res = dispatchConnect(args);
                break;
            case NATIVE_WINDOW_API_DISCONNECT:
                printfWithProcess("MAKit","NATIVE_WINDOW_API_DISCONNECT");
                //res = dispatchDisconnect(args);
                break;
            default:
                //printfWithProcess("MAKit","NAME_NOT_FOUND");
                res = NAME_NOT_FOUND;
                break;
        }
        return res;
    }
    
    int MAWindow::dequeueBuffer(android_native_buffer_t** buffer)
    {
        //ATRACE_CALL();
        //ALOGV("MAWindow::dequeueBuffer");
        //Mutex::Autolock lock(mMutex);
        //int buf = -1;
        //int reqW = mReqWidth ? mReqWidth : mUserWidth;
        //int reqH = mReqHeight ? mReqHeight : mUserHeight;
        //sp<Fence> fence;
        //status_t result = mBufferProducer->dequeueBuffer(&buf, &fence, reqW, reqH, mReqFormat, mReqUsage);
        /*if (result < 0) {
            ALOGV("dequeueBuffer: IGraphicBufferProducer::dequeueBuffer(%d, %d, %d, %d)"
                  "failed: %d", mReqWidth, mReqHeight, mReqFormat, mReqUsage, result);
            return result;
        }*/
        //sp<GraphicBuffer>& gbuf(mSlots[buf].buffer);
        /*if (result & MABufferProducer::RELEASE_ALL_BUFFERS) {
            freeAllBuffers();
        }
        
        if ((result & MABufferProducer::BUFFER_NEEDS_REALLOCATION) || gbuf == 0) {
            result = mBufferProducer->requestBuffer(buf, &gbuf);
            if (result != NO_ERROR) {
                ALOGE("dequeueBuffer: IGraphicBufferProducer::requestBuffer failed: %d",
                      result);
                return result;
            }
        }
        if (fence->isValid()) {
            *fenceFd = fence->dup();
            if (*fenceFd == -1) {
                ALOGE("dequeueBuffer: error duping fence: %d", errno);
                // dup() should never fail; something is badly wrong. Soldier on
                // and hope for the best; the worst that should happen is some
                // visible corruption that lasts until the next frame.
            }
        } else {
            *fenceFd = -1;
        }
        *buffer = gbuf.get();*/
        ANativeWindowBuffer *nativeWindowBuffer = (ANativeWindowBuffer *)malloc(sizeof(ANativeWindowBuffer));
        memset(nativeWindowBuffer, 0, sizeof(ANativeWindowBuffer));
        nativeWindowBuffer->width = mReqWidth;
        nativeWindowBuffer->height = mReqHeight;
        nativeWindowBuffer->format = mReqFormat;
        //int numFds = 0;
        //int numInts = 0;
        //nativeWindowBuffer->handle = native_handle_create(numFds, numInts);
        int fd = -1;
        int ashmem_size = 0;
        int usage = 0;
        //int format = mReqFormat;
        //int frameworkFormat = format;
        GLenum glFormat = GL_RGBA;
        GLenum glType = GL_UNSIGNED_BYTE;
        /*nativeWindowBuffer->handle = new cb_handle_t(fd, ashmem_size, usage,
                                          mReqWidth, mReqHeight, mReqFormat, mReqFormat,
                                          glFormat, glType);
        *buffer = nativeWindowBuffer;*/
        return OK;
    }
    
    int MAWindow::queueBuffer(android_native_buffer_t* buffer)
    {
        //ATRACE_CALL();
        //LOGV("MAWindow::queueBuffer");
        //Mutex::Autolock lock(mMutex);
        /*int64_t timestamp;
        if (mTimestamp == NATIVE_WINDOW_TIMESTAMP_AUTO) {
            timestamp = systemTime(SYSTEM_TIME_MONOTONIC);
            ALOGV("Surface::queueBuffer making up timestamp: %.2f ms",
                  timestamp / 1000000.f);
        } else {
            timestamp = mTimestamp;
        }
        int i = getSlotFromBufferLocked(buffer);
        if (i < 0) {
            return i;
        }*/
        
        
        // Make sure the crop rectangle is entirely inside the buffer.
        /*Rect crop;
        mCrop.intersect(Rect(buffer->width, buffer->height), &crop);
        
        sp<Fence> fence(fenceFd >= 0 ? new Fence(fenceFd) : Fence::NO_FENCE);
        IGraphicBufferProducer::QueueBufferOutput output;
        IGraphicBufferProducer::QueueBufferInput input(timestamp, crop, mScalingMode,
                                                       mTransform, fence);*/
        /*status_t err = mGraphicBufferProducer->queueBuffer(i, input, &output);
        if (err != OK)  {
            ALOGE("queueBuffer: error queuing buffer to SurfaceTexture, %d", err);
        }
        uint32_t numPendingBuffers = 0;
        output.deflate(&mDefaultWidth, &mDefaultHeight, &mTransformHint,
                       &numPendingBuffers);
        
        mConsumerRunningBehind = (numPendingBuffers >= 2);*/
        
        return 0;//err;
    }
    
#pragma mark - Hook functions
    
    int MAWindow::hook_perform(ANativeWindow *window, int operation, ...)
    {
        va_list args;
        va_start(args, operation);
        //MAWindow* c = getSelf(window);
        return _window->perform(operation, args);
    }
    
    int MAWindow::setSwapInterval(int interval)
    {
        //ATRACE_CALL();
        // EGL specification states:
        //  interval is silently clamped to minimum and maximum implementation
        //  dependent values before being stored.
        // Although we don't have to, we apply the same logic here.
        /*printfWithProcess("MAKit","setSwapInterval interval: %d", interval);
        status_t res = mBufferProducer->setSynchronousMode(interval ? true : false);
        */
        return 0;//res;
    }
    
    int MAWindow::hook_setSwapInterval(ANativeWindow* window, int interval)
    {
        //va_list args;
        //va_start(args, operation);
        //MAWindow* c = getSelf(window);
        //return 0;//_window->perform(operation, args);
        
        //Surface* c = getSelf(window);
        return _window->setSwapInterval(interval);
    }
    
    int MAWindow::hook_dequeueBuffer(ANativeWindow* window, ANativeWindowBuffer** buffer)
    {
        va_list args;
        //va_start(args, operation);
        //printfWithProcess("MAKit","hook_dequeueBuffer fenceFd: %p", fenceFd);
        //MAWindow* c = getSelf(window);
        //return 0;//_window->perform(operation, args);
        return 0;//_window->dequeueBuffer(buffer, fenceFd);
    }
    
    int MAWindow::hook_cancelBuffer(ANativeWindow* window, ANativeWindowBuffer* buffer)
    {
        va_list args;
        //va_start(args, operation);
        //printfWithProcess("MAKit","hook_cancelBuffer fenceFd: %d", fenceFd);
        //MAWindow* c = getSelf(window);
        return 0;//_window->perform(operation, args);
    }
    
    int MAWindow::hook_queueBuffer(ANativeWindow* window, ANativeWindowBuffer* buffer)
    {
        va_list args;
        //va_start(args, operation);
        //printfWithProcess("MAKit","hook_queueBuffer fenceFd: %d", fenceFd);
        //MAWindow* c = getSelf(window);
        return 0;//_window->perform(operation, args);
    }
    
    int MAWindow::hook_dequeueBuffer_DEPRECATED(ANativeWindow* window, ANativeWindowBuffer** buffer)
    {
        //Surface* c = getSelf(window);
        ANativeWindowBuffer* buf;
        int fenceFd = -1;
        int result = _window->dequeueBuffer(&buf);
        /*sp<Fence> fence(new Fence(fenceFd));
        int waitResult = fence->waitForever("dequeueBuffer_DEPRECATED");
        if (waitResult != OK) {
            ALOGE("dequeueBuffer_DEPRECATED: Fence::wait returned an error: %d", waitResult);
            _window->cancelBuffer(buf, -1);
            return waitResult;
        }*/
        *buffer = buf;
        return result;
    }
    
    int MAWindow::hook_queueBuffer_DEPRECATED(ANativeWindow* window, ANativeWindowBuffer* buffer)
    {
        //Surface* c = getSelf(window);
        return _window->queueBuffer(buffer);
    }
    
    int MAWindow::query(int what, int* value)
    {
        //ATRACE_CALL();
        //{ // scope for the lock
        //Mutex::Autolock lock(mMutex);
        switch (what) {
            case NATIVE_WINDOW_FORMAT: {
                printfWithProcess("MAKit","MAWindow::query NATIVE_WINDOW_FORMAT");
                if (mReqFormat) {
                    *value = mReqFormat;
                    return NO_ERROR;
                }
                break;
            }
            case NATIVE_WINDOW_QUEUES_TO_WINDOW_COMPOSER: {
                printfWithProcess("MAKit","MAWindow::query NATIVE_WINDOW_QUEUES_TO_WINDOW_COMPOSER");
                /*sp<ISurfaceComposer> composer(
                                              ComposerService::getComposerService());
                if (composer->authenticateSurfaceTexture(mGraphicBufferProducer)) {
                    *value = 1;
                } else {
                    *value = 0;
                }*/
                return NO_ERROR;
            }
            case NATIVE_WINDOW_CONCRETE_TYPE:
                printfWithProcess("MAKit","MAWindow::query NATIVE_WINDOW_CONCRETE_TYPE");
                *value = NATIVE_WINDOW_SURFACE;
                return NO_ERROR;
            case NATIVE_WINDOW_DEFAULT_WIDTH:
                printfWithProcess("MAKit","MAWindow::query NATIVE_WINDOW_DEFAULT_WIDTH");
                *value = mUserWidth ? mUserWidth : mDefaultWidth;
                return NO_ERROR;
            case NATIVE_WINDOW_DEFAULT_HEIGHT:
                printfWithProcess("MAKit","MAWindow::query NATIVE_WINDOW_DEFAULT_HEIGHT");
                *value = mUserHeight ? mUserHeight : mDefaultHeight;
                return NO_ERROR;
            case NATIVE_WINDOW_TRANSFORM_HINT:
                printfWithProcess("MAKit","MAWindow::query NATIVE_WINDOW_TRANSFORM_HINT");
                *value = mTransformHint;
                return NO_ERROR;
            /*case NATIVE_WINDOW_CONSUMER_RUNNING_BEHIND: {
                printfWithProcess("MAKit","MAWindow::query NATIVE_WINDOW_CONSUMER_RUNNING_BEHIND");
                status_t err = NO_ERROR;
                if (!mConsumerRunningBehind) {
                    *value = 0;
                } else {
                    err = 0;//mBufferProducer->query(what, value);
                    if (err == NO_ERROR) {
                        mConsumerRunningBehind = *value;
                    }
                }
                return err;
            }*/
        }
        return 0;//mBufferProducer->query(what, value);
    }
    
    int MAWindow::hook_query(const ANativeWindow* window, int what, int* value)
    {
        va_list args;
        //va_start(args, operation);
        //MAWindow* c = getSelf(window);
        //return _window->perform(operation, args);
        return _window->query(what, value);
    }
    
}; // namespace
