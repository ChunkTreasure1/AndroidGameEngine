//
// Created by ivar on 2021-07-25.
//

#ifndef TESTPROJECT_CODEGRAPH_H
#define TESTPROJECT_CODEGRAPH_H

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "Node.h"

struct GraphSpecification
{
    std::vector<std::shared_ptr<Node>> nodes;
    std::map<uint32_t, std::string> builtCode;
    std::string name;
    std::string path;
};

class CodeGraph
{
public:
    CodeGraph();
    CodeGraph(const GraphSpecification& spec);

    inline uint32_t GetCurrentId() { return m_currentId; }
    inline void SetCurrentId(uint32_t id) { m_currentId = id; }

private:
    uint32_t m_currentId = 0;
    GraphSpecification m_specification;
};


#endif //TESTPROJECT_CODEGRAPH_H
