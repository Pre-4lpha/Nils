#pragma once

#include <Gosu/Platform.hpp>

namespace Gosu
{
    //! List of button ids that can be used with Gosu::Input.
    //! This enumeration contains ids for keyboard keys (KB_*),
    //! mouse buttons and mouse wheel (MS_*) and gamepad buttons (GP_*).
    enum ButtonName
    {
        KB_RANGE_BEGIN,
        KB_ESCAPE          = 41,
        KB_F1              = 58,
        KB_F2              = 59,
        KB_F3              = 60,
        KB_F4              = 61,
        KB_F5              = 62,
        KB_F6              = 63,
        KB_F7              = 64,
        KB_F8              = 65,
        KB_F9              = 66,
        KB_F10             = 67,
        KB_F11             = 68,
        KB_F12             = 69,
        KB_0               = 39,
        KB_1               = 30,
        KB_2               = 31,
        KB_3               = 32,
        KB_4               = 33,
        KB_5               = 34,
        KB_6               = 35,
        KB_7               = 36,
        KB_8               = 37,
        KB_9               = 38,
        KB_TAB             = 43,
        KB_RETURN          = 40,
        KB_SPACE           = 44,
        KB_LEFT_SHIFT      = 225,
        KB_RIGHT_SHIFT     = 229,
        KB_LEFT_CONTROL    = 224,
        KB_RIGHT_CONTROL   = 228,
        KB_LEFT_ALT        = 226,
        KB_RIGHT_ALT       = 230,
        KB_LEFT_META       = 227,
        KB_RIGHT_META      = 231,
        KB_BACKSPACE       = 42,
        KB_LEFT            = 80,
        KB_RIGHT           = 79,
        KB_UP              = 82,
        KB_DOWN            = 81,
        KB_HOME            = 74,
        KB_END             = 77,
        KB_INSERT          = 73,
        KB_DELETE          = 76,
        KB_PAGE_UP         = 75,
        KB_PAGE_DOWN       = 78,
        KB_ENTER           = 88,
        KB_BACKTICK        = 53,
        KB_MINUS           = 45,
        KB_EQUALS          = 46,
        KB_LEFT_BRACKET    = 47,
        KB_RIGHT_BRACKET   = 48,
        KB_BACKSLASH       = 49,
        KB_SEMICOLON       = 51,
        KB_APOSTROPHE      = 52,
        KB_COMMA           = 54,
        KB_PERIOD          = 55,
        KB_SLASH           = 49,
        KB_A               = 4,
        KB_B               = 5,
        KB_C               = 6,
        KB_D               = 7,
        KB_E               = 8,
        KB_F               = 9,
        KB_G               = 10,
        KB_H               = 11,
        KB_I               = 12,
        KB_J               = 13,
        KB_K               = 14,
        KB_L               = 15,
        KB_M               = 16,
        KB_N               = 17,
        KB_O               = 18,
        KB_P               = 19,
        KB_Q               = 20,
        KB_R               = 21,
        KB_S               = 22,
        KB_T               = 23,
        KB_U               = 24,
        KB_V               = 25,
        KB_W               = 26,
        KB_X               = 27,
        KB_Y               = 28,
        KB_Z               = 29,
        KB_ISO             = 100, // ` on US/UK macOS, < ON EU macOS, \ in US/UK Windows
        KB_NUMPAD_0        = 98,
        KB_NUMPAD_1        = 89,
        KB_NUMPAD_2        = 90,
        KB_NUMPAD_3        = 91,
        KB_NUMPAD_4        = 92,
        KB_NUMPAD_5        = 93,
        KB_NUMPAD_6        = 94,
        KB_NUMPAD_7        = 95,
        KB_NUMPAD_8        = 96,
        KB_NUMPAD_9        = 97,
        KB_NUMPAD_PLUS     = 87,
        KB_NUMPAD_MINUS    = 86,
        KB_NUMPAD_MULTIPLY = 85,
        KB_NUMPAD_DIVIDE   = 84,
        KB_RANGE_END       = 0xff,

        MS_RANGE_BEGIN,
        MS_LEFT = MS_RANGE_BEGIN,
        MS_MIDDLE,
        MS_RIGHT,
        MS_WHEEL_UP,
        MS_WHEEL_DOWN,
        MS_OTHER_0,
        MS_OTHER_1,
        MS_OTHER_2,
        MS_OTHER_3,
        MS_OTHER_4,
        MS_OTHER_5,
        MS_OTHER_6,
        MS_OTHER_7,
        MS_RANGE_END = 0x110,
        
        GP_RANGE_BEGIN,
        GP_LEFT = GP_RANGE_BEGIN,
        GP_RIGHT,
        GP_UP,
        GP_DOWN,
        GP_BUTTON_0,
        GP_BUTTON_1,
        GP_BUTTON_2,
        GP_BUTTON_3,
        GP_BUTTON_4,
        GP_BUTTON_5,
        GP_BUTTON_6,
        GP_BUTTON_7,
        GP_BUTTON_8,
        GP_BUTTON_9,
        GP_BUTTON_10,
        GP_BUTTON_11,
        GP_BUTTON_12,
        GP_BUTTON_13,
        GP_BUTTON_14,
        GP_BUTTON_15,

        GP_0_LEFT,
        GP_0_RIGHT,
        GP_0_UP,
        GP_0_DOWN,
        GP_0_BUTTON_0,
        GP_0_BUTTON_1,
        GP_0_BUTTON_2,
        GP_0_BUTTON_3,
        GP_0_BUTTON_4,
        GP_0_BUTTON_5,
        GP_0_BUTTON_6,
        GP_0_BUTTON_7,
        GP_0_BUTTON_8,
        GP_0_BUTTON_9,
        GP_0_BUTTON_10,
        GP_0_BUTTON_11,
        GP_0_BUTTON_12,
        GP_0_BUTTON_13,
        GP_0_BUTTON_14,
        GP_0_BUTTON_15,
        
        GP_1_LEFT,
        GP_1_RIGHT,
        GP_1_UP,
        GP_1_DOWN,
        GP_1_BUTTON_0,
        GP_1_BUTTON_1,
        GP_1_BUTTON_2,
        GP_1_BUTTON_3,
        GP_1_BUTTON_4,
        GP_1_BUTTON_5,
        GP_1_BUTTON_6,
        GP_1_BUTTON_7,
        GP_1_BUTTON_8,
        GP_1_BUTTON_9,
        GP_1_BUTTON_10,
        GP_1_BUTTON_11,
        GP_1_BUTTON_12,
        GP_1_BUTTON_13,
        GP_1_BUTTON_14,
        GP_1_BUTTON_15,
        
        GP_2_LEFT,
        GP_2_RIGHT,
        GP_2_UP,
        GP_2_DOWN,
        GP_2_BUTTON_0,
        GP_2_BUTTON_1,
        GP_2_BUTTON_2,
        GP_2_BUTTON_3,
        GP_2_BUTTON_4,
        GP_2_BUTTON_5,
        GP_2_BUTTON_6,
        GP_2_BUTTON_7,
        GP_2_BUTTON_8,
        GP_2_BUTTON_9,
        GP_2_BUTTON_10,
        GP_2_BUTTON_11,
        GP_2_BUTTON_12,
        GP_2_BUTTON_13,
        GP_2_BUTTON_14,
        GP_2_BUTTON_15,
        
        GP_3_LEFT,
        GP_3_RIGHT,
        GP_3_UP,
        GP_3_DOWN,
        GP_3_BUTTON_0,
        GP_3_BUTTON_1,
        GP_3_BUTTON_2,
        GP_3_BUTTON_3,
        GP_3_BUTTON_4,
        GP_3_BUTTON_5,
        GP_3_BUTTON_6,
        GP_3_BUTTON_7,
        GP_3_BUTTON_8,
        GP_3_BUTTON_9,
        GP_3_BUTTON_10,
        GP_3_BUTTON_11,
        GP_3_BUTTON_12,
        GP_3_BUTTON_13,
        GP_3_BUTTON_14,
        GP_3_BUTTON_15,
        
        GP_RANGE_END       = GP_3_BUTTON_15,
        
        NUM_BUTTONS        = GP_RANGE_END + 1,
        NUM_GAMEPADS       = 4,
        NO_BUTTON          = 0xffffffff,
        
        KB_NUM             = KB_RANGE_END - KB_RANGE_BEGIN + 1,
        MS_NUM             = MS_RANGE_END - MS_RANGE_BEGIN + 1,
        GP_NUM             = GP_RANGE_END - GP_RANGE_BEGIN + 1,
        GP_NUM_PER_GAMEPAD = GP_NUM / (NUM_GAMEPADS + 1)
    };
}
