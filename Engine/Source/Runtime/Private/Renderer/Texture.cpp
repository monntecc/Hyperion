#include "pch.hpp"

#include "Runtime/Renderer/Texture.hpp"
#include "Runtime/Renderer/Renderer.hpp"

#include "Runtime/RHI/OpenGL/OpenGLTexure.hpp"

namespace Hyperion {
    
    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path);

        case RendererAPI::API::None:    
            HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        }

        HR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(width, height);

        case RendererAPI::API::None:    
            HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        }

        HR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
