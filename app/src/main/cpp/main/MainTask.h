//
// Created by xXRag on 2021-06-22.
//

#ifndef GAMEENGINE_MAINTASK_H
#define GAMEENGINE_MAINTASK_H

#include "Task.h"
#include "../rendering/Renderer.h"
#include "../rendering/BasicShader.h"

class MainTask : public Task
{
public:
    MainTask(Renderer* pRenderer, const uint32_t priority);
    virtual ~MainTask() {}

    virtual bool Start() override;
    virtual void OnSuspend() override;
    virtual void Update() override;
    virtual void OnResume() override;

    virtual void Stop() override;

private:
    //State m_state;
    Renderer* m_pRenderer;
    Geometry m_geometry;
    BasicShader m_shader;
    Renderable m_renderable;
};

#endif //GAMEENGINE_MAINTASK_H
