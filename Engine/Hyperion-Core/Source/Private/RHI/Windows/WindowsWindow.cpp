#include "hrpch.hpp"

#include "Engine/Core/Application.hpp"
#include "Engine/Events/ApplicationEvent.hpp"
#include "Engine/Events/KeyEvent.hpp"
#include "Engine/Events/MouseEvent.hpp"

#include "Engine/RHI/OpenGL/OpenGLContext.hpp"
#include "Engine/RHI/Windows/WindowsWindow.hpp"

#include "Engine/Renderer/Renderer.hpp"

#include <Tracy.hpp>
#include <imgui.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Hyperion {

	static uint32_t s_GLFWWindowCount = 0;

	WindowsWindow::WindowsWindow(const WindowProps& props) 
		: m_WindowProps(props)
	{
		WindowsWindow::Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		WindowsWindow::Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		ZoneScoped;
		
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HR_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0)
		{
			ZoneScoped;
			
			HR_CORE_INFO("Initializing GLFW");
			const int _ = glfwInit();

			glfwSetErrorCallback([](int error, const char* description)
			{
				HR_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
			});

			HR_CORE_ASSERT(_, "Could not initialize GLFW!");

			++s_GLFWWindowCount;
		}

		#if defined(HR_DEBUG)
			if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif

		m_Window = glfwCreateWindow(static_cast<int>(props.Width), 
			static_cast<int>(props.Height), m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		// Hide system titlebar
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, GLFW_FALSE);

		glfwSetWindowUserPointer(m_Window, this);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))->m_Data;
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			const WindowData& data = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))->m_Data;
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			const WindowData& data = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))->m_Data;

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				default: break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			const WindowData& data = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))->m_Data;

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowsWindow& windowHandle = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					windowHandle.m_Data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					windowHandle.m_Data.EventCallback(event);
					break;
				}
				
				default: break;
			}

			if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT)
			{
				double xPos, yPos;
				int width, height;
				glfwGetCursorPos(window, &xPos, &yPos);
				glfwGetWindowSize(window, &width, &height);

				const int borderSize = 4;
				if (xPos < borderSize || yPos < borderSize || xPos > width - borderSize || yPos > height - borderSize)
					windowHandle.StartResize(WindowBorder::TopLeft);
				if (xPos > width - borderSize || yPos < borderSize || xPos < borderSize || yPos > height - borderSize)
					windowHandle.StartResize(WindowBorder::TopRight);
				if (xPos < borderSize || yPos > height - borderSize || xPos > width - borderSize || yPos < borderSize)
					windowHandle.StartResize(WindowBorder::BottomLeft);
				if (xPos > width - borderSize || yPos > height - borderSize || xPos < borderSize || yPos < borderSize)
					windowHandle.StartResize(WindowBorder::BottomRight);
				if (xPos < borderSize || yPos < height - borderSize || xPos > width - borderSize || yPos > height - borderSize)
					windowHandle.StartResize(WindowBorder::Bottom);
				if (xPos < width - borderSize || yPos < borderSize || xPos > width - borderSize || yPos > height - borderSize)
					windowHandle.StartResize(WindowBorder::Right);
				if (xPos < borderSize || yPos < borderSize || xPos < width - borderSize || yPos > borderSize)
					windowHandle.StartResize(WindowBorder::Left);
				if(xPos < width - borderSize || yPos < borderSize || xPos > width - borderSize || yPos < height - borderSize)
					windowHandle.StartResize(WindowBorder::Top);
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			const WindowData& data = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))->m_Data;

			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowsWindow& windowHandle = *static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			windowHandle.m_Data.EventCallback(event);
		});
	}
	
	void WindowsWindow::Shutdown()
	{
		ZoneScoped;
		
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			HR_CORE_INFO("Terminating GLFW...");
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		ZoneScoped;
		
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		ZoneScoped;
		
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::StartDrag() const
	{
		if (!m_Window)
			return;

		ReleaseCapture();
		SendMessageA(glfwGetWin32Window(m_Window), WM_NCLBUTTONDOWN, HTCAPTION, 0);
	}

	void WindowsWindow::StartResize(WindowBorder border) const
	{
		if (!m_Window)
			return;

		// Convert from GLFW border to Windows border
		WPARAM windowsBorder = 0;
		switch (border)
		{
			case WindowBorder::Left: windowsBorder = HTLEFT; break;
			case WindowBorder::Top: windowsBorder = HTTOP; break;
			case WindowBorder::Right: windowsBorder = HTRIGHT; break;
			case WindowBorder::Bottom: windowsBorder = HTBOTTOM; break;
			case WindowBorder::TopLeft: windowsBorder = HTTOPLEFT; break;
			case WindowBorder::TopRight: windowsBorder = HTTOPRIGHT; break;
			case WindowBorder::BottomLeft: windowsBorder = HTBOTTOMLEFT; break;
			case WindowBorder::BottomRight: windowsBorder = HTBOTTOMRIGHT; break;
		}

		// Resize window
		ReleaseCapture();
		SendMessageA(glfwGetWin32Window(m_Window), WM_NCLBUTTONDOWN, windowsBorder, 0);
	}

	bool WindowsWindow::IsMaximized() const
	{
		return static_cast<bool>(glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED));
	}

	bool WindowsWindow::IsMinimized() const
	{
		return static_cast<bool>(glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED));
	}

	void WindowsWindow::Maximize(bool restore) const
	{
		if (!m_Window)
			return;

		if (restore)
			glfwRestoreWindow(m_Window);
		else
			glfwMaximizeWindow(m_Window);
	}

	void WindowsWindow::Minimize() const
	{
		if (!m_Window)
			return;

		glfwIconifyWindow(m_Window);
	}

}
