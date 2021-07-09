//
// Created by xXRag on 2021-07-05.
//

#ifndef TESTPROJECT_TEXTURELOADER_H
#define TESTPROJECT_TEXTURELOADER_H

#include <tuple>

class TextureLoader
{
public:
    static std::tuple<uint32_t, uint32_t, uint32_t> LoadTexture(const std::string& path);
};


#endif //TESTPROJECT_TEXTURELOADER_H
