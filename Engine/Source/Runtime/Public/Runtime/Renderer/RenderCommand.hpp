#pragma once

#include "Runtime/Renderer/RendererAPI.hpp"

namespace Hyperion {

	class HYPERION_API RenderCommand
	{
	public:
		static void Init()
		{
			s_RendererAPI->Init();
		}
		
		static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		static void SetViewport(const int x, const int y, const uint32_t width, const uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};

}
