#include "Editor/Layer/Sandbox2DLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2DLayer::Sandbox2DLayer() : Layer("Sandbox2DLayer"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2DLayer::OnUpdate(Hyperion::Timestep timestep)
{
    m_CameraController.OnUpdate(timestep);

    Hyperion::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Hyperion::RenderCommand::Clear();

    Hyperion::Renderer2D::BeginScene(m_CameraController.GetCamera());
    // Draw a quads
    Hyperion::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Hyperion::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    // Draw a texture
    Hyperion::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
    Hyperion::Renderer2D::EndScene(); 

    // TODO Add these functions: Shader::SetMat4, Shader::SetFloat4
    // std::dynamic_pointer_cast<Hyperion::OpenGLShader>(m_FlatColorShader)->Bind();
    // std::dynamic_pointer_cast<Hyperion::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2DLayer::OnEvent(Hyperion::Event& event)
{
    m_CameraController.OnEvent(event);
}

void Sandbox2DLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2DLayer::OnAttach()
{
    m_CheckerboardTexture = Hyperion::Texture2D::Create("Assets/Textures/Checkerboard.png");  
}

void Sandbox2DLayer::OnDetach()
{
}
