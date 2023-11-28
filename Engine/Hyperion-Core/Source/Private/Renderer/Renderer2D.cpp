#include "hrpch.hpp"

#include "Runtime/Renderer/Renderer2D.hpp"

#include "Runtime/Renderer/RenderCommand.hpp"
#include "Runtime/Renderer/Shader.hpp"
#include "Runtime/Renderer/VertexArray.hpp"

#include <glm/ext/matrix_transform.hpp>

#include <Tracy.hpp>

namespace Hyperion {

    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIndex; // Texture index
        float TilingFactor;
    };
    
    struct RendererData
    {
        static constexpr uint32_t MaxQuads = 20000;
        static constexpr uint32_t MaxVertices = MaxQuads * 4;
        static constexpr uint32_t MaxIndices = MaxQuads * 6;
        static constexpr uint32_t MaxTextureSlots = 32; // TODO: Render capabilities

        static constexpr size_t QuadVertexCount = 4;
        static constexpr glm::vec2 QuadTextureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        static constexpr glm::vec4 QuadWhiteColor = glm::vec4(1.0f);
        
        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1; // 0  = white texture

        glm::vec4 QuadVertexPositions[4];

        Renderer2D::Statistics Stats;
    };

    static RendererData s_Data;

    void Renderer2D::Init()
    {
        ZoneScoped;

        s_Data.QuadVertexArray = VertexArray::Create();
        s_Data.QuadVertexBuffer = VertexBuffer::Create(RendererData::MaxVertices * sizeof(QuadVertex));

        s_Data.QuadVertexBuffer->SetLayout({
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
            {ShaderDataType::Float2, "a_TexCoord"},
            {ShaderDataType::Float, "a_TexIndex"},
            {ShaderDataType::Float, "a_TilingFactor"},
        });
        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
        s_Data.QuadVertexBufferBase = new QuadVertex[RendererData::MaxVertices];
        
        const auto quadIndices = new uint32_t[RendererData::MaxIndices];
        uint32_t offset = 0;
        
        for (uint32_t i = 0; i < RendererData::MaxIndices; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        const Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, RendererData::MaxIndices);
        s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
        delete[] quadIndices;

        s_Data.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        int32_t samplers[32];
        for (int32_t i = 0; i < static_cast<int32_t>(RendererData::MaxTextureSlots); i++)
            samplers[i] = i;

        s_Data.TextureShader = Shader::Create("Assets/Shaders/Texture.hrsf");
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetIntArray("u_Textures", samplers, RendererData::MaxTextureSlots);

        // Set white texture to first slot
        s_Data.TextureSlots[0] = s_Data.WhiteTexture;

        s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };
    }

    void Renderer2D::Shutdown()
    {
        ZoneScoped;

        delete[] s_Data.QuadVertexBufferBase;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        ZoneScoped;

        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1;
    }

    void Renderer2D::EndScene()
    {
        ZoneScoped;

        const auto dataSize = reinterpret_cast<uint8_t*>(s_Data.QuadVertexBufferPtr) - reinterpret_cast<uint8_t*>(s_Data.QuadVertexBufferBase);
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, static_cast<uint32_t>(dataSize));

        Flush();
    }

    void Renderer2D::Flush()
    {
	    ZoneScoped;

	    // Bind textures
	    for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
            s_Data.TextureSlots[i]->Bind(i);

	    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

        s_Data.Stats.DrawCalls++;
    }

    void Renderer2D::FlushAndReset()
    {
        EndScene();

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1;
    }


    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        ZoneScoped;

        if (s_Data.QuadIndexCount >= RendererData::MaxIndices)
            FlushAndReset();

        const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        for (size_t i = 0; i < RendererData::QuadVertexCount; i++)
        {
	        constexpr float textureIndex = 0.0f;
            constexpr float tilingFactor = 0.0f; // tiling factor

	        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = RendererData::QuadTextureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, Ref<Texture2D>& texture,
                              float tilingFactor, const glm::vec4& tintColor)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, Ref<Texture2D>& texture,
                              float tilingFactor, const glm::vec4& tintColor)
    {
        ZoneScoped;

        if (s_Data.QuadIndexCount >= RendererData::MaxIndices)
            FlushAndReset();

        constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        float textureIndex = 0.0f;

        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        {
	        if (*s_Data.TextureSlots[i] == *texture.get())
	        {
                textureIndex = static_cast<float>(i);
                break;
	        }
        }

        if (textureIndex == 0.0f)
        {
            if (s_Data.TextureSlotIndex >= RendererData::MaxTextureSlots)
                FlushAndReset();

            textureIndex = static_cast<float>(s_Data.TextureSlotIndex);
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        for (size_t i = 0; i < RendererData::QuadVertexCount; i++)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = tintColor;
            s_Data.QuadVertexBufferPtr->TexCoord = RendererData::QuadTextureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
                                     const glm::vec4& color)
    {
        DrawRotatedQuad({position.x, position.y, 1.0f}, size, rotation, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
                                     const glm::vec4& color)
    {
        ZoneScoped;

        if (s_Data.QuadIndexCount >= RendererData::MaxIndices)
            FlushAndReset();

        const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        for (size_t i = 0; i < RendererData::QuadVertexCount; i++)
        {
	        constexpr float tilingFactor = 0.0f;
	        constexpr float textureIndex = 0.0f;

	        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = RendererData::QuadTextureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
                                     Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        DrawRotatedQuad({position.x, position.y, 1.0f}, size, rotation, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
                                     Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        ZoneScoped;

        if (s_Data.QuadIndexCount >= RendererData::MaxIndices)
            FlushAndReset();

        constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        float textureIndex = 0.0f;

        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        {
            if (*s_Data.TextureSlots[i] == *texture.get())
            {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            if (s_Data.TextureSlotIndex >= RendererData::MaxTextureSlots)
                FlushAndReset();

            textureIndex = static_cast<float>(s_Data.TextureSlotIndex);
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
    		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
    		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        for (size_t i = 0; i < RendererData::QuadVertexCount; i++)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = tintColor;
            s_Data.QuadVertexBufferPtr->TexCoord = RendererData::QuadTextureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::ResetStats()
    {
        memset(&s_Data.Stats, 0, sizeof(Statistics));
    }

    Renderer2D::Statistics Renderer2D::GetStats()
    {
        return s_Data.Stats;
    }
}
