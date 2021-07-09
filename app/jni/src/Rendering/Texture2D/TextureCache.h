//
// Created by xXRag on 2021-07-05.
//

#ifndef TESTPROJECT_TEXTURECACHE_H
#define TESTPROJECT_TEXTURECACHE_H

#include <tuple>
#include <map>

class TextureCache
{
public:
    static std::tuple<uint32_t, uint32_t, uint32_t> GetTexture(const std::string& path);

private:
    static std::map<std::string, std::tuple<uint32_t, uint32_t, uint32_t>> m_textureCache;
};


#endif //TESTPROJECT_TEXTURECACHE_H
