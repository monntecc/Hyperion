#include "pch.hpp"

#include "Runtime/Renderer/Buffer.hpp"
#include "Runtime/Renderer/Renderer.hpp"

#include "Runtime/RHI/OpenGL/OpenGLBuffer.hpp"

namespace Hyperion {
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);

		case RendererAPI::API::None:
			HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(vertices, size);

			case RendererAPI::API::None:
				HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, count);

		case RendererAPI::API::None:
			HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
