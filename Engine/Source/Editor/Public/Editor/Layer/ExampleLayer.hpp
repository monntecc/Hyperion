#pragma once

#include "Hyperion.hpp"

#include "Runtime/RHI/OpenGL/OpenGLShader.hpp"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Hyperion::Layer
{
public:
    ExampleLayer()
        : Layer("Example"),
          m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
          m_CameraPosition(0.0f)
    {
        m_VertexArray = Hyperion::VertexArray::Create();

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        Hyperion::Ref<Hyperion::VertexBuffer> vertexBuffer;
        vertexBuffer = Hyperion::VertexBuffer::Create(vertices, sizeof(vertices));

        const Hyperion::BufferLayout layout = {
            {Hyperion::ShaderDataType::Float3, "a_Position"},
            {Hyperion::ShaderDataType::Float4, "a_Color"},
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };

        Hyperion::Ref<Hyperion::IndexBuffer> indexBuffer;
        indexBuffer = Hyperion::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA = Hyperion::VertexArray::Create();

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        Hyperion::Ref<Hyperion::VertexBuffer> squareVB;
        squareVB = Hyperion::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

        squareVB->SetLayout({
            {Hyperion::ShaderDataType::Float3, "a_Position"},
            {Hyperion::ShaderDataType::Float2, "a_TexCoord"},
        });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        Hyperion::Ref<Hyperion::IndexBuffer> squareIB;
        squareIB = Hyperion::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;

			}
		)";

        m_Shader = Hyperion::Shader::Create(vertexSrc, fragmentSrc);

        std::string flatColorVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

        std::string flatColorFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);

			}
		)";

        m_FlatColorShader = Hyperion::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc);

    	std::string textureVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

    	std::string textureFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);

			}
		)";

    	m_TextureShader = Hyperion::Shader::Create(textureVertexSrc, textureFragmentSrc);

    	m_Texture = Hyperion::Texture2D::Create("Assets/Textures/Checkerboard.png");
    }

    void OnUpdate(Hyperion::Timestep timestep) override
    {
        // Move camera using WASD keys
        if (Hyperion::Input::IsKeyPressed(HR_KEY_W))
            m_CameraPosition.y += m_CameraMoveSpeed * timestep;
        else if (Hyperion::Input::IsKeyPressed(HR_KEY_S))
            m_CameraPosition.y -= m_CameraMoveSpeed * timestep;

        if (Hyperion::Input::IsKeyPressed(HR_KEY_A))
            m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
        else if (Hyperion::Input::IsKeyPressed(HR_KEY_D))
            m_CameraPosition.x += m_CameraMoveSpeed * timestep;

        // Rotate camera using QE keys
        if (Hyperion::Input::IsKeyPressed(HR_KEY_Q))
            m_CameraRotation -= m_CameraRotationSpeed * timestep;
        else if (Hyperion::Input::IsKeyPressed(HR_KEY_E))
            m_CameraRotation += m_CameraRotationSpeed * timestep;

        Hyperion::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Hyperion::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Hyperion::Renderer::BeginScene(m_Camera);

        const static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Hyperion::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Hyperion::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3(
            "u_Color", m_SquareColor);

    	std::dynamic_pointer_cast<Hyperion::OpenGLShader>(m_TextureShader)->Bind();
    	std::dynamic_pointer_cast<Hyperion::OpenGLShader>(m_TextureShader)->UploadUniformInt(
			"u_Texture", 0);

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                const glm::vec3 pos(static_cast<float>(x) * 0.11f, static_cast<float>(y) * 0.11f, 0.0f);
                const glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Hyperion::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

    	m_Texture->Bind();
        Hyperion::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // Triangle
        // Hyperion::Renderer::Submit(m_Shader, m_VertexArray);

        Hyperion::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }


    void OnEvent(Hyperion::Event& event) override
    {
    }

private:
    Hyperion::Ref<Hyperion::Shader> m_Shader;
    Hyperion::Ref<Hyperion::VertexArray> m_VertexArray;

    Hyperion::Ref<Hyperion::Shader> m_FlatColorShader, m_TextureShader;
    Hyperion::Ref<Hyperion::VertexArray> m_SquareVA;

	Hyperion::Ref<Hyperion::Texture2D> m_Texture;

    Hyperion::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;

    float m_CameraMoveSpeed = 5.0f; // meters per second

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f; // degrees per second

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};
