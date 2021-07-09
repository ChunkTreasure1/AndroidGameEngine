//
// Created by xXRag on 2021-07-03.
//

#include "SDL.h"

#include "Application.h"
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "../Core.h"

int SDL_main(int argc, __attribute__ ((unused)) char* argv[argc + 1])
{
    Application* pApp = new Application();
    pApp->Run();

    delete pApp;

    return EXIT_SUCCESS;
}