#pragma once

#include <glm/glm.hpp>

#include "Runtime/Renderer/VertexArray.hpp"

namespace Hyperion {

	class HYPERION_API RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;
		
		enum class API
		{
			None = 0,
			OpenGL = 1,
			// DirectX = 2,
			// Vulkan = 3
		};

		virtual void Init() = 0;
		
		virtual void SetViewport(int x, int y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return s_RendererAPI; }
		static Scope<RendererAPI> Create();
	private:
		static API s_RendererAPI;
	};

}
