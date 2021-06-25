//
// Created by xXRag on 2021-06-22.
//

#include "MainTask.h"

namespace
{
    float verts[] =
            {
                -0.5f, 0.5f, 0.f,
                0.5f, 0.5f, 0.f,
                -0.5f, -0.5f, 0.f,
                0.5f, -0.5f, 0.f
            };

    uint32_t indices[] =
            {
                0, 2, 1,
                2, 3, 1
            };
}

MainTask::MainTask(Renderer *pRenderer, const uint32_t priority)
    : m_pRenderer(pRenderer), Task(priority)
{
    m_renderable.SetGeomentry(&m_geometry);
    m_renderable.SetShader(&m_shader);
}

bool MainTask::Start()
{
    Geometry* pGeometry = m_renderable.GetGeometry();
    pGeometry->SetVertexBuffer(verts);
    pGeometry->SetNumVertices(4);
    pGeometry->SetIndexBuffer(indices);
    pGeometry->SetNumIndices(6);
    pGeometry->SetName("Quad");

    pGeometry->SetNumVertexPositionElements(3);
    pGeometry->SetVertexStride(0);

    m_pRenderer->AddRenderable(&m_renderable);

    return true;
}

void MainTask::Stop()
{
    m_pRenderer->RemoveRenderable(&m_renderable);
}

void MainTask::OnSuspend()
{}

void MainTask::Update()
{}

void MainTask::OnResume()
{}