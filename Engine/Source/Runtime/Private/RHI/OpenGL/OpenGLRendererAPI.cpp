#include "pch.hpp"

#include "Runtime/RHI/OpenGL/OpenGLRendererAPI.hpp"

#include <glad/glad.h>

namespace Hyperion {
	
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST); // Enable depth testing
	}

	void OpenGLRendererAPI::SetViewport(const int x, const int y, const uint32_t width, const uint32_t height)
	{
		glViewport(x ,y, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, 
		    static_cast<GLsizei>(vertexArray->GetIndexBuffer()->GetCount()), 
			GL_UNSIGNED_INT, nullptr);
	}

}
