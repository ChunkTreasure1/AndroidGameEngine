//
// Created by xXRag on 2021-06-21.
//

#include "Application.h"

Application::Application(android_app *pState)
    : m_androidTask(pState, Task::PLATFORM_PRIORITY)
{}

bool Application::Initialize()
{
    bool ret = true;

    m_kernel.AddTask(&m_androidTask);

    return ret;
}

void Application::Run()
{
    m_kernel.Execute();
}