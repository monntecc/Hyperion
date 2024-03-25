#include "hrpch.hpp"

#include "Runtime/Renderer/OrthographicCameraController.hpp"

#include "Runtime/Core/Input.hpp"
#include "Runtime/Core/KeyCodes.hpp"

#include <Tracy.hpp>

namespace Hyperion
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio),
          m_Camera({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }),
          m_Rotation(rotation)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        ZoneScoped;
        
        if (Input::IsKeyPressed(Key::A))
        {
            m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(Key::D))
        {
            m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }

        if (Input::IsKeyPressed(Key::D))
        {
            m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(Key::S))
        {
            m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
            m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        }

        if (m_Rotation)
        {
            if (Input::IsKeyPressed(Key::Q))
                m_CameraRotation += m_CameraRotationSpeed * ts;
            if (Input::IsKeyPressed(Key::E))
                m_CameraRotation -= m_CameraRotationSpeed * ts;

            if (m_CameraRotation > 180.0f)
                m_CameraRotation -= 360.0f;
            else if (m_CameraRotation <= -180.0f)
                m_CameraRotation += 360.0f;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);
        m_CameraTranslationSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        ZoneScoped;
        
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(HR_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(HR_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    void OrthographicCameraController::OnResize(float width, float height)
    {
        ZoneScoped;

        if (width == 0 || height == 0)
        {
            HR_CORE_WARN("Attempted to rezize camera to {0}, {1}", width, height);
            return;
        }

        m_AspectRatio = width / height;
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
    }

    bool OrthographicCameraController::OnMouseScrolled(const MouseScrolledEvent& event)
    {
        ZoneScoped;
        
        m_ZoomLevel -= event.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(const WindowResizeEvent& event)
    {
        ZoneScoped;
        
        OnResize(static_cast<float>(event.GetWidth()), static_cast<float>(event.GetHeight()));
        return false;
    }
}
