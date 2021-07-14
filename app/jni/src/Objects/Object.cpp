//
// Created by ivar on 2021-07-14.
//

#include "Object.h"
#include <Rendering/Renderer.h>
#include <glm/glm/gtc/matrix_transform.hpp>

Object::Object(const std::string &name)
    : m_name(name)
{}

Object::~Object()
{}

void Object::OnEvent(Event &e)
        {
            EventDispatcher dispatcher(e);
            dispatcher.Dispatch<AppRenderEvent>(LP_BIND_EVENT_FN(Object::OnRenderEvent));
            dispatcher.Dispatch<AppUpdateEvent>(LP_BIND_EVENT_FN(Object::OnUpdateEvent));
        }

        bool Object::OnRenderEvent(AppRenderEvent &e)
        {
            if (m_isSprite)
            {
                Renderer::DrawQuad(m_transform, m_texture, m_color);
    }

    return false;
}

bool Object::OnUpdateEvent(AppUpdateEvent &e)
{
    

    return false;
}

void Object::UpdateTransform()
{
    m_transform = glm::translate(glm::mat4(1.f), { m_position.x, m_position.y, 0.f })
            * glm::scale(glm::mat4(1.f), { m_scale.x, m_scale. y, 1.f })
            * glm::rotate(glm::mat4(1.f), m_rotation, { 0.f, 0.f, 1.f });
}