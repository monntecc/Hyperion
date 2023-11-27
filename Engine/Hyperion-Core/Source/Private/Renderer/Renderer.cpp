#include "hrpch.hpp"

#include "Runtime/Renderer/Renderer.hpp"
#include "Runtime/Renderer/Renderer2D.hpp"

#include <Tracy.hpp>

namespace Hyperion {

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<SceneData>();

	void Renderer::Init()
	{
		ZoneScoped;
		
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(const uint32_t width, const uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, 
		const Ref<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix); // ViewProjection is the view projection matrix
		shader->SetMat4("u_Transform", transform); // Transform is the model matrix

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray, vertexArray->GetIndexBuffer()->GetCount());
	}

}
