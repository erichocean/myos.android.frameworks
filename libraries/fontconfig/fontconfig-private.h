
#import <android/log.h>

#ifdef DEBUG
#ifndef RD_LOG
#define RD_LOG
#define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "fontconfig", __VA_ARGS__);
#define fprintf(stderr,...) __android_log_print(ANDROID_LOG_ERROR, "FC Error", __VA_ARGS__);
#define vfprintf(stderr, ...) __android_log_print(ANDROID_LOG_ERROR, "FC Error", __VA_ARGS__);
#endif
#else
#define printf(...)
#define fprintf(stderr,...)
#define vfprintf(stderr, ...)
#endif
