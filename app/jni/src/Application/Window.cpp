//
// Created by xXRag on 2021-07-04.
//

#include <GLES3/gl3.h>
#include "Window.h"

std::unique_ptr<Window> Window::Create(const WindowProps &props)
{
    return std::make_unique<Window>(props);
}

Window::Window(const WindowProps &props)
{
    Initialize(props);
}

Window::~Window()
{
    Shutdown();
}

void Window::Initialize(const WindowProps &props)
{
    m_data.Title = props.Title;
    m_data.IsVSync = m_data.IsVSync;

    //Setup SDL and OpenGL
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_DisplayMode display_mode = {0};
        SDL_DisplayMode best_display_mode = {0};
        for (uint32_t display_mode_num = 0; display_mode_num < SDL_GetNumVideoDisplays(); ++display_mode_num)
        {
            if (SDL_GetCurrentDisplayMode(display_mode_num, &display_mode) < 0)
            {
            }
            if (display_mode.w * display_mode.h > best_display_mode.w * best_display_mode.h)
            {
                best_display_mode = display_mode;
            }
            if (display_mode.w * display_mode.h == best_display_mode.w * best_display_mode.h &&
                display_mode.refresh_rate > best_display_mode.refresh_rate)
            {
                best_display_mode = display_mode;
            }
        }
        SDL_assert(best_display_mode.refresh_rate != 0);

        m_data.Width = best_display_mode.w;
        m_data.Height = best_display_mode.h;

        m_pWindow = SDL_CreateWindow(m_data.Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_data.Width, m_data.Height, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);

        m_context = SDL_GL_CreateContext(m_pWindow);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        glViewport(0, 0, m_data.Width, m_data.Height);
    }
}

void Window::Shutdown()
{
    SDL_DestroyWindow(m_pWindow);
}

void Window::Update(Timestep ts)
{
    //Swap buffers
    SDL_GL_SwapWindow(m_pWindow);
}

void Window::SetIsVSync(bool state)
{}