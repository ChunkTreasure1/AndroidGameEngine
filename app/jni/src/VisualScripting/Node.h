//
// Created by ivar on 2021-07-25.
//

#ifndef TESTPROJECT_NODE_H
#define TESTPROJECT_NODE_H

#include <memory>
#include <string>
#include <vendor/glm/glm/glm.hpp>
#include <vector>

enum class AttributeType
{
    Condition = 0,
    Variable
};

struct Attribute
{
    std::string name;
    uint32_t id;
    AttributeType type;
};

struct Node
{
public:
    Node();
    Node(std::shared_ptr<Node>& node);



    std::string code;
    uint32_t id;
    glm::vec2 position;
    std::vector<Attribute> attributes;
};


#endif //TESTPROJECT_NODE_H
