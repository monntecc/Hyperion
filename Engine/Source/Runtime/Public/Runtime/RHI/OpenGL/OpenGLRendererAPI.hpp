#pragma once

#include "Runtime/Renderer/RendererAPI.hpp"

namespace Hyperion {

	class HYPERION_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;
		
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};

}
