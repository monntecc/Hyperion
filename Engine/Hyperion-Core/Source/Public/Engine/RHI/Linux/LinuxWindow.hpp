#pragma once

#include "Engine/Core/Base.hpp"
#include "Engine/Core/Window.hpp"
#include "Engine/Renderer/GraphicsContext.hpp"

#include <GLFW/glfw3.h>
#include <imgui_internal.h>

namespace Hyperion {

    class LinuxWindow : public Window
    {
    public:
        LinuxWindow(const WindowProps& props);
        ~LinuxWindow() override;

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        // Window attributes
        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void StartDrag() const override;
        void StartResize(WindowBorder border) const override;

        bool IsMaximized() const override;
        bool IsMinimized() const override;

        void Maximize(bool restore = false) const override;
        void Minimize() const override;

        void* GetNativeWindow() const override { return m_Window; }
        const WindowProps& GetWindowData() const override { return m_WindowProps; }
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

        GLFWwindow* m_Window;
        Scope<GraphicsContext>  m_Context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowProps m_WindowProps;
        WindowData m_Data;
    };

}
