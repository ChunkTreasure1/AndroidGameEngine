//
// Created by xXRag on 2021-06-22.
//

#ifndef GAMEENGINE_GEOMETRY_H
#define GAMEENGINE_GEOMETRY_H

#include <cstdint>
#include <string>

class Geometry
{
public:
    Geometry();
    virtual ~Geometry();

    void SetName(const std::string& name) { m_name = name; }
    void SetNumVertices(uint32_t i) { m_numVerts = i; }
    void SetNumIndices(uint32_t i) { m_numIndices = i; }

    const std::string& GetName() const { return m_name; }

    const uint32_t GetNumVertices() const { return m_numVerts; }
    const uint32_t GetNumIndices() const { return m_numIndices; }

    void* GetVertexBuffer() const { return m_pVertices; }
    void* GetIndexBuffer() const { return m_pIndices; }

    void SetVertexBuffer(void* pVert) { m_pVertices = pVert; }
    void SetIndexBuffer(void* pInd) { m_pIndices = pInd; }

    inline void SetNumVertexPositionElements(const int el) { m_numVertexPositionElements = el; }
    int GetNumVertexPositionElements() const { return m_numVertexPositionElements; }

    inline void SetNumColorElements(const int col) { m_numColorElements = col; }
    int GetNumColorElements() const { return m_numColorElements; }

    inline void SetNumTexCoordElements(const int tex) { m_numTexCoordElements = tex; }
    int GetNumTexCoordElements() const { return m_numTexCoordElements; }

    void SetVertexStride(const int stride) { m_vertexStride = stride; }
    int GetVertexStride() const { return m_vertexStride; }

private:
    static const uint32_t NAME_MAX_LENGTH = 16;

    std::string m_name;
    uint32_t m_numVerts;
    uint32_t m_numIndices;

    void* m_pVertices;
    void* m_pIndices;

    int m_numVertexPositionElements;
    int m_numColorElements;
    int m_numTexCoordElements;
    int m_vertexStride;
};

#endif //GAMEENGINE_GEOMETRY_H
