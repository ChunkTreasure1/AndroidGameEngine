//
// Created by xXRag on 2021-07-05.
//

#include "ApplicationLayer.h"

#include "Application/Events/Event.h"
#include "Application/Settings/Language.h"
#include <SDL.h>

#include <imgui.h>

ApplicationLayer::ApplicationLayer(uint32_t width, uint32_t height)
    : m_cameraController((float)width / height, false)
{
    Language::Initialize();
    Renderer::Initialize();

    m_pObjects.resize(10);
    m_viewportBuffer = Framebuffer::Create(1280, 720);
    m_testTexture = Texture2D::Create("Agent.png");
}

ApplicationLayer::~ApplicationLayer()
{
    m_pObjects.clear();
    Renderer::Shutdown();
}

void ApplicationLayer::OnAttach()
{}

void ApplicationLayer::OnDetach()
{}

void ApplicationLayer::OnImGuiRender(Timestep ts)
{
    CreateDockspace();

    //ImGui::ShowDemoWindow();
    RenderViewport();
    RenderSettings();
    RenderObjectsPanel();
    RenderBaseTools();
}

void ApplicationLayer::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<AppUpdateEvent>(LP_BIND_EVENT_FN(ApplicationLayer::OnUpdate));
}

bool ApplicationLayer::OnUpdate(AppUpdateEvent &e)
{
    /////Update/////
    m_cameraController.Update(e.GetTimestep());
    for (auto& obj : m_pObjects)
    {
        obj->OnEvent(e);
    }

    /////Render/////
    Renderer::Clear();
    m_viewportBuffer->Bind();
    Renderer::Clear();

    Renderer::Begin(m_cameraController.GetCamera());

    //Send render event
    AppRenderEvent render;
    for (auto& obj : m_pObjects)
    {
        obj->OnEvent(render);
    }

    Renderer::DrawQuad({0.f, 0.f, 0.f}, m_testTexture, {1.f, 1.f, 1.f, 1.f});

    Renderer::End();
    m_viewportBuffer->Unbind();

    return false;
}