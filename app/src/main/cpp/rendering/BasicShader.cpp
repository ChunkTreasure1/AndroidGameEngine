//
// Created by xXRag on 2021-06-22.
//

#include "BasicShader.h"

BasicShader::BasicShader()
{
    m_vertexCode =
            "attribute vec4 a_Position; \n"
            "void main(){\n"
            "  gl_Position = a_Position; \n"
            "}";

    m_fragmentCode =
            "precision highp float; \n"
            "void main() {\n"
            "   gl_FragColor = vec4(0.2, 0.2, 0.2, 1.0)\n"
            "}";
}

void BasicShader::Link()
{
    Shader::Link();

    m_positionAttributeHandle = glGetAttribLocation(m_id, "a_Position");
}

void BasicShader::Setup(Renderable &renderable)
{
    Shader::Setup(renderable);

    Geometry* pGeom = renderable.GetGeometry();
    assert(pGeom);

    glVertexAttribPointer(m_positionAttributeHandle, pGeom->GetNumVertexPositionElements(), GL_FLOAT, GL_FALSE, pGeom->GetVertexStride(), pGeom->GetVertexBuffer());
    glEnableVertexAttribArray(m_positionAttributeHandle);
}

