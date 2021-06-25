//
// Created by xXRag on 2021-06-22.
//

#ifndef GAMEENGINE_RENDERABLE_H
#define GAMEENGINE_RENDERABLE_H

#include "Geometry.h"

class Shader;

class Renderable
{
public:
    Renderable();
    ~Renderable();

    inline void SetGeomentry(Geometry* pGeom) { m_pGeometry = pGeom; }
    inline Geometry* GetGeometry() { return m_pGeometry;}

    inline void SetShader(Shader* pShader) { m_pShader = pShader; }
    inline Shader* GetShader() { return m_pShader; }


private:
    Geometry* m_pGeometry;
    Shader* m_pShader;

};

#endif //GAMEENGINE_RENDERABLE_H
