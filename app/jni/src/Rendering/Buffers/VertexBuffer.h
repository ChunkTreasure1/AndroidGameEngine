//
// Created by xXRag on 2021-07-04.
//

#ifndef TESTPROJECT_VERTEXBUFFER_H
#define TESTPROJECT_VERTEXBUFFER_H

#include "BufferLayout.h"

class VertexBuffer
{
public:
    VertexBuffer(float* pVertices, uint32_t size);
    VertexBuffer(uint32_t size);

    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    inline void SetBufferLayout(const BufferLayout& buff) { m_layout = buff; }
    inline BufferLayout& GetLayout() { return m_layout; }

    void SetData(const void* pData, uint32_t size);

public:
    static std::shared_ptr<VertexBuffer> Create(uint32_t size);
    static std::shared_ptr<VertexBuffer> Create(float* pVertices, uint32_t size);

private:
    uint32_t m_rendererId;
    BufferLayout m_layout;
};

class IndexBuffer
{
public:
    IndexBuffer(uint32_t* pIndices, uint32_t count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    uint32_t GetCount() { return m_count; }

public:
    static std::shared_ptr<IndexBuffer> Create(uint32_t* pIndices, uint32_t count);

private:
    uint32_t m_rendererId;
    uint32_t m_count;
};

#endif //TESTPROJECT_VERTEXBUFFER_H
