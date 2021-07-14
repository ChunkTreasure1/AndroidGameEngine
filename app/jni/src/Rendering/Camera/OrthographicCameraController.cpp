//
// Created by xXRag on 2021-07-05.
//

#include "OrthographicCameraController.h"

#include <SDL.h>
#include <Application/Input/Input.h>

OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotate)
    : m_aspectRatio(aspectRatio), m_rotate(rotate), m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel)
{
    m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
}

OrthographicCameraController::~OrthographicCameraController()
{}

void OrthographicCameraController::Update(Timestep ts)
{
    if (Input::IsKeyPressed(SDL_SCANCODE_W))
    {
        m_cameraPosition.y += m_cameraTranslationSpeed * ts;
    }
    m_camera.SetPosition(m_cameraPosition);
}

void OrthographicCameraController::OnEvent(Event &e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<KeyPressedEvent>(LP_BIND_EVENT_FN(OrthographicCameraController::OnKeyPressed));
}

bool OrthographicCameraController::OnKeyPressed(KeyPressedEvent &e)
{
    bool t = false;
}

void OrthographicCameraController::SetAspectRatio(float ratio)
{
    m_aspectRatio = ratio;
    m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
}