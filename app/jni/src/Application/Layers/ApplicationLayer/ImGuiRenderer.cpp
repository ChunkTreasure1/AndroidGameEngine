//
// Created by xXRag on 2021-07-07.
//

#include <Application/Layers/ApplicationLayer.h>

void ApplicationLayer::CreateDockspace()
{
    static bool optFullscreenPersistant = true;
    bool optFullscreen = optFullscreenPersistant;
    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (optFullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);

        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiTableColumnFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
        {
            windowFlags |= ImGuiWindowFlags_NoBackground;
        }

        bool pp = true;
        bool* p = &pp;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        ImGui::Begin("Dockspace", p, windowFlags);
        ImGui::PopStyleVar();

        if (optFullscreen)
        {
            ImGui::PopStyleVar(2);
        }

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspaceId = ImGui::GetID("Dockspace");
            ImGui::DockSpace(dockspaceId, ImVec2(0.f, 0.f), dockspaceFlags);
        }

        ImGui::End();
    }
}

void ApplicationLayer::RenderViewport()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Perspective");
    {
        ImVec2 perspectivePanelSize = ImGui::GetContentRegionAvail();
        if (m_lastPerspectiveSize.x != perspectivePanelSize.x && m_lastPerspectiveSize.y != perspectivePanelSize.y)
        {
            m_viewportBuffer->Update((uint32_t)perspectivePanelSize.x, (uint32_t)perspectivePanelSize.y);
            m_lastPerspectiveSize = perspectivePanelSize;

            m_cameraController.SetAspectRatio((float)perspectivePanelSize.x / (float)perspectivePanelSize.y);
        }

        uint32_t texId = m_viewportBuffer->GetTexture();
        ImGui::Image((void*)(uint32_t)texId, ImVec2 { perspectivePanelSize.x, perspectivePanelSize.y }, ImVec2{0, 1}, ImVec2{1, 0});
    }
    ImGui::End();
    ImGui::PopStyleVar();
}