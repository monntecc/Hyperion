#pragma once

#include "Runtime/Core/Input.hpp"

namespace Hyperion {

	class WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(KeyCode keycode) override;

		bool IsMouseButtonPressedImpl(MouseCode button) override;

		std::pair<float, float> GetMousePositionImpl() override;

		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};

}