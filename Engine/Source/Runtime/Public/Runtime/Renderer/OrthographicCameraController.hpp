#pragma once

#include "Runtime/Core/Timestep.hpp"

#include "Runtime/Events/Event.hpp"
#include "Runtime/Events/ApplicationEvent.hpp"
#include "Runtime/Events/MouseEvent.hpp"

#include "Runtime/Renderer/OrthographicCamera.hpp"

namespace Hyperion {

    class HYPERION_API OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep timestep);
        void OnEvent(Event& event);
        
        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

    private:
        bool OnMouseScrolled(const MouseScrolledEvent& event);
        bool OnWindowResized(const WindowResizeEvent& event);
        
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation = false;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };
    
}
