#include "pch.hpp"

#include "Runtime/RHI/OpenGL/OpenGLBuffer.hpp"

#include <glad/glad.h>

#include <Tracy.hpp>

namespace Hyperion {

	// ----------------- VERTEX BUFFER -----------------

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		ZoneScoped;
		
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		ZoneScoped;
		
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		ZoneScoped;
		
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		ZoneScoped;
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// ----------------- INDEX BUFFER -----------------

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		ZoneScoped;
		
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(count * sizeof(uint32_t)),
			indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		ZoneScoped;
		
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		ZoneScoped;
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		ZoneScoped;
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

} 
