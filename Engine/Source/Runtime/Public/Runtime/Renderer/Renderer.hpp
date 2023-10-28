#pragma once

#include "Runtime/Renderer/Shader.hpp"
#include "Runtime/Renderer/RenderCommand.hpp"
#include "Runtime/Renderer/OrthographicCamera.hpp"

namespace Hyperion {

	class  HYPERION_API Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera); // TODO: Add camera, environment, etc.
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>& vertexArray, glm::mat4 transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};

}
