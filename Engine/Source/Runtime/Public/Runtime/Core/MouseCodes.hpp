#pragma once

namespace Hyperion {

    typedef enum class MouseCode : uint16_t
    {
        // From glfw3.h
        Button0                = 0,
        Button1                = 1,
        Button2                = 2,
        Button3                = 3,
        Button4                = 4,
        Button5                = 5,
        Button6                = 6,
        Button7                = 7,

        ButtonLast             = Button7,
        ButtonLeft             = Button0,
        ButtonRight            = Button1,
        ButtonMiddle           = Button2
    } Mouse;

    inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
    {
        os << static_cast<int32_t>(mouseCode);
        return os;
    }
}

#define HR_MOUSE_BUTTON_0      ::Hyperion::Mouse::Button0
#define HR_MOUSE_BUTTON_1      ::Hyperion::Mouse::Button1
#define HR_MOUSE_BUTTON_2      ::Hyperion::Mouse::Button2
#define HR_MOUSE_BUTTON_3      ::Hyperion::Mouse::Button3
#define HR_MOUSE_BUTTON_4      ::Hyperion::Mouse::Button4
#define HR_MOUSE_BUTTON_5      ::Hyperion::Mouse::Button5
#define HR_MOUSE_BUTTON_6      ::Hyperion::Mouse::Button6
#define HR_MOUSE_BUTTON_7      ::Hyperion::Mouse::Button7
#define HR_MOUSE_BUTTON_LAST   ::Hyperion::Mouse::ButtonLast
#define HR_MOUSE_BUTTON_LEFT   ::Hyperion::Mouse::ButtonLeft
#define HR_MOUSE_BUTTON_RIGHT  ::Hyperion::Mouse::ButtonRight
#define HR_MOUSE_BUTTON_MIDDLE ::Hyperion::Mouse::ButtonMiddle