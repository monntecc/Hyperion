#include "Editor/Layer/Sandbox2DLayer.hpp"

#include "Runtime/RHI/OpenGL/OpenGLShader.hpp"

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

    Hyperion::Renderer::BeginScene(m_CameraController.GetCamera());

    std::dynamic_pointer_cast<Hyperion::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Hyperion::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
    
    Hyperion::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Hyperion::Renderer::EndScene(); 
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
    m_SquareVA = Hyperion::VertexArray::Create();

    float squareVertices[3 * 4] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    const Hyperion::Ref<Hyperion::VertexBuffer> squareVB = Hyperion::VertexBuffer::Create(
        squareVertices, sizeof(squareVertices));

    squareVB->SetLayout({
        {Hyperion::ShaderDataType::Float3, "a_Position"},
    });
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    const Hyperion::Ref<Hyperion::IndexBuffer> squareIB = Hyperion::IndexBuffer::Create(
        squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Hyperion::Shader::Create("Assets/Shaders/FlatColor.glsl");
}

void Sandbox2DLayer::OnDetach()
{
}
