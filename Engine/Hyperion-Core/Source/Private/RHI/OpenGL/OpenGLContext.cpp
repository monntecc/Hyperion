#include "hrpch.hpp"

#include "Runtime/RHI/OpenGL/OpenGLContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Tracy.hpp>

namespace Hyperion {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HR_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		ZoneScoped;
		
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		HR_CORE_ASSERT(status, "Failed to initialize Glad!");

		HR_CORE_INFO("OpenGL Info:");
		HR_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		HR_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		HR_CORE_INFO("  Version: {0}\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

	#ifdef HR_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		HR_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hyperion requires at least OpenGL version 4.5!");
	#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		ZoneScoped;
		
		glfwSwapBuffers(m_WindowHandle);
	}

}
