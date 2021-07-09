//
// Created by xXRag on 2021-07-04.
//

#ifndef TESTPROJECT_APPLICATION_H
#define TESTPROJECT_APPLICATION_H

#include "Window.h"
#include "../Rendering/Renderer.h"
#include "Events/Event.h"
#include "Layers/Layer.h"

#include <memory>
#include <vector>

#include "Layers/ImGuiLayer.h"

class Application
{
public:
    Application();
    ~Application();

    void Run();
    void OnEvent(Event& e);

    inline std::unique_ptr<Window>& GetWindow() { return m_pWindow; }
    inline static Application& Get() { return *s_pInstance; }

private:
    void PollEvents();

private:
    static Application* s_pInstance;

private:
    std::unique_ptr<Window> m_pWindow;
    std::vector<Layer*> m_layers;

    ImGuiLayer* m_pImGuiLayer;
    bool m_running = true;
    float m_lastTimeFrame = 0.f;
};


#endif //TESTPROJECT_APPLICATION_H
