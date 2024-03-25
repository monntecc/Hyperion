#pragma once

#include "Runtime/Core/Base.hpp"
#include "Runtime/Core/Log.hpp"

#include <filesystem>

#ifdef HR_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define HR_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { HR##type##ERROR(msg, __VA_ARGS__); HR_DEBUGBREAK(); } }
#define HR_INTERNAL_ASSERT_WITH_MSG(type, check, ...) HR_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define HR_INTERNAL_ASSERT_NO_MSG(type, check) HR_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", HR_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define HR_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define HR_INTERNAL_ASSERT_GET_MACRO(...) HR_EXPAND_MACRO( HR_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, HR_INTERNAL_ASSERT_WITH_MSG, HR_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define HR_ASSERT(...) HR_EXPAND_MACRO( HR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define HR_CORE_ASSERT(...) HR_EXPAND_MACRO( HR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define HR_ASSERT(...)
#define HR_CORE_ASSERT(...)
#endif