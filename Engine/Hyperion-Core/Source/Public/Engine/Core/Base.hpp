#pragma once

#include <memory>

#include "Engine/Core/PlatformDetection.hpp"

#ifndef HR_DEBUG
	#define HR_ENABLE_ASSERTS 1
#endif // HR_DEBUG

#define HR_EXPAND_MACRO(x) x
#define HR_STRINGIFY_MACRO(x) #x

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

#include "Engine/Core/Log.hpp"
#include "Engine/Core/Assert.hpp"