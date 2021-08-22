//
// Created by chunktreasure on 8/22/21.
//

#ifndef TESTPROJECT_ASSETMANAGERPANEL_H
#define TESTPROJECT_ASSETMANAGERPANEL_H

#include <filesystem>
#include <Rendering/Texture2D/Texture2D.h>

class AssetManagerPanel
{
public:
    AssetManagerPanel();

    void OnImGuiRender();

private:
    void UpdateRightClick(bool hovered = false, std::filesystem::path path = "");

private:
    bool m_isOpen = true;
    std::filesystem::path m_currentDirectory;
    std::shared_ptr<Texture2D> m_directoryTexture;
    std::shared_ptr<Texture2D> m_fileTexture;
};

#endif //TESTPROJECT_ASSETMANAGERPANEL_H
