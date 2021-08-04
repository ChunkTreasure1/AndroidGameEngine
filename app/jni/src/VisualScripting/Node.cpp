//
// Created by ivar on 2021-07-25.
//

#include "Node.h"

Node::Node()
    : name("")
{}

Node::Node(std::shared_ptr<Node> &node)
{
    name = node->name;
    id = node->id;
    links = node->links;
    inputAttributes = node->inputAttributes;
    outputAttributes = node->outputAttributes;
}