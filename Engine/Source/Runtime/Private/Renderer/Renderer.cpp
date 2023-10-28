#include "pch.hpp"

#include "Runtime/Renderer/Renderer.hpp"

namespace Hyperion {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", 
			s_SceneData->ViewProjectionMatrix); // ViewProjection is the view projection matrix
		shader->UploadUniformMat4("u_Transform", transform); // Transform is the model matrix

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
