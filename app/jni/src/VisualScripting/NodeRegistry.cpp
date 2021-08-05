//
// Created by chunktreasure on 8/5/21.
//

#include "NodeRegistry.h"

bool NodeRegistry::Register(const std::string &name, CreateMethod func, const std::string &cat)
{
    if (auto it = s_methods().find(name); it == s_methods().end())
    {
        s_methods()[name] = func;
        s_categories()[name] = cat;

        return true;
    }

    return false;
}

std::shared_ptr<Node> NodeRegistry::Create(const std::string &name)
{
    if (auto it = s_methods().find(name); it != s_methods().end())
    {
        return it->second();
    }

    return nullptr;
}

void NodeRegistry::AddStart(Node *node)
{
    s_startNodes().push_back(node);
}

void NodeRegistry::RemoveStart(Node *node)
{
    if (auto it = std::find(s_startNodes().begin(), s_startNodes().end(), node); it != s_startNodes().end())
    {
        s_startNodes().erase(it);
    }
}

const std::string & NodeRegistry::GetCategory(const std::string &name)
{
    return s_categories()[name];
}

std::unordered_map<std::string, NodeRegistry::CreateMethod> & NodeRegistry::s_methods()
{
    static std::unordered_map<std::string, NodeRegistry::CreateMethod> impl;
    return impl;
}

std::unordered_map<std::string, std::string> & NodeRegistry::s_categories()
{
    static std::unordered_map<std::string, std::string> impl;
    return impl;
}

std::vector<Node *> & NodeRegistry::s_startNodes()
{
    static std::vector<Node*> impl;
    return impl;
}