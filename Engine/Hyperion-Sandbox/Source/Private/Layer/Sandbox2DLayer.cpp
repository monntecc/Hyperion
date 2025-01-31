﻿#include "Sandbox/Layer/Sandbox2DLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <Tracy.hpp>

Sandbox2DLayer::Sandbox2DLayer() :
	Layer("Sandbox2DLayer"),
	m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2DLayer::OnAttach()
{
    ZoneScoped;

    m_CheckerboardTexture = Hyperion::Texture2D::Create("Assets/Textures/Checkerboard.png");
}

void Sandbox2DLayer::OnDetach()
{
    ZoneScoped;
}

void Sandbox2DLayer::OnUpdate(const Hyperion::Timestep timestep)
{
    FrameMarkNamed("Sandbox2DLayer::OnUpdate");
    
    // Update
    m_CameraController.OnUpdate(timestep);

    // Render
    Hyperion::Renderer2D::ResetStats();
    {
        ZoneScoped;

        Hyperion::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Hyperion::RenderCommand::Clear();   
    }


    // Draw quads
    {
        static float rotation = glm::radians(0.0f);
        rotation += timestep * glm::radians(50.0f);

        ZoneScoped;
        Hyperion::Renderer2D::BeginScene(m_CameraController.GetCamera());
        // Draw a quads
        Hyperion::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), {0.8f, 0.2f, 0.3f, 1.0f});
        Hyperion::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
        Hyperion::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
        Hyperion::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f, m_CheckerboardColor);
        Hyperion::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 4.0f, m_RotatedCheckerboardColor);
        Hyperion::Renderer2D::EndScene();

        Hyperion::Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f)  // NOLINT(cert-flp30-c)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f) // NOLINT(cert-flp30-c)
            {
                glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
                Hyperion::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
            }
        }
        Hyperion::Renderer2D::EndScene();
    }
}

void Sandbox2DLayer::OnEvent(Hyperion::Event& event)
{
    ZoneScoped;
    
    m_CameraController.OnEvent(event);
}

void Sandbox2DLayer::OnImGuiRender()
{
    ZoneScoped;

    ImGui::Begin("Settings");

    const auto stats = Hyperion::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

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