#include "hrpch.hpp"

#include "Runtime/UI/ImageUI.hpp"

#include <stb_image.h>

namespace Hyperion::UI {

	void* DecodeImage(const void* buffer, uint64_t length, uint32_t& outWidth, uint32_t& outHeight)
	{
		int width, height, channels;
		uint8_t* data = nullptr;
		uint64_t size = 0;

		data = stbi_load_from_memory((const stbi_uc*)buffer, length, &width, &height, &channels, 4);
		size = width * height * 4;

		outWidth = width;
		outHeight = height;

		return data;
	}

}