#pragma once

#include "Engine/Core/Base.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Hyperion {
	class HYPERION_API Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define HR_CORE_TRACE(...)			::Hyperion::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HR_CORE_INFO(...)			::Hyperion::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HR_CORE_WARN(...)			::Hyperion::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HR_CORE_ERROR(...)			::Hyperion::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HR_CORE_CRITICAL(...)		::Hyperion::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HR_TRACE(...)				::Hyperion::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HR_INFO(...)				::Hyperion::Log::GetClientLogger()->info(__VA_ARGS__)
#define HR_WARN(...)				::Hyperion::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HR_ERROR(...)				::Hyperion::Log::GetClientLogger()->error(__VA_ARGS__)
#define HR_CRITICAL(...)			::Hyperion::Log::GetClientLogger()->critical(__VA_ARGS__)