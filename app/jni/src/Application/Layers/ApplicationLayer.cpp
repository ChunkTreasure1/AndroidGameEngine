//
// Created by xXRag on 2021-07-05.
//

#include "ApplicationLayer.h"

#include "../Events/Event.h"
#include <SDL.h>

#include <imgui.h>

ApplicationLayer::ApplicationLayer(uint32_t width, uint32_t height)
    : m_cameraController((float)width / height, false)
{
    Renderer::Initialize();

    m_viewportBuffer = Framebuffer::Create(1280, 720);
    m_testTexture = Texture2D::Create("Agent.png");
}

ApplicationLayer::~ApplicationLayer()
{
    Renderer::Shutdown();
}

void ApplicationLayer::OnAttach()
{}

void ApplicationLayer::OnDetach()
{}

void ApplicationLayer::OnImGuiRender(Timestep ts)
{
    CreateDockspace();

    ImGui::ShowDemoWindow();
    RenderViewport();
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

    /////Render/////
    Renderer::Clear();
    m_viewportBuffer->Bind();
    Renderer::Clear();

    Renderer::Begin(m_cameraController.GetCamera());

    //Send render event
    AppRenderEvent render;

    Renderer::DrawQuad({0.f, 0.f, 0.f}, m_testTexture, {1.f, 1.f, 1.f, 1.f});

    Renderer::End();
    m_viewportBuffer->Unbind();

    return false;
}