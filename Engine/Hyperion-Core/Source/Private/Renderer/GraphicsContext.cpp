#include "hrpch.hpp"

#include "Runtime/Renderer/GraphicsContext.hpp"

#include "Runtime/Renderer/Renderer.hpp"
#include "Runtime/RHI/OpenGL/OpenGLContext.hpp"

namespace Hyperion {

    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        HR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}