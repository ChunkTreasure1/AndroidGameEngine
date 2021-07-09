//
// Created by xXRag on 2021-07-04.
//

#include "VertexArray.h"

#include <GLES3/gl3.h>

static GLenum ElementTypeToGLEnum(ElementType type)
{
    switch (type)
    {
        case ElementType::Bool: return GL_BOOL;
        case ElementType::Int: return GL_INT;
        case ElementType::Float: return GL_FLOAT;
        case ElementType::Float2: return GL_FLOAT;
        case ElementType::Float3: return GL_FLOAT;
        case ElementType::Float4: return GL_FLOAT;
        case ElementType::Mat3: return GL_FLOAT;
        case ElementType::Mat4: return GL_FLOAT;
    }
}

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_rendererId);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_rendererId);
}

void VertexArray::Bind()
{
    glBindVertexArray(m_rendererId);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
{
    glBindVertexArray(m_rendererId);
    vertexBuffer->Bind();

    for (auto& element : vertexBuffer->GetLayout().GetElements())
    {
        glVertexAttribPointer(m_numAttributes,
                              element.GetComponentCount(element.Type),
                              ElementTypeToGLEnum(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              vertexBuffer->GetLayout().GetStride(),
                              (const void*)element.Offset);

        glEnableVertexAttribArray(m_numAttributes);
        m_numAttributes++;
    }

    m_vertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
{
    glBindVertexArray(m_rendererId);
    indexBuffer->Bind();

    m_indexBuffer = indexBuffer;
}

std::shared_ptr<VertexArray> VertexArray::Create()
{
    return std::make_shared<VertexArray>();
}