#include "pch.hpp"

#include "Runtime/RHI/OpenGL/OpenGLRendererAPI.hpp"

#include <glad/glad.h>
#include <Tracy.hpp>

namespace Hyperion
{
    void OpenGLMessageCallback(
        unsigned source,
        unsigned type,
        unsigned id,
        unsigned severity,
        int length,
        const char* message,
        const void* userParam)
    {
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            HR_CORE_CRITICAL(message);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            HR_CORE_ERROR(message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            HR_CORE_WARN(message);
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            HR_CORE_TRACE(message);
            break;
        default:
            HR_CORE_INFO(message);
            break;
        }
    }

    void OpenGLRendererAPI::Init()
    {
        ZoneScoped;

        #ifdef HR_DEBUG
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(OpenGLMessageCallback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
        #endif

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST); // Enable depth testing
    }

    void OpenGLRendererAPI::SetViewport(const int x, const int y, const uint32_t width, const uint32_t height)
    {
        glViewport(x, y, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
    {
        const GLsizei count = indexCount ? static_cast<GLsizei>(vertexArray->GetIndexBuffer()->GetCount()) : static_cast<GLsizei>(indexCount);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
