#pragma once

#include <array>

#include "GamepadInput.h"

namespace gamepad {
  struct Gamepad {
    uintptr_t somePtr;
    GamepadInput buttons;
    GamepadInput buttonsJustPressed;
    GamepadInput buttonsJustReleased;
    GamepadInput simultaneousButtons_NotFullyUnderstood_DoNotUse;
    float leftStickX;
    float leftStickY;
    float rightStickX;
    float rightStickY;
    float rightStickMagnitude;
    float leftStickMagnitude;
    float leftTriggerMagnitude;
    float rightTriggerMagnitude;
    std::array<float, 32> pressDuration;
  };
}  // namespace gamepad
