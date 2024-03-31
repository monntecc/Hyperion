#include "hrpch.hpp"

#include "Engine/Renderer/RendererAPI.hpp"

#include "Engine/RHI/OpenGL/OpenGLRendererAPI.hpp"

namespace Hyperion {

	RendererAPI::API RendererAPI::s_RendererAPI = API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_RendererAPI)
		{
		case API::None:
			HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			
		case API::OpenGL:
			return CreateScope<OpenGLRendererAPI>();
		}

		HR_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
