#pragma once

#include "Hyperion.hpp"

#include "Editor/Panels/SceneHierarchyPanel.hpp"
#include "Editor/Panels/StatisticPanel.hpp"

#include "Editor/Widgets/TitlebarWidget.hpp"
#include "Editor/Widgets/ViewportWidget.hpp"

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

    	Ref<Scene> m_ActiveScene;
        Entity m_SquareEntity;

        Entity m_CameraEntity;
        Entity m_SecondCamera;

        bool m_PrimaryCamera = true;

        glm::vec4 m_SquareColor = { 0.0f, 1.0f, 0.0f, 1.0f };

        // Panels
        SceneHierarchyPanel m_SceneHierarchyPanel;
        StatisticPanel m_StatisticPanel;

        // Widgets
        TitlebarWidget m_TitlebarWidget;
        ViewportWidget m_ViewportWidget;
    };

}
