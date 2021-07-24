//
// Created by xXRag on 2021-07-07.
//

#ifndef TESTPROJECT_IMGUILAYER_H
#define TESTPROJECT_IMGUILAYER_H

#include <SDL_video.h>
#include <vendor/imgui/imgui.h>
#include "Layer.h"

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Event& e) override {}
    virtual void OnImGuiRender(Timestep ts) override {}

    void Begin();
    void End();

private:
    SDL_Window* m_pWindow;
    SDL_GLContext m_context;
    std::string m_iniPath = "";
    ImFont* m_pFont;
};


#endif //TESTPROJECT_IMGUILAYER_H
