#include "pch.hpp"

#include "Runtime/Renderer/VertexArray.hpp"
#include "Runtime/Renderer/Renderer.hpp"

#include "Runtime/RHI/OpenGL/OpenGLVertexArray.hpp"

namespace Hyperion {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();

		case RendererAPI::API::None:    
			HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
