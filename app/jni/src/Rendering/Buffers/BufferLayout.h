//
// Created by xXRag on 2021-07-04.
//

#ifndef TESTPROJECT_BUFFERLAYOUT_H
#define TESTPROJECT_BUFFERLAYOUT_H

#include <string>
#include <vector>

enum class ElementType
{
    Int,
    Bool,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4
};

static uint32_t GetSizeFromType(ElementType elementType)
{
    switch (elementType)
    {
        case ElementType::Bool: return 1;
        case ElementType::Int: return 4;
        case ElementType::Float: return 4;
        case ElementType::Float2: return 4 * 2;
        case ElementType::Float3: return 4 * 3;
        case ElementType::Float4: return 4 * 4;
        case ElementType::Mat3: return 4 * 3 * 3;
        case ElementType::Mat4: return 4 * 4 * 4;
    }

    return 0;
}

struct BufferElement
{
    BufferElement(ElementType type, const std::string& name, bool normalized = false)
        : Name(name), Type(type), Normalized(normalized), Size(GetSizeFromType(type)), Offset(0)
    {}

    uint32_t GetComponentCount(ElementType type)
    {
        switch (type)
        {
            case ElementType::Bool: return 1;
            case ElementType::Int: return 1;
            case ElementType::Float: return 1;
            case ElementType::Float2: return 2;
            case ElementType::Float3: return 3;
            case ElementType::Float4: return 4;
            case ElementType::Mat3: return 3 * 3;
            case ElementType::Mat4: return 4 * 4;
        }

        return 0;
    }

    bool Normalized = false;
    std::string Name;
    size_t Offset;
    uint32_t Size;
    ElementType Type;
};

class BufferLayout
{
public:
    BufferLayout() {}

    BufferLayout(std::initializer_list<BufferElement> elements)
        : m_elements(elements)
    {
        CalculateOffsetAndStride();
    }

    inline uint32_t GetStride() const { return m_stride; }
    inline std::vector<BufferElement>& GetElements() { return m_elements; }

private:
    void CalculateOffsetAndStride()
    {
        size_t offset = 0;
        m_stride = 0;

        for (auto& element : m_elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_stride += element.Size;
        }
    }

private:
    std::vector<BufferElement> m_elements;
    uint32_t m_stride;
};

#endif //TESTPROJECT_BUFFERLAYOUT_H
