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
        static void Flush();

        // Primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color); // X,Y axis
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color); // X,Y,Z axis

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color); // Quad with rotation
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f)); // Quad with rotation
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

        struct Statistics
        {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t GetTotalVertexCount() const { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
        };

        static void ResetStats();
        static Statistics GetStats();
    private:
        static void FlushAndReset();
    };
    
}
