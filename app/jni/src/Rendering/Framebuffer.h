//
// Created by xXRag on 2021-07-07.
//

#ifndef TESTPROJECT_FRAMEBUFFER_H
#define TESTPROJECT_FRAMEBUFFER_H

#include <cstdint>
#include <memory>

class Framebuffer
{
public:
    Framebuffer(const uint32_t width, const uint32_t height);
    ~Framebuffer();

    void Bind();
    void Unbind();
    void Update(const uint32_t width, const uint32_t height);

    inline uint32_t GetTexture() { return m_texture; }

private:
    void Invalidate();

public:
    static std::shared_ptr<Framebuffer> Create(const uint32_t width, const uint32_t height);

private:
    uint32_t m_rendererId = -1;
    uint32_t m_texture = -1;

    uint32_t m_width;
    uint32_t m_height;
};


#endif //TESTPROJECT_FRAMEBUFFER_H
