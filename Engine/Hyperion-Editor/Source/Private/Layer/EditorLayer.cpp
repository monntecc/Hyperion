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

    void EditorLayer::OnUpdate(const Timestep timestep)
    {
        FrameMarkNamed("EditorLayer::OnUpdate");

        // Update
        m_CameraController.OnUpdate(timestep);

        // Render
        Renderer2D::ResetStats();
        {
            ZoneScoped;

            m_FrameBuffer->Bind();

            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RenderCommand::Clear();
        }


        // Draw quads
        {
            static float rotation = glm::radians(0.0f);
            rotation += timestep * glm::radians(50.0f);

            ZoneScoped;
            Renderer2D::BeginScene(m_CameraController.GetCamera());
            // Draw a quads
            Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
            Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
            Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
            Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f, m_CheckerboardColor);
            Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 4.0f, m_RotatedCheckerboardColor);
            Renderer2D::EndScene();

            Renderer2D::BeginScene(m_CameraController.GetCamera());
            for (float y = -5.0f; y < 5.0f; y += 0.5f)  // NOLINT(cert-flp30-c)
            {
                for (float x = -5.0f; x < 5.0f; x += 0.5f) // NOLINT(cert-flp30-c)
                {
                    glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
                    Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
                }
            }
            Renderer2D::EndScene();
            m_FrameBuffer->Unbind();
        }
    }

    void EditorLayer::OnEvent(Event& event)
    {
        ZoneScoped;

        m_CameraController.OnEvent(event);
    }

    void EditorLayer::OnImGuiRender()
    {
        ZoneScoped;

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
            ImGui::End();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });

        // Viewport panel
        {
            ImGui::Begin("Viewport");
            ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
            if (m_ViewportSize != *reinterpret_cast<glm::vec2*>(&viewportPanelSize))
            {
                m_FrameBuffer->Resize(static_cast<uint32_t>(viewportPanelSize.x), 
                    static_cast<uint32_t>(viewportPanelSize.y));
                m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

                m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            }

            const auto textureID = reinterpret_cast<void*>(m_FrameBuffer->GetColorAttachmentRendererID());  // NOLINT(performance-no-int-to-ptr)
            ImGui::Image(textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });
            ImGui::End();
        }

    	ImGui::PopStyleVar();

        ImGui::End();
    }

    void EditorLayer::OnAttach()
    {
        ZoneScoped;
        m_CheckerboardTexture = Texture2D::Create("Assets/Textures/Checkerboard.png");

		FrameBufferSpecification specification = {};
        specification.Width = 1280;
        specification.Height = 720;
        m_FrameBuffer = FrameBuffer::Create(specification);
    }

    void EditorLayer::OnDetach()
    {
        ZoneScoped;
    }

}
