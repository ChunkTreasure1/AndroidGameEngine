//
// Created by chunktreasure on 8/5/21.
//

#ifndef TESTPROJECT_EVENTNODES_H
#define TESTPROJECT_EVENTNODES_H

#include <VisualScripting/Node.h>
#include <VisualScripting/NodeRegistry.h>

class StartNode : public Node
{
public:
    StartNode();
    virtual ~StartNode() override
    {
        NodeRegistry::RemoveStart(this);
    }

    virtual void DrawContent() override;

public:
    static std::string GetFactoryName() { return "Start"; }
    static std::shared_ptr<Node> Create() { return std::make_shared<StartNode>(); }

private:
};

REGISTER_NODE(StartNode, "Base");

#endif //TESTPROJECT_EVENTNODES_H
