#include "hrpch.hpp"

#include "Engine/Renderer/FrameBuffer.hpp"
#include "Engine/Renderer/Renderer.hpp"

#include "Engine/RHI/OpenGL/OpenGLFrameBuffer.hpp"

namespace Hyperion {

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFrameBuffer>(specification);

		case RendererAPI::API::None:
			HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	
}
