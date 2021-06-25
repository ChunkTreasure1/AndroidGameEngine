//
// Created by xXRag on 2021-06-21.
//

#ifndef GAMEENGINE_APPLICATION_H
#define GAMEENGINE_APPLICATION_H

#include <android_native_app_glue.h>
#include "Kernel.h"
#include "Android.h"

class Application
{
public:
    Application(android_app* pState);
    virtual ~Application() {}

    virtual bool Initialize();
    virtual void Run();

protected:
    Kernel m_kernel;
    Android m_androidTask;
};

#endif //GAMEENGINE_APPLICATION_H
