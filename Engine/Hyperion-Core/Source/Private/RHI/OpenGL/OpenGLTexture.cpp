#include "hrpch.hpp"

#include "Engine/RHI/OpenGL/OpenGLTexure.hpp"

#include <stb_image.h>

#include <Tracy.hpp>

namespace Hyperion
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        : m_Path(path)
    {
        ZoneScoped;
        
        int width, height, channels;
        //stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        
        HR_CORE_ASSERT(data, "Failed to load image!");
        m_Width = width;
        m_Height = height;

        if (channels == 4)
        {
            m_InternalFormat = GL_RGBA8;
            m_DataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            m_InternalFormat = GL_RGB8;
            m_DataFormat = GL_RGB;
        }

        HR_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height));

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height),
                            m_DataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height)
    {
        ZoneScoped;
        
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height));

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        ZoneScoped;
        
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::SetData(void* data, uint32_t size)
    {
        ZoneScoped;
        
        // Check bytes per pixel (buffer must to be a size of entire texture) 
        uint32_t bytesPerPixel = m_DataFormat == GL_RGBA ? 4 : 3;
        HR_CORE_ASSERT(size == m_Width * m_Height * bytesPerPixel, "Data must be entire texture!");
        
        glTextureSubImage2D(m_RendererID, 0, 0, 0, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height),
                             m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        ZoneScoped;
        
        glBindTextureUnit(slot, m_RendererID);
    }

    GLenum OpenGLTexture2D::ImageFormatToGL(UI::ImageFormat format) const
    {
        switch (format)
        {
        case UI::ImageFormat::RGBA:    return GL_RGBA;
        case UI::ImageFormat::RGBA32F: return GL_RGBA32F;
        }

        HR_CORE_ASSERT(false, "Unknown ImageFormat!");
        return 0;
    }
}
