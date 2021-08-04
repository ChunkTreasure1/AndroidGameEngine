//
// Created by ivar on 2021-07-25.
//

#include "CodeGraph.h"

CodeGraph::CodeGraph()
{}

CodeGraph::CodeGraph(const GraphSpecification &spec)
    : m_specification(spec)
{}

void CodeGraph::RemoveNode(uint32_t id)
{
    auto func = [&id, this](std::shared_ptr<Node>& node)
    {
        if (id == node->id)
        {
            for (auto& attr : node->inputAttributes)
            {
                if (attr.links.size() > 0)
                {
                    for (auto& link : attr.links)
                    {
                        RemoveLink(link->id);
                    }
                }
            }

            for (auto& attr : node->outputAttributes)
            {
                if (attr.links.size() > 0)
                {
                    for (auto& link : attr.links)
                    {
                        RemoveLink(link->id);
                    }
                }
            }

            return true;
        }

        return false;
    };

    m_specification.nodes.erase(std::remove_if(m_specification.nodes.begin(), m_specification.nodes.end(), func));
}

void CodeGraph::RemoveLink(uint32_t id)
{
    for (auto& node : m_specification.nodes)
    {
        for (auto& attr : node->inputAttributes)
        {
            if (attr.links.size() == 0)
                continue;

            for (auto& link : attr.links)
            {
                if (link->id == id)
                {
                    if (auto it = std::find(attr.links.begin(), attr.links.end(), link); it != attr.links.end())
                    {
                        attr.links.erase(it);
                    }
                    break;
                }
            }
        }

        for (auto& attr : node->outputAttributes)
        {
            if (attr.links.size() == 0)
                continue;

            for (auto& link : attr.links)
            {
                if (link->id == id)
                {
                    if (auto it = std::find(attr.links.begin(), attr.links.end(), link); it != attr.links.end())
                    {
                        attr.links.erase(it);
                    }
                    break;
                }
            }
        }
    }

    auto func = [&id](std::shared_ptr<Link>& link)
    {
        return id == link->id;
    };

    m_specification.links.erase(std::remove_if(m_specification.links.begin(), m_specification.links.end(), func));
}

void CodeGraph::OnEvent(Event &e)
{
    for (auto& node : m_specification.nodes)
    {
        node->OnEvent(e);
    }
}