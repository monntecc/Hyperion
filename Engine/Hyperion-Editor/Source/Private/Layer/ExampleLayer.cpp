#include "Editor/Layer/ExampleLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f)
{
	m_VertexArray = Hyperion::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	const Hyperion::Ref<Hyperion::VertexBuffer> vertexBuffer = Hyperion::VertexBuffer::Create(
		vertices, sizeof(vertices));

	const Hyperion::BufferLayout layout = {
		{Hyperion::ShaderDataType::Float3, "a_Position"},
		{Hyperion::ShaderDataType::Float4, "a_Color"},
	};

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = {0, 1, 2};

	const Hyperion::Ref<Hyperion::IndexBuffer> indexBuffer = Hyperion::IndexBuffer::Create(
		indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA = Hyperion::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};

	const Hyperion::Ref<Hyperion::VertexBuffer> squareVB = Hyperion::VertexBuffer::Create(
		squareVertices, sizeof(squareVertices));

	squareVB->SetLayout({
		{Hyperion::ShaderDataType::Float3, "a_Position"},
		{Hyperion::ShaderDataType::Float2, "a_TexCoord"},
	});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};

	const Hyperion::Ref<Hyperion::IndexBuffer> squareIB = Hyperion::IndexBuffer::Create(
		squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

	m_SquareVA->SetIndexBuffer(squareIB);

	const std::string vertexSrc = R"(
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

	const std::string fragmentSrc = R"(
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

	m_Shader = Hyperion::Shader::Create("TriangleVertexPosColor", vertexSrc, fragmentSrc);

	const std::string flatColorVertexSrc = R"(
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

	const std::string flatColorFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);

			}
		)";

	m_FlatColorShader = Hyperion::Shader::Create("FlatColor", flatColorVertexSrc, flatColorFragmentSrc);

	const auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

	m_Texture = Hyperion::Texture2D::Create("Assets/Textures/Checkerboard.png");
	m_HyperionLogoTexture = Hyperion::Texture2D::Create("Assets/Textures/HyperionLogo.png");

	// textureShader->Bind();
	// textureShader->SetIntArray("u_Textures", 0);
}


void ExampleLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void ExampleLayer::OnUpdate(Hyperion::Timestep timestep)
{
	m_CameraController.OnUpdate(timestep);
	
    Hyperion::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f,  1 });
    Hyperion::RenderCommand::Clear();

    Hyperion::Renderer::BeginScene(m_CameraController.GetCamera());

    const static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    m_FlatColorShader->Bind();
    m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            const glm::vec3 pos(static_cast<float>(x) * 0.11f, static_cast<float>(y) * 0.11f, 0.0f);
            const glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
            Hyperion::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
        }
    }

    const auto textureShader = m_ShaderLibrary.Get("Texture");

    m_Texture->Bind();
    Hyperion::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    m_HyperionLogoTexture->Bind();
    Hyperion::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    // Triangle
    // Hyperion::Renderer::Submit(m_Shader, m_VertexArray);

    Hyperion::Renderer::EndScene(); 
}

void ExampleLayer::OnEvent(Hyperion::Event& event)
{
	m_CameraController.OnEvent(event);
}
