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
    dispatcher.Dispatch<AppRenderEvent>(LP_BIND_EVENT_FN(ApplicationLayer::OnRender));
    dispatcher.Dispatch<AppUpdateEvent>(LP_BIND_EVENT_FN(ApplicationLayer::OnUpdate));
}

bool ApplicationLayer::OnUpdate(AppUpdateEvent &e)
{
    m_cameraController.Update(e.GetTimestep());
    return false;
}

bool ApplicationLayer::OnRender(AppRenderEvent &e)
{
    Renderer::Clear();
    m_viewportBuffer->Bind();
    Renderer::Clear();

    Renderer::Begin(m_cameraController.GetCamera());

    Renderer::DrawQuad({ 0.f, 0.f, 0.f }, { 2.f, 2.f }, { 0.f, 1.f, 0.f, 1.f });

    Renderer::End();
    m_viewportBuffer->Unbind();

    return false;
}