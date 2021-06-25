//
// Created by xXRag on 2021-06-21.
//

#ifndef GAMEENGINE_RENDERER_H
#define GAMEENGINE_RENDERER_H

#endif //GAMEENGINE_RENDERER_H

#include "../main/Task.h"
#include "Renderable.h"

#include <EGL/egl.h>
#include <vector>

struct android_app;

class Renderer : public Task
{
public:
    explicit Renderer(android_app* pState, const uint32_t priority);
    virtual ~Renderer() {}

    void Initialize();
    void Destroy();

    virtual bool Start() override;
    virtual void OnSuspend() override;
    virtual void Update() override;
    virtual void OnResume() override;
    virtual void Stop() override;

    bool IsInitialized() { return m_initialized; }

    void AddRenderable(Renderable* pRenderable);
    void RemoveRenderable(Renderable* pRenderable);

private:
    std::vector<Renderable*> m_renderables;

    void Draw(Renderable* pRenderable);

private:
    android_app* m_pState;
    EGLDisplay m_display;
    EGLContext m_context;
    EGLSurface m_surface;

    uint32_t m_width;
    uint32_t m_height;
    bool m_initialized;
};