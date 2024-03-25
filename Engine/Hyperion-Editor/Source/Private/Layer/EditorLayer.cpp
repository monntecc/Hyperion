#include "hrpch.hpp"

#include "Editor/Layer/EditorLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <Tracy.hpp>

namespace Hyperion {

    EditorLayer::EditorLayer() :
        Layer("EditorLayer"),
        m_CameraController(1280.0f / 720.0f)
    {
    }

    void EditorLayer::OnAttach()
    {
        FrameBufferSpecification specification = {};
        specification.Width = 1280;
        specification.Height = 720;
        m_FrameBuffer = FrameBuffer::Create(specification);

        m_ActiveScene = CreateRef<Scene>();

        auto entity = m_ActiveScene->CreateEntity("Square");
        entity.AddComponent<SpriteRendererComponent>(m_SquareColor);
        m_SquareEntity = entity;

        m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
        m_CameraEntity.AddComponent<CameraComponent>();

        m_SecondCamera = m_ActiveScene->CreateEntity("Clip-Space Entity");
        auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
        cc.Primary = false;

        class CameraController : public ScriptableEntity
        {
        public:
            void OnCreate()
            {
            }

            void OnDestroy()
            {
            }

            void OnUpdate(Timestep ts)
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
    }

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(const Timestep timestep)
    {
        FrameMarkNamed("EditorLayer::OnUpdate");

        // Resize
        {
            m_FrameBuffer->Resize(static_cast<uint32_t>(m_ViewportSize.x),
                static_cast<uint32_t>(m_ViewportSize.y));
            m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);

            m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        }

        // Update
		if (m_ViewportFocused)
            m_CameraController.OnUpdate(timestep);

        // Render
        Renderer2D::ResetStats();

        // Bind framebuffer, set color
        m_FrameBuffer->Bind();
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();

        // Draw quads
        Renderer2D::BeginScene(m_CameraController.GetCamera());

        // Update scene
    	m_ActiveScene->OnUpdate(timestep);

    	Renderer2D::EndScene();

        m_FrameBuffer->Unbind();
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
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
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
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
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

        // Menu bar
        {
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Exit")) { Application::Get().Shutdown(); }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
        }

        // Settings panel
        {
            ImGui::Begin("Settings");
            const auto stats = Renderer2D::GetStats();
            ImGui::Text("Renderer2D Stats:");
            ImGui::Text("Draw Calls: %d", stats.DrawCalls);
            ImGui::Text("Quads: %d", stats.QuadCount);
            ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
            ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

            if (m_SquareEntity)
            {
                ImGui::Separator();
                const auto& tag = m_SquareEntity.GetComponent<TagComponent>().Tag;
                ImGui::Text("%s", tag.c_str());

                auto& squareColor = m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;
                ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
                ImGui::Separator();
            }

            ImGui::DragFloat3("Camera Transform",
                glm::value_ptr(m_CameraEntity.GetComponent<TransformComponent>().Transform[3]));

            if (ImGui::Checkbox("Camera A", &m_PrimaryCamera))
            {
                m_CameraEntity.GetComponent<CameraComponent>().Primary = m_PrimaryCamera;
                m_SecondCamera.GetComponent<CameraComponent>().Primary = !m_PrimaryCamera;
            }

            {
                auto& camera = m_SecondCamera.GetComponent<CameraComponent>().Camera;
                float orthoSize = camera.GetOrthographicSize();
                if (ImGui::DragFloat("Second Camera Ortho Size", &orthoSize))
                    camera.SetOrthographicSize(orthoSize);
            }
                
            ImGui::End();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });

        // Viewport panel
        {
            ImGui::Begin("Viewport");
            {
                m_ViewportFocused = ImGui::IsWindowFocused(); // is window focused?
                m_ViewportHovered = ImGui::IsWindowHovered(); // is mouse hovered over active window?
                Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered); // if viewport not focused, block events
            }
            ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
            m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

            uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
            ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
            ImGui::End();
        }

    	ImGui::PopStyleVar();

        ImGui::End();
    }

}
