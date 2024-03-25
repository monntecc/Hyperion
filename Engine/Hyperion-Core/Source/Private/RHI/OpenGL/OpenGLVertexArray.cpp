#include "hrpch.hpp"

#include "Runtime/RHI/OpenGL/OpenGLVertexArray.hpp"

#include <glad/glad.h>

#include <Tracy.hpp>

namespace Hyperion {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
				return GL_FLOAT;

			case ShaderDataType::Int:      
			case ShaderDataType::Int2:     
			case ShaderDataType::Int3:     
			case ShaderDataType::Int4:
				return GL_INT;

			case ShaderDataType::Bool:     
				return GL_BOOL;

			case ShaderDataType::None:     
				break;
		}

		HR_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		ZoneScoped;
		
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		ZoneScoped;
		
		glDeleteVertexArrays(1, &m_RendererID);
	} 

	void OpenGLVertexArray::Bind() const
	{
		ZoneScoped;
	
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		ZoneScoped;
		
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		ZoneScoped;
		
		HR_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index,
						static_cast<uint8_t>(element.GetComponentCount()),
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						reinterpret_cast<const void*>(element.Offset));
					index++;
					break;
				}

				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					const auto count = static_cast<uint8_t>(element.GetComponentCount());
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(index);
						glVertexAttribPointer(index,
							count,
							ShaderDataTypeToOpenGLBaseType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							reinterpret_cast<const void*>(element.Offset + sizeof(float) * count * i));
						glVertexAttribDivisor(index, 1);
						index++;
					}
					break;
				}

				case ShaderDataType::None:
					HR_CORE_ASSERT(false, "Unknown ShaderDataType!");
				}
		}

		m_VertexBuffers.push_back(vertexBuffer);
		m_VertexBufferIndexOffset += static_cast<uint32_t>(layout.GetElements().size());
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		ZoneScoped;
		
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		
		m_IndexBuffer = indexBuffer;
	}

}
