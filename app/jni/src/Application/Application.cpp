//
// Created by xXRag on 2021-07-04.
//

#include "Application.h"

#include <GLES3/gl3.h>

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Layers/ApplicationLayer.h"
#include <ctime>
#include <Core.h>

Application* Application::s_pInstance = nullptr;

static double currentTimeInMilliseconds()
{
    struct timeval tv{};
    gettimeofday(&tv, nullptr);
    return ((tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0)) * 0.001;
}

Application::Application()
{
    s_pInstance = this;

    //Create the android window
    m_pWindow = Window::Create();

    m_layers.push_back(new ApplicationLayer(m_pWindow->GetWidth(), m_pWindow->GetHeight()));
    m_layers[m_layers.size() - 1]->OnAttach();

    m_pImGuiLayer = new ImGuiLayer();
    m_layers.push_back(m_pImGuiLayer);
    m_pImGuiLayer->OnAttach();
}

Application::~Application()
{
    for (int i = 0; i < m_layers.size(); ++i)
    {
        m_layers[i]->OnDetach();
        delete m_layers[i];
        m_layers[i] = nullptr;
    }

    m_layers.clear();
}

void Application::Run()
{
    while (m_running)
    {
        double time = currentTimeInMilliseconds();
        Timestep ts = time - m_lastTimeFrame;
        m_lastTimeFrame = time;

        AppUpdateEvent update(ts);
        OnEvent(update);

        m_pImGuiLayer->Begin();
        for (Layer* pLayer : m_layers)
        {
            pLayer->OnImGuiRender(ts);
        }
        m_pImGuiLayer->End();

        m_pWindow->Update(ts);
        PollEvents();
    }
}

void Application::OnEvent(Event &e)
{
    for (auto& layer : m_layers)
    {
        layer->OnEvent(e);
    }
}

void Application::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                WindowCloseEvent e;
                OnEvent(e);
                break;
            }

            case SDL_MOUSEMOTION:
            {
                MouseMovedEvent e(event.motion.x, event.motion.y);
                OnEvent(e);
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            {
                MouseButtonPressedEvent e(event.button.button);
                OnEvent(e);
                break;
            }

            case SDL_MOUSEBUTTONUP:
            {
                MouseButtonReleasedEvent e(event.button.button);
                OnEvent(e);
                break;
            }

            case SDL_KEYDOWN:
            {
                KeyPressedEvent e(event.key.keysym.sym, 0);
                OnEvent(e);
                break;
            }

            case SDL_KEYUP:
            {
                KeyReleasedEvent e(event.key.keysym.sym);
                OnEvent(e);
                break;
            }
        }
    }
}
