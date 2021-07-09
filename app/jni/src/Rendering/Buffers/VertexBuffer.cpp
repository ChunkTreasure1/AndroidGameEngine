//
// Created by xXRag on 2021-07-04.
//

#include "VertexBuffer.h"

#include <GLES3/gl3.h>

/////Vertex Buffer/////
VertexBuffer::VertexBuffer(uint32_t size)
{
    glGenBuffers(1, &m_rendererId);

    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(float *pVertices, uint32_t size)
{
    glGenBuffers(1, &m_rendererId);

    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, pVertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_rendererId);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void *pData, uint32_t size)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, pData);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
    return std::make_shared<VertexBuffer>(size);
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(float *pVertices, uint32_t size)
{
    return std::make_shared<VertexBuffer>(pVertices, size);
}

/////Index Buffer/////
IndexBuffer::IndexBuffer(uint32_t *pIndices, uint32_t count)
    : m_count(count)
{
    glGenBuffers(1, &m_rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), pIndices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_rendererId);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t *pIndices, uint32_t count)
{
    return std::make_shared<IndexBuffer>(pIndices, count);
}