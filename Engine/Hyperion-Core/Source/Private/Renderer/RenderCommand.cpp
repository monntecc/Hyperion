#include "hrpch.hpp"

#include "Engine/Renderer/RenderCommand.hpp"

#include "Engine/RHI/OpenGL/OpenGLRendererAPI.hpp"

namespace Hyperion {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
