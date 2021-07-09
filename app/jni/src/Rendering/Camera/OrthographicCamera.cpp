//
// Created by xXRag on 2021-07-05.
//

#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_projectionMatrix(glm::ortho(left, right, bottom, top, -1.f, 1.f)), m_viewMatrix(1.f)
{
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
    m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.f);
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix()
{
    glm::mat4 trans = glm::translate(glm::mat4(1.f), m_position) *
            glm::rotate(glm::mat4(1.f), glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));

    m_viewMatrix = glm::inverse(trans);
    m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}