
#import <android/native_window_jni.h>
#import <android/log.h>

#ifndef printfWithProcess
//#define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "", __VA_ARGS__);
#define printfWithProcess(process, ...) __android_log_print(ANDROID_LOG_DEBUG, process, __VA_ARGS__);
#endif


#ifdef __cplusplus
extern "C" {
#endif

extern ANativeWindow *getNativeWindow(int pipeRead);
extern void disposeNativeWindow();

#ifdef __cplusplus
}
#endif
