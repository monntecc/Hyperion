#include "hrpch.hpp"

#include "Engine/Core/Application.hpp"
#include "Engine/Events/ApplicationEvent.hpp"
#include "Engine/Events/KeyEvent.hpp"
#include "Engine/Events/MouseEvent.hpp"

#include "Engine/RHI/OpenGL/OpenGLContext.hpp"
#include "Engine/RHI/Linux/LinuxWindow.hpp"

#include "Engine/Renderer/Renderer.hpp"
#include "Editor/Widgets/TitlebarWidget.hpp"

#include <Tracy.hpp>
#include <imgui.h>

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

#include <X11/Xlib.h>

namespace Hyperion {

    static uint32_t s_GLFWWindowCount = 0;

    LinuxWindow::LinuxWindow(const WindowProps& props)
            : m_WindowProps(props)
    {
        LinuxWindow::Init(props);
    }

    LinuxWindow::~LinuxWindow()
    {
        LinuxWindow::Shutdown();
    }

    void LinuxWindow::Init(const WindowProps& props)
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

        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

        int monitorX, monitorY;
        glfwGetMonitorPos(primaryMonitor, &monitorX, &monitorY);

        // Hide system titlebar
        glfwSetWindowAttrib(m_Window, GLFW_DECORATED, GLFW_FALSE);

        // Center window
        glfwSetWindowPos(m_Window,
                         monitorX + (videoMode->width - m_Data.Width) / 2,
                         monitorY + (videoMode->height - m_Data.Height) / 2);

        glfwSetWindowUserPointer(m_Window, this);
        SetVSync(true);

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                double xpos, ypos;
                glfwGetCursorPos(window, &xpos, &ypos);
                glfwSetWindowUserPointer(window, new double[2]{ xpos, ypos });
            } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
                double* pos = static_cast<double*>(glfwGetWindowUserPointer(window));
                delete[] pos;
            }
        });
        glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos){
            double* pos = static_cast<double*>(glfwGetWindowUserPointer(window));
            if (pos != nullptr) {
                glfwSetWindowPos(window, xpos - pos[0], ypos - pos[1]);
            }
        });

        // Set GLFW callbacks
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = static_cast<LinuxWindow*>(glfwGetWindowUserPointer(window))->m_Data;
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            const WindowData& data = static_cast<LinuxWindow*>(glfwGetWindowUserPointer(window))->m_Data;
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            const WindowData& data = static_cast<LinuxWindow*>(glfwGetWindowUserPointer(window))->m_Data;

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
            const WindowData& data = static_cast<LinuxWindow*>(glfwGetWindowUserPointer(window))->m_Data;

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            LinuxWindow& windowHandle = *static_cast<LinuxWindow*>(glfwGetWindowUserPointer(window));

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
            const WindowData& data = static_cast<LinuxWindow*>(glfwGetWindowUserPointer(window))->m_Data;

            MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            LinuxWindow& windowHandle = *static_cast<LinuxWindow*>(glfwGetWindowUserPointer(window));

            MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
            windowHandle.m_Data.EventCallback(event);
        });
    }

    void LinuxWindow::Shutdown()
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

    void LinuxWindow::OnUpdate()
    {
        ZoneScoped;

        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void LinuxWindow::SetVSync(bool enabled)
    {
        ZoneScoped;

        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool LinuxWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

    void LinuxWindow::StartDrag() const
    {
        if (!m_Window)
            return;

        // TODO: Add window dragging to X11
    }

    void LinuxWindow::StartResize(WindowBorder border) const
    {
        if (!m_Window)
            return;

        // TODO: Add resize to X11
    }

    bool LinuxWindow::IsMaximized() const
    {
        return static_cast<bool>(glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED));
    }

    bool LinuxWindow::IsMinimized() const
    {
        return static_cast<bool>(glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED));
    }

    void LinuxWindow::Maximize(bool restore) const
    {
        if (!m_Window)
            return;

        if (restore)
            glfwRestoreWindow(m_Window);
        else
            glfwMaximizeWindow(m_Window);
    }

    void LinuxWindow::Minimize() const
    {
        if (!m_Window)
            return;

        glfwIconifyWindow(m_Window);
    }

}
