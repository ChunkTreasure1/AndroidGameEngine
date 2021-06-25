//
// Created by xXRag on 2021-06-22.
//

#include "MainApp.h"

MainApp::MainApp(android_app *pState)
    : Application(pState), m_mainTask(&m_renderer, Task::PLATFORM_PRIORITY), m_renderer(pState, 0)
{
}

bool MainApp::Initialize()
{
    m_kernel.AddTask(&m_androidTask);

    bool success = true;
    if (success)
    {
        m_kernel.AddTask(&m_mainTask);
    }

    return success;
}
