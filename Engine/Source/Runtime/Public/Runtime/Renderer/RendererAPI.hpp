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
	public:
		virtual void SetClearColor(const glm::vec4& color);
		virtual void Clear();

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray);

		inline static API GetAPI() { return s_RendererAPI; }
	private:
		static API s_RendererAPI;
	};

}
