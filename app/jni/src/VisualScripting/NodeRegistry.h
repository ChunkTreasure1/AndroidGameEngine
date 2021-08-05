//
// Created by chunktreasure on 8/5/21.
//

#ifndef TESTPROJECT_NODEREGISTRY_H
#define TESTPROJECT_NODEREGISTRY_H

#include "Node.h"
#include <unordered_map>

#define REGISTER_NODE(x, y) static bool x ## _entry = NodeRegistry::Register(x::GetFactoryName(), x::Create, y);

class NodeRegistry
{
public:
    using CreateMethod = std::shared_ptr<Node>(*)();

public:
    NodeRegistry() = delete;

    static bool Register(const std::string& name, CreateMethod func, const std::string& cat);
    static std::shared_ptr<Node> Create(const std::string& name);

    /////Start nodes/////
    static void AddStart(Node* node);
    static void RemoveStart(Node* node);
    /////////////////////

    static const std::string& GetCategory(const std::string& name);

    static std::unordered_map<std::string, CreateMethod>& s_methods();
    static std::unordered_map<std::string, std::string>& s_categories();
    static std::vector<Node*>& s_startNodes();
};


#endif //TESTPROJECT_NODEREGISTRY_H
