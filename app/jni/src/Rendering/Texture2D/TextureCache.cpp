//
// Created by xXRag on 2021-07-05.
//

#include "TextureCache.h"
#include "TextureLoader.h"

#include <string>

std::map<std::string, std::tuple<uint32_t, uint32_t, uint32_t>> TextureCache::m_textureCache;

std::tuple<uint32_t, uint32_t, uint32_t> TextureCache::GetTexture(const std::string &path)
{
    auto mit =  m_textureCache.find(path);
    if (mit == m_textureCache.end())
    {
        auto tex = TextureLoader::LoadTexture(path);
        m_textureCache.insert(std::make_pair(path, tex));

        return tex;
    }

    return mit->second;
}