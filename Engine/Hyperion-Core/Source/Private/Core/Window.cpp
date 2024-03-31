#include "hrpch.hpp"

#include "Engine/Core/Window.hpp"

#ifdef HR_PLATFORM_WINDOWS
    #include "Engine/RHI/Windows/WindowsWindow.hpp"
#endif

#ifdef HR_PLATFORM_LINUX
    #include "Engine/RHI/Linux/LinuxWindow.hpp"
#endif

namespace Hyperion {

    Window::Window()
    {
    }

    Scope<Window> Window::Create(const WindowProps& props)
    {
    #ifdef HR_PLATFORM_WINDOWS
        return CreateScope<WindowsWindow>(props);
    #elif defined(HR_PLATFORM_LINUX)
        return CreateScope<LinuxWindow>(props);
    #else
        HR_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
    #endif
    }

}