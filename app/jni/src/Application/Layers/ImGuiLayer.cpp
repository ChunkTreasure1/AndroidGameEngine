//
// Created by xXRag on 2021-07-07.
//

#include "ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_opengl3.h>

#include <Application/Application.h>
#include <Application/Settings/Settings.h>

ImGuiLayer::ImGuiLayer()
{}

ImGuiLayer::~ImGuiLayer()
{}

void ImGuiLayer::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    m_iniPath = Settings::GetFilePath() + "/imgui.ini";
    io.IniFilename = m_iniPath.c_str();

    //Set the style
    Settings::SetTheme("dark");

    //Set the window rounding
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.f;
        style.Colors[ImGuiCol_WindowBg].w = 1.f;
    }

    style.ChildRounding = 4.0f;
    style.FrameBorderSize = 1.0f;
    style.FrameRounding = 2.0f;
    style.GrabMinSize = 7.0f;
    style.PopupRounding = 2.0f;
    style.ScrollbarRounding = 12.0f;
    style.ScrollbarSize = 13.0f;
    style.TabBorderSize = 1.0f;
    style.TabRounding = 1.0f;
    style.WindowRounding = 4.0f;

    m_pWindow = Application::Get().GetWindow()->GetNativeWindow();
    m_context = Application::Get().GetWindow()->GetGLConxtext();

    ImGui_ImplSDL2_InitForOpenGL(m_pWindow, m_context);
    ImGui_ImplOpenGL3_Init(NULL);
}

void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_pWindow);
    ImGui::NewFrame();
}

void ImGuiLayer::End()
{
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();

    io.DisplaySize = ImVec2((float)app.GetWindow()->GetWidth(), (float)app.GetWindow()->GetHeight());

    //Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();

        SDL_GL_MakeCurrent(m_pWindow, m_context);
    }
}