//
// Created by ivar on 2021-07-14.
//

#include "Filesystem.h"

AAssetManager* Filesystem::s_pAssetManager = nullptr;

AAsset * Filesystem::Open(const std::string &path)
{
    return AAssetManager_open(s_pAssetManager, path.c_str(), AASSET_MODE_BUFFER);
}

void Filesystem::Read(AAsset *pAsset, void *pData, uint32_t length)
{
    AAsset_read(pAsset, pData, length);
}

uint32_t Filesystem::GetLength(AAsset *pAsset)
{
    return AAsset_getLength(pAsset);
}

void Filesystem::Close(AAsset *pAsset)
{
    AAsset_close(pAsset);
}

void Filesystem::SetAssetManager(AAssetManager *pManager)
{
    s_pAssetManager = pManager;
}