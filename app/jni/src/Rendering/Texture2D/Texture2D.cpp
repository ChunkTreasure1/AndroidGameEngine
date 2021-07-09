//
// Created by xXRag on 2021-07-05.
//

#include "Texture2D.h"
#include "TextureCache.h"

Texture2D::Texture2D(const std::string &path)
{
    auto tex = TextureCache::GetTexture(path);
    m_rendererId = std::get<0>(tex);
    m_width = std::get<1>(tex);
    m_height = std::get<2>(tex);
}

Texture2D::Texture2D(uint32_t width, uint32_t height)
    : m_width(width), m_height(height)
{
    m_internalFormat = GL_RGBA8, m_dataFormat = GL_RGBA;

    glGenTextures(1, &m_rendererId);
    glBindTexture(GL_TEXTURE_2D, m_rendererId);

    glTexStorage2D(m_rendererId, 1, m_internalFormat, m_width, m_height);

    //Set texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Set filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture2D::Bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_rendererId);
}

void Texture2D::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::SetData(void *pData, uint32_t size)
{
    glTexSubImage2D(m_rendererId, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, pData);
}