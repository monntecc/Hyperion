#include "pch.hpp"

#include "Runtime/Renderer/RenderCommand.hpp"

#include "Runtime/RHI/OpenGL/OpenGLRendererAPI.hpp"

namespace Hyperion {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
