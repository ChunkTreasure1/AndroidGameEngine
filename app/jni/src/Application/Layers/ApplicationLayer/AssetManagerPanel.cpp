//
// Created by chunktreasure on 8/22/21.
//

#include "AssetManagerPanel.h"
#include <Application/Settings/Settings.h>
#include <imgui.h>
#include <Application/Settings/Language.h>

AssetManagerPanel::AssetManagerPanel()
        : m_currentDirectory(Settings::GetFilesPath())
{
    m_directoryTexture = Texture2D::Create("textures/ui/directoryIcon.png");
    m_fileTexture = Texture2D::Create("textures/ui/files.png");
}

void AssetManagerPanel::OnImGuiRender()
{
    std::string name = Language::GetSymbol("am_assetManager"); name += "###assetManager";
    ImGui::Begin(name.c_str(), &m_isOpen);

    if (m_currentDirectory != std::filesystem::path(Settings::GetFilesPath()))
    {
        if (ImGui::Button("<-"))
        {
            m_currentDirectory = m_currentDirectory.parent_path();
        }
    }

    static float padding = 16.f;
    static float thumbnailSize = 100.f;

    float cellSize = thumbnailSize + padding;
    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int)(panelWidth / cellSize);
    if (columnCount < 1)
    {
        columnCount = 1;
    }

    ImGui::Columns(columnCount, 0, false);
    static bool fileHovered = false;
    static std::filesystem::path savedPath = "";

    for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentDirectory))
    {
        const auto& path = directoryEntry.path();
        auto relativePath = std::filesystem::relative(path, Settings::GetFilesPath());
        std::string filenameString = relativePath.filename().string();

        ImGui::PushID(filenameString.c_str());

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.f, 0.f, 0.f, 0.f });
        std::shared_ptr<Texture2D> icon = directoryEntry.is_directory() ? m_directoryTexture : m_fileTexture;
        ImGui::ImageButton((ImTextureID)icon->GetId(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

        ImGui::PopStyleColor();
        fileHovered = ImGui::IsItemHovered();

        if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && fileHovered)
        {
            if  (directoryEntry.is_directory())
            {
                m_currentDirectory /= path.filename();
            }
            else
            {
                //open
            }
        }

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && fileHovered)
        {
            ImGui::OpenPopup("am_rightClick");
        }
        UpdateRightClick(fileHovered, path);

        ImGui::TextWrapped("%s", filenameString.c_str());

        ImGui::NextColumn();
        ImGui::PopID();
    }
    fileHovered = false;
    ImGui::Columns(1);

    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right) && !fileHovered)
    {
        ImGui::OpenPopup("am_rightClick");
    }
    UpdateRightClick(false, "");

    ImGui::End();
}

void AssetManagerPanel::UpdateRightClick(bool hovered, std::filesystem::path path)
{
    if (ImGui::BeginPopup("am_rightClick"))
    {
        if (hovered)
        {
            static std::string sCreate = Language::GetSymbol("am_create"); sCreate += "###am_create";
            static std::string sDir = Language::GetSymbol("am_createDir"); sDir += "###am_createDir";
            if (ImGui::BeginMenu(sCreate.c_str()))
            {
                if (ImGui::Selectable(sDir.c_str()))
                {
                    std::string dir = Settings::GetFilesPath() + "/directory";
                    std::filesystem::create_directory(dir.c_str());
                }

                ImGui::EndMenu();
            }
        }
        else
        {
            if (ImGui::Selectable("Delete"))
            {
                std::filesystem::remove(path);
            }
        }

        ImGui::EndPopup();
    }
}