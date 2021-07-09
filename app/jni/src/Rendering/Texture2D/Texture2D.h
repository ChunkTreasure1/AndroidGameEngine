//
// Created by xXRag on 2021-07-05.
//

#ifndef TESTPROJECT_TEXTURE2D_H
#define TESTPROJECT_TEXTURE2D_H


#include <cstdint>
#include <GLES3/gl3.h>
#include <string>

class Texture2D
{
public:
    Texture2D(const std::string& path);
    Texture2D(uint32_t width, uint32_t height);

    void Bind(uint32_t slot = 0) const;
    void Unbind();

    void SetData(void* pData, uint32_t size);
    bool operator==(const Texture2D& other) const
    {
        return m_rendererId == other.GetId();
    }

    //Getting
    inline const uint32_t GetWidth() const { return m_width; }
    inline const uint32_t GetHeight() const { return m_height; }
    inline const uint32_t GetId() const { return m_rendererId; }

public:
    static std::shared_ptr<Texture2D> Create(uint32_t width, uint32_t height) { return std::make_shared<Texture2D>(width, height); }
    static std::shared_ptr<Texture2D> Create(const std::string& path) { return std::make_shared<Texture2D>(path); }

private:
    uint32_t m_rendererId;
    uint32_t m_width;
    uint32_t m_height;

    GLenum m_internalFormat;
    GLenum m_dataFormat;
};


#endif //TESTPROJECT_TEXTURE2D_H
