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
#include <unordered_map>
#include <VisualScripting/NodeRegistry.h>
#include <Application/Input/Input.h>
#include <SDL.h>

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
    if (m_nodeToCreate != nullptr)
    {
        if (m_currentlyOpenGraph == nullptr)
        {
            m_nodeToCreate = nullptr;
        }
        else
        {
            static int frameCount = 0;
            ImNodes::SetNodeScreenSpacePos(m_nodeToCreate->id, ImGui::GetMousePos());

            if (Input::IsMouseButtonPressed(SDL_BUTTON_LMASK) && frameCount > 10)
            {
                m_currentlyOpenGraph->GetSpecification().nodes.push_back(m_nodeToCreate);
                frameCount = 0;
                m_nodeToCreate = nullptr;
            }

            if (Input::IsMouseButtonPressed(SDL_BUTTON_RMASK))
            {
                m_nodeToCreate = nullptr;
            }

            frameCount++;
        }
    }

    if (Input::IsKeyPressed(SDL_SCANCODE_DELETE))
    {
        const int numSelectedNodes = ImNodes::NumSelectedNodes();
        if (numSelectedNodes > 0)
        {
            std::vector<int> selectedNodes;
            selectedNodes.resize(numSelectedNodes);

            ImNodes::GetSelectedNodes(selectedNodes.data());

            for (auto& node : selectedNodes)
            {
                RemoveNode(node);
            }
        }

        const int numSelectedLinks = ImNodes::NumSelectedLinks();
        if (numSelectedLinks > 0)
        {
            std::vector<int> selectedLinks;
            selectedLinks.resize(numSelectedLinks);

            ImNodes::GetSelectedLinks(selectedLinks.data());
            for (auto& link : selectedLinks)
            {
                RemoveLink(link);
            }
        }
    }

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
    UpdateTextCodeWindow();
    UpdateVariableList();
    UpdateNodeList();

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

void VisualScriptingEditor::UpdateTextCodeWindow()
{
    ImGui::Begin("TextCode");
    {
        if (m_currentlyOpenGraph)
        {
            auto startNodes = NodeRegistry::s_startNodes();
            if (startNodes.size() > 0)
            {
                auto code = startNodes[0]->CreateCode();
                for (auto line : code)
                {
                    ImGui::Text("%s", line.second.c_str());
                }
            }
        }
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

        static bool canCreate = true;

        //Name
        ImGui::Text("%s", Language::GetSymbol("inputName"));
        ImGui::SameLine();
        ImGui::InputText("", &m_variableToCreate->name);

        //Check if name already exists
        for (auto& var : m_currentlyOpenGraph->GetSpecification().variables)
        {
            if (var->name == m_variableToCreate->name)
            {
                canCreate = false;
                ImGui::TextColored(ImVec4 { 1.f, 0.f, 0.f, 1.f }, "%s", Language::GetSymbol("vs_nameExists"));
            }
            else
            {
                canCreate = true;
            }
        }

        //Type
        ShowTypeSelect(m_variableToCreate);

        if (ImGui::Button(Language::GetSymbol("vs_create")) && canCreate)
        {
            m_currentlyOpenGraph->GetSpecification().variables.push_back(std::move(m_variableToCreate));
            m_variableToCreate = nullptr;

            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void VisualScriptingEditor::ShowTypeSelect(std::shared_ptr<Variable> &var)
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

    if (typeCurrSel != typeLastSel || !var->data.has_value())
    {
        switch (typeCurrSel)
        {
            case 0:
                var->type = PropertyType::Integer;
                var->data = 0;
                break;

            case 1:
                var->type = PropertyType::Decimal;
                var->data = 0.f;
                break;

            case 2:
                var->type = PropertyType::Bool;
                var->data = false;
                break;

            case 3:
                var->type = PropertyType::Text;
                var->data = "";
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

                int i = std::any_cast<int>(var->data);
                ImGui::InputInt("##vsInputInt", &i);
                var->data = i;
                break;
            }

            case 1:
            {
                ImGui::Text("%s", Language::GetSymbol("vs_value"));
                ImGui::SameLine();

                float i = std::any_cast<float>(var->data);
                ImGui::InputFloat("##vsInputFloat", &i);
                var->data = i;
                break;
            }

            case 2:
            {
                ImGui::Text("%s", Language::GetSymbol("vs_value"));
                ImGui::SameLine();

                bool i = std::any_cast<bool>(var->data);
                ImGui::Checkbox("##vsInputBool", &i);
                var->data = i;
                break;
            }

            case 3:
            {
                ImGui::Text("%s", Language::GetSymbol("value"));
                ImGui::SameLine();

                std::string i = std::any_cast<std::string>(var->data);
                ImGui::InputText("##vsInputText", &i);
                var->data = i;
                break;
            }
        }
    }
}

void VisualScriptingEditor::UpdateNodeList()
{
    ImGui::Begin("Nodes");
    if (ImGui::TreeNode("Nodes"))
    {
        std::unordered_map<std::string, std::vector<std::pair<std::string, NodeRegistry::CreateMethod>>> sorted;
        for (auto& key : NodeRegistry::s_methods())
        {
            sorted[NodeRegistry::GetCategory(key.first)].push_back(key);
        }

        static ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;


        int i = 0;
        for (auto& key :sorted)
        {
            if (ImGui::TreeNode(key.first.c_str()))
            {
                for (auto& p : key.second)
                {
                    ImGui::TreeNodeEx((void*)i, nodeFlags, "%s", p.first.c_str());
                    if (ImGui::IsItemClicked() && m_currentlyOpenGraph)
                    {
                        std::shared_ptr<Node> n = p.second();
                        n->id = m_currentlyOpenGraph->GetCurrentId()++;

                        for (int i = 0; i < n->inputAttributes.size(); ++i)
                        {
                            n->inputAttributes[i].id = m_currentlyOpenGraph->GetCurrentId()++;
                        }

                        for (int i = 0; i < n->outputAttributes.size(); ++i)
                        {
                            n->outputAttributes[i].id = m_currentlyOpenGraph->GetCurrentId()++;
                        }

                        m_nodeToCreate = n;
                    }
                    i++;
                }

                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }
    ImGui::End();
}

void VisualScriptingEditor::UpdateVariableList()
{
    std::string name = Language::GetSymbol("vs_varList"); name += "###varList";
    ImGui::Begin(name.c_str(), &m_isOpen);
    {
        if (m_currentlyOpenGraph != nullptr)
        {
            for (auto& var : m_currentlyOpenGraph->GetSpecification().variables)
            {
                if (ImGui::CollapsingHeader(var->name.c_str()))
                {
                    ShowTypeSelect(var);
                }
            }
        }
    }
    ImGui::End();
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

            if (m_nodeToCreate)
            {
                DrawNode(m_nodeToCreate);
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

        //Check for selected nodes
        const int numSelectedNodes = ImNodes::NumSelectedNodes();
        if (numSelectedNodes == 1)
        {
            int selNode = 0;
            ImNodes::GetSelectedNodes(&selNode);

            for (auto& node : m_currentlyOpenGraph->GetSpecification().nodes)
            {
                if (node->id == selNode)
                {
                    m_selectedNode = node;
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

    node->DrawContent();

    ImNodes::EndNode();
}

void VisualScriptingEditor::DrawInput(InputAttribute &attr, std::shared_ptr<Node> &node, bool isProperties) {}

void VisualScriptingEditor::DrawOutput(OutputAttribute &attr, std::shared_ptr<Node> &node, bool isProperties) {}