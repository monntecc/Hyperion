#include "hrpch.hpp"

#include "Runtime/Renderer/RenderCommand.hpp"

#include "Runtime/RHI/OpenGL/OpenGLRendererAPI.hpp"

namespace Hyperion {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
