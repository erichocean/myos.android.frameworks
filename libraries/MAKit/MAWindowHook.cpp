/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
// Copied from frameworks/base/cmds/stagefright/stream.cpp

// Note to NDK developers who happen to see this: this module uses Android internal platform APIs
// that are not part of the NDK supported APIs, and are subject to change at any time.

//#import <binder/ProcessState.h>
//#import <gui/SurfaceComposerClient.h>
//#import <utils/String8.h>
#import <utils/Errors.h>
#import "MAWindowHook.h"
#import "MAWindow.h"

/*
#if 1
#include <assert.h>
#define CHECK assert
#define CHECK_EQ(a,b) CHECK((a)==(b))
#else
#include <media/stagefright/foundation/ADebug.h>
#endif
*/

namespace android
{
//Surface *nativeWindow;
//sp<Surface> gSurface;
//sp<SurfaceComposerClient> gComposerClient;
//sp<SurfaceControl> gControl;
 
ANativeWindow *getNativeWindow_(int pipeRead)
{
    //ANativeWindow *nativeWindow = (ANativeWindow *)malloc(sizeof(ANativeWindow));
    //gSurface = surface;
    MAWindow *window = new MAWindow(pipeRead);//(Surface *)malloc(sizeof(Surface));
    //window->nativeWindow->perform = window->hook_perform;
    //memset(nativeWindow, 0, sizeof(ANativeWindow));
    //memset(nativeWindow, 0, sizeof(Surface));
    //((ANativeWindow *)nativeWindow)->perform = hook_perform;
    //nativeWindow->minSwapInterval = 0;
    //nativeWindow->maxSwapInterval = 1;
    return window->nativeWindow;
    
    /*#if 0
     android::ProcessState::self()->startThreadPool();
     #endif
     
     printf("getNativeWindow_ 1");
     sp<SurfaceComposerClient> composerClient = new SurfaceComposerClient;
     printf("getNativeWindow_ 1.1");
     CHECK_EQ(composerClient->initCheck(), (status_t)OK);
     printf("getNativeWindow_ 2");
     sp<SurfaceControl> control =
     composerClient->createSurface(
     String8("A Surface"),
     1280,
     800,
     PIXEL_FORMAT_RGB_565,
     0);
     
     CHECK(control != NULL);
     CHECK(control->isValid());
     printf("getNativeWindow_ 3");
     SurfaceComposerClient::openGlobalTransaction();
     CHECK_EQ(control->setLayer(30000), (status_t)OK);
     CHECK_EQ(control->show(), (status_t)OK);
     SurfaceComposerClient::closeGlobalTransaction();
     printf("getNativeWindow_ 4");
     sp<Surface> surface = control->getSurface();
     CHECK(surface != NULL);
     
     gSurface = surface;
     gComposerClient = composerClient;
     printf("getNativeWindow_ 5");
     gControl = control;
     // composerClient->dispose() at exit
     return surface.get();*/
}

void disposeNativeWindow_()
{
    //gComposerClient->dispose();
}

}; // namespace MN

ANativeWindow *getNativeWindow(int pipeRead)
{
    return android::getNativeWindow_(pipeRead);
}

void disposeNativeWindow()
{
    android::disposeNativeWindow_();
}
