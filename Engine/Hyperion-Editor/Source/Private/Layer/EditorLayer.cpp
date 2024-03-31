#include "hrpch.hpp"

#include "Editor/Layer/EditorLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <Tracy.hpp>

#include <imgui_internal.h>

namespace Hyperion {

    EditorLayer::EditorLayer() :
        Layer("EditorLayer"),
        m_CameraController(1280.0f / 720.0f)
    {
    }

    void EditorLayer::OnAttach()
    {
        FrameMarkNamed("EditorLayer::OnAttach");

        m_ViewportWidget.Init();

        m_ActiveScene = CreateRef<Scene>();

        auto entity = m_ActiveScene->CreateEntity("Green Square");
        entity.AddComponent<SpriteRendererComponent>(m_SquareColor);
        m_SquareEntity = entity;

        auto redSquare = m_ActiveScene->CreateEntity("Red Square");
        redSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
        redSquare.GetComponent<TransformComponent>().Transform[3][0] = 2.0f;

        m_CameraEntity = m_ActiveScene->CreateEntity("Camera A");
        m_CameraEntity.AddComponent<CameraComponent>();

        m_SecondCamera = m_ActiveScene->CreateEntity("Camera B");
        auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
        cc.Primary = false;

        class CameraController : public ScriptableEntity
        {
        public:
            virtual void OnCreate() override
            {
                auto& transform = GetComponent<TransformComponent>().Transform;
                transform[3][0] = rand() % 10 - 5.0f;
            }

            virtual void OnDestroy() override
            {
            }

            virtual void OnUpdate(Timestep ts) override
            {
                auto& transform = GetComponent<TransformComponent>().Transform;

                float speed = 5.0f;

                if (Input::IsKeyPressed(Key::A))
                    transform[3][0] -= speed * ts;
                if (Input::IsKeyPressed(Key::D))
                    transform[3][0] += speed * ts;
                if (Input::IsKeyPressed(Key::W))
                    transform[3][1] += speed * ts;
                if (Input::IsKeyPressed(Key::S))
                    transform[3][1] -= speed * ts;
            }
        };

        m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();

        m_SecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();

        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(const Timestep timestep)
    {
        FrameMarkNamed("EditorLayer::OnUpdate");

        // Resize
        {
            m_ViewportWidget.Resize(glm::vec2(static_cast<uint32_t>(m_ViewportWidget.GetSize().x),
                static_cast<uint32_t>((m_ViewportWidget.GetSize().y))));

            m_CameraController.OnResize(m_ViewportWidget.GetSize().x, m_ViewportWidget.GetSize().y);
            
            m_ActiveScene->OnViewportResize(static_cast<uint32_t>(m_ViewportWidget.GetSize().x),
                static_cast<uint32_t>((m_ViewportWidget.GetSize().y)));
        }

        // Update
		if (m_ViewportWidget.IsFocused())
            m_CameraController.OnUpdate(timestep);

        // Render
        Renderer2D::ResetStats();

        // Bind framebuffer, set color
        m_ViewportWidget.BindFrameBuffer();
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();

        // Draw quads
        Renderer2D::BeginScene(m_CameraController.GetCamera());

        // Update scene
    	m_ActiveScene->OnUpdate(timestep);

    	Renderer2D::EndScene();

        m_ViewportWidget.UnbindFrameBuffer();
    }

    void EditorLayer::OnEvent(Event& event)
    {
        m_CameraController.OnEvent(event);
    }

    void EditorLayer::OnImGuiRender()
    {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos + ImVec2(0,50.0f));
            ImGui::SetNextWindowSize(viewport->WorkSize - ImVec2(0, 50.0f));
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("MyDockSpace", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        const ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            const ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        // Scene Hierarchy panel
        m_SceneHierarchyPanel.OnImGuiRender();

        // Statistics widget
        m_StatisticPanel.Draw();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });

        // Viewport widget
        m_ViewportWidget.Draw();

    	ImGui::PopStyleVar();

        ImGui::End();

        // Render titlebar
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetMainViewport()->Size.x, 50.0f));
        ImGui::Begin("Titlebar", nullptr, ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking);
        m_TitlebarWidget.DrawUITitlebar();
        ImGui::End();
    }

}
