#pragma once

#include "Runtime/Core/Base.hpp"
#include "Runtime/Events/Event.hpp"

#include <sstream>

namespace Hyperion {

	enum class HYPERION_API WindowBorder
	{
		Left = 0,
		Top = 1,
		Right = 2,
		Bottom = 3,
		TopLeft = 4,
		TopRight = 5,
		BottomLeft = 6,
		BottomRight = 7
	};

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Hyperion Engine",
			uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class HYPERION_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window();
		virtual ~Window() = default;
		Window(const Window&) = delete;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void StartDrag() const = 0;
		virtual void StartResize(WindowBorder border) const = 0;

		virtual bool IsMaximized() const = 0;
		virtual bool IsMinimized() const = 0;

		virtual void Maximize(bool restore = false) const = 0;
		virtual void Minimize() const = 0;

		// Window data
		virtual void* GetNativeWindow() const = 0;
		virtual const WindowProps& GetWindowData() const = 0;

		// Window creation
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}