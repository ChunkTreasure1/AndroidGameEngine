//
// Created by xXRag on 2021-07-05.
//

#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GLES3/gl3.h>
#include <string>
#include <android/asset_manager.h>
#include <Application/Filesystem/Filesystem.h>
#include <Core.h>

std::tuple<uint32_t, uint32_t, uint32_t> TextureLoader::LoadTexture(const std::string &path)
{
    uint32_t texture;

    //Generate texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //Set texture wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Set filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //Setup file
    AAsset* pFile = Filesystem::Open(path);
    uint32_t size = Filesystem::GetLength(pFile);

    stbi_uc* pFileContent = new unsigned char[size];

    Filesystem::Read(pFile, pFileContent, size);
    Filesystem::Close(pFile);

    //Load file
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* pData = stbi_load_from_memory(pFileContent, size, &width, &height, &channels, 4);

    GLenum dataFormat = 0, internalFormat = 0;
    if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    if (pData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, pData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        LOGE("Failed to load texture!");
    }
    stbi_image_free(pData);

    return std::make_tuple(texture, width, height);
}