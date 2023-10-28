#include "pch.hpp"

#include "Runtime/Renderer/Renderer.hpp"

#include "Runtime/RHI/OpenGL/OpenGLShader.hpp"

namespace Hyperion {

	Renderer::SceneData* Renderer::s_SceneData = new SceneData;

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
		 std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", 
			s_SceneData->ViewProjectionMatrix); // ViewProjection is the view projection matrix
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform); // Transform is the model matrix

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
