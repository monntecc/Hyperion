#pragma once

#include "Runtime/Events/Event.hpp"

#include "Runtime/Core/KeyCodes.hpp"

namespace Hyperion {

	class HYPERION_API KeyEvent : public Event
	{
	public:
		virtual ~KeyEvent() = default;
		KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(const KeyCode  keycode)
			: m_KeyCode(keycode) {}
	
		KeyCode m_KeyCode;
	};

	class HYPERION_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		uint16_t GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		uint16_t m_RepeatCount;
	};

	class HYPERION_API KeyReleasedEvent : public KeyEvent
	{
		public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class HYPERION_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};


}
