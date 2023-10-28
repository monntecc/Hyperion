#pragma once

#include "Runtime/Renderer/Texture.hpp"

namespace Hyperion {

    class HYPERION_API OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;
        
        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }
        
        void Bind(uint32_t slot) const override;
    private:
        std::string m_Path;
        
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
    };
    
}
