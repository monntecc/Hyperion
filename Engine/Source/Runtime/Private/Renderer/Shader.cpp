#include "pch.hpp"

#include "Runtime/Renderer/Shader.hpp"
#include "Runtime/Renderer/Renderer.hpp"

#include "Runtime/RHI/OpenGL/OpenGLShader.hpp"

namespace Hyperion {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);

		case RendererAPI::API::None:    
			HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);

		case RendererAPI::API::None:    
			HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
