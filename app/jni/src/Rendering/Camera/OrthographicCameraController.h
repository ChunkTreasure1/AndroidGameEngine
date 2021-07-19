//
// Created by xXRag on 2021-07-05.
//

#ifndef TESTPROJECT_ORTHOGRAPHICCAMERACONTROLLER_H
#define TESTPROJECT_ORTHOGRAPHICCAMERACONTROLLER_H

#include <Application/Timestep.h>
#include <Application/Events/Event.h>

#include "OrthographicCamera.h"
#include <Application/Events/KeyEvent.h>
#include <glm/glm.hpp>

class OrthographicCameraController
{
public:
    OrthographicCameraController(float aspectRatio, bool rotate = false);
    ~OrthographicCameraController();

    void Update(Timestep ts);
    void OnEvent(Event& e);

    //Getting
    OrthographicCamera& GetCamera() { return m_camera; }
    const OrthographicCamera& GetCamera() const { return m_camera; }

    //Setting
    void SetAspectRatio(float ratio);
    void SetPosition(const glm::vec3& pos) { m_cameraPosition = pos; }

private:
    float m_aspectRatio = 0.f;
    float m_zoomLevel = 6.f;
    OrthographicCamera m_camera;

    bool m_rotate;

    glm::vec3 m_cameraPosition = { 0.f, 0.f, 0.f };
    float m_cameraRotation = 0.f;
    float m_cameraTranslationSpeed = 5.f, m_cameraRotationSpeed = 180.f;
};


#endif //TESTPROJECT_ORTHOGRAPHICCAMERACONTROLLER_H
