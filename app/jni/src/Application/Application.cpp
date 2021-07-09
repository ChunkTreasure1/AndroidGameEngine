//
// Created by xXRag on 2021-07-04.
//

#include "Application.h"

#include <GLES3/gl3.h>

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Layers/ApplicationLayer.h"
#include <time.h>

Application* Application::s_pInstance = nullptr;

static float now_ms(void) {

    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (float) res.tv_nsec / 1e6;
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
        float time = now_ms();
        Timestep timestep = time - m_lastTimeFrame;
        m_lastTimeFrame = time;

        AppRenderEvent render;
        OnEvent(render);

        AppUpdateEvent update(timestep);
        OnEvent(update);

        m_pImGuiLayer->Begin();
        for (Layer* pLayer : m_layers)
        {
            pLayer->OnImGuiRender(timestep);
        }
        m_pImGuiLayer->End();

        m_pWindow->Update(timestep);
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
