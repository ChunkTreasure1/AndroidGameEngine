LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := \
            Application/main.cpp \
            Application/Application.cpp \
            Application/Window.cpp \
            Rendering/Renderer.cpp \
            Rendering/Buffers/VertexBuffer.cpp \
            Rendering/Buffers/VertexArray.cpp

LOCAL_SHARED_LIBRARIES := SDL2 \
SDL2_image \
SDL2_mixer

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lGLESv3 -llog

include $(BUILD_SHARED_LIBRARY)
