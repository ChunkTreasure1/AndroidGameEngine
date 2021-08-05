//
// Created by ivar on 2021-07-25.
//

#ifndef TESTPROJECT_NODE_H
#define TESTPROJECT_NODE_H

#include <memory>
#include <string>
#include <vendor/glm/glm/glm.hpp>
#include <vector>
#include "Link.h"
#include <any>
#include <Application/Events/Event.h>
#include <map>

enum class PropertyType
{
    Integer, //int32_t
    Decimal, //float
    Bool, //bool
    Text, //string
    Typeless
};

struct Variable
{
    std::any data;
    PropertyType type;
    std::string name;
};

class Attribute
{
public:
    Attribute() {}
    virtual ~Attribute() {}

public:
    std::string name;
    uint32_t id;
    std::vector<std::shared_ptr<Link>> links;

    PropertyType type;
    std::any data;
    bool linkable = true;
};

struct Node;

struct InputAttribute : public Attribute
{
    using Func = std::function<void()>;

    InputAttribute(const std::string& n, bool linkable)
    {
        name = n;
        linkable = linkable;
    }

    Func function = NULL;
    Node* pNode = nullptr;
};

struct OutputAttribute : public Attribute
{
    OutputAttribute(const std::string& n, bool linkable)
    {
        name = n;
        linkable = linkable;
    }
};

struct Node
{
public:
    Node();
    Node(std::shared_ptr<Node>& node);
    virtual ~Node() {}

public:
    virtual void OnEvent(Event& e) {}
    virtual void DrawContent() = 0;
    virtual std::map<uint32_t, std::string> CreateCode() = 0;

public:
    template<typename T>
    InputAttribute InputAttributeConfig(const std::string& name, PropertyType type, Node* pNode, bool linkable = true)
    {
        InputAttribute attr(name, linkable);
        attr.data = T();
        attr.type = type;
        attr.pNode = pNode;

        return attr;
    }

    template<typename T>
    InputAttribute InputAttributeConfig(const std::string& name, PropertyType type, InputAttribute::Func f, Node* pNode, bool linkable = true)
    {
        InputAttribute attr(name, linkable);
        attr.data = T();
        attr.type = type;
        attr.function = f;
        attr.pNode = pNode;

        return attr;
    }

    InputAttribute InputAttributeConfig_Void(const std::string& name, PropertyType type, Node* pNode, bool linkable = true)
    {
        InputAttribute attr(name, linkable);
        attr.type = type;
        attr.pNode = pNode;

        return attr;
    }

    InputAttribute InputAttributeConfig_Void(const std::string& name, PropertyType type, InputAttribute::Func f, Node* pNode, bool linkable = true)
    {
        InputAttribute attr(name, linkable);
        attr.type = type;
        attr.function = f;
        attr.pNode = pNode;

        return attr;
    }

    template<typename T>
    OutputAttribute OutputAttributeConfig(const std::string& name, PropertyType type, bool linkable = true)
    {
        OutputAttribute attr(name, linkable);
        attr.type = type;
        attr.data = T();

        return attr;
    }

    OutputAttribute OutputAttributeConfig_Void(const std::string& name, PropertyType type, bool linkable = true)
    {
        OutputAttribute attr(name, linkable);
        attr.type = type;

        return attr;
    }

    template<typename T>
    void ActivateOutput(uint32_t index, T data)
    {
        if (outputAttributes[index].links.size() > 0)
        {
            for (auto& link : outputAttributes[index].links)
            {
                link->pInput->data = data;
                if (link->pInput->function != NULL)
                {
                    link->pInput->function();
                }
            }
        }
    }

    template<typename T>
    void ActivateOutput(uint32_t index)
    {
        if (outputAttributes[index].links.size() > 0)
        {
            for (auto& link : outputAttributes[index].links)
            {
                if (link->pInput->function != NULL)
                {
                    link->pInput->function();
                }
            }
        }
    }

    template<typename T>
    T& GetInput(uint32_t index)
    {
        return std::any_cast<T&>(inputAttributes[index].data);
    }

public:
    std::string name;
    uint32_t id;
    glm::vec2 position;

    std::map<uint32_t, std::string> code;
    std::vector<std::shared_ptr<Link>> links;
    std::vector<InputAttribute> inputAttributes;
    std::vector<OutputAttribute> outputAttributes;
};


#endif //TESTPROJECT_NODE_H
