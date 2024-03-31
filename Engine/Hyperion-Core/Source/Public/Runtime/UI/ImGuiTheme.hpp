#pragma once

#include <imgui.h>

#include <glm/glm.hpp>

namespace Hyperion::UI {

	namespace Colors
	{
		inline ImU32 ColorWithMultipliedValue(const ImColor& color, float multiplier)
		{
			const ImVec4& colRow = color.Value;
			float hue, sat, val;
			ImGui::ColorConvertRGBtoHSV(colRow.x, colRow.y, colRow.z, hue, sat, val);
			return ImColor::HSV(hue, sat, std::min(val * multiplier, 1.0f));
		}
	}

	void HYPERION_API SetEditorTheme();

}