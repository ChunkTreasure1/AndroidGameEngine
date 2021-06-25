//
// Created by xXRag on 2021-06-22.
//

#ifndef GAMEENGINE_BASICSHADER_H
#define GAMEENGINE_BASICSHADER_H

#include "Shader.h"

class BasicShader : public Shader
{
public:
    BasicShader();
    virtual ~BasicShader() {}

    virtual void Link();
    virtual void Setup(Renderable& renderable);

private:
    GLint m_positionAttributeHandle;

};


#endif //GAMEENGINE_BASICSHADER_H
