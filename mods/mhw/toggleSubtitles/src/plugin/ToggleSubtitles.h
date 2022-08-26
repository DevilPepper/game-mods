#pragma once

#include <Windows.h>
#include <gamepad.h>
#include <types/address.h>

#include "../model/Addresses.h"

namespace plugin {
  using gamepad::Button;
  using gamepad::Gamepad;
  using model::Addresses;
  using stuff::types::Offsets;

  class ToggleSubtitles {
   private:
    Addresses addresses;
    static const Button SubtitlesToggle = Button::Select;

    intptr_t subtitle_setting = 0x10A;
    Offsets subtitle_show{ 0x13e20, 0x332c };

    void toggleSubtitles();

   public:
    ToggleSubtitles();
    void handleInput(const Gamepad& input);
  };
}  // namespace plugin
