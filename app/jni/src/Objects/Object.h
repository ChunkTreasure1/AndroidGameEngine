//
// Created by ivar on 2021-07-14.
//

#ifndef TESTPROJECT_OBJECT_H
#define TESTPROJECT_OBJECT_H

#include <string>
#include <Application/Events/ApplicationEvent.h>
#include <glm/glm/glm.hpp>
#include <Rendering/Texture2D/Texture2D.h>

class Object
{
public:
    Object(const std::string& name);
    ~Object();

    void OnEvent(Event& e);

    //Setting
    void SetPosition(const glm::vec2& pos) { m_position = pos; UpdateTransform(); }
    void SetScale(const glm::vec2& scale) { m_scale = scale; UpdateTransform(); }
    void SetRotation(float rot) { m_rotation = rot; UpdateTransform(); }

    //Getting
    inline const glm::vec2& GetPosition() const { return m_position; }
    inline const glm::vec2& GetScale() const { return m_scale; }
    inline const float GetRotation() const { return m_rotation; }
    inline const glm::mat4& GetTransform() const { return m_transform; }

private:
    bool OnRenderEvent(AppRenderEvent& e);
    bool OnUpdateEvent(AppUpdateEvent& e);

    void UpdateTransform();

private:
    bool m_isSprite = true;
    std::string m_name;

    glm::vec2 m_position = { 0.f, 0.f };
    glm::vec2 m_scale = { 0.f, 0.f };
    glm::vec4 m_color = { 1.f, 1.f, 1.f, 1.f };
    glm::mat4 m_transform = glm::mat4(1.f);

    float m_rotation = 0.f;


    std::shared_ptr<Texture2D> m_texture;
};


#endif //TESTPROJECT_OBJECT_H
