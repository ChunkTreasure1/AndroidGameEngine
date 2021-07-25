//
// Created by Emilia on 2021-07-25.
//

#include "VisualScriptingEditor.h"

#include <imgui.h>
#include <Application/Settings/Language.h>
#include <Application/Events/Event.h>
#include <Core.h>
#include <vendor/imnodes/imnodes.h>

VisualScriptingEditor::VisualScriptingEditor()
        : m_isOpen(true)
{

}

VisualScriptingEditor::~VisualScriptingEditor()
{

}

void VisualScriptingEditor::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<AppUpdateEvent>(LP_BIND_EVENT_FN(VisualScriptingEditor::OnUpdate));
    dispatcher.Dispatch<ImGuiUpdateEvent>(LP_BIND_EVENT_FN(VisualScriptingEditor::OnImGuiUpdate));
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
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspaceId = ImGui::GetID(name.c_str());
            ImGui::DockSpace(dockspaceId, ImVec2(0.f, 0.f), dockspaceFlags);
        }
    }
    ImGui::End();

    UpdateNodeWindow();

    return false;
}

void VisualScriptingEditor::UpdateNodeWindow()
{
    std::string name = Language::GetSymbol("visualScriptingCode"); name += "###visualScriptingCode";
    ImGui::Begin(name.c_str(), &m_isOpen);
    {
/*        ImNodes::BeginNodeEditor();
        ImNodes::EndNodeEditor();*/
    }
    ImGui::End();
}