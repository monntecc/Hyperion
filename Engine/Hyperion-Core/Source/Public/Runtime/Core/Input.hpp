#pragma once

#include "Runtime/Core/Core.hpp"

#include "Runtime/Core/KeyCodes.hpp"
#include "Runtime/Core/MouseCodes.hpp"

namespace Hyperion {

	class HYPERION_API Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
		virtual ~Input() = default;
		
		static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }

		static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;

		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		static Scope<Input> Create();
	private:
		static Scope<Input> s_Instance;
	};

}