#include "hrpch.hpp"

#include "Engine/Renderer/VertexArray.hpp"
#include "Engine/Renderer/Renderer.hpp"

#include "Engine/RHI/OpenGL/OpenGLVertexArray.hpp"

namespace Hyperion {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();

		case RendererAPI::API::None:    
			HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
