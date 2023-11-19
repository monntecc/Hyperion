#include "pch.hpp"
#include "Runtime/Core/Input.hpp"

#ifdef HR_PLATFORM_WINDOWS
    #include "Runtime/RHI/Windows/WindowsInput.hpp"
#endif

namespace Hyperion {

    Scope<Input> Input::s_Instance = Create();

    Scope<Input> Input::Create()
    {
    #ifdef HR_PLATFORM_WINDOWS
        return CreateScope<WindowsInput>();
    #else
        HR_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
    #endif
    }
    
}
