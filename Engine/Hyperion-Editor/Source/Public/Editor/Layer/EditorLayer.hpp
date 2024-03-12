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
        Ref<FrameBuffer> m_FrameBuffer;

    	Ref<Scene> m_ActiveScene;
        Entity m_SquareEntity;

        Entity m_CameraEntity;
        Entity m_SecondCamera;

        bool m_PrimaryCamera = true;

        bool m_ViewportFocused = false;
        bool m_ViewportHovered= false;
        glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

        glm::vec4 m_SquareColor = { 0.0f, 1.0f, 0.0f, 1.0f };
    };

}
