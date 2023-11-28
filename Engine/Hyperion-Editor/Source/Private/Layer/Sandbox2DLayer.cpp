#include "Editor/Layer/Sandbox2DLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <Tracy.hpp>

Sandbox2DLayer::Sandbox2DLayer() :
	Layer("Sandbox2DLayer"),
	m_CameraController(1280.0f / 720.0f),
	m_Particle()
{
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
        Hyperion::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
        Hyperion::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f, { 0.3f, 0.5f, 0.4f, 1.0f });
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

    if (Hyperion::Input::IsMouseButtonPressed(HR_MOUSE_BUTTON_LEFT))
    {
        auto [x, y] = Hyperion::Input::GetMousePosition();
        const auto width = static_cast<float>(Hyperion::Application::Get().GetWindow().GetWidth());
        const auto height = static_cast<float>(Hyperion::Application::Get().GetWindow().GetHeight());

        const auto bounds = m_CameraController.GetBounds();
        const auto pos = m_CameraController.GetCamera().GetPosition();
        x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
        y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
        m_Particle.Position = { x + pos.x, y + pos.y };
        for (int i = 0; i < 50; i++)
            m_ParticleSystem.Emit(m_Particle);
    }

    m_ParticleSystem.OnUpdate(timestep);
    m_ParticleSystem.OnRender(m_CameraController.GetCamera());
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

    ImGui::Separator();

    ImGui::Text("Particle Stats:");
    ImGui::ColorEdit4("Birth Color", glm::value_ptr(m_Particle.ColorBegin));
    ImGui::ColorEdit4("Death Color", glm::value_ptr(m_Particle.ColorEnd));
    ImGui::DragFloat("Life Time", &m_Particle.LifeTime, 0.1f, 0.0f, 1000.0f);

    ImGui::Separator();

    ImGui::Text("Scene Configuration:");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    
    ImGui::End();
}

void Sandbox2DLayer::OnAttach()
{
    ZoneScoped;

    m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
    m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
    m_Particle.SizeBegin = 0.5f;
    m_Particle.SizeVariation = 0.3f;
	m_Particle.SizeEnd = 0.0f;
    m_Particle.LifeTime = 5.0f;
    m_Particle.Velocity = { 0.0f, 0.0f };
    m_Particle.VelocityVariation = { 3.0f, 1.0f };
    m_Particle.Position = { 0.0f, 0.0f };
    
    m_CheckerboardTexture = Hyperion::Texture2D::Create("Assets/Textures/Checkerboard.png");  
}

void Sandbox2DLayer::OnDetach()
{
    ZoneScoped;
}
