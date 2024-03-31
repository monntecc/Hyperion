#pragma once

#include "Runtime/Core/Base.hpp"

#include "Runtime/Renderer/Texture.hpp"

#include <imgui.h>
#include <imgui_internal.h>

namespace Hyperion::UI {

	enum class HYPERION_API ImageFormat
	{
		None = 0,
		RGBA,
		RGBA32F
	};

	void HYPERION_API ShiftCursorX(float distance);
	void HYPERION_API ShiftCursorY(float distance);
	void HYPERION_API ShiftCursor(float x, float y);

	ImRect HYPERION_API GetItemRect();
	ImRect HYPERION_API RectExpanded(const ImRect& rect, float x, float y);
	ImRect HYPERION_API RectOffset(const ImRect& rect, float x, float y);
	ImRect HYPERION_API RectOffset(const ImRect& rect, ImVec2 xy);

	void HYPERION_API DrawButtonImage(const Ref<Texture2D>& imageNormal, const Ref<Texture2D>& imageHovered, const Ref<Texture2D>& imagePressed,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImVec2 rectMin, ImVec2 rectMax);

	void HYPERION_API DrawButtonImage(const Ref<Texture2D>& imageNormal, const Ref<Texture2D>& imageHovered, const Ref<Texture2D>& imagePressed,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImRect rectangle);

	void HYPERION_API DrawButtonImage(const Ref<Texture2D>& image,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImVec2 rectMin, ImVec2 rectMax);

	void HYPERION_API DrawButtonImage(const Ref<Texture2D>& image,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImRect rectangle);

	void HYPERION_API DrawButtonImage(const Ref<Texture2D>& imageNormal, const Ref<Texture2D>& imageHovered, const Ref<Texture2D>& imagePressed,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed);

	void HYPERION_API DrawButtonImage(const Ref<Texture2D>& image,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed);
}