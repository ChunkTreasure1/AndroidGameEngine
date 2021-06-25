
cmake_minimum_required(VERSION 3.6.0)

add_library(native_app_glue STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC
        ${ANDROID_NDK}/sources/android/native_app_glue)

find_library(log-lib
        log)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
add_library(main SHARED
        src/main/cpp/main/EntryPoint.cpp
        src/main/cpp/main/Application.cpp
        src/main/cpp/main/Application.h
        src/main/cpp/main/Kernel.h
        src/main/cpp/main/Task.h
        src/main/cpp/main/Kernel.cpp
        src/main/cpp/main/Android.h
        src/main/cpp/main/Android.cpp
        src/main/cpp/main/Timer.h
        src/main/cpp/main/Timer.cpp
        src/main/cpp/rendering/Shader.h
        src/main/cpp/rendering/Shader.cpp
        src/main/cpp/rendering/Geometry.cpp
        src/main/cpp/rendering/Geometry.h
        src/main/cpp/rendering/Renderable.cpp
        src/main/cpp/rendering/Renderable.h
        src/main/cpp/rendering/Renderer.h
        src/main/cpp/rendering/Renderer.cpp
        src/main/cpp/rendering/BasicShader.cpp
        src/main/cpp/rendering/BasicShader.h
        src/main/cpp/main/MainTask.cpp
        src/main/cpp/main/MainTask.h
        src/main/cpp/main/MainApp.cpp
        src/main/cpp/main/MainApp.h)

target_link_libraries(
        main
        android
        native_app_glue
        ${log-lib}
        EGL
        GLESv3)