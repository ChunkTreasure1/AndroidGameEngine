//
// Created by xXRag on 2021-06-22.
//

#include "Shader.h"

Shader::Shader()
{}

Shader::~Shader()
{}

void Shader::Setup(Renderable &renderable)
{
    glUseProgram(m_id);
}

void Shader::LoadShader(GLenum id, const std::string &code)
{
    static const uint32_t NUM_SHADERS = 1;

    const GLchar* pCode = code.c_str();
    GLint length = code.length();

    glShaderSource(id, NUM_SHADERS, &pCode, &length);
    glCompileShader(id);

    glAttachShader(m_id, id);
}

void Shader::Link()
{
    m_id = glCreateProgram();

    m_vertexId = glCreateShader(GL_VERTEX_SHADER);
    LoadShader(m_vertexId, m_vertexCode);

    m_fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    LoadShader(m_fragmentId, m_fragmentCode);

    glLinkProgram(m_id);
    m_isLinked = true;
}