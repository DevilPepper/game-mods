#pragma once

#include <cstdint>

namespace gamepad {
    typedef uint32_t GamepadInput;
    
    struct Gamepad {
        uintptr_t somePtr;
        GamepadInput buttons;
        unsigned char unknownBytes[12];
        float leftStickX;
        float leftStickY;
        float rightStickX;
        float rightStickY;
        float rightStickMagnitude;
        float leftStickMagnitude;
        float leftTriggerMagnitude;
        float rightTriggerMagnitude;
        float pressDuration[32];
    };
}
