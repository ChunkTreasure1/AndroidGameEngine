//
// Created by xXRag on 2021-07-03.
//

#include "SDL.h"

#include "Application.h"
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "../Core.h"
#include "Filesystem/Filesystem.h"

int SDL_main(int argc, __attribute__ ((unused)) char* argv[argc + 1])
{
    Application* pApp = new Application();
    pApp->Run();

    delete pApp;

    return EXIT_SUCCESS;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_engine_test_GameActivity_Load(JNIEnv *env, jclass clazz, jobject mgr)
{
    AAssetManager* pManager = AAssetManager_fromJava(env, mgr);
    Filesystem::SetAssetManager(pManager);
}