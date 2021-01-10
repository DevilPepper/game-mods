#pragma once

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
    float pressDuration[32];
  };
}  // namespace gamepad
