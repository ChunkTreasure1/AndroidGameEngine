//
// Created by xXRag on 2021-07-07.
//

#include <Application/UI/UIUtility.h>
#include <Application/Layers/ApplicationLayer.h>
#include <Application/Settings/Language.h>
#include <Application/Settings/Settings.h>
#include <Application/Application.h>

#include <misc/cpp/imgui_stdlib.h>
#include <glm/gtc/type_ptr.hpp>

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

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu(Language::GetSymbol("file")))
            {
                ImGui::MenuItem(Language::GetSymbol("settings"), NULL, &m_settingsOpen);

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu(Language::GetSymbol("tools")))
            {
                ImGui::MenuItem(Language::GetSymbol("basetools"), NULL, &m_baseToolsOpen);
                ImGui::MenuItem(Language::GetSymbol("objectsPanel"), NULL, &m_objectsPanelOpen);
                ImGui::MenuItem(Language::GetSymbol("visualScripting"), NULL, &m_pVisualScriptingWindow->GetIsOpen());
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();
    }
}

void ApplicationLayer::RenderViewport()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    std::string name = Language::GetSymbol("viewport"); name += "###viewport";
    ImGui::Begin(name.c_str());
    {
        ImVec2 perspectivePanelSize = ImGui::GetContentRegionAvail();
        if (m_lastPerspectiveSize.x != perspectivePanelSize.x || m_lastPerspectiveSize.y != perspectivePanelSize.y)
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

void ApplicationLayer::RenderSettings()
{
    if (!m_settingsOpen)
        return;

    std::string name = Language::GetSymbol("settings"); name += "###settings";
    ImGui::Begin(name.c_str(), &m_settingsOpen);
    {
        if (UI::BeginProperties())
        {
            /////Theme/////
            {
                static int themeCurrSelected = 0;
                static int themeLastSelected = 0;

                std::vector<const char*> themeItems = { Language::GetSymbol("theme_dark"), Language::GetSymbol("theme_light")};

                if (UI::Combo(Language::GetSymbol("theme"), themeCurrSelected, themeItems))
                {
                    if (themeCurrSelected == 0)
                    {
                        Settings::SetTheme("dark");
                    }
                    else if (themeCurrSelected == 1)
                    {
                        Settings::SetTheme("light");
                    }

                    themeLastSelected = themeCurrSelected;
                }
            }
            ///////////////

            /////Language/////
            {
                static int langCurrSelected = 1;
                static int langLastSelected = 1;
                std::vector<const char*> langItems = { "English", "Svenska" };

                if (UI::Combo(Language::GetSymbol("language"), langCurrSelected, langItems))
                {
                    if (langLastSelected != langCurrSelected)
                    {
                        if (langCurrSelected == 0)
                        {
                            Language::LoadLanguage("en");
                        }
                        else if (langCurrSelected == 1)
                        {
                            Language::LoadLanguage("sv");
                        }

                        langLastSelected = langCurrSelected;
                    }
                }
            }
            //////////////////

            UI::EndProperties();
        }
    }
    ImGui::End();
}

void ApplicationLayer::RenderBaseTools()
{
    if (!m_baseToolsOpen)
    {
        return;
    }

    std::string name = Language::GetSymbol("basetools"); name += "###baseTools";
    ImGui::Begin(name.c_str(), &m_baseToolsOpen);
    {
        if (ImGui::Button(Language::GetSymbol("addObject")))
        {
            Object* obj = new Object("Object" + std::to_string(m_list.size()));
            m_list.push_back(obj);
        }
    }
    ImGui::End();
}

void ApplicationLayer::RenderObjectsPanel()
{
    if (!m_objectsPanelOpen)
        return;

    std::string name = Language::GetSymbol("objectsPanel"); name += "###objectsPanel";
    ImGui::Begin(name.c_str(), &m_objectsPanelOpen);
    {
        for (int i = 0; i < m_list.size(); ++i)
        {

            ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            ImGui::TreeNodeEx((void*)(intptr_t)i, nodeFlags, "%s", m_list[i]->GetName().c_str());

            if (ImGui::IsItemClicked())
            {
                m_pSelectedObject = m_list[i];
            }
        }
    }
    ImGui::End();
}

void ApplicationLayer::RenderObjectProperties()
{
    if (!m_objectPropertiesOpen)
        return;

    std::string name = Language::GetSymbol("objectProperties"); name += "###objectProperties";
    ImGui::Begin(name.c_str(), &m_objectPropertiesOpen);
    {
        if (m_pSelectedObject != nullptr)
        {
            std::string objName = m_pSelectedObject->GetName();
            ImGui::InputText("##objName",&objName);
            m_pSelectedObject->SetName(objName);

            if (ImGui::CollapsingHeader(Language::GetSymbol("transform"), ImGuiTreeNodeFlags_DefaultOpen))
            {
                UI::PushId();

                if (UI::BeginProperties("", false))
                {
                    UI::PropertyAxisColor(Language::GetSymbol("position"), const_cast<glm::vec2&>(m_pSelectedObject->GetPosition()));
                    UI::Property(Language::GetSymbol("rotation"), const_cast<float&>(m_pSelectedObject->GetRotation()));
                    UI::PropertyAxisColor(Language::GetSymbol("scale"), const_cast<glm::vec2&>(m_pSelectedObject->GetScale()));

                    m_pSelectedObject->UpdateTransform();

                    UI::EndProperties(false);
                }

                UI::PopId();
            }

            if (ImGui::CollapsingHeader(Language::GetSymbol("settings")))
            {
                UI::BeginProperties();

                UI::PropertyColor(Language::GetSymbol("color"), const_cast<glm::vec4&>(m_pSelectedObject->GetColor()));
                UI::Property(Language::GetSymbol("isSprite"), const_cast<bool&>(m_pSelectedObject->GetIsSprite()));

                UI::EndProperties();
            }

            if (ImGui::CollapsingHeader(Language::GetSymbol("visualScriptingCode")))
            {
                if (m_pSelectedObject->GetCodeGraph() == nullptr)
                {
                    if (ImGui::Button(Language::GetSymbol("visualScriptingCreate")))
                    {
                        m_pSelectedObject->SetCodeGraph(std::make_shared<CodeGraph>());
                    }
                }
                else
                {
                    if (ImGui::Button(Language::GetSymbol("visualScriptingOpen")))
                    {
                        m_pVisualScriptingWindow->OpenGraph(m_pSelectedObject->GetCodeGraph());
                    }
                }
            }
        }
        else
        {
            ImGui::Text("%s", Language::GetSymbol("selectObjectText"));
        }
    }
    ImGui::End();
}