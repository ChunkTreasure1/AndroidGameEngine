//
// Created by xXRag on 2021-07-05.
//

#include "ApplicationLayer.h"

#include "Application/Events/Event.h"
#include "Application/Settings/Language.h"
#include <SDL.h>

#include <imgui.h>
#include <vendor/imnodes/imnodes.h>

ApplicationLayer::ApplicationLayer(uint32_t width, uint32_t height)
    : m_cameraController((float)width / height, false)
{
    Language::Initialize();
    Renderer::Initialize();

    m_viewportBuffer = Framebuffer::Create(1280, 720);
    m_testTexture = Texture2D::Create("Agent.png");

    m_list.push_back(new Object("Object0"));
}

ApplicationLayer::~ApplicationLayer()
{
    for (int i = 0; i < m_list.size(); ++i)
    {
        delete m_list[i];
        m_list[i] = nullptr;
    }

    m_list.clear();

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
    RenderObjectProperties();
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
    for (int i = 0; i < m_list.size(); ++i)
    {
        m_list[i]->OnEvent(e);
    }

    /////Render/////
    Renderer::Clear();
    m_viewportBuffer->Bind();
    Renderer::Clear();

    Renderer::Begin(m_cameraController.GetCamera());
    
    //Send render event
    AppRenderEvent render(e.GetTimestep());
    for (int i = 0; i < m_list.size(); ++i)
    {
        m_list[i]->OnEvent(render);
    }

    //Renderer::DrawQuad({0.f, 0.f, 0.f}, m_testTexture, {1.f, 1.f, 1.f, 1.f});

    Renderer::End();
    m_viewportBuffer->Unbind();

    return false;
}