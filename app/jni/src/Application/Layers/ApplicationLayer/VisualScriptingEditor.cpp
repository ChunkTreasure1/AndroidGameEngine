//
// Created by Emilia on 2021-07-25.
//

#include "VisualScriptingEditor.h"

#include <imgui.h>
#include <Application/Settings/Language.h>
#include <Application/Events/Event.h>
#include <Core.h>
#include <vendor/imnodes/imnodes.h>
#include <misc/cpp/imgui_stdlib.h>

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

void VisualScriptingEditor::OpenGraph(std::shared_ptr<CodeGraph> &graph)
{
    m_currentlyOpenGraph = graph;

    for (auto& n : graph->GetSpecification().nodes)
    {
        ImNodes::SetNodeEditorSpacePos(n->id, ImVec2{ n->position.x, n->position.y });
    }
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
    UpdateToolsWindow();

    return false;
}

void VisualScriptingEditor::UpdateToolsWindow()
{
    std::string name = Language::GetSymbol("visualScriptingTools"); name += "###visualScriptingTools";
    ImGui::Begin(name.c_str(), &m_isOpen);
    {
        if (ImGui::Button(Language::GetSymbol("visualScriptingCreateVariable")) && m_currentlyOpenGraph != nullptr)
        {
            ImGui::OpenPopup("CreateVariable");
        }
        UpdateCreateVariable();
    }
    ImGui::End();
}

void VisualScriptingEditor::UpdateCreateVariable()
{
    if (ImGui::BeginPopup("CreateVariable"))
    {
        if (m_variableToCreate == nullptr)
        {
            m_variableToCreate = std::make_shared<Variable>();
        }

        //Name
        ImGui::Text("%s", Language::GetSymbol("inputName"));
        ImGui::SameLine();
        ImGui::InputText("", &m_variableToCreate->name);

        //Type
        {
            static int typeCurrSel = -1;
            static int typeLastSel = -1;
            const char* types[] =
                    {
                        Language::GetSymbol("t_integer"),
                        Language::GetSymbol("t_decimal"),
                        Language::GetSymbol("t_bool"),
                        Language::GetSymbol("t_text")
                    };

            ImGui::Text("%s", Language::GetSymbol("vs_type"));
            ImGui::SameLine();
            ImGui::Combo("##typeCombo", &typeCurrSel, types, 4);

            if (typeCurrSel != typeLastSel || !m_variableToCreate->data.has_value())
            {
                switch (typeCurrSel)
                {
                    case 0:
                        m_variableToCreate->type = PropertyType::Integer;
                        m_variableToCreate->data = 0;
                        break;

                    case 1:
                        m_variableToCreate->type = PropertyType::Decimal;
                        m_variableToCreate->data = 0.f;
                        break;

                    case 2:
                        m_variableToCreate->type = PropertyType::Bool;
                        m_variableToCreate->data = false;
                        break;

                    case 3:
                        m_variableToCreate->type = PropertyType::Text;
                        m_variableToCreate->data = "";
                        break;
                }

                typeLastSel = typeCurrSel;
            }
            else
            {
                switch (typeCurrSel)
                {
                    case 0:
                    {
                        ImGui::Text("%s", Language::GetSymbol("vs_value"));
                        ImGui::SameLine();

                        int i = std::any_cast<int>(m_variableToCreate->data);
                        ImGui::InputInt("##vsInputInt", &i);
                        m_variableToCreate->data = i;
                        break;
                    }

                    case 1:
                    {
                        ImGui::Text("%s", Language::GetSymbol("vs_value"));
                        ImGui::SameLine();

                        float i = std::any_cast<float>(m_variableToCreate->data);
                        ImGui::InputFloat("##vsInputFloat", &i);
                        m_variableToCreate->data = i;
                        break;
                    }

                    case 2:
                    {
                        ImGui::Text("%s", Language::GetSymbol("vs_value"));
                        ImGui::SameLine();

                        bool i = std::any_cast<bool>(m_variableToCreate->data);
                        ImGui::Checkbox("##vsInputBool", &i);
                        m_variableToCreate->data = i;
                        break;
                    }

                    case 3:
                    {
                        ImGui::Text("%s", Language::GetSymbol("value"));
                        ImGui::SameLine();

                        std::string i = std::any_cast<std::string>(m_variableToCreate->data);
                        ImGui::InputText("##vsInputText", &i);
                        m_variableToCreate->data = i;
                        break;
                    }
                }
            }
        }

        if (ImGui::Button(Language::GetSymbol("vs_create")))
        {
            m_currentlyOpenGraph->GetSpecification().variables.push_back(std::move(m_variableToCreate));
            m_variableToCreate = nullptr;

            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void VisualScriptingEditor::UpdateNodeWindow()
{
    std::string name = Language::GetSymbol("visualScriptingCode"); name += "###visualScriptingCode1";
    ImGui::Begin(name.c_str(), &m_isOpen);
    {
        ImNodes::BeginNodeEditor();

        //Draw the nodes and links
        if (m_currentlyOpenGraph)
        {
            for (auto& node : m_currentlyOpenGraph->GetSpecification().nodes)
            {
                DrawNode(node);
            }

            for (auto& link : m_currentlyOpenGraph->GetSpecification().links)
            {
                ImNodes::Link(link->id, link->pOutput->id, link->pInput->id);
            }
        }

        ImNodes::EndNodeEditor();

        //Check for new links
        int startAttr, endAttr;
        if (ImNodes::IsLinkCreated(&startAttr, &endAttr))
        {
            Node* pStartNode = nullptr;
            Node* pEndNode = nullptr;

            Attribute* pStartAttr = nullptr;
            Attribute* pEndAttr = nullptr;

            if (m_currentlyOpenGraph)
            {
                for (auto& node : m_currentlyOpenGraph->GetSpecification().nodes)
                {
                    for (uint32_t i = 0; i < node->inputAttributes.size(); i++)
                    {
                        if (node->inputAttributes[i].id == startAttr)
                        {
                            pStartNode = node.get();
                            pStartAttr = &node->inputAttributes[i];

                            break;
                        }

                        if (node->inputAttributes[i].id == endAttr)
                        {
                            pEndNode = node.get();
                            pEndAttr = &node->inputAttributes[i];

                            break;
                        }
                    }

                    for (uint32_t i = 0; i < node->outputAttributes.size(); ++i)
                    {
                        if (node->outputAttributes[i].id == endAttr)
                        {
                            pEndNode = node.get();
                            pEndAttr = &node->outputAttributes[i];

                            break;
                        }

                        if (node->outputAttributes[i].id == startAttr)
                        {
                            pStartNode = node.get();
                            pStartAttr = &node->outputAttributes[i];

                            break;
                        }
                    }
                }

                if (pStartAttr && pEndAttr)
                {
                    if (pStartAttr->type == pEndAttr->type)
                    {
                        std::shared_ptr<Link> link = std::make_shared<Link>();
                        link->id = m_currentlyOpenGraph->GetCurrentId()++;

                        if (auto* p = dynamic_cast<InputAttribute*>(pStartAttr))
                        {
                            link->pInput = p;
                        }

                        if (auto* p = dynamic_cast<OutputAttribute*>(pStartAttr))
                        {
                            link->pOutput = p;
                        }

                        if (auto* p = dynamic_cast<InputAttribute*>(pEndAttr))
                        {
                            link->pInput = p;
                        }

                        if (auto* p = dynamic_cast<OutputAttribute*>(pEndAttr))
                        {
                            link->pOutput = p;
                        }

                        pStartNode->links.push_back(link);
                        pEndNode->links.push_back(link);

                        pStartAttr->links.push_back(link);
                        pEndAttr->links.push_back(link);

                        m_currentlyOpenGraph->GetSpecification().links.push_back(link);
                    }
                }
            }
        }
    }
    ImGui::End();
}

void VisualScriptingEditor::RemoveLink(uint32_t id)
{
    m_currentlyOpenGraph->RemoveLink(id);
}

void VisualScriptingEditor::RemoveNode(uint32_t id)
{
    m_currentlyOpenGraph->RemoveNode(id);
}

void VisualScriptingEditor::DrawNode(std::shared_ptr<Node> &node)
{
    ImNodes::BeginNode(node->id);
    ImVec2 pos = ImNodes::GetNodeEditorSpacePos(node->id);
    if (pos.x != node->position.x || pos.y != node->position.y)
    {
        node->position = { pos.x, pos.y };
    }

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("%s", node->name.c_str());
    ImNodes::EndNodeTitleBar();
}

void VisualScriptingEditor::DrawInput(InputAttribute &attr, std::shared_ptr<Node> &node, bool isProperties) {}

void VisualScriptingEditor::DrawOutput(OutputAttribute &attr, std::shared_ptr<Node> &node, bool isProperties) {}