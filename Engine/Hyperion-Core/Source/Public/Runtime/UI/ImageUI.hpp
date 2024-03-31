#pragma once

#include "Runtime/Core/Base.hpp"

namespace Hyperion::UI {

	enum class ImageFormat
	{
		None = 0,
		RGBA,
		RGBA32F
	};

	HYPERION_API void* DecodeImage(const void* buffer, uint64_t length, uint32_t& outWidth, uint32_t& outHeight);
}