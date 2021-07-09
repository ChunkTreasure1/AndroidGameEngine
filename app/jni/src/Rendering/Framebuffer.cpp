//
// Created by xXRag on 2021-07-07.
//

#include "Framebuffer.h"

#include <GLES3/gl3.h>

Framebuffer::Framebuffer(const uint32_t width, const uint32_t height)
    : m_height(height), m_width(width)
{
    Invalidate();
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &m_rendererId);
}

void Framebuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
}

void Framebuffer::Unbind()
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Update(const uint32_t width, const uint32_t height)
{
    m_width = width;
    m_height = height;

    Invalidate();
    glViewport(0, 0, m_width, m_height);
}

void Framebuffer::Invalidate()
{
    if (m_rendererId < 0 && m_texture < 0)
    {
        glDeleteTextures(1, &m_texture);
        glDeleteFramebuffers(1, &m_rendererId);
    }
    glGenFramebuffers(1, &m_rendererId);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

std::shared_ptr<Framebuffer> Framebuffer::Create(const uint32_t width, const uint32_t height)
{
    return std::make_shared<Framebuffer>(width, height);
}
