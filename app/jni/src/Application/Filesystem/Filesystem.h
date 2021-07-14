//
// Created by ivar on 2021-07-14.
//

#ifndef TESTPROJECT_FILESYSTEM_H
#define TESTPROJECT_FILESYSTEM_H

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <string>

class Filesystem
{
public:
    static AAsset* Open(const std::string& path);
    static uint32_t GetLength(AAsset* pAsset);
    static void Read(AAsset* pAsset, void* pData, uint32_t length);
    static void Close(AAsset* pAsset);

    static void SetAssetManager(AAssetManager* pManager);

private:
    static AAssetManager* s_pAssetManager;
};


#endif //TESTPROJECT_FILESYSTEM_H
