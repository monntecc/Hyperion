#pragma once

#include <memory>

#ifdef HR_PLATFORM_WINDOWS
	#if HR_DYNAMIC_LINK
		#ifdef HR_BUILD_DLL
			#define HYPERION_API __declspec(dllexport)
		#else
			#define HYPERION_API __declspec(dllimport)
		#endif // HR_BUILD_DLL
	#else
		#define HYPERION_API
	#endif // HR_DYNAMIC_LINK

#else
	#error HyperionEngine only support Windows x64 platform!
#endif // HR_PLATFORM_WINDOWS

#ifndef HR_DEBUG
	#define HR_ENABLE_ASSERTS
#endif // HR_ENABLE_ASSERTS

#ifdef HR_ENABLE_ASSERTS
	#define HR_ASSERT(x, ...) { if(!(x)) { HR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HR_CORE_ASSERT(x, ...) { if(!(x)) { HR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HR_ASSERT(x, ...)
	#define HR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hyperion {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
	
}