//
// Created by xXRag on 2021-07-04.
//

#ifndef TESTPROJECT_CORE_H
#define TESTPROJECT_CORE_H

#include <android/log.h>

#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //TESTPROJECT_CORE_H
