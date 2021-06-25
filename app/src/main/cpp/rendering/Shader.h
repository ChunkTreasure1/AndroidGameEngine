//
// Created by xXRag on 2021-06-22.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <string>
#include <GLES3/gl3.h>

#include "Renderable.h"

class Shader
{
public:
    Shader();
    virtual ~Shader();

    virtual void Link();
    virtual void Setup(Renderable& renderable);

    bool IsLinked() { return m_isLinked; }

protected:
    GLuint m_vertexId;
    GLuint m_fragmentId;
    GLint m_id;

    std::string m_vertexCode;
    std::string m_fragmentCode;

    bool m_isLinked;

private:
    void LoadShader(GLenum id, const std::string& code);
};

#endif //GAMEENGINE_SHADER_H
