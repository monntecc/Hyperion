#include "hrpch.hpp"

#include "Runtime/Renderer/Shader.hpp"
#include "Runtime/Renderer/Renderer.hpp"

#include "Runtime/RHI/OpenGL/OpenGLShader.hpp"

namespace Hyperion {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(filepath);

		case RendererAPI::API::None:    
			HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
			return nullptr;
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);

		case RendererAPI::API::None:    
			HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
			return nullptr;
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		HR_CORE_ASSERT(Exists(name), "Shader '" + name +  "' already exists!")
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HR_CORE_ASSERT(Exists(name), "Shader '" + name +  "' already exists!")
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		const auto shader = Shader::Create(filepath);
		Add(shader);
		return m_Shaders.at(shader->GetName());
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		const auto shader = Shader::Create(filepath);
		Add(name, shader);
		return m_Shaders.at(shader->GetName());
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		HR_CORE_ASSERT(!Exists(name), "Shader '" + name +  "'not found!")
		return m_Shaders.at(name);
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.contains(name);
	}
}
