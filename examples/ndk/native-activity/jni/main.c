/*
 * Copyright (C) 2010 The Android Open Source Project
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
 *
 */

//BEGIN_INCLUDE(all)
#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

/**
 * Our saved state data.
 */
typedef struct {
    float green;
    int32_t x;
    int32_t y;
} saved_state;

/**
 * Shared state for our app.
 */
typedef struct {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    saved_state state;
} engine;

/**
 * Initialize an EGL context for the current display.
 */
static int engine_init_display(engine* myEngine)
{
    // initialize OpenGL ES and EGL

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(myEngine->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, myEngine->app->window, NULL);
    context = eglCreateContext(display, config, NULL, NULL);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    myEngine->display = display;
    myEngine->context = context;
    myEngine->surface = surface;
    myEngine->width = w;
    myEngine->height = h;
    myEngine->state.green = 0;

    // Initialize GL state.
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);

    return 0;
}

/**
 * Just the current frame in the display.
 */
static void engine_draw_frame(engine* myEngine)
{
    if (myEngine->display == NULL) {
        // No display.
        return;
    }

    // Just fill the screen with a color.
    glClearColor(((float)myEngine->state.x)/myEngine->width, myEngine->state.green,((float)myEngine->state.y)/myEngine->height, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    eglSwapBuffers(myEngine->display, myEngine->surface);
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engine_term_display(engine* myEngine)
{
    if (myEngine->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(myEngine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (myEngine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(myEngine->display, myEngine->context);
        }
        if (myEngine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(myEngine->display, myEngine->surface);
        }
        eglTerminate(myEngine->display);
    }
    myEngine->animating = 0;
    myEngine->display = EGL_NO_DISPLAY;
    myEngine->context = EGL_NO_CONTEXT;
    myEngine->surface = EGL_NO_SURFACE;
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
{
    engine* myEngine = (engine*)app->userData;
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
        myEngine->state.green = 0;
        myEngine->animating = 1;
        myEngine->state.x = AMotionEvent_getX(event, 0);
        myEngine->state.y = AMotionEvent_getY(event, 0);
        return 1;
    }
    return 0;
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
    engine* myEngine = (engine*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            myEngine->app->savedState = malloc(sizeof(saved_state));
            *((saved_state*)myEngine->app->savedState) = myEngine->state;
            myEngine->app->savedStateSize = sizeof(saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (myEngine->app->window != NULL) {
                engine_init_display(myEngine);
                engine_draw_frame(myEngine);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine_term_display(myEngine);
            break;
        case APP_CMD_GAINED_FOCUS:
            // When our app gains focus, we start monitoring the accelerometer.
            if (myEngine->accelerometerSensor != NULL) {
                ASensorEventQueue_enableSensor(myEngine->sensorEventQueue,
                        myEngine->accelerometerSensor);
                // We'd like to get 60 events per second (in us).
                ASensorEventQueue_setEventRate(myEngine->sensorEventQueue,
                        myEngine->accelerometerSensor, (1000L/60)*1000);
            }
            break;
        case APP_CMD_LOST_FOCUS:
            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            if (myEngine->accelerometerSensor != NULL) {
                ASensorEventQueue_disableSensor(myEngine->sensorEventQueue,
                        myEngine->accelerometerSensor);
            }
            // Also stop animating.
            myEngine->animating = 0;
            engine_draw_frame(myEngine);
            break;
    }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state)
{
    engine *myEngine;

    myEngine = malloc(sizeof(engine));
    // Make sure glue isn't stripped.
    app_dummy();

    memset(myEngine, 0, sizeof(engine));
    state->userData = myEngine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    myEngine->app = state;

    // Prepare to monitor accelerometer
    myEngine->sensorManager = ASensorManager_getInstance();
    myEngine->accelerometerSensor = ASensorManager_getDefaultSensor(myEngine->sensorManager,
            ASENSOR_TYPE_ACCELEROMETER);
    myEngine->sensorEventQueue = ASensorManager_createEventQueue(myEngine->sensorManager,
            state->looper, LOOPER_ID_USER, NULL, NULL);

    if (state->savedState != NULL) {
        // We are starting with a previous saved state; restore from it.
        myEngine->state = *(saved_state*)state->savedState;
    }

    // loop waiting for stuff to do.

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(myEngine->animating ? 0 : -1, NULL, &events, (void**)&source)) >= 0) {
            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                if (myEngine->accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(myEngine->sensorEventQueue,
                            &event, 1) > 0) {
                        LOGI("accelerometer: x=%f y=%f z=%f",
                                event.acceleration.x, event.acceleration.y,
                                event.acceleration.z);
                    }
                }
            }
            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                engine_term_display(myEngine);
                return;
            }
        }
        if (myEngine->animating) {
            // Done with events; draw next animation frame.
            myEngine->state.green += .01f;
            if (myEngine->state.green > 1) {
                myEngine->state.green = 0;
            }
            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.
            engine_draw_frame(myEngine);
        }
    }
    free(myEngine);
}
//END_INCLUDE(all)
