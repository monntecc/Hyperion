#pragma once

#include "Runtime/Renderer/OrthographicCamera.hpp"
#include "Runtime/Renderer/Texture.hpp"

#include <glm/glm.hpp>

namespace Hyperion {

    class HYPERION_API Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();
        
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        // Primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color); // X,Y axis
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color); // X,Y,Z axis

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D>& texture);
    };
    
}
