#pragma once

#include "Hyperion.hpp"

namespace Hyperion {

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        ~EditorLayer() override = default;

        void OnUpdate(Timestep timestep) override;
        void OnEvent(Event& event) override;
        void OnImGuiRender() override;

        void OnAttach() override;
        void OnDetach() override;
    private:
        OrthographicCameraController m_CameraController;
        Ref<Texture2D> m_CheckerboardTexture;

        Ref<FrameBuffer> m_FrameBuffer;

        bool m_ViewportFocused = false;
        bool m_ViewportHovered= false;
        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

        glm::vec4 m_SquareColor = { 0.8f, 0.2f, 0.3f, 1.0f };
        glm::vec4 m_CheckerboardColor = glm::vec4(1.0f);
        glm::vec4 m_RotatedCheckerboardColor = glm::vec4(1.0f);
    };

}
