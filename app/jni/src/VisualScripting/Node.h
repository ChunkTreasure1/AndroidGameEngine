//
// Created by ivar on 2021-07-25.
//

#ifndef TESTPROJECT_NODE_H
#define TESTPROJECT_NODE_H

#include <memory>
#include <string>

class Node
{
public:
    Node();
    Node(std::shared_ptr<Node>& node);

    inline const std::string& GetCode() { return m_code; }

private:
    std::string m_code = "if (%v %c %v) { }";
};


#endif //TESTPROJECT_NODE_H
