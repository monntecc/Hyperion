#pragma once

namespace Hyperion {

    typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
    
}

#define HR_KEY_SPACE           ::Hyperion::Key::Space
#define HR_KEY_APOSTROPHE      ::Hyperion::Key::Apostrophe    /* ' */
#define HR_KEY_COMMA           ::Hyperion::Key::Comma         /* , */
#define HR_KEY_MINUS           ::Hyperion::Key::Minus         /* - */
#define HR_KEY_PERIOD          ::Hyperion::Key::Period        /* . */
#define HR_KEY_SLASH           ::Hyperion::Key::Slash         /* / */
#define HR_KEY_0               ::Hyperion::Key::D0
#define HR_KEY_1               ::Hyperion::Key::D1
#define HR_KEY_2               ::Hyperion::Key::D2
#define HR_KEY_3               ::Hyperion::Key::D3
#define HR_KEY_4               ::Hyperion::Key::D4
#define HR_KEY_5               ::Hyperion::Key::D5
#define HR_KEY_6               ::Hyperion::Key::D6
#define HR_KEY_7               ::Hyperion::Key::D7
#define HR_KEY_8               ::Hyperion::Key::D8
#define HR_KEY_9               ::Hyperion::Key::D9
#define HR_KEY_SEMICOLON       ::Hyperion::Key::Semicolon     /* ; */
#define HR_KEY_EQUAL           ::Hyperion::Key::Equal         /* = */
#define HR_KEY_A               ::Hyperion::Key::A
#define HR_KEY_B               ::Hyperion::Key::B
#define HR_KEY_C               ::Hyperion::Key::C
#define HR_KEY_D               ::Hyperion::Key::D
#define HR_KEY_E               ::Hyperion::Key::E
#define HR_KEY_F               ::Hyperion::Key::F
#define HR_KEY_G               ::Hyperion::Key::G
#define HR_KEY_H               ::Hyperion::Key::H
#define HR_KEY_I               ::Hyperion::Key::I
#define HR_KEY_J               ::Hyperion::Key::J
#define HR_KEY_K               ::Hyperion::Key::K
#define HR_KEY_L               ::Hyperion::Key::L
#define HR_KEY_M               ::Hyperion::Key::M
#define HR_KEY_N               ::Hyperion::Key::N
#define HR_KEY_O               ::Hyperion::Key::O
#define HR_KEY_P               ::Hyperion::Key::P
#define HR_KEY_Q               ::Hyperion::Key::Q
#define HR_KEY_R               ::Hyperion::Key::R
#define HR_KEY_S               ::Hyperion::Key::S
#define HR_KEY_T               ::Hyperion::Key::T
#define HR_KEY_U               ::Hyperion::Key::U
#define HR_KEY_V               ::Hyperion::Key::V
#define HR_KEY_W               ::Hyperion::Key::W
#define HR_KEY_X               ::Hyperion::Key::X
#define HR_KEY_Y               ::Hyperion::Key::Y
#define HR_KEY_Z               ::Hyperion::Key::Z
#define HR_KEY_LEFT_BRACKET    ::Hyperion::Key::LeftBracket   /* [ */
#define HR_KEY_BACKSLASH       ::Hyperion::Key::Backslash     /* \ */
#define HR_KEY_RIGHT_BRACKET   ::Hyperion::Key::RightBracket  /* ] */
#define HR_KEY_GRAVE_ACCENT    ::Hyperion::Key::GraveAccent   /* ` */
#define HR_KEY_WORLD_1         ::Hyperion::Key::World1        /* non-US #1 */
#define HR_KEY_WORLD_2         ::Hyperion::Key::World2        /* non-US #2 */

#define HR_KEY_ESCAPE          ::Hyperion::Key::Escape
#define HR_KEY_ENTER           ::Hyperion::Key::Enter
#define HR_KEY_TAB             ::Hyperion::Key::Tab
#define HR_KEY_BACKSPACE       ::Hyperion::Key::Backspace
#define HR_KEY_INSERT          ::Hyperion::Key::Insert
#define HR_KEY_DELETE          ::Hyperion::Key::Delete
#define HR_KEY_RIGHT           ::Hyperion::Key::Right
#define HR_KEY_LEFT            ::Hyperion::Key::Left
#define HR_KEY_DOWN            ::Hyperion::Key::Down
#define HR_KEY_UP              ::Hyperion::Key::Up
#define HR_KEY_PAGE_UP         ::Hyperion::Key::PageUp
#define HR_KEY_PAGE_DOWN       ::Hyperion::Key::PageDown
#define HR_KEY_HOME            ::Hyperion::Key::Home
#define HR_KEY_END             ::Hyperion::Key::End
#define HR_KEY_CAPS_LOCK       ::Hyperion::Key::CapsLock
#define HR_KEY_SCROLL_LOCK     ::Hyperion::Key::ScrollLock
#define HR_KEY_NUM_LOCK        ::Hyperion::Key::NumLock
#define HR_KEY_PRINT_SCREEN    ::Hyperion::Key::PrintScreen
#define HR_KEY_PAUSE           ::Hyperion::Key::Pause
#define HR_KEY_F1              ::Hyperion::Key::F1
#define HR_KEY_F2              ::Hyperion::Key::F2
#define HR_KEY_F3              ::Hyperion::Key::F3
#define HR_KEY_F4              ::Hyperion::Key::F4
#define HR_KEY_F5              ::Hyperion::Key::F5
#define HR_KEY_F6              ::Hyperion::Key::F6
#define HR_KEY_F7              ::Hyperion::Key::F7
#define HR_KEY_F8              ::Hyperion::Key::F8
#define HR_KEY_F9              ::Hyperion::Key::F9
#define HR_KEY_F10             ::Hyperion::Key::F10
#define HR_KEY_F11             ::Hyperion::Key::F11
#define HR_KEY_F12             ::Hyperion::Key::F12
#define HR_KEY_F13             ::Hyperion::Key::F13
#define HR_KEY_F14             ::Hyperion::Key::F14
#define HR_KEY_F15             ::Hyperion::Key::F15
#define HR_KEY_F16             ::Hyperion::Key::F16
#define HR_KEY_F17             ::Hyperion::Key::F17
#define HR_KEY_F18             ::Hyperion::Key::F18
#define HR_KEY_F19             ::Hyperion::Key::F19
#define HR_KEY_F20             ::Hyperion::Key::F20
#define HR_KEY_F21             ::Hyperion::Key::F21
#define HR_KEY_F22             ::Hyperion::Key::F22
#define HR_KEY_F23             ::Hyperion::Key::F23
#define HR_KEY_F24             ::Hyperion::Key::F24
#define HR_KEY_F25             ::Hyperion::Key::F25

/* Keypad */
#define HR_KEY_KP_0            ::Hyperion::Key::KP0
#define HR_KEY_KP_1            ::Hyperion::Key::KP1
#define HR_KEY_KP_2            ::Hyperion::Key::KP2
#define HR_KEY_KP_3            ::Hyperion::Key::KP3
#define HR_KEY_KP_4            ::Hyperion::Key::KP4
#define HR_KEY_KP_5            ::Hyperion::Key::KP5
#define HR_KEY_KP_6            ::Hyperion::Key::KP6
#define HR_KEY_KP_7            ::Hyperion::Key::KP7
#define HR_KEY_KP_8            ::Hyperion::Key::KP8
#define HR_KEY_KP_9            ::Hyperion::Key::KP9
#define HR_KEY_KP_DECIMAL      ::Hyperion::Key::KPDecimal
#define HR_KEY_KP_DIVIDE       ::Hyperion::Key::KPDivide
#define HR_KEY_KP_MULTIPLY     ::Hyperion::Key::KPMultiply
#define HR_KEY_KP_SUBTRACT     ::Hyperion::Key::KPSubtract
#define HR_KEY_KP_ADD          ::Hyperion::Key::KPAdd
#define HR_KEY_KP_ENTER        ::Hyperion::Key::KPEnter
#define HR_KEY_KP_EQUAL        ::Hyperion::Key::KPEqual

#define HR_KEY_LEFT_SHIFT      ::Hyperion::Key::LeftShift
#define HR_KEY_LEFT_CONTROL    ::Hyperion::Key::LeftControl
#define HR_KEY_LEFT_ALT        ::Hyperion::Key::LeftAlt
#define HR_KEY_LEFT_SUPER      ::Hyperion::Key::LeftSuper
#define HR_KEY_RIGHT_SHIFT     ::Hyperion::Key::RightShift
#define HR_KEY_RIGHT_CONTROL   ::Hyperion::Key::RightControl
#define HR_KEY_RIGHT_ALT       ::Hyperion::Key::RightAlt
#define HR_KEY_RIGHT_SUPER     ::Hyperion::Key::RightSuper
#define HR_KEY_MENU            ::Hyperion::Key::Menu
