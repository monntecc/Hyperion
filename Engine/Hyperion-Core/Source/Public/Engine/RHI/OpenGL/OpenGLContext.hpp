#pragma once

#include "Engine/Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace Hyperion {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}
