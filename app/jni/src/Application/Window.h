//
// Created by xXRag on 2021-07-04.
//

#ifndef TESTPROJECT_WINDOW_H
#define TESTPROJECT_WINDOW_H

#include <string>
#include "Timestep.h"
#include "SDL.h"

struct WindowProps
{
    WindowProps(std::string title = "Lamp", bool vsync = true)
        : Title(title), IsVSync(vsync)
    {}

    std::string Title;
    bool IsVSync;
    uint32_t Width;
    uint32_t Height;
};

class Window
{
public:
    Window(const WindowProps& props);
    ~Window();

    void Update(Timestep ts);

    //Getting
    inline const uint32_t GetWidth() const { return m_data.Width; }
    inline const uint32_t GetHeight() const { return m_data.Height; }
    inline const bool GetIsVSync() const { return m_data.IsVSync; }
    inline SDL_Window* GetNativeWindow() { return m_pWindow; }
    inline SDL_GLContext& GetGLConxtext() { return m_context; }

    //Setting
    void SetIsVSync(bool state);

public:
    static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());

private:
    void Initialize(const WindowProps& props);
    void Shutdown();

private:
    SDL_Window* m_pWindow;
    SDL_GLContext m_context;

    struct WindowData
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
        bool IsVSync;
    };

    WindowData m_data;
};


#endif //TESTPROJECT_WINDOW_H
