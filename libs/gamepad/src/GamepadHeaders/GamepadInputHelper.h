#pragma once

#include "GamepadStruct.h"

namespace gamepad {
  static bool justPressed(const Gamepad& gamepad, GamepadInput btns) {
    return ((gamepad.buttonsJustPressed & btns) == btns);
  }

  static bool justReleased(const Gamepad& gamepad, GamepadInput btns) {
    return ((gamepad.buttonsJustReleased & btns) == btns);
  }

  static bool pressing(const Gamepad& gamepad, GamepadInput btns) {
    return ((gamepad.buttons & btns) == btns);
  }
}  // namespace gamepad
