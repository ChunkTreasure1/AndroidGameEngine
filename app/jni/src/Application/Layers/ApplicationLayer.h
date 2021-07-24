//
// Created by xXRag on 2021-07-05.
//

#ifndef TESTPROJECT_APPLICATIONLAYER_H
#define TESTPROJECT_APPLICATIONLAYER_H

#include "Layer.h"
#include <Rendering/Camera/OrthographicCameraController.h>
#include <Rendering/Framebuffer.h>

#include <imgui.h>
#include <Objects/Object.h>
#include <list>
#include <vector>

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
    /////ImGui/////
    void CreateDockspace();
    void RenderViewport();
    void RenderSettings();
    void RenderBaseTools();
    void RenderObjectsPanel();
    void RenderObjectProperties();

private:
    bool OnUpdate(AppUpdateEvent& e);

private:
    OrthographicCameraController m_cameraController;

    std::shared_ptr<Framebuffer> m_viewportBuffer;
    ImVec2 m_lastPerspectiveSize = { 0.f, 0.f };

    /////Windows/////
    bool m_settingsOpen = false;
    bool m_baseToolsOpen = true;
    bool m_objectsPanelOpen = true;
    bool m_objectPropertiesOpen = true;

    /////Objects/////
    std::vector<Object*> m_list;
    Object* m_pSelectedObject = nullptr;

    /////Testing/////
    std::shared_ptr<Texture2D> m_testTexture;
};


#endif //TESTPROJECT_APPLICATIONLAYER_H
