#pragma once

#include "GamepadStruct.h"

namespace gamepad {
  static bool justPressed(const Gamepad& gamepad, GamepadInput btns) {
    return ((gamepad.buttonsJustPressed & btns) > 0);
  }

  static bool justReleased(const Gamepad& gamepad, GamepadInput btns) {
    return ((gamepad.buttonsJustReleased & btns) > 0);
  }

  static bool pressing(const Gamepad& gamepad, GamepadInput btns) {
    return ((gamepad.buttons & btns) > 0);
  }
}  // namespace gamepad
