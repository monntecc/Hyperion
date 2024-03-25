#pragma once

#include "Runtime/Core/Base.hpp"

#include "Runtime/Core/KeyCodes.hpp"
#include "Runtime/Core/MouseCodes.hpp"

#include <glm/glm.hpp>

namespace Hyperion {

	class HYPERION_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();

		static float GetMouseX();
		static float GetMouseY();
	};

}