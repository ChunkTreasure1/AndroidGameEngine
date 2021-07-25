//
// Created by Emilia on 2021-07-25.
//

#include "VisualScriptingEditor.h"

#include <imgui.h>
#include <Application/Settings/Language.h>

VisualScriptingEditor::~VisualScriptingEditor()
{

}

VisualScriptingEditor::VisualScriptingEditor()
    : m_isOpen(true)
{

}

void VisualScriptingEditor::OnEvent(Event &e)
{
    EventDispatcher dispatcher;
    dispatcher.Dispatch<AppUpdateEvent>(LP_BIND_EVENT_FUNC(VisualScriptingEditor::OnUpdate));
    dispatcher.Dispatch<ImGuiUpdateEvent>(LP_BIND_EVENT_FUNC(VisualScriptingEditor::OnImGuiUpdate));
}

bool VisualScriptingEditor::OnUpdate(AppUpdateEvent& e)
{
    return false;
}

bool VisualScriptingEditor::OnImGuiUpdate(ImGuiUpdateEvent& e)
{
    if (!m_isOpen)
        return false;

    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    std::string name = Language::GetSymbol("visualScripting"); name += "###visualScripting";
    ImGui::Begin(name.c_str(), &m_isOpen);
    ImGui::PopStyleVar();
    {
        ImGuiIO& io ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspaceId = ImGui::GetID(name.c_str());
            ImGui::DockSpace(dockspaceId, ImVec2(0.f, 0.f), dockspaceFlags);
        }
    }
    ImGui::End();

    return false;
}