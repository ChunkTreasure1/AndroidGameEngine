//
// Created by xXRag on 2021-06-22.
//

#ifndef GAMEENGINE_MAINAPP_H
#define GAMEENGINE_MAINAPP_H

#include "Application.h"
#include "MainTask.h"

class MainApp : public Application
{
public:
    MainApp(android_app* pState);
    virtual ~MainApp() {}

    virtual bool Initialize();

private:
    MainTask m_mainTask;
    Renderer m_renderer;
};

#endif //GAMEENGINE_MAINAPP_H
