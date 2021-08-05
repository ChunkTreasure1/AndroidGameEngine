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
    virtual std::map<uint32_t, std::string> CreateCode() override;

public:
    static std::string GetFactoryName() { return "Start"; }
    static std::shared_ptr<Node> Create() { return std::make_shared<StartNode>(); }

private:
};

class TestNode : public Node
{
public:
    TestNode();
    virtual ~TestNode() override {}

    virtual void DrawContent() override;
    virtual std::map<uint32_t, std::string> CreateCode() override;

public:
    static std::string GetFactoryName() { return "Test"; }
    static std::shared_ptr<Node> Create() { return std::make_shared<TestNode>(); }
};

REGISTER_NODE(StartNode, "Base");
REGISTER_NODE(TestNode, "Testing");

#endif //TESTPROJECT_EVENTNODES_H
