//
// Created by xXRag on 2021-07-05.
//

#ifndef TESTPROJECT_APPLICATIONLAYER_H
#define TESTPROJECT_APPLICATIONLAYER_H

#include "Layer.h"
#include "../Rendering/Camera/OrthographicCameraController.h"
#include "../../Rendering/Framebuffer.h"

#include <imgui.h>

class ApplicationLayer : public Layer
{
public:
    ApplicationLayer(uint32_t width, uint32_t height);
    virtual ~ApplicationLayer() override;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnEvent(Event &e) override;
    virtual void OnImGuiRender(Timestep ts) override;

private:
    void CreateDockspace();
    void RenderViewport();

private:
    bool OnUpdate(AppUpdateEvent& e);
    bool OnRender(AppRenderEvent& e);

private:
    Renderer* m_pRenderer = nullptr;
    OrthographicCameraController m_cameraController;

    std::shared_ptr<Framebuffer> m_viewportBuffer;
    ImVec2 m_lastPerspectiveSize = { 0.f, 0.f };
};


#endif //TESTPROJECT_APPLICATIONLAYER_H
