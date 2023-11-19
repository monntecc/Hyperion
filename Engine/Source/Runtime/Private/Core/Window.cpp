#include "pch.hpp"

#include "Runtime/Core/Window.hpp"

#ifdef HR_PLATFORM_WINDOWS
    #include "Runtime/RHI/Windows/WindowsWindow.hpp"
#endif

namespace Hyperion {

    Scope<Window> Window::Create(const WindowProps& props)
    {
    #ifdef HR_PLATFORM_WINDOWS
        return CreateScope<WindowsWindow>(props);
    #else
        HR_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
    #endif
    }

}