//
// Created by chunktreasure on 8/5/21.
//

#include "EventNodes.h"
#include <imnodes.h>
#include <vendor/imgui/imgui.h>


StartNode::StartNode()
{
    name = "Start";
    outputAttributes = { OutputAttributeConfig_Void("Start", PropertyType::Typeless) };
    NodeRegistry::AddStart(this);

    code[1] = "void Start()";
    code[2] = "{";
    code[3] = "}";
}

std::map<uint32_t, std::string> StartNode::CreateCode()
{
    auto temp = code;

    for (auto& link : outputAttributes[0].links)
    {
        if (link->pInput)
        {
            auto c = link->pInput->pNode->CreateCode();
            uint32_t start = 3;
            for (auto it = c.begin(); it != c.end(); it++)
            {
                code[start] = it->second;
                start++;
            }
        }
    }

    temp[temp.size() + 1] = "}";

    return temp;
}

void StartNode::DrawContent()
{
    ImNodes::BeginOutputAttribute(outputAttributes[0].id);

    ImGui::Text("%s", name.c_str());

    ImNodes::EndOutputAttribute();
}

TestNode::TestNode()
{
    name = "Test";
    inputAttributes = { InputAttributeConfig_Void("Testing", PropertyType::Typeless, this) };

    code[0] = "if (x == 1)";
    code[1] = "{";
    code[2] = "}";
}

std::map<uint32_t, std::string> TestNode::CreateCode()
{
    return code;
}

void TestNode::DrawContent()
{
    ImNodes::BeginInputAttribute(inputAttributes[0].id);

    ImGui::Text("Testing");

    ImNodes::EndInputAttribute();
}