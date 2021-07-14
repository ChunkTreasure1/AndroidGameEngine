//
// Created by xXRag on 2021-07-04.
//

#include "Shader.h"
#include "../../Core.h"
#include "../../Application/Filesystem/Filesystem.h"

#include <fstream>
#include <GLES3/gl3.h>
#include <glm/gtc/type_ptr.inl>
#include <vector>

Shader::Shader(const std::string &vPath, const std::string &fPath, bool isCode)
    : m_id(0)
{
    std::string vCode;
    std::string fCode;

    if (!isCode)
    {
        //Vertex file
        AAsset* pFile = Filesystem::Open(vPath);
        uint32_t size = Filesystem::GetLength(pFile);

        std::vector<char> vShader;
        vShader.resize(size);

        Filesystem::Read(pFile, static_cast<void*>(vShader.data()), size);
        Filesystem::Close(pFile);

        //Fragment file
        pFile = Filesystem::Open(fPath);
        size = Filesystem::GetLength(pFile);

        std::vector<char> fShader;
        fShader.resize(size);

        Filesystem::Read(pFile, static_cast<void*>(fShader.data()), size);
        Filesystem::Close(pFile);

        //Set code
        vCode = vShader.data();
        fCode = fShader.data();
    }
    else
    {
        vCode = vPath;
        fCode = fPath;
    }

    //Generate shaders
    GenerateShader(vCode.c_str(), fCode.c_str());
}

void Shader::GenerateShader(const char *vCode, const char *fCode)
{
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vCode, NULL);
    glCompileShader(vertex);

    //Check if shader compiles
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        LOGE("Shader compilation failed: %s", infoLog);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fCode, NULL);
    glCompileShader(fragment);

    //Check if shader compiles
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        LOGE("Shader compilation failed: %s", infoLog);
    }

    //Create program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Bind()
{
    glUseProgram(m_id);
}

void Shader::UploadBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void Shader::UploadInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::UploadIntArray(const std::string &name, int *value, uint32_t count) const
{
    glUniform1iv(glGetUniformLocation(m_id, name.c_str()), count, value);
}

void Shader::UploadFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::UploadFloat4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::UploadMat4(const std::string &name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

std::shared_ptr<Shader> Shader::Create(const std::string &vPath, const std::string &fPath, bool isCode)
{
    return std::make_shared<Shader>(vPath, fPath, isCode);
}