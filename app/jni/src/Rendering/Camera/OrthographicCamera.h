//
// Created by xXRag on 2021-07-05.
//

#ifndef TESTPROJECT_ORTHOGRAPHICCAMERA_H
#define TESTPROJECT_ORTHOGRAPHICCAMERA_H

#include <glm/glm.hpp>

class OrthographicCamera
{
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    //Getting
    const glm::vec3& GetPosition() const { return m_position; }
    const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
    const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }

    const glm::mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }
    float GetRotation() { return m_rotation; }

    //Setting
    void SetProjection(float left, float right, float bottom, float top);
    void SetPosition(const glm::vec3& position) { m_position = position; RecalculateViewMatrix(); }
    void SetRotation(float rotation) { m_rotation = rotation; RecalculateViewMatrix(); }

private:
    void RecalculateViewMatrix();

private:
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_viewProjectionMatrix;

    glm::vec3 m_position = { 0.f, 0.f, 0.f };
    float m_rotation = 0.0f;
};


#endif //TESTPROJECT_ORTHOGRAPHICCAMERA_H
