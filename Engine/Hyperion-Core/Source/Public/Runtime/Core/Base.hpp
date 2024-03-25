#pragma once

#include <memory>

#include "Runtime/Core/PlatformDetection.hpp"

#ifndef HR_DEBUG
	#define HR_ENABLE_ASSERTS 1
#endif // HR_DEBUG

#ifdef HR_ENABLE_ASSERTS
	#define HR_ASSERT(x, ...) { if(!(x)) { HR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HR_CORE_ASSERT(x, ...) { if(!(x)) { HR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HR_ASSERT(x, ...)
	#define HR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HR_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Hyperion {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	
}