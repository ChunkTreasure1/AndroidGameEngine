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
}

void StartNode::DrawContent()
{
    ImNodes::BeginOutputAttribute(outputAttributes[0].id);

    ImGui::Text("%s", name.c_str());

    ImNodes::EndOutputAttribute();
}