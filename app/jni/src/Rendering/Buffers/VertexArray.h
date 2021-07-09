//
// Created by xXRag on 2021-07-04.
//

#ifndef TESTPROJECT_VERTEXARRAY_H
#define TESTPROJECT_VERTEXARRAY_H

#include "VertexBuffer.h"

#include <memory>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void Bind();
    void Unbind();

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

    std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() { return m_vertexBuffers; }
    std::shared_ptr<IndexBuffer>& GetIndexBuffer() { return m_indexBuffer; }

public:
    static std::shared_ptr<VertexArray> Create();

private:
    uint32_t m_rendererId;
    uint32_t m_numAttributes = 0;

    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
};


#endif //TESTPROJECT_VERTEXARRAY_H
