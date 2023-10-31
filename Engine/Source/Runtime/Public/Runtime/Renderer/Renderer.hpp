#pragma once

#include "Runtime/Renderer/Shader.hpp"
#include "Runtime/Renderer/RenderCommand.hpp"
#include "Runtime/Renderer/OrthographicCamera.hpp"

namespace Hyperion {

	class  HYPERION_API Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		
		static void BeginScene(OrthographicCamera& camera); // TODO: Add camera, environment, etc.
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray, glm::mat4 transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};

}
