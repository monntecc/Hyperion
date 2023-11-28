#include "Editor/Layer/Sandbox2DLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include <Tracy.hpp>

Sandbox2DLayer::Sandbox2DLayer() : Layer("Sandbox2DLayer"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2DLayer::OnUpdate(Hyperion::Timestep timestep)
{
    FrameMarkNamed("Sandbox2DLayer::OnUpdate");
    
    // Update
    m_CameraController.OnUpdate(timestep);

    // Render
    {
        ZoneScoped;
        Hyperion::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Hyperion::RenderCommand::Clear();   
    }


    // Draw quads
    {
        ZoneScoped;
        Hyperion::Renderer2D::BeginScene(m_CameraController.GetCamera());
        // Draw a quads
        Hyperion::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        Hyperion::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
        Hyperion::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f, glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));
        Hyperion::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 20.0f, glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));
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
    
    //ImGui::Begin("Settings");
    //ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    //
    //ImGui::End();
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
